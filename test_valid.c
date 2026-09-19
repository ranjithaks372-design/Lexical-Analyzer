#include <stdio.h>
#include "myheader.h"
#define MAX 100
#define FLAG 0b1010
int main(void)
{
    int a = 25;
    float b = 12.50;
    int oct = 0123;
    int hex = 0x1A;
    int bin = 0b1010;
    char ch = 'A';
    char newline = '\n';
    a += 5;
    a -= 2;
    a *= 3;
    a /= 2;
    a %= 2;
    if (a == 25 && a != 0 && a <= 100 && a >= 1)
    {
        a++;
        --a;
        a <<= 1;
        a >>= 1;
    }

    int result = (a > 10) ? a : 10;

    result = a & 1;
    result = a | 2;
    result = a ^ 3;
    result = ~a;

    a &= 1;
    a |= 2;
    a ^= 3;

    int array[3] = {1, 2, 3};

    struct Student
    {
        int id;
        char grade;
    };

    struct Student s;
    struct Student *ptr = &s;

    s.id = 101;
    ptr->grade = 'A';

    printf("Hello\tWorld\n");

    // Single-line comment

    /*
       Multi-line comment
       with line tracking
    */

    return 0;
}

