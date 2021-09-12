#include <stdio.h>
#define MAX_LIMIT 20
char** tokenize(char* str);

int main()
{
    char str[MAX_LIMIT];
    fgets(str, MAX_LIMIT, stdin);

    char* x = str;
    tokenize(x);
}

char** tokenize(char* str) {
    char* new_string = (char*) malloc(str_size * sizeof(str));
    printf("%s", new_string);
    return 1;
}