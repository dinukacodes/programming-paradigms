#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formLang.h"

void generate_html_header(FILE* output) {
    fprintf(output, "<!DOCTYPE html>\n");
    fprintf(output, "<html>\n<head>\n");
    fprintf(output, "<title>%s</title>\n", current_form->name);
    fprintf(output, "<style>\n");
    fprintf(output, "body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }\n");
    fprintf(output, "form { background: #f9f9f9; padding: 20px; border-radius: 5px; }\n");
    fprintf(output, "fieldset { border: 1px solid #ddd; padding: 15px; margin-bottom: 20px; }\n");
    fprintf(output, "legend { font-weight: bold; padding: 0 10px; }\n");
    fprintf(output, "label { display: block; margin: 10px 0 5px; }\n");
    fprintf(output, "input { width: 100%%; padding: 8px; margin-bottom: 10px; border: 1px solid #ddd; border-radius: 4px; }\n");
    fprintf(output, "input[type=submit] { background: #4CAF50; color: white; border: none; padding: 10px 20px; cursor: pointer; }\n");
    fprintf(output, "input[type=submit]:hover { background: #45a049; }\n");
    fprintf(output, "</style>\n");
    fprintf(output, "</head>\n<body>\n");
    fprintf(output, "<h1>%s</h1>\n", current_form->name);
    fprintf(output, "<form>\n");
}

void generate_html_footer(FILE* output) {
    fprintf(output, "<input type=\"submit\" value=\"Submit\">\n");
    fprintf(output, "</form>\n");
    fprintf(output, "</body>\n</html>\n");
}

void generate_section_html(FILE* output, Section* section) {
    fprintf(output, "<fieldset>\n");
    fprintf(output, "<legend>%s</legend>\n", section->name);
    
    for (int i = 0; i < section->field_count; i++) {
        Field* field = &section->fields[i];
        fprintf(output, "<label for=\"%s\">%s%s</label>\n", 
                field->name, field->name, field->required ? " *" : "");
        
        const char* type;
        switch (field->type) {
            case FIELD_TEXT: type = "text"; break;
            case FIELD_EMAIL: type = "email"; break;
            case FIELD_PASSWORD: type = "password"; break;
            case FIELD_NUMBER: type = "number"; break;
            default: type = "text"; break;
        }
        
        fprintf(output, "<input type=\"%s\" id=\"%s\" name=\"%s\"%s>\n",
                type, field->name, field->name,
                field->required ? " required" : "");
    }
    
    fprintf(output, "</fieldset>\n");
}

void generate_html(FILE* output) {
    if (!current_form) {
        fprintf(stderr, "Error: No form to generate HTML for\n");
        return;
    }

    generate_html_header(output);
    
    for (int i = 0; i < current_form->section_count; i++) {
        generate_section_html(output, current_form->sections[i]);
    }
    
    generate_html_footer(output);
}
