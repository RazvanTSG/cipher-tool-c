#include "functions.h"
#include <stdio.h>

int main()
{
    int row,col;
    const char * input_file_1="input_text_a.txt";
    const char * output_file="output_text_a.txt";
    FILE *f=open_file(input_file_1);
    char * keyword=get_keyword_from_file(f);
    char * sentence=get_sentence_from_file(f);
    char **mat=build_matrix(keyword,sentence,&row,&col);
    Keyword * SortKeyword=get_order_from_keyword(keyword);
    char * encrypted_text=get_encrypted_text(mat,row,col,SortKeyword);
    print_result(output_file, mat,row,col,encrypted_text);
    clean_up(mat,row,keyword,sentence,SortKeyword,encrypted_text);
    fclose(f);
}