#include "lexer.h"

Token scanSingleLineComment(int first_char)
{
    Token token = {0};
    int index = 0;
    int ch;

    token.line_number = current_line;
    token.lexeme[index++] = first_char;
    token.lexeme[index++] = '/';

    while ((ch = fgetc(source_file)) != EOF && ch != '\n')
    {
        if (index < MAX_TOKEN_SIZE - 1)
        {
            token.lexeme[index++] = ch;
        }
    }

    token.lexeme[index] = '\0';
    token.type = COMMENT;

    if (ch == '\n')
    {
        current_line++;
    }

    return token;
}

Token scanMultiLineComment(int first_char, int second_char)
{
    Token token = {0};
    int index = 0;
    int ch;
    int previous = 0;
    int closed = 0;

    token.line_number = current_line;
    token.lexeme[index++] = first_char;
    token.lexeme[index++] = second_char;

    while ((ch = fgetc(source_file)) != EOF)
    {
        if (ch == '\n')
        {
            current_line++;
        }

        if (index < MAX_TOKEN_SIZE - 1)
        {
            token.lexeme[index++] = ch;
        }

        if (previous == '*' && ch == '/')
        {
            closed = 1;
            break;
        }

        previous = ch;
    }

    token.lexeme[index] = '\0';

    if (closed)
    {
        token.type = COMMENT;
    }
    else
    {
        setLexicalError(&token, "Unterminated comment");
    }

    return token;
}
