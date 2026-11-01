
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
// apenas incializando o basico
void start_base(){
    initscr();
    cbreak();
    noecho();
    raw();
    keypad(stdscr, TRUE);
    curs_set(1);
}
// paleta de cores
void start_colors(int *color){
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_WHITE, COLOR_BLUE);
        init_pair(3, COLOR_CYAN, COLOR_BLACK);
        *color = 1;
    }
}
// exibi a matriz na tela sem cores
void draw_minimal(char **strings, int lines, int max_y, int off_y){
    for(int a = 0; a < max_y; a++){
        if((a + off_y)< lines && strings[a+off_y] != NULL){
            mvprintw(a, 0, "%s", strings[a+off_y]);
        }else{
            mvprintw(a, 0, "-");
        }
    }
}
// desenha a matriz com cores
void draw_text(char **strings, int lines, int max_y, int off_y, const int color, const int bold){
    if(bold == 1){
        attron(COLOR_PAIR(color) | A_BOLD);
    }
    else{
        attron(COLOR_PAIR(color));
    }
    for(int a = 0; a < max_y; a++){
        if((a + off_y)< lines && strings[a+off_y] != NULL){
            mvprintw(a, 0, "%s", strings[a+off_y]);
        }else{
            mvprintw(a, 0, " ");
        }
    }
    if(bold == 1){
        attroff(COLOR_PAIR(color) | A_BOLD);
    }
    else{
        attroff(COLOR_PAIR(color));
    }
}
