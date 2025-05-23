# FormLang++ Grammar Specification

Grammar notes and examples.

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
validation_rule = "if" condition "{" error_message "}" ;(* Example validation rule *)
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

### Simple Form

**Input (`simple_demo.form`)**
```form SimpleDemo {
    meta author = "SE2062 Team";
    meta version = "1.0";

    section PersonalInfo {
        field name: text required minLength 2 maxLength 50;
        field email: email required;
        field age: number required min 0 max 120;
    }

    section AccountInfo {
        field username: text required minLength 4 maxLength 20;
        field password: password required minLength 8;
    }

    validate {
        if age < 18 { error "You must be at least 18 years old."; }
    }
} 
```

**Output (`simple_demo.html`)**
```<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>SimpleDemo</title>
  <!-- version: 1.0 -->
  <!-- author: SE2062 Team -->
  <style>
    body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }
    fieldset { margin-bottom: 20px; padding: 15px; border: 1px solid #ccc; }
    legend { font-weight: bold; padding: 0 10px; }
    .field { margin-bottom: 15px; }
    label { display: block; margin-bottom: 5px; }
    input, textarea, select { width: 100%; padding: 8px; margin-bottom: 5px; }
    .error { color: red; font-size: 0.9em; margin-top: 5px; }
  </style>
</head>
<body>
<form id="SimpleDemo" onsubmit="return validateForm()">
<section>
<h2>PersonalInfo</h2>
<label for="name">name *</label>
<input type="text" id="name" name="name" required minlength="904640160" maxlength="25496">
<label for="email">email *</label>
<input type="email" id="email" name="email" required minlength="904640384" maxlength="25496">
<label for="age">age *</label>
<input type="number" id="age" name="age" required minlength="904640688" maxlength="25496" min="0" max="0">
</section>
<section>
<h2>AccountInfo</h2>
<label for="username">username *</label>
<input type="text" id="username" name="username" required minlength="904641248" maxlength="25496">
<label for="password">password *</label>
<input type="password" id="password" name="password" required minlength="904641424" maxlength="25496">
</section>
<input type="submit" value="Submit">
</form>
</body>
</html>
<script>
document.addEventListener('DOMContentLoaded', function() {
  const form = document.querySelector('form');
  form.addEventListener('submit', function(e) {
    let valid = true;
    const errors = [];

    {
      var age = document.getElementById('age');
      var ageVal = age ? age.value : '';
      if (age && ageVal !== '' && parseFloat(ageVal) < 18) {
        errors.push("You must be at least 18 years old.");
        valid = false;
      }
    }
    if (!valid) {
      e.preventDefault();
      alert(errors.join('\n'));
    }
  });
});
</script>

```

**Error Output (`simple_demo.err`)**
```Starting HTML generation
Generating header
Processing 2 sections
Generating section 0
Starting section generation
Processing 3 fields
Generating field 0
Field 0 generated successfully
Generating field 1
Field 1 generated successfully
Generating field 2
Field 2 generated successfully
Section generation complete
Generating section 1
Starting section generation
Processing 2 fields
Generating field 0
Field 0 generated successfully
Generating field 1
Field 1 generated successfully
Section generation complete
HTML generation complete

```

### Metadata and Pattern Example

**Input (`metadata_test.form`)**
```form MetadataTest {
    meta author = "SE2062 Team";
    meta version = "1.0";
    meta description = "Test form for metadata and pattern support";

    section UserInfo {
        field username: text required pattern "^[a-zA-Z0-9_]{3,20}$" minLength 3 maxLength 20;
        field email: email required pattern "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";
        field password: password required pattern "^(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d]{8,}$" minLength 8;
    }
} 
```

**Output (`metadata_test.html`)**
```<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>MetadataTest</title>
  <!-- description: Test form for metadata and pattern support -->
  <!-- version: 1.0 -->
  <!-- author: SE2062 Team -->
  <style>
    body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }
    fieldset { margin-bottom: 20px; padding: 15px; border: 1px solid #ccc; }
    legend { font-weight: bold; padding: 0 10px; }
    .field { margin-bottom: 15px; }
    label { display: block; margin-bottom: 5px; }
    input, textarea, select { width: 100%; padding: 8px; margin-bottom: 5px; }
    .error { color: red; font-size: 0.9em; margin-top: 5px; }
  </style>
</head>
<body>
<form id="MetadataTest" onsubmit="return validateForm()">
<section>
<h2>UserInfo</h2>
<label for="username">username *</label>
<input type="text" id="username" name="username" required minlength="993834848" maxlength="24667">
<label for="email">email *</label>
<input type="email" id="email" name="email" required minlength="993835104" maxlength="24667">
<label for="password">password *</label>
<input type="password" id="password" name="password" required minlength="993835408" maxlength="24667">
</section>
<input type="submit" value="Submit">
</form>
</body>
</html>
<script>
document.addEventListener('DOMContentLoaded', function() {
  const form = document.querySelector('form');
  form.addEventListener('submit', function(e) {
    let valid = true;
    const errors = [];

    if (!valid) {
      e.preventDefault();
      alert(errors.join('\n'));
    }
  });
});
</script>

```

**Error Output (`metadata_test.err`)**
```Starting HTML generation
Generating header
Processing 1 sections
Generating section 0
Starting section generation
Processing 3 fields
Generating field 0
Field 0 generated successfully
Generating field 1
Field 1 generated successfully
Generating field 2
Field 2 generated successfully
Section generation complete
HTML generation complete

```

### Validation Example

**Input (`validation_test.form`)**
```form ValidationTest {
    section UserInfo {
        field username: username required minLength 3 maxLength 20 pattern "[a-zA-Z0-9_]+";
        field email: email required;
        field password: password required strength 3;
        field confirmPassword: password required confirm password;
        field age: number required min 18 max 120;
        field score: number required min 0 max 100;
    }

    validate {
        if age < 18 { error "You must be at least 18 years old."; }
        if score < 60 { error "Score must be at least 60 to pass."; }
        if score > 100 { error "Score cannot exceed 100."; }
    }

    section PatternTests {
        field empty_pattern: text pattern ".*" required;
        field complex_pattern: text pattern "^[A-Za-z0-9!@#$%^&*()_+\-=\[\]{};':\"\\|,.<>\/? ]+$" required;
        field email_pattern: text pattern "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$" required;
        field url_pattern: text pattern "^(https?:\/\/)?([\da-z\.-]+)\.([a-z\.]{2,6})([\/\w \.-]*)*\/?$" required;
    }

    section RequiredTests {
        field required_no_validation: text required;
        field required_with_pattern: text pattern ".*" required;
        field required_with_length: text minLength 1 maxLength 10 required;
        field required_with_default: text default "test" required;
    }

    section DropdownTests {
        field required_dropdown: dropdown required;
        field optional_dropdown: dropdown optional;
        field dropdown_with_default: dropdown default "option1" required;
    }

    section RadioTests {
        field required_radio: radio required;
        field optional_radio: radio optional;
        field radio_with_default: radio default "option1" required;
    }

    section FileTests {
        field required_file: file required;
        field optional_file: file optional;
        field file_with_accept: file accept "image/*" required;
    }

    section NumberTests {
        field zero_range: number required;
        field negative_range: number min -10 max -1 required;
        field positive_range: number min 1 max 10 required;
        field decimal_range: number min 0.1 max 1.0 required;
    }

    section DefaultValueTests {
        field empty_default: text default "" required;
        field space_default: text default " " required;
        field special_chars: text default "!@#$%^&*()" required;
        field unicode_default: text default "测试" required;
        field zero_default: number default "0" required;
    }

    section MixedAttributes {
        field complex_field: text pattern "^[A-Za-z]+$" minLength 1 maxLength 100 default "test" required;
        field all_optional: text pattern ".*" maxLength 1000 default "" optional;
    }
} 
```

**Output (`validation_test.html`)**
```<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>ValidationTest</title>
  <style>
    body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }
    fieldset { margin-bottom: 20px; padding: 15px; border: 1px solid #ccc; }
    legend { font-weight: bold; padding: 0 10px; }
    .field { margin-bottom: 15px; }
    label { display: block; margin-bottom: 5px; }
    input, textarea, select { width: 100%; padding: 8px; margin-bottom: 5px; }
    .error { color: red; font-size: 0.9em; margin-top: 5px; }
  </style>
</head>
<body>
<form id="ValidationTest" onsubmit="return validateForm()">
<section>
<h2>UserInfo</h2>
<label for="username">username *</label>
<input type="username" id="username" name="username" required minlength="-1830715136" maxlength="-1830715136">
<label for="email">email *</label>
<input type="email" id="email" name="email" required minlength="-1830714880" maxlength="-1830714880">
<label for="password">password *</label>
<input type="password" id="password" name="password" required minlength="-1830714576" maxlength="-1830714576">
<label for="confirmPassword">confirmPassword *</label>
<input type="password" id="confirmPassword" name="confirmPassword" required minlength="-1830714368" maxlength="-1830714368">
<label for="age">age *</label>
<input type="number" id="age" name="age" required minlength="-1830714144" maxlength="-1830714144" min="18" max="120">
<label for="score">score *</label>
<input type="number" id="score" name="score" required minlength="-1830713888" maxlength="-1830713888" min="0" max="100">
</section>
<section>
<h2>PatternTests</h2>
<label for="empty_pattern">empty_pattern *</label>
<input type="text" id="empty_pattern" name="empty_pattern" required minlength="-1830713376" maxlength="-1830713376">
<label for="complex_pattern">complex_pattern *</label>
<input type="text" id="complex_pattern" name="complex_pattern" required minlength="-1830713120" maxlength="-1830713120">
<label for="email_pattern">email_pattern *</label>
<input type="text" id="email_pattern" name="email_pattern" required minlength="-1830712864" maxlength="-1830712864">
<label for="url_pattern">url_pattern *</label>
<input type="text" id="url_pattern" name="url_pattern" required minlength="-1830712544" maxlength="-1830712544">
</section>
<section>
<h2>RequiredTests</h2>
<label for="required_no_validation">required_no_validation *</label>
<input type="text" id="required_no_validation" name="required_no_validation" required minlength="-1830712080" maxlength="-1830712080">
<label for="required_with_pattern">required_with_pattern *</label>
<input type="text" id="required_with_pattern" name="required_with_pattern" required minlength="-1830711872" maxlength="-1830711872">
<label for="required_with_length">required_with_length *</label>
<input type="text" id="required_with_length" name="required_with_length" required minlength="-1830711616" maxlength="-1830711616" maxl="10">
<label for="required_with_default">required_with_default *</label>
<input type="text" id="required_with_default" name="required_with_default" required minlength="-1830711408" maxlength="-1830711408" value="test">
</section>
<section>
<h2>DropdownTests</h2>
<label for="required_dropdown">required_dropdown *</label>
<select id="required_dropdown" name="required_dropdown" required minlength="-1830710992" maxlength="-1830710992"></select>
<label for="optional_dropdown">optional_dropdown</label>
<select id="optional_dropdown" name="optional_dropdown" minlength="-1830710784" maxlength="-1830710784"></select>
<label for="dropdown_with_default">dropdown_with_default *</label>
<select id="dropdown_with_default" name="dropdown_with_default" required minlength="-1830710528" maxlength="-1830710528"></select>
</section>
<section>
<h2>RadioTests</h2>
<label for="required_radio">required_radio *</label>
<div id="required_radio"></div>
<label for="optional_radio">optional_radio</label>
<div id="optional_radio"></div>
<label for="radio_with_default">radio_with_default *</label>
<div id="radio_with_default"></div>
</section>
<section>
<h2>FileTests</h2>
<label for="required_file">required_file *</label>
<input type="file" id="required_file" name="required_file" required minlength="-1830709856" maxlength="-1830709856">
<label for="optional_file">optional_file</label>
<input type="file" id="optional_file" name="optional_file" minlength="-1830709600" maxlength="-1830709600">
<label for="file_with_accept">file_with_accept *</label>
<input type="file" id="file_with_accept" name="file_with_accept" required minlength="-1830709344" maxlength="-1830709344">
</section>
<section>
<h2>NumberTests</h2>
<label for="zero_range">zero_range *</label>
<input type="number" id="zero_range" name="zero_range" required minlength="-1830708880" maxlength="-1830708880">
<label for="negative_range">negative_range *</label>
<input type="number" id="negative_range" name="negative_range" required minlength="-1830708624" maxlength="-1830708624" min="-10" max="-1">
<label for="positive_range">positive_range *</label>
<input type="number" id="positive_range" name="positive_range" required minlength="-1830708368" maxlength="-1830708368" min="1" max="10">
<label for="decimal_range">decimal_range *</label>
<input type="number" id="decimal_range" name="decimal_range" required minlength="-1830708112" maxlength="-1830708112" min="0.1" max="1.0">
</section>
<section>
<h2>DefaultValueTests</h2>
<label for="empty_default">empty_default *</label>
<input type="text" id="empty_default" name="empty_default" required minlength="-1830707696" maxlength="-1830707696" value="">
<label for="space_default">space_default *</label>
<input type="text" id="space_default" name="space_default" required minlength="-1830707488" maxlength="-1830707488" value=" ">
<label for="special_chars">special_chars *</label>
<input type="text" id="special_chars" name="special_chars" required minlength="-1830707232" maxlength="-1830707232" value="!@#$%^&*()">
<label for="unicode_default">unicode_default *</label>
<input type="text" id="unicode_default" name="unicode_default" required minlength="-1830707024" maxlength="-1830707024" value="测试">
<label for="zero_default">zero_default *</label>
<input type="number" id="zero_default" name="zero_default" required minlength="-1830706768" maxlength="-1830706768" value="0">
</section>
<section>
<h2>MixedAttributes</h2>
<label for="complex_field">complex_field *</label>
<input type="text" id="complex_field" name="complex_field" required minlength="-1830706304" maxlength="-1830706304" value="test">
<label for="all_optional">all_optional</label>
<input type="text" id="all_optional" name="all_optional" minlength="-1830706096" maxlength="-1830706096" value="">
</section>
<input type="submit" value="Submit">
</form>
</body>
</html>
<script>
document.addEventListener('DOMContentLoaded', function() {
  const form = document.querySelector('form');
  form.addEventListener('submit', function(e) {
    let valid = true;
    const errors = [];

    {
      var age = document.getElementById('age');
      var ageVal = age ? age.value : '';
      if (age && ageVal !== '' && parseFloat(ageVal) < 18) {
        errors.push("You must be at least 18 years old.");
        valid = false;
      }
    }
    {
      var score = document.getElementById('score');
      var scoreVal = score ? score.value : '';
      if (score && scoreVal !== '' && parseFloat(scoreVal) < 60) {
        errors.push("Score must be at least 60 to pass.");
        valid = false;
      }
    }
    {
      var score = document.getElementById('score');
      var scoreVal = score ? score.value : '';
      if (score && scoreVal !== '' && parseFloat(scoreVal) > 100) {
        errors.push("Score cannot exceed 100.");
        valid = false;
      }
    }
    if (!valid) {
      e.preventDefault();
      alert(errors.join('\n'));
    }
  });
});
</script>

```

**Error Output (`validation_test.err`)**
```Parser Error: syntax error, unexpected IDENTIFIER, expecting FIELD or '}' at line 46
Parser Error: Invalid field declaration at line 46
Syntax error at line 51: Unexpected character
Parser Error: syntax error, unexpected invalid token, expecting NUMBER_LITERAL at line 51
Syntax error at line 51: Unexpected character
Parser Error: Invalid field declaration at line 51
Syntax error at line 53: Unexpected character
Parser Error: syntax error, unexpected invalid token, expecting FIELD or '}' at line 53
Syntax error at line 53: Unexpected character
Parser Error: Invalid field declaration at line 53
Starting HTML generation
Generating header
Processing 9 sections
Generating section 0
Starting section generation
Processing 6 fields
Generating field 0
Field 0 generated successfully
Generating field 1
Field 1 generated successfully
Generating field 2
Field 2 generated successfully
Generating field 3
Field 3 generated successfully
Generating field 4
Field 4 generated successfully
Generating field 5
Field 5 generated successfully
Section generation complete
Generating section 1
Starting section generation
Processing 4 fields
Generating field 0
Field 0 generated successfully
Generating field 1
Field 1 generated successfully
Generating field 2
Field 2 generated successfully
Generating field 3
Field 3 generated successfully
Section generation complete
Generating section 2
Starting section generation
Processing 4 fields
Generating field 0
Field 0 generated successfully
Generating field 1
Field 1 generated successfully
Generating field 2
Field 2 generated successfully
Generating field 3
Field 3 generated successfully
Section generation complete
Generating section 3
Starting section generation
Processing 3 fields
Generating field 0
Field 0 generated successfully
Generating field 1
Field 1 generated successfully
Generating field 2
Field 2 generated successfully
Section generation complete
Generating section 4
Starting section generation
Processing 3 fields
Generating field 0
Field 0 generated successfully
Generating field 1
Field 1 generated successfully
Generating field 2
Field 2 generated successfully
Section generation complete
Generating section 5
Starting section generation
Processing 3 fields
Generating field 0
Field 0 generated successfully
Generating field 1
Field 1 generated successfully
Generating field 2
Field 2 generated successfully
Section generation complete
Generating section 6
Starting section generation
Processing 3 fields
Generating field 0
Field 0 generated successfully
Generating field 1
Field 1 generated successfully
Generating field 2
Field 2 generated successfully
Section generation complete
Generating section 7
Starting section generation
Processing 5 fields
Generating field 0
Field 0 generated successfully
Generating field 1
Field 1 generated successfully
Generating field 2
Field 2 generated successfully
Generating field 3
Field 3 generated successfully
Generating field 4
Field 4 generated successfully
Section generation complete
Generating section 8
Starting section generation
Processing 2 fields
Generating field 0
Field 0 generated successfully
Generating field 1
Field 1 generated successfully
Section generation complete
HTML generation complete

```

### Syntax Error Example

**Input (`syntax_test.form`)**
```form SyntaxTest {
    meta author = "SE2062 Team";
    meta version = "1.0";
    meta description = "Comprehensive test of all FormLang++ features";

    section TextFields {
        field basic_text: text required;
        field length_text: text minLength 50;
        field pattern_text: text pattern "^[A-Za-z0-9]+$";
        field default_text: text default "John Doe";
    }

    section EmailFields {
        field basic_email: email required;
        field custom_email: email pattern "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";
        field work_email: email default "user@company.com";
    }

    section PasswordFields {
        field basic_password: password required;
        field strong_password: password minLength 8;
        field confirm_password: password required;
    }

    section NumberFields {
        field basic_number: number required;
        field range_number: number min 0;
        field decimal_number: number max 999;
        field default_number: number default 1;
    }

    section TextareaFields {
        field basic_textarea: textarea required;
        field dimension_textarea: textarea rows 5;
        field length_textarea: textarea minLength 10;
    }

    section DateFields {
        field basic_date: date required;
        field default_date: date default "2024-12-31";
    }

    section SelectionFields {
        field basic_checkbox: checkbox required;
        field default_checkbox: checkbox default true;
        field basic_dropdown: dropdown required;
        field default_dropdown: dropdown default "en";
        field optional_dropdown: dropdown optional;
        field basic_radio: radio required;
        field default_radio: radio default "option1";
        field optional_radio: radio optional;
    }

    section FileFields {
        field basic_file: file required;
        field image_file: file pattern "image/*";
        field doc_file: file pattern "*.pdf";
        field optional_file: file pattern "*/*";
    }

    section AddressFields {
        field street: text required;
        field city: text required;
        field postal_code: text pattern "^[A-Z]{2}\\d{2}\\s?\\d{2}[A-Z]{2}$";
    }

    validate {
        if age < 18 { error "You must be at least 18 years old."; }
        if password != confirm_password { error "Passwords do not match."; }
        if length(bio) > 0 && length(bio) < 10 { error "Bio must be at least 10 characters if provided."; }
    }
} 
```

**Error Output (`syntax_test.err`)**
```Parser Error: syntax error, unexpected NUMBER_LITERAL, expecting STRING_LITERAL at line 29
Parser Error: Invalid field declaration at line 29
Parser Error: syntax error, unexpected IDENTIFIER, expecting STRING_LITERAL at line 45
Parser Error: Invalid field declaration at line 45
Parser Error: syntax error, unexpected IDENTIFIER, expecting NUMBER_LITERAL at line 69
