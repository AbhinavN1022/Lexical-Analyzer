#ifndef HEADER_H
#define HEADER_H


#include<stdio.h>
#include<string.h>
#include<ctype.h>

void lexical_analyser(FILE*fptr);
void check_type(char *line);
int is_keyword(char*token);
int is_digit(char*token);
int is_operator(char ch);
int is_assignment(char ch);
int is_symbol(char ch);
int is_special(char ch);
int is_binary(char*num);
int is_octal(char *num);
int is_hexa(char*num);
int is_identifier(char*token);


#endif