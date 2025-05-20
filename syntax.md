# FormLang Syntax Guide

## Basic Structure

```
form FormName {
    section SectionName {
        field field_name: type attributes;
    }
}
```

## Field Types and Their Attributes

### Text Fields
```
# Basic text field
field username: text required;

# Text with length constraints
field short_text: text minLength 1 maxLength 50 required;

# Text with pattern validation
field alphanumeric: text pattern "^[A-Za-z0-9]+$" required;

# Text with default value
field name: text default "John Doe" required;

# Text with all attributes
field complex_text: text pattern "^[A-Za-z]+$" minLength 1 maxLength 100 default "test" required;
```

### Email Fields
```
# Basic email field
field email: email required;

# Email with custom pattern
field custom_email: email pattern "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$" required;

# Email with default
field work_email: email default "user@company.com" required;
```

### Password Fields
```
# Basic password field
field password: password required;

# Password with strength requirements
field strong_password: password pattern "^(?=.*[A-Za-z])(?=.*\d)[A-Za-z\d]{8,}$" minLength 8 maxLength 32 required;

# Password with confirmation
field password_confirm: password pattern "^(?=.*[A-Za-z])(?=.*\d)[A-Za-z\d]{8,}$" required;
```

### Number Fields
```
# Basic number field
field age: number required;

# Number with range
field score: number min 0 max 100 required;

# Number with decimal range
field price: number min 0.01 max 999.99 required;

# Number with default
field quantity: number default 1 min 1 max 100 required;
```

### Textarea Fields
```
# Basic textarea
field description: textarea required;

# Textarea with dimensions
field long_text: textarea rows 5 cols 50 required;

# Textarea with length constraints
field bio: textarea minLength 10 maxLength 1000 required;

# Textarea with default
field notes: textarea default "Enter your notes here" rows 3 cols 40 required;
```

### Date Fields
```
# Basic date field
field birth_date: date required;

# Date with default
field appointment: date default "2024-12-31" required;
```

### Checkbox Fields
```
# Basic checkbox
field terms: checkbox required;

# Checkbox with default
field newsletter: checkbox default "true" required;
```

### Dropdown Fields
```
# Basic dropdown
field country: dropdown required;

# Dropdown with default
field language: dropdown default "en" required;

# Optional dropdown
field title: dropdown optional;
```

### Radio Fields
```
# Basic radio group
field gender: radio required;

# Radio with default
field preference: radio default "option1" required;

# Optional radio
field subscription: radio optional;
```

### File Fields
```
# Basic file upload
field document: file required;

# File with type restriction
field image: file accept "image/*" required;

# File with multiple types
field document: file accept "*.pdf,*.doc,*.docx" required;

# Optional file
field attachment: file accept "*/*" optional;
```

## Common Patterns

### Email Validation
```
pattern "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$"
```

### URL Validation
```
pattern "^(https?:\/\/)?([\da-z\.-]+)\.([a-z\.]{2,6})([\/\w \.-]*)*\/?$"
```

### Phone Number
```
pattern "^\+?[\d\s-]{10,}$"
```

### Postal Code
```
pattern "^[A-Z]{2}\d{2}\s?\d{2}[A-Z]{2}$"
```

### Password Strength
```
pattern "^(?=.*[A-Za-z])(?=.*\d)(?=.*[@$!%*#?&])[A-Za-z\d@$!%*#?&]{8,}$"
```

## Complete Form Example

```
form RegistrationForm {
    section PersonalInfo {
        field username: text pattern "^[A-Za-z0-9_]{3,20}$" minLength 3 maxLength 20 required;
        field email: email pattern "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$" required;
        field password: password pattern "^(?=.*[A-Za-z])(?=.*\d)[A-Za-z\d]{8,}$" minLength 8 maxLength 32 required;
        field confirm_password: password pattern "^(?=.*[A-Za-z])(?=.*\d)[A-Za-z\d]{8,}$" required;
    }

    section ContactInfo {
        field phone: text pattern "^\+?[\d\s-]{10,}$" required;
        field address: textarea minLength 10 maxLength 200 required;
        field city: text required;
        field postal_code: text pattern "^[A-Z]{2}\d{2}\s?\d{2}[A-Z]{2}$" required;
        field country: dropdown required;
    }

    section Preferences {
        field newsletter: checkbox default "true" required;
        field communication: radio default "email" required;
        field language: dropdown default "en" required;
        field terms: checkbox required;
    }
}
```

## Notes and Best Practices

1. **Attribute Order**
   - Attributes can be in any order
   - `required` or `optional` should be last
   - Pattern should come before length constraints

2. **String Values**
   - Use double quotes for strings
   - Escape special characters in patterns
   - Empty strings are allowed for defaults

3. **Number Values**
   - Can be integers or decimals
   - Negative numbers are allowed
   - Scientific notation is not supported

4. **Pattern Validation**
   - Use `pattern ".*"` to match anything
   - Empty patterns are not allowed
   - Complex patterns should be tested

5. **File Types**
   - Use MIME types (e.g., "image/*")
   - Use file extensions (e.g., "*.pdf")
   - Multiple types: "*.pdf,*.doc"

6. **Default Values**
   - Must match field type
   - Can be empty string
   - Should be valid for patterns

7. **Required vs Optional**
   - One must be specified
   - Cannot use both
   - Default is optional

8. **Length Constraints**
   - minLength must be <= maxLength
   - Both must be positive
   - Applies to text and textarea

9. **Number Ranges**
   - min must be <= max
   - Can be negative
   - Decimals are supported

10. **Section Organization**
    - Group related fields
    - Use descriptive names
    - Keep sections focused 