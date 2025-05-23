# FormLang++ Grammar Specification

This document provides the complete EBNF (Extended Backus-Naur Form) grammar specification for the FormLang++ DSL.

## Core Grammar Rules

```
(* Top-level form declaration *)
form_declaration = "form" identifier "{" { metadata_declaration } { section_declaration } "}" ;

(* Metadata declarations *)
metadata_declaration = "meta" identifier "=" string_literal ";" ;

(* Section declarations *)
section_declaration = "section" identifier "{" { field_declaration } "}" ;

(* Field declarations *)
field_declaration = "field" identifier ":" field_type "{" { field_attribute } "}" ;

(* Field types *)
field_type = "text" | "email" | "password" | "number" | "date" | "textarea" 
           | "checkbox" | "dropdown" | "radio" | "file" ;

(* Field attributes *)
field_attribute = required_attribute
                | optional_attribute
                | pattern_attribute
                | min_length_attribute
                | max_length_attribute
                | min_value_attribute
                | max_value_attribute
                | rows_attribute
                | cols_attribute
                | default_attribute
                | options_attribute ;

(* Specific attributes *)
required_attribute = "required" ";" ;
optional_attribute = "optional" ";" ;
pattern_attribute = "pattern" "=" string_literal ";" ;
min_length_attribute = "minLength" "=" number ";" ;
max_length_attribute = "maxLength" "=" number ";" ;
min_value_attribute = "min" "=" number ";" ;
max_value_attribute = "max" "=" number ";" ;
rows_attribute = "rows" "=" number ";" ;
cols_attribute = "cols" "=" number ";" ;
default_attribute = "default" "=" (string_literal | number | boolean) ";" ;
options_attribute = "options" "=" "[" { string_literal } "]" ";" ;

(* Validation blocks *)
validation_block = "validate" "{" { validation_rule } "}" ;
validation_rule = "if" condition "{" error_message "}" ;
condition = field_reference comparison_operator (field_reference | literal) ;
error_message = "error" string_literal ";" ;
field_reference = identifier ;
comparison_operator = "<" | ">" | "<=" | ">=" | "==" | "!=" ;

(* Basic elements *)
identifier = letter { letter | digit | "_" } ;
string_literal = '"' { character } '"' ;
number = digit { digit } ;
boolean = "true" | "false" ;
letter = "A" | "B" | ... | "Z" | "a" | "b" | ... | "z" ;
digit = "0" | "1" | ... | "9" ;
character = (* any character except double quote *) ;
```

## Grammar Notes

1. **Form Structure**
   - Each form must have a unique identifier
   - Forms can contain multiple metadata declarations
   - Forms must contain at least one section
   - Sections must contain at least one field

2. **Metadata**
   - Metadata declarations must appear before any sections
   - Each metadata entry must have a unique key
   - Values must be string literals

3. **Sections**
   - Each section must have a unique identifier within its form
   - Sections can contain multiple fields
   - Field identifiers must be unique within their section

4. **Fields**
   - Each field must have a type and at least one attribute
   - Field types determine which attributes are valid
   - Some attributes are mutually exclusive (e.g., required/optional)

5. **Validation**
   - Validation blocks can reference any field in the form
   - Conditions can compare fields to literals or other fields
   - Error messages must be string literals

## Field Type-Specific Rules

1. **Text Fields** (text, email, password)
   - Support: pattern, minLength, maxLength, default
   - Email fields must contain a valid email pattern
   - Password fields should not have default values

2. **Numeric Fields** (number)
   - Support: min, max, default
   - Default values must be numbers

3. **Text Area** (textarea)
   - Support: rows, cols, default
   - Default values must be strings

4. **Selection Fields** (dropdown, radio)
   - Must have an options attribute
   - Options must be non-empty string arrays
   - Support: default (must match an option)

5. **File Fields** (file)
   - Support: pattern (for file type restrictions)
   - No default values allowed

## Examples

### Basic Form
```
form Registration {
    meta author = "SE2062 Team";
    
    section PersonalInfo {
        field name: text {
            required;
            minLength = 2;
            maxLength = 50;
        }
    }
}
```

### Form with Validation
```
form AgeVerification {
    section Details {
        field age: number {
            required;
            min = 0;
            max = 120;
        }
    }
    
    validate {
        if age < 18 {
            error "You must be at least 18 years old.";
        }
    }
} 