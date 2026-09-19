#include "lexer.h"
#include <string.h>

void setLexicalError(Token *token, const char *message)
{
    token->type = UNKNOWN;

    strncpy(token->error_message,
            message,
            MAX_TOKEN_SIZE - 1);

    token->error_message[MAX_TOKEN_SIZE - 1] = '\0';
}

const char *getTokenTypeName(TokenType type)
{
    switch (type)
    {
        case KEYWORD:             return "KEYWORD";
        case IDENTIFIER:          return "IDENTIFIER";
        case INTEGER_CONSTANT:    return "INTEGER_CONSTANT";
        case OCTAL_CONSTANT:      return "OCTAL_CONSTANT";
        case HEX_CONSTANT:        return "HEX_CONSTANT";
        case BINARY_CONSTANT:     return "BINARY_CONSTANT";
        case FLOAT_CONSTANT:      return "FLOAT_CONSTANT";
        case OPERATOR:            return "OPERATOR";
        case SPECIAL_CHARACTER:   return "SPECIAL_CHARACTER";
        case STRING_LITERAL:      return "STRING_LITERAL";
        case CHARACTER_CONSTANT:  return "CHARACTER_CONSTANT";
        case COMMENT:             return "COMMENT";
        case PREPROCESSOR:        return "PREPROCESSOR";
        case HEADER_FILE:         return "HEADER_FILE";
        case UNKNOWN:             return "UNKNOWN";
        case ENDFILE:             return "ENDFILE";
        default:                  return "UNKNOWN";
    }
}

const char *getDetailedTokenName(Token token)
{
    if (token.type == KEYWORD) return "Keyword";
    if (token.type == IDENTIFIER) return "Identifier";
    if (token.type == INTEGER_CONSTANT) return "Integer Constant";
    if (token.type == OCTAL_CONSTANT) return "Octal Constant";
    if (token.type == HEX_CONSTANT) return "Hexadecimal Constant";
    if (token.type == BINARY_CONSTANT) return "Binary Constant";
    if (token.type == FLOAT_CONSTANT) return "Floating Point Constant";
    if (token.type == STRING_LITERAL) return "String Literal";
    if (token.type == CHARACTER_CONSTANT) return "Character Constant";

    if (token.type == COMMENT)
    {
        if (token.lexeme[1] == '/')
            return "Single Line Comment";
        else
            return "Multi Line Comment";
    }

    if (token.type == PREPROCESSOR)
        return "Preprocessor Directive";

    if (token.type == HEADER_FILE)
        return "Header File";

    if (token.type == UNKNOWN)
    {
        if (token.error_message[0] != '\0')
            return "Lexical Error";

        return "Unknown Token";
    }

    if (token.type == SPECIAL_CHARACTER)
    {
        if (strcmp(token.lexeme, "(") == 0) return "Open Parenthesis";
        if (strcmp(token.lexeme, ")") == 0) return "Close Parenthesis";
        if (strcmp(token.lexeme, "{") == 0) return "Open Brace";
        if (strcmp(token.lexeme, "}") == 0) return "Close Brace";
        if (strcmp(token.lexeme, "[") == 0) return "Open Bracket";
        if (strcmp(token.lexeme, "]") == 0) return "Close Bracket";
        if (strcmp(token.lexeme, ";") == 0) return "Semicolon / Delimiter";
        if (strcmp(token.lexeme, ",") == 0) return "Comma / Delimiter";
        if (strcmp(token.lexeme, ":") == 0) return "Colon";
        if (strcmp(token.lexeme, "?") == 0) return "Question Mark";
        if (strcmp(token.lexeme, ".") == 0) return "Dot";
    }

    if (token.type == OPERATOR)
    {
        if (strcmp(token.lexeme, "+") == 0) return "Addition Operator";
        if (strcmp(token.lexeme, "-") == 0) return "Subtraction Operator";
        if (strcmp(token.lexeme, "*") == 0) return "Multiplication Operator";
        if (strcmp(token.lexeme, "/") == 0) return "Division Operator";
        if (strcmp(token.lexeme, "%") == 0) return "Modulus Operator";
        if (strcmp(token.lexeme, "=") == 0) return "Assignment Operator";
        if (strcmp(token.lexeme, "==") == 0) return "Equality Operator";
        if (strcmp(token.lexeme, "!=") == 0) return "Not Equal Operator";
        if (strcmp(token.lexeme, "<") == 0) return "Less Than Operator";
        if (strcmp(token.lexeme, ">") == 0) return "Greater Than Operator";
        if (strcmp(token.lexeme, "<=") == 0) return "Less Than or Equal Operator";
        if (strcmp(token.lexeme, ">=") == 0) return "Greater Than or Equal Operator";
        if (strcmp(token.lexeme, "&&") == 0) return "Logical AND Operator";
        if (strcmp(token.lexeme, "||") == 0) return "Logical OR Operator";
        if (strcmp(token.lexeme, "!") == 0) return "Logical NOT Operator";
        if (strcmp(token.lexeme, "++") == 0) return "Increment Operator";
        if (strcmp(token.lexeme, "--") == 0) return "Decrement Operator";
        if (strcmp(token.lexeme, "&") == 0) return "Bitwise AND Operator";
        if (strcmp(token.lexeme, "|") == 0) return "Bitwise OR Operator";
        if (strcmp(token.lexeme, "^") == 0) return "Bitwise XOR Operator";
        if (strcmp(token.lexeme, "~") == 0) return "Bitwise NOT Operator";
        if (strcmp(token.lexeme, "<<") == 0) return "Left Shift Operator";
        if (strcmp(token.lexeme, ">>") == 0) return "Right Shift Operator";
        if (strcmp(token.lexeme, "+=") == 0) return "Addition Assignment Operator";
        if (strcmp(token.lexeme, "-=") == 0) return "Subtraction Assignment Operator";
        if (strcmp(token.lexeme, "*=") == 0) return "Multiplication Assignment Operator";
        if (strcmp(token.lexeme, "/=") == 0) return "Division Assignment Operator";
        if (strcmp(token.lexeme, "%=") == 0) return "Modulus Assignment Operator";
        if (strcmp(token.lexeme, "&=") == 0) return "Bitwise AND Assignment Operator";
        if (strcmp(token.lexeme, "|=") == 0) return "Bitwise OR Assignment Operator";
        if (strcmp(token.lexeme, "^=") == 0) return "Bitwise XOR Assignment Operator";
        if (strcmp(token.lexeme, "<<=") == 0) return "Left Shift Assignment Operator";
        if (strcmp(token.lexeme, ">>=") == 0) return "Right Shift Assignment Operator";
        if (strcmp(token.lexeme, "->") == 0) return "Structure Pointer Operator";
    }

    if (token.type == ENDFILE)
        return "End Of File";

    return "Unknown Token";
}
