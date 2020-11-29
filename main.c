#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<stdbool.h> 
//gcc main.c $(sdl2-config --cflags --libs) 
int main(int argc, char *argv[]) {
    SDL_Window * win = NULL; 
    SDL_Renderer * rendu = NULL;
    SDL_Texture * text = NULL;
    if(0 != SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    win = SDL_CreateWindow("firstWindow",// creation of the window
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
    rendu = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);//creation of the renderer
    if(NULL == rendu) {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(win);
        SDL_Quit();
    }
    text = SDL_CreateTexture(rendu, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 200, 200);
    if(NULL == text) {
        fprintf(stderr, "Erreur SDL_CreateTexture : %s", SDL_GetError());
        SDL_DestroyTexture(text);
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(win);
        SDL_Quit();
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(0 != SDL_SetRenderDrawColor(rendu,255, 255, 220, SDL_ALPHA_OPAQUE)) {//preparing the color
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(win);
        SDL_Quit();
    }
    if(0 != SDL_RenderClear(rendu)){// put the background color on the renderer
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(win);
        SDL_Quit();
    }

    //from there we can draw 
    SDL_Rect rect = {50, 50, 100, 100};
    SDL_SetRenderDrawColor(rendu, 150, 0, 150, 255);
    SDL_SetRenderTarget(rendu, text);
    SDL_RenderFillRect(rendu, &rect);
    SDL_SetRenderTarget(rendu, NULL);

    SDL_RenderPresent(rendu);
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
    SDL_DestroyTexture(text);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return EXIT_SUCCESS;
}
