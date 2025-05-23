# FormLang++ Grammar Specification

Grammar notes and EBNF definition.

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

1.  **Form Structure**
    -   Forms need a unique id.
    -   Can have multiple metadata.
    -   Need at least one section.
    -   Sections need at least one field.

2.  **Metadata**
    -   Meta goes before sections.
    -   Each meta entry needs a unique key.
    -   Values must be strings.

3.  **Sections**
    -   Sections need unique ids within a form.
    -   Can have multiple fields.
    -   Field ids unique within a section.

4.  **Fields**
    -   Each field needs a type and at least one attribute.
    -   Attributes depend on type.
    -   Some attributes can't be used together (e.g., required/optional).

5.  **Validation**
    -   Validation blocks can reference any field.
    -   Conditions compare fields or literals.
    -   Error messages must be strings.

## Field Type-Specific Rules

1.  **Text Fields** (text, email, password)
    -   Supports: pattern, minLength, maxLength, default.
    -   Emails need valid pattern.
    -   Passwords shouldn't have default values.

2.  **Numeric Fields** (number)
    -   Supports: min, max, default.
    -   Default values are numbers.

3.  **Text Area** (textarea)
    -   Supports: rows, cols, default.
    -   Default values are strings.

4.  **Selection Fields** (dropdown, radio)
    -   Need options attribute.
    -   Options are non-empty string arrays.
    -   Default must match an option.

5.  **File Fields** (file)
    -   Supports: pattern (for file types).
    -   No default values.

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