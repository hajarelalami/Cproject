#ifndef INTI_H
#define INTI_H
#include <SDL.h>
#include <SDL_image.h>




void sicercle(SDL_Rect *pos, int rands[], int nombre);

void deplacercercle(SDL_Rect *pos, SDL_Rect shapes[],int rands[], int* nombre, int tab[]);

int condition(int *up, int *right, int *down, int *left, SDL_Rect *pos, SDL_Rect shapes[], int rands[], int* nombre, int tab[]);

void posrobot(SDL_Rect *rect, int x_vel, int y_vel, int w, int h);


#endif

