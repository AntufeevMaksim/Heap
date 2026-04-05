
#include "heap.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    char* big = (char*) my_malloc(100);
    my_free(big);

    char* small1 = (char*) my_malloc(4);
    char* small2 = (char*) my_malloc(4);


    int* a = (int*) my_malloc(sizeof(int));
    *a = 4;

    int* b = (int*) my_malloc(sizeof(int));
    *b = 4;

    int* c = (int*) my_malloc(sizeof(int));
    *c = *a + *b;

    my_free(a);
    my_free(b);

    int c_stack = *c;

    my_free(c);

    int* a2 = (int*) my_malloc(sizeof(int));
    *a2 = 6;

    int* b2 = (int*) my_malloc(sizeof(int));
    *b2 = 6;

    int* c2 = (int*) my_malloc(sizeof(int));
    *c2 = *a2 + *b2;

    my_free(a2);
    my_free(b2);

    int c_stack2 = *c2;

    my_free(c2);


    char* big_string = (char*) my_malloc(256*1024);
    
    char* big_string2 = (char*) malloc(256*1024);

    srand(98);

    for (int i = 0; i < 256*1024; ++i)
    {
        char c = (char) rand() % 256;
        big_string[i] = c;
        big_string2[i] = c;
    }

    for (int i = 0; i < 256*1024; ++i)
    {
        if (big_string[i] != big_string2[i])
        {
            printf("ERR\n");
        }
    }

    my_free(big_string);
    free(big_string2);


    printf("%d", c_stack);
}
