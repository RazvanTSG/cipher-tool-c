#include "functions.h"

FILE *open_file(const char * file)
{
    FILE *f=fopen(file,"r");
    if(f==NULL)
    {
       perror("Error opening the file");
        exit(1);
    }
    return f;
}

char * get_keyword_from_file(FILE* fp)
{
    char buffer[SIZE];
    fgets(buffer,SIZE,fp);
    buffer[strcspn(buffer,"\n")]=0;
    char word[SIZE];
    sscanf(buffer,"%s",word);
    int l=strlen(word);
    int f[150]={};
    for(int i=0;i<l;i++)
    {
        if(!isalpha(word[i]))
        {
            printf("Invalid word(1)");
            exit(1);
        }
        if(f[(int)(word[i])]==1)
        {
            printf("Invalid word(2)");
            exit(1);
        }
        f[(int)(word[i])]=1;
    }
    char * keyword=malloc(sizeof(char)*(l+1));
    if(keyword==NULL)
    {
        perror("Memory allocation failed");
        exit(1);
    }
    strcpy(keyword,word);
    return keyword;
}

char * get_sentence_from_file(FILE* fp)
{
    char buffer[SIZE];
    fgets(buffer,SIZE,fp);
    buffer[strcspn(buffer,"\n")]=0;
    int l=strlen(buffer);
    char sentence[SIZE];
    int p=0;
    for(int i=0;i<l;i++)
    {
        if('0'<= buffer[i] && '9'>=buffer[i])
        {
            printf("Invalid input");
            exit(1);
        }
        if(isalpha(buffer[i]))
        {
            if(islower(buffer[i]))
            {
                sentence[p]=toupper(buffer[i]);
            }
            else
            {
               sentence[p]=buffer[i]; 
            }
            p+=1;
        }
    }
    sentence[p]=0;
    char * sent=malloc((p+1)*sizeof(char));
    if(sent==NULL)
    {
        perror("Memory allocation failed");
        exit(1);
    }
    strcpy(sent,sentence);
    fclose(fp);
    return sent;
}

char ** build_matrix(char * keyword, char * sent, int * row, int * col)
{
    int l1=strlen(keyword);
    int l2=strlen(sent);
    int cols=l1;
    int rows=l2/l1;
    if(l2%l1!=0)
    {
        rows+=1;
    }
    char **mat=malloc((rows)*sizeof(char*));
    if(mat==NULL)
    {
        perror("Memory allocation failed");
        exit(1);
    }
    for(int i=0;i<rows;i++)
    {
        mat[i]=malloc((cols)*sizeof(char));
        if(mat[i]==NULL)
        {
            perror("Memory allocation failed");
            exit(1);
        }
    }
    int p=0;
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
        {
            if(p<=l2-1)
            {
                mat[i][j]=sent[p];
                p+=1;
            }
            else
            {
                mat[i][j]='*';
            }
        }
    (*row)=rows;
    (*col)=cols;
    return mat;
}

Keyword* get_order_from_keyword(char *keyword)
{
    Keyword* sort_word=malloc(sizeof(Keyword));
    if(sort_word==NULL)
    {
        perror("Memory allocation failed");
        exit(1);
    }
    int l=strlen(keyword);
    (*sort_word).length=l;
    for(int i=0;i<l;i++)
    {
        int p=0;
        for(int j=0;j<l;j++)
        {
            if(keyword[j]<keyword[i])
                p+=1;
        }
        (*sort_word).order[p]=i;
    }
    strcpy((*sort_word).keyword,keyword);
    return sort_word;
}

char * get_encrypted_text(char **mat,int row,int col,Keyword* SortKeyword)
{
    char encrypted_text[SIZE];
    int p=0;
    int l=0;
    int len=strlen((*SortKeyword).keyword);
    for(int i=0;i<len;i++)
    {
        for(int j=0;j<row;j++)
        {
            if(mat[j][(*SortKeyword).order[i]]=='*')
                continue;
            encrypted_text[p]=mat[j][(*SortKeyword).order[i]];
            p+=1;
            l+=1;
            if(l%5==0)
            {
                encrypted_text[p]=' ';
                p+=1; 
                l=0;
            }
        }
    }
    encrypted_text[p]=0;
    char * allocated_encrypted_text=malloc((p+1));
    if(allocated_encrypted_text==NULL)
    {
        perror("Memory allocation failed");
        exit(1);
    }
    strcpy(allocated_encrypted_text,encrypted_text);
    return allocated_encrypted_text;
}

void print_result(const char *output_file,char ** mat,int row,int col,char *encrypted_text)
{
    FILE *f=fopen(output_file,"w");
    if(f==NULL)
    {
        perror("could not open file");
        exit(1);
    }
    fputs("The matrix is:\n",f);
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            fputc(mat[i][j],f);
        }
        fputc('\n',f);
    }
    fputs("The encrypted code is:\n",f);
    fprintf(f,"%s",encrypted_text);
    fclose(f);

}

void clean_up(char **mat,int row,char *keyword,char *sentence,Keyword* SortKeyword,char *encrypted_text)
{
    free(SortKeyword);
    for(int i=0;i<row;i++)
    {
        free(mat[i]);
    }
    free(mat);
    free(keyword);
    free(sentence);
    free(encrypted_text);
}