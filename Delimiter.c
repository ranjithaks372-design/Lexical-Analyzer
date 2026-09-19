#include "lexer.h"

Token scanSpecialCharacter(int ch)
{
    Token token = {0};

    token.lexeme[0] = ch;
    token.lexeme[1] = '\0';
    token.type = SPECIAL_CHARACTER;
    token.line_number = current_line;

    return token;
}
