#ifndef FUNCTIONS
#define FUNCTIONS

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define SIZE 1024

typedef struct{
    char keyword[SIZE];
    int order[SIZE];
    int length;
} Keyword;

FILE *open_file(const char * file);

char * get_keyword_from_file(FILE* fp);

char * get_sentence_from_file(FILE* fp);

char ** build_matrix(char * keyword, char * sent, int * row, int * col);

Keyword* get_order_from_keyword( char *keyword);

char * get_encrypted_text(char **mat,int row,int col,Keyword* SortKeyword);

void print_result(const char *output_file,char ** mat,int row,int col,char *encrypted_text);

void clean_up(char **mat,int row,char *keyword,char *sentence,Keyword *SortKeyword,char *encrypted_text);


#endif