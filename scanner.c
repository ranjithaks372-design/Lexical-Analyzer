#include "lexer.h"
#include <ctype.h>
#include <string.h>

/* Shared lexer state */
FILE *source_file = NULL;
int current_line = 1;
int expecting_header = 0;

void initializeLexer(FILE *file)
{
    source_file = file;
    current_line = 1;
    expecting_header = 0;
}

Token getNextToken(void)
{
    Token token;
    int ch;

    memset(&token, 0, sizeof(Token));

    token.lexeme[0] = '\0';
    token.type = UNKNOWN;
    token.line_number = current_line;

    if (source_file == NULL)
    {
        strcpy(token.lexeme, "EOF");
        token.type = ENDFILE;
        return token;
    }

    while ((ch = fgetc(source_file)) != EOF)
    {
        /* Skip spaces, tabs and carriage returns */
        if (ch == ' ' || ch == '\t' || ch == '\r')
        {
            continue;
        }

        /* Track line number */
        if (ch == '\n')
        {
            current_line++;
            continue;
        }

        token.line_number = current_line;

        /* Identifier or keyword */
        if (isalpha(ch) || ch == '_')
        {
            return scanIdentifierOrKeyword(ch);
        }

        /* Preprocessor directive */
        if (ch == '#')
        {
            return scanPreprocessor();
        }

        /* Header after #include */
        if (expecting_header && (ch == '<' || ch == '"'))
        {
            return scanHeaderFile(ch);
        }

        /* String literal */
        if (ch == '"')
        {
            return scanStringLiteral();
        }

        /* Character constant */
        if (ch == '\'')
        {
            return scanCharacterConstant();
        }

        /* Number */
        if (isdigit(ch))
        {
            return scanNumber(ch);
        }

        /* Operators and comments */
        if (ch == '+' || ch == '-' ||
            ch == '*' || ch == '/' ||
            ch == '%' || ch == '=' ||
            ch == '<' || ch == '>' ||
            ch == '!' || ch == '&' ||
            ch == '|' || ch == '^' ||
            ch == '~')
        {
            return scanOperator(ch);
        }

        /* Special characters */
        if (ch == '(' || ch == ')' ||
            ch == '{' || ch == '}' ||
            ch == '[' || ch == ']' ||
            ch == ';' || ch == ',' ||
            ch == ':' || ch == '?' ||
            ch == '.')
        {
            return scanSpecialCharacter(ch);
        }

        /* Unknown character */
        token.lexeme[0] = ch;
        token.lexeme[1] = '\0';
        setLexicalError(&token, "Unknown character");

        return token;
    }

    strcpy(token.lexeme, "EOF");
    token.type = ENDFILE;
    token.line_number = current_line;

    return token;
}
