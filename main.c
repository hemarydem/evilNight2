#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>

//gcc main.c $(sdl2-config --cflags --libs) 

int main(int argc, char *argv[]) {
    if(0 != SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Quit();
    return EXIT_SUCCESS;
}
