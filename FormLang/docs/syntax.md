# FormLang++ Syntax Guide

## Metadata Declarations

Metadata: key-value info for a form. Metadata is declared at the top level of a form, before any sections or fields. Each metadata entry uses the `meta` keyword, a key, an equals sign, and a string value, ending with a semicolon.

**Syntax:**

```
meta <key> = <string>;
```

- `<key>`: An identifier for the metadata entry (e.g., `author`, `version`, `description`).
- `<string>`: The value for the metadata, enclosed in double quotes.

**Where:**
- Metadata declarations must appear inside the form block, before any section or field declarations.

**Example:**

```
form ExampleForm {
    meta author = "SE2062 Team";
    meta version = "1.0";
    meta description = "A sample form with metadata support.";

    section Info {
        field name: text {
            required;
        }
    }
}
```

**Effect:**
- Metadata is included in the generated HTML as comments in the `<head>` section.
- You can add any number of metadata entries to a form. 