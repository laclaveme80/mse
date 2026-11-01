#ifndef DRAW_H
#define DRAW_H
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
// funcoes
void start_base();

void start_colors(int *color);

void draw_text(char **strings, int lines, int max_y, int off_y, const int color, const int bold);

void draw_minimal(char **strings, int lines, int max_y, int off_y);
#endif
