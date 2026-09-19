# Lexical Analyzer in C
A modular Lexical Analyzer developed in C to tokenize source code, identify keywords, identifiers, constants, operators, delimiters, comments, strings, character constants, preprocessor directives, and lexical errors.

## Project Overview

A **Lexical Analyzer** is the first phase of a compiler. Its primary responsibility is to read the source program character by character, group characters into meaningful sequences called **lexemes**, and classify those lexemes into **tokens**.

This project implements a modular **Lexical Analyzer for C source code using C programming**. The analyzer scans an input C source file, identifies different types of tokens, tracks their line numbers, and reports invalid lexical constructs with meaningful error messages.

The project is designed using separate modules for different lexical components such as identifiers, numbers, operators, comments, delimiters, strings, character constants, and preprocessor directives.

---

## Objectives

The main objectives of this project are:

* Understand the role of lexical analysis in a compiler.
* Process source code character by character.
* Identify and classify C language tokens.
* Distinguish keywords from identifiers.
* Validate different numeric constant formats.
* Recognize operators and delimiters.
* Handle string and character literals.
* Process single-line and multi-line comments.
* Recognize preprocessor directives and header files.
* Detect and report lexical errors.
* Track source-code line numbers.
* Develop a modular C application using multiple source files.
* Build and execute the project using a Makefile.

---

## Compiler Workflow

Lexical analysis is the first stage in the compiler pipeline.

```text
                C Source Code
                      |
                      v
              +---------------+
              |    Lexer      |
              | Lexical       |
              | Analysis      |
              +---------------+
                      |
                      v
                    Tokens
                      |
                      v
              Syntax Analysis
                      |
                      v
             Semantic Analysis
                      |
                      v
            Intermediate Code
                      |
                      v
                Optimization
                      |
                      v
              Code Generation
```

This project focuses specifically on the **Lexical Analysis** stage.

---

## What is a Token?

A **token** is a meaningful unit identified by the lexical analyzer.

For example, consider:

```c
int count = 10;
```

The lexer separates this source code into:

```text
int       -> KEYWORD
count     -> IDENTIFIER
=         -> OPERATOR
10        -> INTEGER_CONSTANT
;         -> SPECIAL_CHARACTER
```

### Lexeme

A **lexeme** is the actual sequence of characters found in the source program.

Example:

```text
int
count
=
10
;
```

### Token

A token represents the category assigned to a lexeme.

```text
int  -> KEYWORD
count -> IDENTIFIER
10 -> INTEGER_CONSTANT
```

The project stores this information using a `Token` structure.

---

## Token Structure

Each recognized token contains:

```c
typedef struct
{
    char lexeme[MAX_TOKEN_SIZE];
    TokenType type;
    int line_number;
    char error_message[MAX_TOKEN_SIZE];
} Token;
```

The structure stores:

* **lexeme** – actual text extracted from the source file.
* **type** – classification of the token.
* **line_number** – source-code line where the token occurs.
* **error_message** – description when a lexical error is detected.

---

## Supported Token Types

The lexer supports the following categories:

### 1. Keywords

Examples:

```text
int
char
float
double
if
else
for
while
return
struct
union
enum
typedef
const
static
sizeof
void
```

The lexer maintains a list of C keywords and checks whether an identifier-like sequence belongs to the keyword list.

---

### 2. Identifiers

Identifiers are names used for variables, functions, structures, and other user-defined entities.

Examples:

```c
count
total
student
main
value_1
```

The lexer recognizes identifiers containing letters, digits, and underscores according to the scanning rules implemented in the project.

---

### 3. Integer Constants

Examples:

```c
10
25
1000
```

---

### 4. Octal Constants

Examples:

```c
0123
077
```

The lexer also validates octal digits and reports invalid values such as:

```text
098
```

---

### 5. Hexadecimal Constants

Examples:

```c
0x1A
0XFF
```

Invalid hexadecimal values are detected, for example:

```text
0xG1
```

---

### 6. Binary Constants

Examples:

```c
0b1010
0B1101
```

Invalid binary digits are detected:

```text
0b102
```

---

### 7. Floating-Point Constants

Examples:

```c
12.50
3.14
```

The lexer also detects malformed numeric sequences such as:

```text
12.3.4
```

---

## Operator Recognition

The lexer supports single-character and multi-character operators.

### Arithmetic Operators

```text
+
-
*
/
%
```

### Assignment Operators

```text
=
+=
-=
*=
/=
%=
```

### Relational Operators

```text
<
>
<=
>=
==
!=
```

### Logical Operators

```text
&&
||
!
```

### Increment and Decrement

```text
++
--
```

### Bitwise Operators

```text
&
|
^
~
```

### Shift Operators

```text
<<
>>
<<=
>>=
```

### Compound Bitwise Assignment

```text
&=
|=
^=
```

### Pointer Member Access

```text
->
```

The lexer uses look-ahead where necessary to distinguish single-character operators from compound operators.

---

## Delimiters and Special Characters

The analyzer recognizes special characters used in C syntax, including:

```text
(
)
{
}
[
]
;
,
:
?
.
```

These are classified as special characters/delimiters.

---

##
