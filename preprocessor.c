#include "lexer.h"
#include <ctype.h>
#include <string.h>

Token scanPreprocessor(void)
{
    Token token = {0};
    int index = 0;
    int ch;

    token.line_number = current_line;
    token.lexeme[index++] = '#';

    ch = fgetc(source_file);

    while (ch == ' ' || ch == '\t')
    {
        ch = fgetc(source_file);
    }

    while (isalpha(ch))
    {
        if (index < MAX_TOKEN_SIZE - 1)
        {
            token.lexeme[index++] = ch;
        }

        ch = fgetc(source_file);
    }

    token.lexeme[index] = '\0';

    if (strcmp(token.lexeme, "#include") == 0)
    {
        expecting_header = 1;

        if (ch != EOF)
        {
            ungetc(ch, source_file);
        }

        token.type = PREPROCESSOR;
        return token;
    }

    /* Other directives: #define, #ifdef, #ifndef, etc. */
    while (ch != EOF && ch != '\n')
    {
        if (index < MAX_TOKEN_SIZE - 1)
        {
            token.lexeme[index++] = ch;
        }

        ch = fgetc(source_file);
    }

    token.lexeme[index] = '\0';

    if (ch == '\n')
    {
        current_line++;
    }

    token.type = PREPROCESSOR;

    return token;
}

Token scanHeaderFile(int first_char)
{
    Token token = {0};
    int index = 0;
    int ch;
    char closing_char;

    token.line_number = current_line;
    token.lexeme[index++] = first_char;

    if (first_char == '<')
    {
        closing_char = '>';
    }
    else
    {
        closing_char = '"';
    }

    while ((ch = fgetc(source_file)) != EOF)
    {
        if (index < MAX_TOKEN_SIZE - 1)
        {
            token.lexeme[index++] = ch;
        }

        if (ch == closing_char)
        {
            token.lexeme[index] = '\0';
            token.type = HEADER_FILE;
            expecting_header = 0;

            return token;
        }

        if (ch == '\n')
        {
            current_line++;
            break;
        }
    }

    token.lexeme[index] = '\0';
    expecting_header = 0;

    setLexicalError(&token, "Unterminated header file");

    return token;
}
