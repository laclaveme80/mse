#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include <stdlib.h>
// funcoes
int check_file(const char *arquivo);
char** get_text(const char *arquivo, int *linhas);
void print_text(char **texto, int linhas);
void free_text(char **strings, int lines);
int alloc(char **vetor, int *capacidade);
int add_vetor(char **vetor, int *capacidade, char c, int x);
int rem_vetor(char **vetor, int *capacidade, int x);
int save_text(const char *arquivo, char **texto, int linhas);
#endif
