#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<stdbool.h>
#define WINDOW_HEIGHT (640)
#define WINDOW_WIDTH (480)
#define SPEED (300)
int erroStop(const char * erroMsg,SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture);
void erroCheck(int funReturn,const char * erroMsg,SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture);
//gcc main.c $(sdl2-config --cflags --libs)
void erroCheck(int funReturn,const char * erroMsg,SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture) {
    if(0 != funReturn){
       erroStop(erroMsg, window,renderer,texture);
    }
}
int erroStop(const char * erroMsg,SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture){
    fprintf(stderr, erroMsg, SDL_GetError());
        if(NULL != texture)
            SDL_DestroyTexture(texture);
        if(NULL != renderer)
            SDL_DestroyRenderer(renderer);
        if(NULL != window)
            SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
}
int main(int argc, char **argv) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_Surface *tmp = NULL; 
    int statut = EXIT_FAILURE;
    SDL_Rect dest;
    //intialisation
    erroCheck(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER),"Erreur SDL_Init : %s",window,renderer,texture);
   
    // création du rendu et de la fenètre en même temps
    erroCheck(SDL_CreateWindowAndRenderer(WINDOW_HEIGHT,WINDOW_WIDTH, SDL_WINDOW_SHOWN, &window, &renderer),"Erreur SDL_CreateWindowAndRenderer : %s",window,renderer,texture);
    
    tmp = SDL_LoadBMP("src/icone.bmp");//on charge l'image
    if(NULL == tmp) erroStop("Erreur SDL_LoadBMP : %s",window,renderer,texture);
    
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp); /* On libère la surface, on n’en a plus besoin */
    if(NULL == texture) erroStop("Erreur SDL_CreateTextureFromSurface : %s",window,renderer,texture);
    
    
    //on prend les dimenssiond e la texture
    SDL_QueryTexture(texture,NULL,NULL,&dest.w, &dest.h);
    printf("dest x = %d\n", dest.x);
    printf("dest y = %d\n\n", dest.y);
    // on position au centre bas de la fenètre
    dest.x = 0;
    dest.y = 0;
    printf("dest x = %d\n", dest.x);
    printf("dest y = %d", dest.y);
    

    while (dest.y < WINDOW_HEIGHT){
        
        // on effeca le contenu précédent
        SDL_RenderClear(renderer);
        //initialiser la position
        dest.y += 20;
        // mettre la texture sur le rendu
        /*
        Pour que la texture ci dessu soit plus petite 
        il à la place de source il aurai fallu utiliser
        un rectangle source aux dimenssion voulu
        */
        SDL_RenderCopy(renderer, texture, NULL, &dest);
        //affichage du rendu
        SDL_RenderPresent(renderer);
        //mettre à jour la position du sprite
        //y_pos -=(float) SPEED/60;
        //la boucle rest tous les 60ieme de seconde pour
        //être caler à 60 fps
        SDL_Delay(1000/60);
    }
     bool isquit = false;
        SDL_Event event;
        while (!isquit) {
            if (SDL_PollEvent( & event)) {
                if (event.type == SDL_QUIT) {
                    isquit = true;
                }
            }
        }
    statut = EXIT_SUCCESS;
///////////////////////////////////////////////////////////////////////////////////////////////////////////
   
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
