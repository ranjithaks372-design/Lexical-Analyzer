#include "lexer.h"

Token scanOperator(int first_char)
{
    Token token = {0};
    int ch;
    int third;

    token.line_number = current_line;
    token.lexeme[0] = first_char;
    token.lexeme[1] = '\0';

    ch = fgetc(source_file);

    /* Comments */
    if (first_char == '/' && ch == '/')
    {
        return scanSingleLineComment(first_char);
    }

    if (first_char == '/' && ch == '*')
    {
        return scanMultiLineComment(first_char, ch);
    }

    /* Three-character operators: <<= and >>= */
    if ((first_char == '<' && ch == '<') ||
        (first_char == '>' && ch == '>'))
    {
        third = fgetc(source_file);

        if (third == '=')
        {
            token.lexeme[1] = ch;
            token.lexeme[2] = third;
            token.lexeme[3] = '\0';
            token.type = OPERATOR;
            return token;
        }

        if (third != EOF)
        {
            ungetc(third, source_file);
        }
    }

    /* Two-character operators */
    if ((first_char == '=' && ch == '=') ||
        (first_char == '!' && ch == '=') ||
        (first_char == '<' && ch == '=') ||
        (first_char == '>' && ch == '=') ||
        (first_char == '+' && ch == '+') ||
        (first_char == '-' && ch == '-') ||
        (first_char == '+' && ch == '=') ||
        (first_char == '-' && ch == '=') ||
        (first_char == '*' && ch == '=') ||
        (first_char == '/' && ch == '=') ||
        (first_char == '%' && ch == '=') ||
        (first_char == '&' && ch == '&') ||
        (first_char == '|' && ch == '|') ||
        (first_char == '&' && ch == '=') ||
        (first_char == '|' && ch == '=') ||
        (first_char == '^' && ch == '=') ||
        (first_char == '<' && ch == '<') ||
        (first_char == '>' && ch == '>') ||
        (first_char == '-' && ch == '>'))
    {
        token.lexeme[1] = ch;
        token.lexeme[2] = '\0';
        token.type = OPERATOR;
        return token;
    }

    /* Second character was not part of the operator */
    if (ch != EOF)
    {
        ungetc(ch, source_file);
    }

    token.type = OPERATOR;

    return token;
}
