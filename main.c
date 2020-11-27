#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>

//gcc main.c $(sdl2-config --cflags --libs) 

int main(int argc, char *argv[]) {
    SDL_Window * win = NULL;
    SDL_Window * win2 = NULL;
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
    win2 = SDL_CreateWindow("secondWindow",
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
    if(NULL == win2){
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_DestroyWindow(win2);
        SDL_Quit();
        return EXIT_FAILURE;
    }
    /* On agit sur la fenêtre ici */
    SDL_Delay(3000);
    SDL_DestroyWindow(win2);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return EXIT_SUCCESS;
}
