#include "fun.h"
#include <SDL.h>
#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

SDL_Texture * buildTextur(const char * imgPath, SDL_Renderer * renderer, SDL_Texture *texture){
    SDL_Surface * surface;
     surface = SDL_LoadBMP(imgPath);
    if(!surface){
        printf("\nERROR BUILD SURFACE");
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    return texture;
}

int freeAndQuitIfNull(int compare,const char * strErroMsg,SDL_Window * win, SDL_Renderer * renderer, SDL_Texture * tex){
    if (compare){
        char * str;
        str = buildStr(25);
        strcpy(str, "---error----\n is null ");
        strcat(strcat(str, strErroMsg),"\n/0");
        printf("%s",str);
        if (tex != NULL){
            SDL_DestroyTexture(tex);
        }
        if (renderer != NULL){
            SDL_DestroyRenderer(renderer);
        }
        if (win != NULL){
            SDL_DestroyWindow(win);
        }
        SDL_Quit();
        free(str);
        return EXIT_FAILURE;
    }
    return 0;
}
void dontCrosseBorder(float * velocity, float * position){
    if(*position <= 0) {
        *position = 0;
        *velocity = - *velocity;
    }
}
//y with height and x whith widht
void dontCrosseBottomBorder(int HeightORwidht,int spriteHorW,float * velocity, float * position){
   // printf("debut fonction");
    
    if(*position >= HeightORwidht - spriteHorW){
//printf("int HeightORwidht = %d\n int spriteHorW = %d\nfloat * velocity = %f\nfloat * position = %f\n",HeightORwidht, spriteHorW, *velocity, *position);
        *position = HeightORwidht - spriteHorW;
        *velocity = - *velocity;
   //     printf("int HeightORwidht = %d\n int spriteHorW = %d\nfloat * velocity = %f\nfloat * position = %f\n\n\n",HeightORwidht, spriteHorW, *velocity, *position);
    }
   // printf("fin fonction\n\n");
}

char * buildStr(int size){
    char* string;
    string =  malloc(sizeof(char) *  size);
    if(string != NULL)
        return string;
    printf("\nerror string not build\n");
    return(string);
}