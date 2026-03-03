#include "includes.h"

void Fade(void)
{
    Fade_Gfx();
    Fade_Sfx();
}

void Fade_Gfx(void)
{
    if(gGen.isTransition)
    { 
        // Parcours des 256 cases de la palette.
        for (int i = 0; i < 256; i++)
        {
            gFade.pColor[i].r = (gGen.pColor[i].r * gFade.nFadeVal) / 255;
            gFade.pColor[i].g = (gGen.pColor[i].g * gFade.nFadeVal) / 255;
            gFade.pColor[i].b = (gGen.pColor[i].b * gFade.nFadeVal) / 255;
#ifdef DEBUG
    if(i==0)
    {
        printf("gFade.pColor[%d].r %d, gFade.pColor[%d].g %d, gFade.pColor[%d].b %d", i, gFade.pColor[i].r, i, gFade.pColor[i].g, i, gFade.pColor[i].b);lf
    } 
#endif
        }
    }
    // Récupère le mode vidéo courant.
    SDL_SetPalette(SDL_GetVideoSurface(), SDL_PHYSPAL, gFade.pColor, 0, 256); 
}

void Fade_Sfx(void)
{
    // A Revoir en fonction de la granulométrie de la transition gfx (FADE_STEP).
    if(gFade.nState == e_Menu_FadeOut && gFade.nFadeVal > 0 &&  gSound.nModularitySound > 0)
        gSound.nModularitySound-=gSound.nSoundSaveVolume/65+1; // +1 sinon on est à 0 à cause de GCC qui prend la valeur entière la plus basse.
    if(gSound.nModularitySound < 1)
    {
        Sound_Stop();
    }
}