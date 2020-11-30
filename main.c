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
    SDL_Rect rect = {100, 100, 100, 100}, dst = {0, 0, 0, 0};
    SDL_Color rouge = {255, 0, 0, 255}, bleu = {0, 0, 255, 255};
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
    if(0 != SDL_SetRenderDrawColor(renderer,255, 255, 220, SDL_ALPHA_OPAQUE)) {//preparing the color
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        if(NULL != texture)
            SDL_DestroyTexture(texture);
        if(NULL != renderer)
            SDL_DestroyRenderer(renderer);
        if(NULL != window)
            SDL_DestroyWindow(window);
        SDL_Quit();
        return statut;
    }
    
    if(0 != SDL_RenderClear(renderer)){// put the background color on the renderer
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        if(NULL != texture)
            SDL_DestroyTexture(texture);
        if(NULL != renderer)
            SDL_DestroyRenderer(renderer);
        if(NULL != window)
            SDL_DestroyWindow(window);
        SDL_Quit();
        return statut;
    }

    SDL_SetRenderTarget(renderer, texture);// on cible la texture
    /* La texture est la cible de rendu, maintenant, on dessine sur la texture. */
    SDL_SetRenderDrawColor(renderer, bleu.r, bleu.g, bleu.b, bleu.a); // on transforme la texture en bleu
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, rouge.r, rouge.g, rouge.b, rouge.a);//on colorrie le care en rouge
    SDL_RenderFillRect(renderer, &rect); /* On dessine un rectangle rouge sur la texture. */

    SDL_SetRenderTarget(renderer, NULL); /* Le renderer est la cible de rendu. */

    /* On récupère les dimensions de la texture, on la copie sur le renderer
       et on met à jour l’écran. */
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_RenderPresent(renderer);
    statut = EXIT_SUCCESS;
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
