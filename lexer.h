#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

#define MAX_TOKEN_SIZE 200

typedef enum
{
    KEYWORD,
    IDENTIFIER,

    INTEGER_CONSTANT,
    OCTAL_CONSTANT,
    HEX_CONSTANT,
    BINARY_CONSTANT,
    FLOAT_CONSTANT,

    OPERATOR,
    SPECIAL_CHARACTER,

    STRING_LITERAL,
    CHARACTER_CONSTANT,

    COMMENT,
    PREPROCESSOR,
    HEADER_FILE,

    UNKNOWN,
    ENDFILE

} TokenType;

typedef struct
{
    char lexeme[MAX_TOKEN_SIZE];
    TokenType type;
    int line_number;
    char error_message[MAX_TOKEN_SIZE];
} Token;

/* Lexer state is owned by scanner.c */
extern FILE *source_file;
extern int current_line;
extern int expecting_header;

void initializeLexer(FILE *file);
Token getNextToken(void);

int isKeyword(const char *word);
Token scanIdentifierOrKeyword(int first_char);
Token scanNumber(int first_char);

Token scanOperator(int first_char);
Token scanSingleLineComment(int first_char);
Token scanMultiLineComment(int first_char, int second_char);

Token scanSpecialCharacter(int ch);

Token scanStringLiteral(void);
Token scanCharacterConstant(void);

Token scanPreprocessor(void);
Token scanHeaderFile(int first_char);

void setLexicalError(Token *token, const char *message);

const char *getTokenTypeName(TokenType type);
const char *getDetailedTokenName(Token token);

#endif
