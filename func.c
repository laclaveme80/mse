#include <stdio.h>
#include "func.h"
#include <stdlib.h>
#include <string.h>

// apenas veificação de arquivo
int check_file(const char *arquivo){
    FILE* fp = fopen(arquivo, "r");
    if(fp == NULL){
        perror("arquivo nao existe");
        return 1;
    }
    fclose(fp);
    return 0;
}
// le o arquivo e retorna para uma matriz
char** get_text(const char *arquivo, int *linhas){
    FILE* fp = fopen(arquivo, "r");
    if(fp == NULL){
        perror("erro ao abrir o arquivo");
        return NULL;
    }
    char *temp = NULL;
    int c;
    int lines = 0;
    int chars = 255;
    int i = 0;
    int max_l = 100;
    char *string =  malloc(chars * sizeof(char));
    char **matrix = malloc(max_l *sizeof(char*));

    while((c = fgetc(fp)) != EOF){
        if (c == '\n'){
            string[i] = '\0';
            if (lines >= max_l -1){
                max_l *=2;
                char **tmp = realloc(matrix, max_l * sizeof(char*));
                if (tmp == NULL){
                    perror("erro de alocacao da memoria da matriz");
                    return NULL;
                }
                matrix = tmp;
            }
            matrix[lines] = malloc((i + 1) * sizeof(char));
            if (matrix[lines] == NULL){
                perror("erro ao alocar mem para linha");
                fclose(fp);
                return NULL;
            }
            strcpy(matrix[lines], string);
            lines++;
            i = 0;
        }else {
            if (i >= chars - 1){
                chars*=2;
                temp = realloc(string, chars * sizeof(char));
                if (temp == NULL){
                    perror("erro ao alocar memoria da string");
                    for(int k = 0; k < lines; k++) free(matrix[k]);
                    free(matrix);
                    return NULL;
                }
                string = temp;
            }
            string[i] = c;
            i++;
        }
    }
    if (i > 0) {
        string[i] = '\0';
        if (lines >= max_l - 1) {
            max_l *= 2;
            char **tmp = realloc(matrix, max_l * sizeof(char*));
            if (tmp == NULL){
                fclose(fp);
                free(string);
                return NULL;
            }
            matrix = tmp;
        }
        matrix[lines] = malloc((i + 1) * sizeof(char));
        strcpy(matrix[lines], string);
        lines++;
    }
    fclose(fp);
    free(string);
    *linhas = lines;
    return matrix;
}
// ele faz o print no console a matriz
void print_text(char **texto, int linhas){
    for(int x = 0; x < linhas; x++){
        printf("%s\n", texto[x]);
    }

}
// libera a memoria da matriz
void free_text(char **strings, int lines){
    for(int n = 0; n < lines; n++){
        if(strings[n] != NULL){
            free(strings[n]);
        }
    }
    free(strings);
}
// aloca memoria
int alloc(char **vetor, int *capacidade){
    *capacidade +=1;
    char *x = realloc(*vetor, (*capacidade) * sizeof(char));
    if (x == NULL){
        return 1;
    }
    *vetor = x;
    return 0;
}
// adiciona um character num char vetor
int add_char(char **vetor, int *capacidade, char c, int x){
    if(alloc(vetor, capacidade)== 1){
        perror("erro ao adicionar character");
        return 1;
    }
    for(int i = *capacidade-1; i > x; i--){
        (*vetor)[i] = (*vetor)[i-1];
    }
    (*vetor)[x] = c;
    return 0;
}
// remove um caracter de um char vetor
int rem_char(char **vetor, int *capacidade, int x){
    int c = x-1;
    if(c <0){
        return 0;
    }
    for(int i = c; i < *capacidade-1; i++){
        (*vetor)[i] = (*vetor)[i+1];
    }
    (*vetor)[*capacidade-2] = '\0';
    int nova_capacidade = (*capacidade)-1;
    char *tmp = realloc(*vetor, nova_capacidade * sizeof(char));
    if(tmp == NULL){
        perror("erro ao deletar character");
        return 1;
    }
    *vetor = tmp;
    *capacidade = nova_capacidade;
    return 0;
}
// passa o matriz para um arquivo
int save_text(const char *arquivo, char **texto, int linhas){
    FILE *fp = fopen(arquivo, "w");
    if (fp  == NULL){
        return 1;
    }

    for (int x = 0; x < linhas; x++){
        if (texto[x] != NULL){
            fprintf(fp, "%s\n", texto[x]);
        }else {
            fprintf(fp, "\n");
        }
    }
    fclose(fp);
    return 0;
}

int add_line(char ***matriz, int *linhas, int y){
    int nova_linhas = (*linhas) +1;
    char **temp = realloc(*matriz, nova_linhas * sizeof(char*));
    if (temp == NULL){
        printf("erro ao adicionar linha\n");
        return 1;
    }
    *matriz = temp;
    for(int i = nova_linhas-1; i > y; i--){
        (*matriz)[i] = (*matriz)[i-1];
    }
    (*matriz)[y] = malloc( 1 * sizeof(char));
    if ((*matriz)[y] == NULL){
        printf("erro ao alocar mem para linha\n");
        return 1;
    }
    (*matriz)[y][0] = '\0';
    *linhas = nova_linhas;
    return 0;
}
