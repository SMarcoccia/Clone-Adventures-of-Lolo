#include "includes.h"

// 1 frame toute les 16 milliseconde, soit 60 frames par seconde (1000 milliseconde).
#define FPS 1000/60 

// Variable pour récupérer le temps.
int gnTimer=0;

void Frame_Init(void)
{
    gnTimer=SDL_GetTicks();
}
void Frame_Wait(void)
{
    int nTimer=0;
    while (1)
    {
        nTimer = SDL_GetTicks()-gnTimer;
        if(nTimer >= FPS) break;
        SDL_Delay(3);
    }
    gnTimer = SDL_GetTicks();
}