#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

void deplacercercle(SDL_Rect *rect, SDL_Rect zone1[],int random[], int* nombre, int zone2[]){
    int m = rect->x+50 ;
    if(*nombre==-1){
        if(rect->y>=100 && rect->y<130 && m>100 && m<=700){
            if(random[m/100-1]==0) *nombre =  m/100-1;
        }else{
            *nombre = -1;
        }
    }
if(*nombre!=-1){
        if(rect->y>=270 && rect->y<=300 && m>100 && m<=700 && zone2[(m/100)-1]==0){

            random[*nombre]=-1;
            zone1[*nombre].x= (m/100)*100;
            zone1[*nombre].y= 400;
            *nombre =  -1;
            zone2[(m/100)-1] = 1;
        }
    }
}

int animation(int *up, int *right, int *down, int *left, SDL_Rect *rect, SDL_Rect zone1[], int random[], int* nombre, int tab[]){
    SDL_Event e;
    if(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            return 1;
        }
        }
        if(e.type == SDL_KEYDOWN){
            switch (e.key.keysym.scancode)
            {
           case SDL_SCANCODE_UP:
                *up = 1;
                break;
           case SDL_SCANCODE_LEFT:
                *left = 1;
                break;
           case SDL_SCANCODE_DOWN:
                *down = 1;
                break;
           case SDL_SCANCODE_RIGHT:
                *right = 1;
                break;
            case SDL_SCANCODE_SPACE:
                    deplacercercle(rect, zone1, random, nombre, tab);
                break;
            }
        }
        if(e.type == SDL_KEYUP){
            switch (e.key.keysym.scancode)
            {
            case SDL_SCANCODE_UP:
                *up = 0;
                break;
            case SDL_SCANCODE_LEFT:
                *left = 0;
                break;
            case SDL_SCANCODE_DOWN:
                *down = 0;
                break;
            case SDL_SCANCODE_RIGHT:
                *right = 0;
                break;
            }
        }

    return 0;
}

void posrobot(SDL_Rect *rect, int x_vel, int y_vel){
    rect->x+=x_vel;
    rect->y+=y_vel;
         // detection de collision avec les bornes et la zone 1 et 2
    if(rect->x>WINDOW_WIDTH-100) rect->x=WINDOW_WIDTH-100;
    if(rect->x<0) rect->x=0;
    if(rect->y<0) rect->y=0;
    if(rect->y>WINDOW_HEIGHT-100) rect->y=WINDOW_HEIGHT-100;


    if((rect->x<=700 && rect->x>0 && rect->y<=100)||(rect->x<=700 && rect->x>0 && rect->y>=300)){

            rect->x-=x_vel;
            rect->y-=y_vel;
    }

}


