#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "draw.h"
#include "config.h"

// define os atalhos do editor
#define CTRL_Q 17
#define CTRL_S 19

int main(int argc, char *argv[]) {
    //verificação padrao
    if (argc < 2){
        printf("parametros insuficientes...\n");
        return 1;
    }
    if (check_file(argv[1]) == 1){
        return 1;
    }
    // gerando a matriz
    int linhas = 0;
    char **texto = get_text(argv[1], &linhas);

    // preparando para o ncurses
    start_base();

    int term_color = 0;
    // verificando se o term possui cor
    // retornara 1 se sim
    start_colors(&term_color);

    int max_x = 0, max_y = 0;
    int cX = 0, cY = 0;
    int capacidade = 0;
    capacidade = strlen(texto[cY])+1;
    char *vetor = texto[cY];
    int c;
    int off_y = 0;
    // loop principal
    while((c = getch()) != CTRL_Q){
        getmaxyx(stdscr, max_y, max_x);
        clear();
        switch (c) {
            case KEY_UP:
                if(cY > 0){
                    cY--;
                }
                else if(off_y >0){
                    off_y--;
                }
                vetor = texto[cY];
                capacidade = strlen(vetor) + 1;
                if (cX > strlen(vetor)) cX = strlen(vetor);
                break;
            case KEY_DOWN:
                if(cY < max_y -1 && cY < linhas-1){
                    cY++;
                }
                else if (off_y+cY <linhas-1){
                    off_y++;
                }
                vetor = texto[cY];
                capacidade = strlen(vetor) + 1;
                if (cX > strlen(vetor)) cX = strlen(vetor);
                break;
            case KEY_LEFT:
                if(cX > 0)cX--;
                break;
            case KEY_RIGHT:
                if(cX < max_x -1 && cX < strlen(vetor))cX++;
                break;
            default:
                vetor = texto[cY];
                capacidade = strlen(texto[cY])+1;
                if (c == CTRL_S){
                    save_text(argv[1], texto, linhas);
                }
                else if(c == KEY_BACKSPACE){
                    if(cX > 0){
                        if(rem_vetor(&vetor, &capacidade, cX) == 1){
                            endwin();
                            free_text(texto, linhas);
                            return 1;
                        }
                        cX--;
                    }
                    break;
                }
                if (c >= 32 && c <= 126) {
                    if(add_vetor(&vetor, &capacidade, c, cX) == 1){
                        endwin();
                        free_text(texto, linhas);
                        return 1;
                    }
                    vetor[capacidade -1] = '\0';
                    texto[cY] = vetor;
                    if(cX < max_x -1) cX++;
                    break;
                }
        }
        if (term_color == 1){
            if (theme > 3){
                draw_text(texto, linhas, max_y,  off_y, 1, bold);
            } else{
                bkgd(COLOR_PAIR(theme));
                draw_text(texto, linhas, max_y,  off_y, theme, bold);
            }
        }else{
            draw_minimal(texto, linhas, max_y,  off_y);
        }
        move(cY, cX);
        refresh();

    }
    // fechamento
    endwin();
    free_text(texto, linhas);
    return 0;
}
