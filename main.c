
/*TODO : 
    Quand on clique avant la fin du fadeout se remet sur le menu.
    Faire une machine à état pour affichage du volume du son.
    Dans fade.c a revoir fade sfx pour passé à 0 peut importe le volume.
    Faire une struct pour les objets, séparer objets et items.
*/

#include "includes.h"

struct SGen gGen;

int main(int argc, char **argv)
{
    freopen("CON", "w", stdout);
    Init_InitSDL();

    // Pour l'aléatoir avec rand.
    srand(time(NULL));

    // RENDER VIDEO :
    Render_InitVideo();
    Render_SetModeVideo();

    // EVENTS KEYBOARD :
    gGen.pKeys = SDL_GetKeyState(NULL);

    // SPRITES :
    Sprites_Init();
    Sprites_ExtractSprSheet("_gfx/decor.bmp"); 
    Sprites_ExtractSprSheet("_gfx/monsters.bmp");
    Sprites_ExtractSprSheet("_gfx/lolo.bmp");
    Sprites_ExtractSprSheet("_gfx/font_small.bmp");
    
    char *pBkgs[]=BKGs_FILENAMES;
    Sprites_ExtractBkgs(pBkgs);

    // SOUND :
    bool soundInit = false;
    if((soundInit=Sound_Init()) == true)
    {
        char *pSfx[]=SOUND_FILENAMES;
        Sound_LoadWAV(pSfx);
        SDL_PauseAudio(0); 
    }
    
    u32 nLoop = true;
    u32 nMenuChoice = e_Menu_Main;

    while (nLoop)
    {
        switch (nMenuChoice)
        {
        case e_Menu_Main:
            nMenuChoice = Menu();
            break;
        case e_Menu_Game:
            Game();
            nMenuChoice=e_Menu_Main;
            break;
        case e_Menu_Options:
            nMenuChoice=e_Menu_Main;
            break;
        case e_Menu_HallOfFame:
            nMenuChoice = e_Menu_Main;
            break;
        case e_Menu_Quit:
            nLoop = false;
            break;
        }
    }

    Render_FreeSurface();
    Sprites_FreeAllBMPs(NULL, 0);
    Sprites_Release();
    if( ! soundInit)
    { 
        SDL_CloseAudio(); // Fermeture de l'audio.
        Sound_Free();
    }

    return EXIT_SUCCESS;
}