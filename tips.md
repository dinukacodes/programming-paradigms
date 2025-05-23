# FormLang Usage Guide



## Creating Form Files

1. Create a new file with `.form` extension
2. Follow the FormLang syntax:
   ```form
   form FormName {
       section SectionName {
           field fieldName: fieldType attribute;
       }
   }
   ```

### Field Types
- `text`: Text input
- `email`: Email input
- `password`: Password input
- `number`: Number input

### Attributes
- `required`: Field must be filled
- `optional`: Field can be left empty

### Example Form
```form
form MyForm {
    section Personal {
        field name: text required;
        field email: email required;
        field phone: number optional;
    }
}
```

## Processing Form Files

1. Make sure the code is compiled:
   ```bash
   make clean
   make
   ```

2. Process your form file:
   ```bash
   ./bin/formLang < your_form.form > output/your_form.html
   ```

3. View the generated HTML:
   ```bash
   cat output/your_form.html
   ```

## Tips

1. **File Location**: Place your `.form` files in the `examples` directory
2. **Output**: Generated HTML files will be in the `output` directory
3. **Validation**: The parser will show errors if your form definition is invalid
4. **Empty Sections**: You can have sections with no fields
5. **Field Names**: Use descriptive names for better HTML output
6. **Required Fields**: Mark important fields as `required`

## Common Commands

```bash
# Compile the code
make clean && make

# Process a form file
./bin/formLang < examples/your_form.form > output/your_form.html

# View generated HTML
cat output/your_form.html

# Process multiple forms
./bin/formLang < examples/form1.form > output/form1.html
./bin/formLang < examples/form2.form > output/form2.html
```

## Error Handling

If you get errors:
1. Check the form syntax
2. Ensure all fields have proper types
3. Verify semicolons are present
4. Check for duplicate field names
5. Make sure sections are properly nested

## Example Forms

Check the `examples` directory for sample form definitions:
- `registration.form`: Basic registration form
- `all_fields.form`: Form with all field types
- `complex_form.form`: Complex form with multiple sections
- `mixed_attributes.form`: Form with required and optional fields 