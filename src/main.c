/*
* r
* mac command
*gcc src/main.c src/fun.c -o bin/pika.app  $(sdl2-config --cflags --libs)
*remy hamed
*ce programme fait un animation d'une image qu va ver le haut
*
*gcc src/main.c src/fun.c -o bin/rtt.exe -lm  `pkg-config --cflags --libs sdl2  SDL2_image`
*
*/

#include<SDL.h>
#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<SDL_image.h>
#include "fun.h"
#define WINDOW_WIDTH (620)
#define WINDOW_HEIGHT (440)
#define SPEED (300)
#define MARIOSPEED (150)
//gcc src/main.c src/fun.c -o bin/pika.app  $(sdl2-config --cflags --libs)
//gcc src/main.c src/fun.c -o bin/uPikachu.exe -I include -L lib -lmingw32 -lSDL2main -lSDL2
//bin/uPikachu.exe
int main(int argc, char ** argv) {
    SDL_Window * win;
    SDL_Renderer * renderer;
    SDL_Texture * pikaTex, *arenaTex, *marioTex;
    SDL_Rect pikachu = {0, 0, 50, 50};
    SDL_Rect mario;
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0){
        printf("error initialisation");
        return EXIT_FAILURE;
    } 
    win  = SDL_CreateWindow("animation pikachu",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH, WINDOW_HEIGHT,0);
    freeAndQuitIfNull(win == NULL,"creation window" ,win, renderer,pikaTex);
    renderer = SDL_CreateRenderer(win, -1,SDL_RENDERER_ACCELERATED);
    freeAndQuitIfNull(renderer == NULL,"creation renderer" ,win, renderer,pikaTex);
    pikaTex = buildTextur("img/pika.bmp", renderer, pikaTex); 
    freeAndQuitIfNull(pikaTex == NULL,"error creation texture 1" ,win, renderer,pikaTex);
    arenaTex = buildTextur("img/arena.bmp", renderer, arenaTex); 
    freeAndQuitIfNull(arenaTex == NULL,"error creation texture 2" ,win, renderer,pikaTex);
    marioTex = buildTextur("img/mario.bmp", renderer, marioTex);
    freeAndQuitIfNull(marioTex == NULL,"error creation texture 3" ,win, renderer,pikaTex);
    //prend la lngeur et la hauter de la textre 
    SDL_QueryTexture(pikaTex,NULL,NULL, &pikachu.w, &pikachu.h);
    SDL_QueryTexture(marioTex,NULL,NULL, &mario.w, &mario.h);
    //multiplie par 2 la taile de l'image
    pikachu.h /= 4;
    pikachu.w /= 4;
     mario.h /= 4;
    mario.w /= 4;

    float y_pos = (WINDOW_HEIGHT - pikachu.h) / 2;
    float x_pos = (WINDOW_WIDTH - pikachu.w) / 2;
    float xVel = SPEED;
    float yVel = SPEED;

    float mario_y_pos = 10;
    float mario_x_pos = 10;
    float mario_xVel = MARIOSPEED;
    float mario_yVel = MARIOSPEED;

    int close = 0;
    //boucle d'annimation
    while (!close) {
        SDL_Event event;
        while (SDL_PollEvent(&event) == 1) {
            if(event.type == SDL_QUIT) {
                 close = 1;
            }
        }
        //manage colistion pikachu
        dontCrosseBorder(&xVel, &x_pos);
        dontCrosseBorder(&yVel, &y_pos);
        dontCrosseBottomBorder(WINDOW_WIDTH,pikachu.w,&xVel,&x_pos);
        dontCrosseBottomBorder(WINDOW_HEIGHT,pikachu.h,&yVel,&y_pos);
        //manage colistion mario
        dontCrosseBorder(&mario_xVel, &mario_x_pos);
        dontCrosseBorder(&mario_yVel, &mario_y_pos);
        dontCrosseBottomBorder(WINDOW_WIDTH,mario.w,&mario_xVel,&mario_x_pos);
        dontCrosseBottomBorder(WINDOW_HEIGHT,mario.h,&mario_yVel,&mario_y_pos);
        if (SDL_HasIntersection(&mario,&pikachu)){
            mario_xVel = - mario_xVel;
            mario_yVel = - mario_yVel;
            xVel = - xVel;
            yVel = - yVel;
        }
        x_pos += xVel/60;
        y_pos += yVel/60;
        pikachu.x = (int) x_pos;
        pikachu.y = (int) y_pos;

        mario_x_pos += mario_xVel/60;
        mario_y_pos += mario_yVel/60;

        mario.x = (int) mario_x_pos;
        mario.y = (int) mario_y_pos;
        //permet de savoir qui est la cible
        //SDL_RenderTargetSupported(renderer)
        SDL_SetRenderTarget(renderer,arenaTex);
        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer,0,0,WINDOW_WIDTH,WINDOW_HEIGHT);

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, arenaTex, NULL, NULL);
        SDL_RenderCopy(renderer, pikaTex, NULL, &pikachu);
        SDL_RenderCopy(renderer, marioTex, NULL, &mario);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/60);
    }
    SDL_DestroyTexture(pikaTex);
    SDL_DestroyTexture(arenaTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return EXIT_SUCCESS;
}