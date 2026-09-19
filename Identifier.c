#include "lexer.h"
#include <ctype.h>
#include <string.h>

int isKeyword(const char *word)
{
    const char *keywords[] =
    {
        "auto", "break", "case", "char", "const", "continue",
        "default", "do", "double", "else", "enum", "extern",
        "float", "for", "goto", "if", "inline", "int", "long",
        "register", "restrict", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef",
        "union", "unsigned", "void", "volatile", "while",
        "_Bool", "_Complex", "_Imaginary"
    };

    int count = sizeof(keywords) / sizeof(keywords[0]);
    int i;

    for (i = 0; i < count; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
        {
            return 1;
        }
    }

    return 0;
}

Token scanIdentifierOrKeyword(int first_char)
{
    Token token = {0};
    int index = 0;
    int ch;

    token.line_number = current_line;
    token.lexeme[index++] = first_char;

    while (index < MAX_TOKEN_SIZE - 1)
    {
        ch = fgetc(source_file);

        if (isalnum(ch) || ch == '_')
        {
            token.lexeme[index++] = ch;
        }
        else
        {
            if (ch != EOF)
            {
                ungetc(ch, source_file);
            }

            break;
        }
    }

    token.lexeme[index] = '\0';

    if (isKeyword(token.lexeme))
    {
        token.type = KEYWORD;
    }
    else
    {
        token.type = IDENTIFIER;
    }

    return token;
}
