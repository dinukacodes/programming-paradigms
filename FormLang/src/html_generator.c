#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formLang.h"

void generate_html_header(FILE* output) {
    fprintf(output, "<!DOCTYPE html>\n<html>\n<head>\n");
    fprintf(output, "<style>\n");
    fprintf(output, "body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }\n");
    fprintf(output, "form { background: #f5f5f5; padding: 20px; border-radius: 5px; }\n");
    fprintf(output, "section { margin-bottom: 20px; padding: 15px; background: white; border-radius: 5px; }\n");
    fprintf(output, "h2 { color: #333; margin-top: 0; }\n");
    fprintf(output, "label { display: block; margin-bottom: 5px; }\n");
    fprintf(output, "input, textarea, select { width: 100%%; padding: 8px; margin-bottom: 10px; border: 1px solid #ddd; border-radius: 4px; }\n");
    fprintf(output, "input[type=submit] { background: #4CAF50; color: white; border: none; padding: 10px 20px; cursor: pointer; width: auto; }\n");
    fprintf(output, "input[type=submit]:hover { background: #45a049; }\n");
    fprintf(output, ".radio-group { margin-bottom: 10px; }\n");
    fprintf(output, ".radio-group label { display: inline; margin-left: 5px; }\n");
    fprintf(output, "</style>\n</head>\n<body>\n");
}

void generate_html_footer(FILE* output) {
    fprintf(output, "</body>\n</html>\n");
}

char* escape_html_attr(const char* input) {
    if (!input) return strdup("");
    
    char* output = malloc(strlen(input) * 2 + 1);
    int j = 0;
    
    for (int i = 0; input[i] != '\0'; i++) {
        switch (input[i]) {
            case '&': strcpy(output + j, "&amp;"); j += 5; break;
            case '"': strcpy(output + j, "&quot;"); j += 6; break;
            case '<': strcpy(output + j, "&lt;"); j += 4; break;
            case '>': strcpy(output + j, "&gt;"); j += 4; break;
            default: output[j++] = input[i];
        }
    }
    output[j] = '\0';
    return output;
}

void generate_section_html(FILE* output, Section* section) {
    fprintf(stderr, "Starting section generation\n");
    if (!section || !output) {
        fprintf(stderr, "Null section or output\n");
        return;
    }

    // Skip empty sections
    if (section->field_count == 0) {
        return;
    }

    fprintf(output, "<section>\n");
    fprintf(output, "<h2>%s</h2>\n", section->name);

    fprintf(stderr, "Processing %d fields\n", section->field_count);
    for (int i = 0; i < section->field_count; i++) {
        fprintf(stderr, "Generating field %d\n", i);
        Field* field = &section->fields[i];
        
        // Generate label
        char* escaped_name = escape_html_attr(field->name);
        fprintf(output, "<label for=\"%s\">%s%s</label>\n", 
               escaped_name, escaped_name, field->attributes.required ? " *" : "");
        free(escaped_name);

        const char* type = "text";
        switch (field->type) {
            case FIELD_TEXT: type = "text"; break;
            case FIELD_EMAIL: type = "email"; break;
            case FIELD_PASSWORD: type = "password"; break;
            case FIELD_NUMBER: type = "number"; break;
            case FIELD_TEXTAREA: type = "textarea"; break;
            case FIELD_DATE: type = "date"; break;
            case FIELD_CHECKBOX: type = "checkbox"; break;
            case FIELD_DROPDOWN: type = "select"; break;
            case FIELD_RADIO: type = "radio"; break;
            case FIELD_FILE: type = "file"; break;
        }

        if (field->type == FIELD_TEXTAREA) {
            fprintf(output, "<textarea id=\"%s\" name=\"%s\"", field->name, field->name);
            if (field->attributes.rows > 0) fprintf(output, " rows=\"%d\"", field->attributes.rows);
            if (field->attributes.cols > 0) fprintf(output, " cols=\"%d\"", field->attributes.cols);
            if (field->attributes.required) fprintf(output, " required");
            fprintf(output, "></textarea>\n");
        } else if (field->type == FIELD_DROPDOWN) {
            fprintf(output, "<select id=\"%s\" name=\"%s\"", field->name, field->name);
            if (field->attributes.required) fprintf(output, " required");
            fprintf(output, ">\n");
            if (!field->attributes.required) {
                fprintf(output, "  <option value=\"\">Select an option</option>\n");
            }
            fprintf(output, "  <option value=\"option1\">Option 1</option>\n");
            fprintf(output, "  <option value=\"option2\">Option 2</option>\n");
            fprintf(output, "</select>\n");
        } else if (field->type == FIELD_RADIO) {
            fprintf(output, "<div class=\"radio-group\">\n");
            fprintf(output, "  <input type=\"radio\" id=\"%s_1\" name=\"%s\" value=\"option1\"", field->name, field->name);
            if (field->attributes.required) fprintf(output, " required");
            fprintf(output, ">\n");
            fprintf(output, "  <span>Option 1</span><br>\n");
            fprintf(output, "  <input type=\"radio\" id=\"%s_2\" name=\"%s\" value=\"option2\"", field->name, field->name);
            if (field->attributes.required) fprintf(output, " required");
            fprintf(output, ">\n");
            fprintf(output, "  <span>Option 2</span>\n");
            fprintf(output, "</div>\n");
        } else {
            fprintf(output, "<input type=\"%s\" id=\"%s\" name=\"%s\"", type, field->name, field->name);
            
            // Handle required attribute
            if (field->attributes.required) {
                fprintf(output, " required");
            }
            
            // Handle length constraints
            if (field->attributes.min_length > 0) {
                fprintf(output, " minlength=\"%d\"", field->attributes.min_length);
            }
            if (field->attributes.max_length > 0) {
                fprintf(output, " maxlength=\"%d\"", field->attributes.max_length);
            }
            
            // Handle number constraints
            if (field->type == FIELD_NUMBER) {
                if (field->attributes.min_value != 0) {
                    fprintf(output, " min=\"%d\"", field->attributes.min_value);
                }
                if (field->attributes.max_value != 0) {
                    fprintf(output, " max=\"%d\"", field->attributes.max_value);
                }
            }
            
            // Handle pattern
            if (field->attributes.pattern && strlen(field->attributes.pattern) > 0) {
                char* escaped_pattern = escape_html_attr(field->attributes.pattern);
                fprintf(output, " pattern=\"%s\"", escaped_pattern);
                free(escaped_pattern);
            }
            
            // Handle default value
            if (field->attributes.default_value) {
                char* escaped_value = escape_html_attr(field->attributes.default_value);
                fprintf(output, " value=\"%s\"", escaped_value);
                free(escaped_value);
            }
            
            // Handle file type
            if (field->type == FIELD_FILE) {
                fprintf(output, " accept=\"*/*\"");
            }
            
            // Handle checkbox
            if (field->type == FIELD_CHECKBOX && field->attributes.default_value) {
                fprintf(output, " checked");
            }
            
            fprintf(output, ">\n");
        }
        fprintf(stderr, "Field %d generated successfully\n", i);
    }

    fprintf(output, "</section>\n");
    fprintf(stderr, "Section generation complete\n");
}

void generate_html(FILE* output) {
    fprintf(stderr, "Starting HTML generation\n");
    if (!current_form || !output) {
        fprintf(stderr, "Null form or output\n");
        return;
    }

    fprintf(stderr, "Generating header\n");
    generate_html_header(output);
    fprintf(output, "<form>\n");

    fprintf(stderr, "Processing %d sections\n", current_form->section_count);
    for (int i = 0; i < current_form->section_count; i++) {
        fprintf(stderr, "Generating section %d\n", i);
        generate_section_html(output, current_form->sections[i]);
    }

    fprintf(output, "<input type=\"submit\" value=\"Submit\">\n");
    fprintf(output, "</form>\n");
    generate_html_footer(output);
    fprintf(stderr, "HTML generation complete\n");
}
