#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<stdbool.h> 
//gcc main.c $(sdl2-config --cflags --libs)
/* Cette structure permet de représenter un carré par sa couleur et un SDL_Rect. */
struct carre {
   SDL_Rect rect;
   Uint32 couleur;
};
int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Surface *surface;
    size_t i;
    
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("icone", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,800, 600, SDL_WINDOW_RESIZABLE);
    surface = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0);

    /* On crée quatre carré pour notre icône. */
    struct carre carre[4] = {
        { {  4,  4, 10, 10 }, SDL_MapRGB(surface->format, 0, 0, 0) }, /* Noir */
        { {  4, 18, 10, 10 }, SDL_MapRGB(surface->format, 0, 0, 255) }, /* Bleu */
        { { 18,  4, 10, 10 }, SDL_MapRGB(surface->format, 0, 255, 0) }, /* Vert */
        { { 18, 18, 10, 10 }, SDL_MapRGB(surface->format, 255, 255, 255) } /* Blanc */
    };
    
    /* On remplit notre surface grâce à nos carrés. */
    for(i = 0; i < 4; i++)
        SDL_FillRect(surface, &carre[i].rect, carre[i].couleur);

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
