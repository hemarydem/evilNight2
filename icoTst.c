#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<stdbool.h> 
//gcc main.c $(sdl2-config --cflags --libs)
/* Cette structure permet de représenter un carré par sa couleur et un SDL_Rect. */

int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect rect;
    size_t i;
    
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("icone", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,800, 600, SDL_WINDOW_RESIZABLE);
    SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    surface = SDL_LoadBMP("src/icone.bmp");
    SDL_CreateTextureFromSurface(renderer, surface);
    /* On crée quatre carré pour notre icône. */
    
    /* On remplit notre surface grâce à nos carrés. */
        SDL_BlitSurface(surface, NULL,surface,&rect);

    SDL_SetWindowIcon(window, surface);
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
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
