#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<stdbool.h>

#define WINDOW_WIDTH (640)
#define WINDOW_HEGHT (480)

#define SCROLL_SPEED (300)

int main(int argc, char ** argv) {
    SDL_Window * win;
    SDL_Renderer * renderer;
    SDL_Texture * tex;
    SDL_Surface * Surface;
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0){
        printf("error initialisation");
        return EXIT_FAILURE;
    } 
    win  = SDL_CreateWindow("test",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH, WINDOW_HEGHT,0);

    if(!win) {
        printf("error creation fenètre");
        SDL_Quit();
        return EXIT_FAILURE;
    }
    uint32_t renderer_flag = SDL_RENDERER_ACCELERATED;
    renderer = SDL_CreateRenderer(win, -1,renderer_flag);
    if(!renderer) {
        printf("error creation rendu");
        SDL_DestroyWindow(win);
        SDL_Quit();
        return EXIT_FAILURE;
    }
    Surface = SDL_LoadBMP("src/icone.bmp");
    if(!Surface) {
        printf("error creation image");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return EXIT_FAILURE;
    }
    tex = SDL_CreateTextureFromSurface(renderer,Surface);
    if(!tex) {
        printf("error creation texture");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return EXIT_FAILURE;
    }
    SDL_FreeSurface(Surface);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, tex, NULL, NULL);
    SDL_RenderPresent(renderer);
    bool isquit = false;
    SDL_Event event;
    while (!isquit) {
        if (SDL_PollEvent( & event)) {
            if (event.type == SDL_QUIT) {
                isquit = true;
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return EXIT_SUCCESS;
}


