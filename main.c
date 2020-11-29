#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<stdbool.h> 
//gcc main.c $(sdl2-config --cflags --libs) 
int main(int argc, char *argv[]) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    int statut = EXIT_FAILURE;

    if(0 != SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        if(NULL != texture)
            SDL_DestroyTexture(texture);
        if(NULL != renderer)
            SDL_DestroyRenderer(renderer);
        if(NULL != window)
            SDL_DestroyWindow(window);
        SDL_Quit();
        return statut;
    }
    if(0 != SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_SHOWN, &window, &renderer)) {
        fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        if(NULL != texture)
            SDL_DestroyTexture(texture);
        if(NULL != renderer)
            SDL_DestroyRenderer(renderer);
        if(NULL != window)
            SDL_DestroyWindow(window);
        SDL_Quit();
        return statut;
    }
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, 
                                SDL_TEXTUREACCESS_TARGET, 200, 200);
    if(NULL == texture) {
        fprintf(stderr, "Erreur SDL_CreateTexture : %s", SDL_GetError());
         if(NULL != texture)
            SDL_DestroyTexture(texture);
        if(NULL != renderer)
            SDL_DestroyRenderer(renderer);
        if(NULL != window)
            SDL_DestroyWindow(window);
        SDL_Quit();
        return statut;
        }

///////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool isquit = false;
    SDL_Event event;
    while (!isquit) {
        if (SDL_PollEvent( & event)) {
            if (event.type == SDL_QUIT) {
                isquit = true;
            }
        }
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
