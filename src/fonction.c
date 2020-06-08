#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500
#include <SDL_image.h>

int init()
{
    srand(time(NULL));
//INITIALISER LA SDL
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("erreur d'initialisation de la SDL: %s\n", SDL_GetError());
        return 1;
    }
//CREER une fenêtre
       SDL_Window* win = SDL_CreateWindow("HM-ROBOT",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH, WINDOW_HEIGHT,0);

    if (!win)
    {
        printf("erreur creation window: %s\n", SDL_GetError());
        SDL_Quit();
	    return 1;
    }
//Renderer
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend)
    {
        printf("erreur de création du renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
//CHARGER l'image du robot en mémoire à l'aide de la fonction de la bibliothèque SDL_image
    SDL_Surface* surface = IMG_Load("src/robott.png");
    if (!surface)
    {
        printf("erreur de création de surface\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
//CHARGER l'image à l'aide d'une texture
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if (!tex)
    {
        printf("erreur de création de la texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
//STRUCTURE qui conserve la position du robot
    SDL_Rect robot;
//POSITION initiale du robot
    robot.x = WINDOW_WIDTH -150;
    robot.y = WINDOW_HEIGHT/2 -50;
//CHANGER la TAILLE du robot
    robot.w = 150;
    robot.h = 110;
//Cercle
        SDL_Surface* cercle = IMG_Load("src/cercle.png");
    if(!cercle){

        printf("Erreur surface cercle !\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Texture * texCercle = SDL_CreateTextureFromSurface(rend, cercle);
    SDL_FreeSurface(cercle);
    if(!texCercle){
        printf("Erreur texture cercle!\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
//Rectangle
 SDL_Surface* rect = IMG_Load("src/rect1.png");
    if(!rect){
        printf("Erreur surface rectangle\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Texture * texRect = SDL_CreateTextureFromSurface(rend, rect);
    SDL_FreeSurface(rect);
    if(!texRect){
        printf("Erreur  Texture rectangle\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
//Hexagonal
    SDL_Surface* hex = IMG_Load("src/hex.png");
    if(!hex){
        printf("Erreur  Surface hexagonal\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Texture * texhex = SDL_CreateTextureFromSurface(rend, hex);
    SDL_FreeSurface(hex);
    if(!texhex){
        printf("Erreur  Texture hexagonal!!\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    //triangle
        SDL_Surface* triangle = IMG_Load("src/tri.png");
    if(!triangle){
        printf("Erreur  Surface Triangle!!\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Texture * textri = SDL_CreateTextureFromSurface(rend, hex);
    SDL_FreeSurface(triangle );
    if(!texhex){
        printf("Erreur  Texture triangle\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

//ZONE 1
    SDL_Rect zone1[6];
    for(int i = 1; i<=6; i++){
        zone1[i-1].x = i*100;
        zone1[i-1].y = 0;
        zone1[i-1].w = 100;
        zone1[i-1].h = 100;
    }
//La vitesse
    int speed = 4;

//INITIALISER les entrées
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;

    int k;
//saisir un nombre aléatoire  de 0 à 3 6 fois
    int random[6];
    for (int i = 0; i<6; i++){
        k = rand()%4;
        random[i] = k;
    }

    int NOMBREOBJ = -1;
    int zone2[6]={0,0,0,0,0,0};


    while(1){
            int close_requested = 0;
           close_requested = animation(&up, &right, &down, &left, &robot, zone1, random, &NOMBREOBJ, zone2);
            if(close_requested ==1) break;

                    //la vitesse du robot dans une direction donnée.

            int x_vel = 0;
            int y_vel = 0;
           if (up && !down) y_vel = -speed;
           if (down && !up) y_vel = speed;
           if (left && !right) x_vel = -speed;
           if (right && !left) x_vel = speed;

//CHANGER la couleur du renderer
            SDL_SetRenderDrawColor(rend, 255, 255, 255, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(rend);



            for(int i = 0; i<6; i++){
                switch (random[i])
                {
                case 0:
                     SDL_RenderCopy(rend, texCercle, NULL, &zone1[i]);
                     break;
                case 1:
                     SDL_RenderCopy(rend, texRect, NULL, &zone1[i]);
                     break;
                case 2:
                     SDL_RenderCopy(rend, texhex, NULL, &zone1[i]);
                     break;
                case 3:
                    SDL_RenderCopy(rend, textri, NULL, &zone1[i]);
                     break;
                case -1:
                    SDL_RenderCopy(rend, texCercle, NULL, &zone1[i]);
                    break;
                 }
            }
            posrobot(&robot, x_vel, y_vel);
         SDL_RenderCopy(rend, tex, NULL, &robot);
          SDL_RenderPresent(rend);




if(NOMBREOBJ!=-1){
                zone1[NOMBREOBJ].x = robot.x;
                zone1[NOMBREOBJ].y = robot.y;
            }
//attendre 1/60 de seconds

    SDL_Delay(1000/60);

            }

    SDL_DestroyTexture(tex);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}


