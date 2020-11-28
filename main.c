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
    //from there we can draw on the renderer
    https://stackoverflow.com/questions/18914960/how-to-iterate-over-of-an-array-of-structures/18914961
    SDL_SetRenderDrawColor(rendu, 0, 0, 0, SDL_ALPHA_OPAQUE);//put the color black for next things will be draw
    SDL_Rect rect[48];// creat 48 rect
    SDL_Rect *ptr = rect;// we need ptr for the loop
    int x = 0;//set the position
    int y = 0; 
    int decale = 0;//each line need to switch the colore rythme
    for (size_t i = 0; i < 48; i++) {
        if(x > 700) {// it's the last rect got to the line under
            x = 0;
            y += 100;
            if (decale == 0){// to stop the alternate the color must same as last of the upper line
                decale =1;
            }else{
                decale = 0;
            } 
        }
        if (decale == 1){
            ptr[i].x = x;
            ptr[i].y = y;
            ptr[i].h = 100;
            ptr[i].w = 100;
            SDL_RenderFillRect(rendu, &ptr[i]); 
            decale = 0;
        } else {
            ptr[i].x = x;
            ptr[i].y = y;
            ptr[i].h = 100;
            ptr[i].w = 100;
            SDL_RenderDrawRect(rendu, &ptr[i]);
            decale = 1;
        }
        x += 100;
    }
    SDL_RenderPresent(rendu);
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
