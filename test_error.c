#include <stdio.h>

int main()
{
    /* Invalid octal */
    int a = 098;

    /* Invalid binary */
    int b = 0b102;

    /* Invalid hexadecimal */
    int c = 0xG1;

    /* Invalid numeric constant */
    int d = 123abc;

    /* Multiple decimal points */
    float e = 12.3.4;

    /* Invalid character constant */
    char f = 'AB';

    /* Empty character constant */
    char g = '';

    return 0;
}

