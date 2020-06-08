#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>


void sicercle(SDL_Rect *rect, int random[], int* nombre){

    int m = rect->x + 50;
    if(*nombre==-1){
        if(rect->y>=100 && rect->y<130 && m>100 && m<=700){
            if(random[m/100-1]==0) *nombre =  m/100-1;
        }else{
            *nombre = -1;
        }
    }
}

void deplacercercle(SDL_Rect *rect, SDL_Rect objets[],int random[], int* nombre, int T[]){
    int m = rect->x + 50;
    if(*nombre!=-1){
        if(rect->y>=270 && rect->y<=300 && m>100 && m<=700 && T[(m/100)-1]==0){

            random[*nombre]=-1;
            objets[*nombre].x= (m/100)*100;
            objets[*nombre].y= 400;
            *nombre =  -1;
            T[(m/100)-1] = 1;
        }
    }
}

int condition(int *up, int *right, int *down, int *left, SDL_Rect *rect, SDL_Rect objets[], int random[], int* nombre, int tab[]){
    SDL_Event e;
    if(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            return 1;
        }
        }
        if(e.type == SDL_KEYDOWN){
            switch (e.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                *up = 1;
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                *left = 1;
                break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                *down = 1;
                break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                *right = 1;
                break;
            case SDL_SCANCODE_SPACE:
                    sicercle(rect, random, nombre);
                    deplacercercle(rect, objets, random, nombre, tab);
                break;
            }
        }
        if(e.type == SDL_KEYUP){
            switch (e.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                *up = 0;
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                *left = 0;
                break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                *down = 0;
                break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                *right = 0;
                break;
            }
        }

    return 0;
}

void posrobot(SDL_Rect *rect, int x_vel, int y_vel, int w, int h){
    rect->x+=x_vel;
    rect->y+=y_vel;
    if(rect->x>w-100) rect->x=w-100;
    if(rect->x<0) rect->x=0;
    if(rect->y<0) rect->y=0;
    if(rect->y>h-100) rect->y=h-100;

           if((rect->x<=700 && rect->x>0 && rect->y<=100)||(rect->x<=700 && rect->x>0 && rect->y>=300)){

            rect->x-=x_vel;
            rect->y-=y_vel;
    }
}





