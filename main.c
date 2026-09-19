#include "lexer.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *file;
    Token token;

    if (argc != 2)
    {
        printf("Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    file = fopen(argv[1], "r");

    if (file == NULL)
    {
        perror("fopen");
        return 1;
    }

    initializeLexer(file);

    printf("%-8s %-35s %s\n", "Line", "Token Type", "Lexeme");
    printf("---------------------------------------------------------------\n");

    while (1)
    {
        token = getNextToken();

        if (token.type == ENDFILE)
        {
            break;
        }

        if (token.type == UNKNOWN)
        {
            printf("Line %-5d %-35s %s\n",
                   token.line_number,
                   getDetailedTokenName(token),
                   token.error_message);
        }
        else
        {
            printf("Line %-5d %-35s %s\n",
                   token.line_number,
                   getDetailedTokenName(token),
                   token.lexeme);
        }
    }

    fclose(file);

    return 0;
}
