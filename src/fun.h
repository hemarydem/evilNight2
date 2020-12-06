#ifndef fun_h
#define fun_h
#include <SDL.h>
#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#endif

SDL_Texture * buildTextur(const char * imgPath, SDL_Renderer * renderer, SDL_Texture *texture);
int freeAndQuitIfNull(int compare,const char * strErroMsg,SDL_Window * win, SDL_Renderer * renderer, SDL_Texture * tex);

char * buildStr(int size);

void dontCrosseBorder(float * velocity, float * position);
void dontCrosseBottomBorder(int HeightORwidht,int spriteHorW,float * velocity, float * position);