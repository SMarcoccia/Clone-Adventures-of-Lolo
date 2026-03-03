#include "includes.h"

void Init_InitSDL(void)
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        fprintf(stdout, "Unable to init SDL: %s", SDL_GetError());lf
        exit(EXIT_FAILURE);
    }
    atexit(SDL_Quit);
}