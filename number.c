#include "lexer.h"
#include <ctype.h>

Token scanNumber(int first_char)
{
    Token token = {0};
    int index = 0;
    int ch;
    int is_valid = 1;
    int has_dot = 0;

    token.line_number = current_line;
    token.lexeme[index++] = first_char;

    /* Hexadecimal: 0x or 0X */
    if (first_char == '0')
    {
        ch = fgetc(source_file);

        if (ch == 'x' || ch == 'X')
        {
            token.lexeme[index++] = ch;

            ch = fgetc(source_file);

            if (!isxdigit(ch))
            {
                is_valid = 0;
            }

            while (isalnum(ch))
            {
                if (index < MAX_TOKEN_SIZE - 1)
                {
                    token.lexeme[index++] = ch;
                }

                if (!isxdigit(ch))
                {
                    is_valid = 0;
                }

                ch = fgetc(source_file);
            }

            if (ch != EOF)
            {
                ungetc(ch, source_file);
            }

            token.lexeme[index] = '\0';

            if (is_valid)
            {
                token.type = HEX_CONSTANT;
            }
            else
            {
                setLexicalError(&token, "Invalid hexadecimal constant");
            }

            return token;
        }

        /* Binary: 0b or 0B */
        if (ch == 'b' || ch == 'B')
        {
            token.lexeme[index++] = ch;

            ch = fgetc(source_file);

            if (ch != '0' && ch != '1')
            {
                is_valid = 0;
            }

            while (isalnum(ch))
            {
                if (index < MAX_TOKEN_SIZE - 1)
                {
                    token.lexeme[index++] = ch;
                }

                if (ch != '0' && ch != '1')
                {
                    is_valid = 0;
                }

                ch = fgetc(source_file);
            }

            if (ch != EOF)
            {
                ungetc(ch, source_file);
            }

            token.lexeme[index] = '\0';

            if (is_valid)
            {
                token.type = BINARY_CONSTANT;
            }
            else
            {
                setLexicalError(&token, "Invalid binary constant");
            }

            return token;
        }

        if (ch != EOF)
        {
            ungetc(ch, source_file);
        }
    }

    /* Decimal / octal / floating point */
    while ((ch = fgetc(source_file)) != EOF)
    {
        if (isdigit(ch))
        {
            if (index < MAX_TOKEN_SIZE - 1)
            {
                token.lexeme[index++] = ch;
            }
        }
        else if (ch == '.')
        {
            if (has_dot)
            {
                is_valid = 0;
            }

            has_dot = 1;

            if (index < MAX_TOKEN_SIZE - 1)
            {
                token.lexeme[index++] = ch;
            }
        }
        else if (isalpha(ch))
        {
            is_valid = 0;

            if (index < MAX_TOKEN_SIZE - 1)
            {
                token.lexeme[index++] = ch;
            }
        }
        else
        {
            ungetc(ch, source_file);
            break;
        }
    }

    token.lexeme[index] = '\0';

    if (!is_valid)
    {
        setLexicalError(&token, "Invalid numeric constant");
    }
    else if (has_dot)
    {
        token.type = FLOAT_CONSTANT;
    }
    else if (token.lexeme[0] == '0' &&
             token.lexeme[1] != '\0')
    {
        int i;

        for (i = 1; token.lexeme[i] != '\0'; i++)
        {
            if (token.lexeme[i] < '0' ||
                token.lexeme[i] > '7')
            {
                is_valid = 0;
                break;
            }
        }

        if (is_valid)
        {
            token.type = OCTAL_CONSTANT;
        }
        else
        {
            setLexicalError(&token, "Invalid octal constant");
        }
    }
    else
    {
        token.type = INTEGER_CONSTANT;
    }

    return token;
}
