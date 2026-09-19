#include "lexer.h"

Token scanStringLiteral(void)
{
    Token token = {0};
    int index = 0;
    int ch;
    int escaped = 0;
    int closed = 0;

    token.line_number = current_line;
    token.lexeme[index++] = '"';

    while ((ch = fgetc(source_file)) != EOF)
    {
        if (index < MAX_TOKEN_SIZE - 1)
        {
            token.lexeme[index++] = ch;
        }

        if (ch == '\n')
        {
            current_line++;
            break;
        }

        if (escaped)
        {
            escaped = 0;
        }
        else if (ch == '\\')
        {
            escaped = 1;
        }
        else if (ch == '"')
        {
            closed = 1;
            break;
        }
    }

    token.lexeme[index] = '\0';

    if (closed)
    {
        token.type = STRING_LITERAL;
    }
    else
    {
        setLexicalError(&token, "Unterminated string literal");
    }

    return token;
}

Token scanCharacterConstant(void)
{
    Token token = {0};
    int index = 0;
    int ch;
    int char_count = 0;
    int escaped = 0;
    int closed = 0;

    token.line_number = current_line;
    token.lexeme[index++] = '\'';

    while ((ch = fgetc(source_file)) != EOF)
    {
        if (index < MAX_TOKEN_SIZE - 1)
        {
            token.lexeme[index++] = ch;
        }

        /* Newline before closing quote */
        if (ch == '\n')
        {
            current_line++;
            break;
        }

        /* Handle escape sequence */
        if (escaped)
        {
            escaped = 0;
            char_count++;
            continue;
        }

        if (ch == '\\')
        {
            escaped = 1;
            continue;
        }

        /* Closing quote */
        if (ch == '\'')
        {
            closed = 1;
            break;
        }

        /* Normal character */
        char_count++;

        /* More than one normal character */
        if (char_count > 1)
        {
            /* Keep reading until closing quote */
            while ((ch = fgetc(source_file)) != EOF)
            {
                if (index < MAX_TOKEN_SIZE - 1)
                {
                    token.lexeme[index++] = ch;
                }

                if (ch == '\n')
                {
                    current_line++;
                    break;
                }

                if (ch == '\'')
                {
                    closed = 1;
                    break;
                }
            }

            break;
        }
    }

    token.lexeme[index] = '\0';

    if (!closed)
    {
        setLexicalError(&token,
                        "Unterminated character constant");
    }
    else if (char_count == 0)
    {
        setLexicalError(&token,
                        "Empty character constant");
    }
    else if (char_count > 1)
    {
        setLexicalError(&token,
                        "Invalid character constant");
    }
    else
    {
        token.type = CHARACTER_CONSTANT;
    }

    return token;
}