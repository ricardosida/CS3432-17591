#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_LIMIT 1000

int count_tokens(char* str);
char** tokenize(char* str);
char *word_start(char* str);
bool non_delim_character(char c);
bool delim_character(char c);
char *end_word(char* str);
char *copy_str(char *inStr, short len);
void print_all_tokens(char** tokens);

int main()
{
    /*Ask for input*/
    char* str = (char*) malloc(MAX_LIMIT * sizeof(char));
    scanf("%999[^\n]", str);
    
    /*I send the pointer to tokenize*/
    tokenize(str);

}

char** tokenize(char* str) {
    /*First we get the number of tokens*/
    int num_tokens = count_tokens(str);
    /*I create a new pointer of pointers with the number of tokens avaiable as length*/
    char ** tokens = (char**) malloc((num_tokens+1)*sizeof(char*));
    /*Get the initial word and the initial end of word*/
    char *initial_word = word_start(str);
    char *last_word  = end_word(initial_word);
    for (int i = 0; i < num_tokens; i++) {
        /*Now we subtract the addreses of both pointers*/
        int difference = (last_word - initial_word);
        /*send the length of the word and the first letter to copy method, and assign the pointer to the token variable*/
        tokens[i]  = copy_str(initial_word, difference);
        /*we get the initial and last letter of each word*/
        initial_word = word_start(last_word);
        last_word  = end_word(initial_word);
    }

    /*Print all tokens*/
    print_all_tokens(tokens);
 
    /*return the char***/
    return tokens;

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
    /*Call recursively until i get the start of the word*/
    char *pointer = str; 
    if (non_delim_character(*pointer) == true){
        char *p = pointer;
        return p;
    }
    return word_start(pointer +1);
    

}

/* Returns a pointer to the first space character of the zero
terminated string*/
char *end_word(char* str){
    /*base case, in case pointer is at the end of array*/
    if (*str == '\0'){
        return str;
    }
    /*Call recursively until i get the end of the word*/
    char *pointer = str; 
    if (delim_character(*pointer) == true){
        char *p = pointer;
        return p;
    }
    return end_word(pointer +1);

}
// counts the number of words or tokens
int count_tokens(char* str){
    char * t; // copy the pointer to not change the original
    int size = 0;
    for (t = word_start(str) ;*t != '\0'; t++) {
        /*Every time i hit a space that means it is a new word*/
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
    /*Create a new pointer and fill it out with all the chars of the given word*/
    char* new_string = (char*) malloc(len * sizeof(char));
    for (int i = 0; i < len; i++) {
        new_string[i] = *inStr;
        inStr++;
    }

    return new_string;

}

void print_all_tokens(char** tokens){
    /*I print all tokens*/
    int i = 0;
    for (char **p = tokens; *p; p++){
        printf("Token[%d] = %s\n",i,*p);
        i++;
    }


}