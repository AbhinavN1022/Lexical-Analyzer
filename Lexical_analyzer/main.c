#include"Header.h"

int error_flag = 0;

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Pass the file name\n");
        return  0;
    }

    char filename[20];
    strcpy(filename,argv[1]);
    char *ptr = strstr(filename,".c");

    if((ptr == NULL) || ((strcpy(ptr,".c"))!=0))
    {
        printf("pass only .c files\n");
        return  0;
    }

    FILE *fptr = fopen(filename,"r");
    if(fptr == NULL)
    {
        printf("Failed\n");
        return 0;
    }

    lexical_analyser(fptr);
    fclose(fptr);

    if(error_flag)
    {
        printf("Lexical analysis completed. Invalid tokens found.\n");
    }
    else
    {
        printf("Lexical analysis completed successfully.\n");
    }

    return 0;
}