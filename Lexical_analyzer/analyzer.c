#include"Header.h"

extern int error_flag;

char *keywords[] =
{
    "auto", "break", "case", "char", "const",
    "continue", "default", "do", "double", "else",
    "enum", "extern", "float", "for", "goto",
    "if", "inline", "int", "long", "register",
    "restrict", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while",NULL
};

char operator[] = "+-/%^!~,<>&|";
char symbol[] = "{}[]";
char special[] = "();";
char delim[] = "\n\t \r";

void lexical_analyser(FILE *fptr)
{
    char line[150];
    while(fscanf(fptr,"%[^\n]\n",line) != EOF)
    {
        if(line[0] == '#')
        {
            printf("\nHeader file detected\n");
            continue;
        }
        check_type(line);
    }
}

void check_type(char *line)
{
    char *temp = line;
    char arr[50];

    while(*temp)
    {
        if(strchr(delim,*temp))
        {
            temp++;
            continue;
        }
        int i = 0 ;
        //string
        if(*temp == '"')
        {
            temp++;
            while(*temp && *temp != '"')
            {
                arr[i++] = *temp++;
            }
            arr[i] = '\0';

            if(*temp == '"')
            {
                printf("%s : STRING\n",arr);
                temp++;
            }
            else
            {
                  error_flag = 1;
            }
            continue;
        }
        //Character
        if(*temp == '\'')
        {
            temp++;
            arr[i++] = *temp++;
            if(*temp == '\'')
            {
                printf("%c : CHAR\n",arr[0]);
                temp++;
            }
            else
            {
                error_flag=1;
            }
            continue;
        }
        //assignment
        if(is_assignment(*temp))
        {
            printf("%c : ASSIGNMENT\n",*temp);
            temp++;
            continue;
        }
        if(is_operator(*temp))
        {
            printf("%c : OPERATOR\n", *temp);
            temp++;
            continue;
        }
        if(is_symbol(*temp))
        {
            printf("%c : SYMBOL\n", *temp);
            temp++;
            continue;
        }
        if(is_special(*temp))
        {
            printf("%c : SPECIAL\n", *temp);
            temp++;
            continue;
        }

        while(*temp && !strchr(delim,*temp) && !is_assignment(*temp) && !is_special(*temp)&& !is_symbol(*temp)&& !is_operator(*temp))
        {
            arr[i++] = *temp++;
        }
        arr[i] = '\0';

        if(i == 0)
        continue;
        if(is_keyword(arr))
        continue;
        if(is_binary(arr))
        continue;
        if(is_hexa(arr))
        continue;
        if(is_octal(arr))
        continue;
        if(is_digit(arr))
        continue;
        if(is_identifier(arr))
        continue;
        printf("%s : UNVALID TOKEN\n",arr);
        error_flag = 1;
    }
}

//Support function
int is_identifier(char *token)
{
    int i = 0;
    if(!(isalpha(token[0]) || token[0] == '_'))
    {
        return 0;
    }
    for(i = 1 ; token[i]!='\0' ; i++)
    {
        if(!(isalnum(token[i]) || token[i]=='_'))
        return 0;
    }
    printf("%s : IDENTIFIER\n",token);
    return 1;
}

int is_keyword(char *token)
{
    for(int i=0 ; keywords[i] != NULL ; i++)
    {
        if(strcmp(token,keywords[i]) == 0)
        {
            printf("%s : KEYWORD\n",token);
            return 1;
        }
    }
    return 0;
}

int is_digit(char *token)
{
    int dot = 0, digit = 0;
    for(int i=0 ; token[i]!='\0' ; i++)
    {
        if(token[i] == '.')
        dot++;
        else if(token[i]>='0' && token[i]<='9')
        digit++;
        else
        return 0;
    }
    if(digit == 0)
    return 0;
    if(dot == 0)
    printf("%s : INTEGER\n",token);
    else if(dot == 1)
    printf("%s : float",token);
    else
    {
        printf("ERROR : Invalid number %s\n",token);
        error_flag = 1;
        return 0;
    }
    return 1;
}
int is_operator(char ch)
{
   for(int i=0 ; operator[i]!='\0' ; i++)
   {
      if(ch == operator[i])
      return 1;
   }
   return 0;
}
int is_assignment(char ch)
{
    return (ch == '=');
}
int is_symbol(char ch)
{
    for(int i=0 ; symbol[i]!='\0' ; i++)
    {
        if(ch == symbol[i])
        return 1;
    }
    return 0;
}
int is_special(char ch)
{
    for(int i=0 ; special[i]!='\0' ; i++)
    {
        if(ch == special[i])
        return 1;
    }
    return 0;
}
int is_binary(char *num)
{
    if(strncmp(num,"0b",2) != 0 && strncmp(num,"0B",2) !=0 )
    return 0;
    if(num[2] == '\0')
    return 0;
    for(int i=2 ; num[i]!='\0' ; i++)
    {
        if(num[i]!='0' && num[i]!='1')
        return 0;
    }
    printf("%s : BINARY",num);
    return 1;
}
int is_octal(char *num)
{
    if(strncmp(num,"0X",2)!=0 && strncmp(num,"0x",2) !=0 )
    return 0;
    if(num[2] == '\0')
    return 0;
    for(int i=1 ; num[i]!='\0' ; i++)
    {
        if(num[i]<'0' && num[i]>'7')
        return 0;
    }
    printf("%s : OCTAL",num);
    return 1;
}
int is_hexa(char *num)
{
    if(strncmp(num,"0x",2)!=0 && strncmp(num,"0X",2)!=0)
    return 0;
    if(num[2]=='\0')
    return 0;
    for(int i=2;num[i]!='\0';i++)
    {
        if(!((num[i]>='0' && num[i]<='9')||(num[i]>='a'&&num[i]<='f')||(num[i]>='A'&&num[i]<='F')))
        return 0;
    }
    printf("%s : HEXADECIMAL\n",num);
    return 1;
}