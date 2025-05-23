#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "formLang.h"

void generate_html_header(FILE* output) {
    fprintf(output, "<!DOCTYPE html>\n<html>\n<head>\n");
    fprintf(output, "  <meta charset=\"UTF-8\">\n");
    fprintf(output, "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
    fprintf(output, "  <title>%s</title>\n", current_form->name);
    
    // Add metadata as HTML comments
    Metadata* meta = current_form->metadata;
    while (meta) {
        fprintf(output, "  <!-- %s: %s -->\n", meta->key, meta->value);
        meta = meta->next;
    }
    
    fprintf(output, "  <style>\n");
    fprintf(output, "    body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }\n");
    fprintf(output, "    fieldset { margin-bottom: 20px; padding: 15px; border: 1px solid #ccc; }\n");
    fprintf(output, "    legend { font-weight: bold; padding: 0 10px; }\n");
    fprintf(output, "    .field { margin-bottom: 15px; }\n");
    fprintf(output, "    label { display: block; margin-bottom: 5px; }\n");
    fprintf(output, "    input, textarea, select { width: 100%%; padding: 8px; margin-bottom: 5px; }\n");
    fprintf(output, "    .error { color: red; font-size: 0.9em; margin-top: 5px; }\n");
    fprintf(output, "  </style>\n");
    fprintf(output, "</head>\n<body>\n");
    fprintf(output, "<form id=\"%s\" onsubmit=\"return validateForm()\">\n", current_form->name);
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
            case FIELD_USERNAME: type = "text"; break;
            case FIELD_ADDRESS: type = "text"; break;
        }

        if (field->type == FIELD_TEXTAREA) {
            fprintf(output, "<textarea id=\"%s\" name=\"%s\"", field->name, field->name);
            if (field->attributes.rows > 0) fprintf(output, " rows=\"%d\"", field->attributes.rows);
            if (field->attributes.cols > 0) fprintf(output, " cols=\"%d\"", field->attributes.cols);
            if (field->attributes.required) fprintf(output, " required");
            fprintf(output, ">");
            if (field->attributes.default_value) {
                char* escaped_value = escape_html_attr(field->attributes.default_value);
                fprintf(output, "%s", escaped_value);
                free(escaped_value);
            }
            fprintf(output, "</textarea>\n");
        } else if (field->type == FIELD_DROPDOWN) {
            fprintf(output, "<select id=\"%s\" name=\"%s\"", field->name, field->name);
            if (field->attributes.required) fprintf(output, " required");
            fprintf(output, ">\n");
            if (!field->attributes.required) {
                fprintf(output, "  <option value=\"\">Select an option</option>\n");
            }
            fprintf(output, "  <option value=\"option1\"%s>Option 1</option>\n", 
                   field->attributes.default_value && strcmp(field->attributes.default_value, "option1") == 0 ? " selected" : "");
            fprintf(output, "  <option value=\"option2\"%s>Option 2</option>\n",
                   field->attributes.default_value && strcmp(field->attributes.default_value, "option2") == 0 ? " selected" : "");
            fprintf(output, "</select>\n");
        } else if (field->type == FIELD_RADIO) {
            fprintf(output, "<div class=\"radio-group\">\n");
            fprintf(output, "  <input type=\"radio\" id=\"%s_1\" name=\"%s\" value=\"option1\"%s", 
                   field->name, field->name,
                   field->attributes.default_value && strcmp(field->attributes.default_value, "option1") == 0 ? " checked" : "");
            if (field->attributes.required) fprintf(output, " required");
            fprintf(output, ">\n");
            fprintf(output, "  <span>Option 1</span><br>\n");
            fprintf(output, "  <input type=\"radio\" id=\"%s_2\" name=\"%s\" value=\"option2\"%s", 
                   field->name, field->name,
                   field->attributes.default_value && strcmp(field->attributes.default_value, "option2") == 0 ? " checked" : "");
            if (field->attributes.required) fprintf(output, " required");
            fprintf(output, ">\n");
            fprintf(output, "  <span>Option 2</span>\n");
            fprintf(output, "</div>\n");
        } else if (field->type == FIELD_ADDRESS) {
            fprintf(output, "<div class=\"address-group\">\n");
            fprintf(output, "<input type=\"text\" id=\"%s_street\" name=\"%s_street\" placeholder=\"Street\" required>\n", field->name, field->name);
            fprintf(output, "<input type=\"text\" id=\"%s_city\" name=\"%s_city\" placeholder=\"City\" required>\n", field->name, field->name);
            fprintf(output, "<input type=\"text\" id=\"%s_state\" name=\"%s_state\" placeholder=\"State\" required>\n", field->name, field->name);
            fprintf(output, "<input type=\"text\" id=\"%s_zip\" name=\"%s_zip\" placeholder=\"ZIP\" required>\n", field->name, field->name);
            fprintf(output, "<input type=\"text\" id=\"%s_country\" name=\"%s_country\" placeholder=\"Country\" required>\n", field->name, field->name);
            fprintf(output, "</div>\n");
        } else {
            const char* input_type = type;
            if (field->type == FIELD_USERNAME) input_type = "text";
            if (field->type == FIELD_PASSWORD) input_type = "password";
            if (field->type == FIELD_EMAIL) input_type = "email";
            fprintf(output, "<input type=\"%s\" id=\"%s\" name=\"%s\"", input_type, field->name, field->name);
            if (field->attributes.required) fprintf(output, " required");
            if (field->attributes.min_length > 0) fprintf(output, " minlength=\"%d\"", field->attributes.min_length);
            if (field->attributes.max_length > 0) fprintf(output, " maxlength=\"%d\"", field->attributes.max_length);
            if (field->type == FIELD_NUMBER) {
                if (field->attributes.min_value != -1) fprintf(output, " min=\"%d\"", field->attributes.min_value);
                if (field->attributes.max_value != -1) fprintf(output, " max=\"%d\"", field->attributes.max_value);
            }
            if (field->attributes.pattern && strlen(field->attributes.pattern) > 0) {
                char* escaped_pattern = escape_html_attr(field->attributes.pattern);
                fprintf(output, " pattern=\"%s\"", escaped_pattern);
                free(escaped_pattern);
            }
            if (field->attributes.default_value) {
                char* escaped_value = escape_html_attr(field->attributes.default_value);
                if (field->type == FIELD_CHECKBOX) {
                    fprintf(output, " %s", strcmp(escaped_value, "true") == 0 ? "checked" : "");
                } else {
                    fprintf(output, " value=\"%s\"", escaped_value);
                }
                free(escaped_value);
            }
            if (field->type == FIELD_FILE) fprintf(output, " accept=\"*/*\"");
            if (field->attributes.confirm_field) fprintf(output, " data-confirm=\"%s\"", field->attributes.confirm_field);
            if (field->attributes.strength_required > 0) fprintf(output, " data-strength=\"%d\"", field->attributes.strength_required);
            fprintf(output, ">\n");
            if (field->type == FIELD_PASSWORD && field->attributes.strength_required > 0) {
                fprintf(output, "<meter id=\"%s_strength\" min=\"0\" max=\"4\"></meter>\n", field->name);
            }
        }
        fprintf(stderr, "Field %d generated successfully\n", i);
    }

    fprintf(output, "</section>\n");
    fprintf(stderr, "Section generation complete\n");
}

static void parse_condition(const char* cond, char* field, char* op, char* value) {
    // cond is like "score > 100" or "age < 18"
    // Extract field, op, value
    const char* p = cond;
    while (*p && isspace(*p)) p++;
    int i = 0;
    while (*p && !isspace(*p) && *p != '<' && *p != '>' && *p != '=' && *p != '!') field[i++] = *p++;
    field[i] = '\0';
    while (*p && isspace(*p)) p++;
    int j = 0;
    if (*p == '<' || *p == '>' || *p == '=' || *p == '!') {
        op[j++] = *p++;
        if (*p == '=' || (*(p-1) == '<' && *p == '>')) op[j++] = *p++;
    }
    op[j] = '\0';
    while (*p && isspace(*p)) p++;
    int k = 0;
    while (*p) value[k++] = *p++;
    value[k] = '\0';
}

void generate_validation_js(FILE* output, Form* form) {
    fprintf(output, "<script>\n");
    fprintf(output, "document.addEventListener('DOMContentLoaded', function() {\n");
    fprintf(output, "  const form = document.querySelector('form');\n");
    fprintf(output, "  form.addEventListener('submit', function(e) {\n");
    fprintf(output, "    let valid = true;\n");
    fprintf(output, "    const errors = [];\n\n");

    ValidationRule* rule = form->validation_rules;
    while (rule) {
        char field[64], op[4], value[64];
        parse_condition(rule->condition, field, op, value);
        fprintf(output, "    {\n");
        fprintf(output, "      var %s = document.getElementById('%s');\n", field, field);
        fprintf(output, "      var %sVal = %s ? %s.value : '';\n", field, field, field);
        fprintf(output, "      if (%s && %sVal !== '' && parseFloat(%sVal) %s %s) {\n", field, field, field, op, value);
        fprintf(output, "        errors.push(\"%s\");\n", rule->error_message);
        fprintf(output, "        valid = false;\n");
        fprintf(output, "      }\n");
        fprintf(output, "    }\n");
        rule = rule->next;
    }

    fprintf(output, "    if (!valid) {\n");
    fprintf(output, "      e.preventDefault();\n");
    fprintf(output, "      alert(errors.join('\\n'));\n");
    fprintf(output, "    }\n");
    fprintf(output, "  });\n");
    fprintf(output, "});\n");
    fprintf(output, "</script>\n");
}

void generate_html(FILE* output) {
    fprintf(stderr, "Starting HTML generation\n");
    if (!current_form || !output) {
        fprintf(stderr, "Null form or output\n");
        return;
    }

    fprintf(stderr, "Generating header\n");
    generate_html_header(output);

    fprintf(stderr, "Processing %d sections\n", current_form->section_count);
    for (int i = 0; i < current_form->section_count; i++) {
        fprintf(stderr, "Generating section %d\n", i);
        generate_section_html(output, current_form->sections[i]);
    }

    fprintf(output, "<input type=\"submit\" value=\"Submit\">\n");
    fprintf(output, "</form>\n");
    generate_html_footer(output);
    
    // Generate validation JavaScript
    generate_validation_js(output, current_form);
    
    fprintf(stderr, "HTML generation complete\n");
}
