#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_LIMIT 20

int count_tokens(char* str);
char** tokenize(char* str);
char *word_start(char* str);
bool non_delim_character(char c);
bool delim_character(char c);
char *end_word(char* str);

int main()
{
    /*Ask fro input*/
    char str[MAX_LIMIT];
    fgets(str, MAX_LIMIT, stdin);

    /*create a pointer for the input*/
    char* pointer = str;

    /*EXCEPTION: check if first char is a space*/
    if (*pointer == ' '){
        tokenize(pointer +1);
    }else{
        tokenize(pointer);
    }

}

char** tokenize(char* str) {

    /*First we get the number of tokens*/
    int num_tokens = count_tokens(str);

    /* once we have # tokens, we call malloc*/
    char* new_string = (char*) malloc(num_tokens * sizeof(char));


    char *initial_word = word_start(str);

    printf("%c\n",*initial_word);

    
    return 0;
}


/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').
   Zero terminators are not printable (therefore false) */
bool delim_character(char c){
    if (c == ' ' || c == '\t'){
        return true;
    }
    return false;

}

/* Return true (non-zero) if c is a non-whitespace
   character (not tab or space).
   Zero terminators are not printable (therefore false) */
bool non_delim_character(char c){
    if (c != ' '|| c == '\t'){
        return true;
    }
    return false;
}

/* Returns a pointer to the first character of the next
   space-separated word*/
char *word_start(char* str){

    char *pointer = str;
    
    if (non_delim_character(*pointer) == true){
        char *p = pointer;
        return p;
    }
    word_start(pointer +1);
    
    return 0;

}

/* Returns a pointer to the first space character of the zero
terminated string*/
char *end_word(char* str){
    char *pointer = str;
    
    if (delim_character(*pointer) == true){
        char *p = pointer;
        return p;
    }
    end_word(pointer +1);
    
    return 0;
}
// counts the number of words or tokens
int count_tokens(char* str){
    char * t; // copy the pointer to not change the original
    int size = 0;

    for (t = str; *t != '\0'; t++) {
        if (delim_character(*t) == true){
            size++;
        }
    }
    size++;

    return size;


}
/* Returns a freshly allocated zero-terminated vector of freshly allocated
   space-separated tokens from zero-terminated str.
   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string"
     tokens[3] = 0
*/
char *copy_str(char *inStr, short len){
return 0;
}

void print_all_tokens(char** tokens){

}
