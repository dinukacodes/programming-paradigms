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
    fprintf(output, "</style>\n</head>\n<body>\n");
}

void generate_html_footer(FILE* output) {
    fprintf(output, "</body>\n</html>\n");
}

void generate_section_html(FILE* output, Section* section) {
    fprintf(stderr, "Starting section generation\n");
    if (!section || !output) {
        fprintf(stderr, "Null section or output\n");
        return;
    }

    fprintf(output, "<section>\n");
    fprintf(output, "<h2>%s</h2>\n", section->name);

    fprintf(stderr, "Processing %d fields\n", section->field_count);
    for (int i = 0; i < section->field_count; i++) {
        fprintf(stderr, "Generating field %d\n", i);
        Field* field = &section->fields[i];
        fprintf(output, "<label for=\"%s\">%s%s</label>\n", 
               field->name, field->name, field->attributes.required ? " *" : "");

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
            fprintf(output, "  <option value=\"\">Select an option</option>\n");
            fprintf(output, "  <option value=\"option1\">Option 1</option>\n");
            fprintf(output, "  <option value=\"option2\">Option 2</option>\n");
            fprintf(output, "</select>\n");
        } else if (field->type == FIELD_RADIO) {
            fprintf(output, "<div class=\"radio-group\">\n");
            fprintf(output, "  <input type=\"radio\" id=\"%s_1\" name=\"%s\" value=\"option1\"", field->name, field->name);
            if (field->attributes.required) fprintf(output, " required");
            fprintf(output, ">\n");
            fprintf(output, "  <label for=\"%s_1\">Option 1</label><br>\n", field->name);
            fprintf(output, "  <input type=\"radio\" id=\"%s_2\" name=\"%s\" value=\"option2\"", field->name, field->name);
            if (field->attributes.required) fprintf(output, " required");
            fprintf(output, ">\n");
            fprintf(output, "  <label for=\"%s_2\">Option 2</label>\n", field->name);
            fprintf(output, "</div>\n");
        } else {
            fprintf(output, "<input type=\"%s\" id=\"%s\" name=\"%s\"", type, field->name, field->name);
            if (field->attributes.required) fprintf(output, " required");
            if (field->attributes.min_length > 0) fprintf(output, " minlength=\"%d\"", field->attributes.min_length);
            if (field->attributes.max_length > 0) fprintf(output, " maxlength=\"%d\"", field->attributes.max_length);
            if (field->attributes.min_value > 0) fprintf(output, " min=\"%d\"", field->attributes.min_value);
            if (field->attributes.max_value > 0) fprintf(output, " max=\"%d\"", field->attributes.max_value);
            if (field->attributes.pattern) fprintf(output, " pattern=\"%s\"", field->attributes.pattern);
            if (field->attributes.default_value) fprintf(output, " value=\"%s\"", field->attributes.default_value);
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
