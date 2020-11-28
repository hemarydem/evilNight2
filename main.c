#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<stdbool.h> 

//gcc main.c $(sdl2-config --cflags --libs) 

int main(int argc, char *argv[]) {
    SDL_Window * win = NULL;
    SDL_Renderer* rendu = NULL;
    if(0 != SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    win = SDL_CreateWindow("firstWindow",
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED,
                        800,
                        600,
                        SDL_WINDOW_SHOWN);
    
    if(NULL == win){
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    rendu = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
    if(NULL == rendu) {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(win);
        SDL_Quit();
    }
   
    /* On agit sur la fenêtre ici */

    //SDL_delay(3000);
    //https://stackoverflow.com/questions/34424816/sdl-window-does-not-show
    bool isquit = false;
    SDL_Event event;
    while (!isquit) {
        if (SDL_PollEvent( & event)) {
            if (event.type == SDL_QUIT) {
                isquit = true;
            }
        }
    }

    SDL_DestroyWindow(win);
    SDL_Quit();
    return EXIT_SUCCESS;
}
