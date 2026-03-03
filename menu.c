
#include "includes.h"

SMenuChoice gpMenu[]={
    {"GAME", 0, e_Menu_Game,},
    {"OPTIONS", 0, e_Menu_Options,},
    {"HALL OF FAME", 0, e_Menu_HallOfFame,},
    {"QUIT", 0, e_Menu_Quit,},
};

bool Menu_CollideSprMouseMenu(int x, int y,  int w, int h)
{   
    if(gGen.nMouseX > x && gGen.nMouseX < x+w && gGen.nMouseY > y  && gGen.nMouseY < y + h)
    {
        return true;
    }
    return false;
}

#define MENU_GAP_PHRASES 15
#define SCALE2X 2 // Coeficient multiplicateur en modeVideo 2x.

int Menu_Main(bool eventFilter)
{
    // La soustraction de MENU_GAP_PHRASES est pour supprimer de la dernière phrase le GAP, ce qui permettra d'avoir un centrage exacte.
    int nHtMenu=NBELEM(gpMenu)*(FONT_HEIGHT+MENU_GAP_PHRASES)-MENU_GAP_PHRASES;
    const SDL_VideoInfo *pVideoInfo = NULL;
    int nOldIdx = gMenu.nIdx;
    static bool collide = false;
    u8 nMenuChoice=e_Menu_Null;

    // Blit les phrase du menu :
    // On stock les sprites pour le blittage.
    for (int i = 0; i < NBELEM(gpMenu); i++)
    {
        Font_PhraseStockedForBlitting(gpMenu[i].pStr, SCR_WIDTH/2 - gpMenu[i].nLg/2, SCR_HEIGHT/2 - nHtMenu/2+(i*(FONT_HEIGHT+MENU_GAP_PHRASES)), FONT_DISPO);
    }

    if(eventFilter) return nMenuChoice;

    // Transition :
    switch (gFade.nState)
    {
        case e_Menu_FadeIn:
            gGen.isTransition=true;
            
            // On a initialisé à -1 donc on arrive à 0 et on va jusqu'a 255 ce qui fait que dans Menu la palette aura été modifier 256 fois.
            gFade.nFadeVal+=FADE_STEP; 
            if (gFade.nFadeVal > 255)
            {
                gFade.nState=e_Menu_FadeInput;
                gGen.isTransition=false;
            }
            break;
        case e_Menu_FadeInput:
            
            pVideoInfo = SDL_GetVideoInfo();
            float coefResizeW=pVideoInfo->current_w*1.0/gGen.pScreen->w;
            float coefResizeH=pVideoInfo->current_h*1.0/gGen.pScreen->h;

            // Recherche de collision.
            for (int i = 0; i < NBELEM(gpMenu); i++)
            {
               collide = Menu_CollideSprMouseMenu((SCR_WIDTH/2 - gpMenu[i].nLg/2)*coefResizeW, (SCR_HEIGHT/2 - nHtMenu/2+(i*(FONT_HEIGHT+MENU_GAP_PHRASES)))*coefResizeH, gpMenu[i].nLg*coefResizeW, FONT_HEIGHT*coefResizeH);
#ifdef DEBUG
    if (collide == true) 
    {
        printf("-------------- nMouseX %d, nMouseY %d -------------------, menuXorg %d, menuYorg %d, menuW %d, menuH %d", gGen.nMouseX, gGen.nMouseY, (int)((SCR_WIDTH/2 - gpMenu[i].nLg/2)*coefResizeW), (int)((SCR_HEIGHT/2 - nHtMenu/2+(i*(FONT_HEIGHT+MENU_GAP_PHRASES)))*coefResizeH), (int)(gpMenu[i].nLg*coefResizeW+(SCR_WIDTH/2 - gpMenu[i].nLg/2)*coefResizeW), (int)(FONT_HEIGHT*coefResizeH+(SCR_HEIGHT/2 - nHtMenu/2+(i*(FONT_HEIGHT+MENU_GAP_PHRASES)))*coefResizeH));lf
    }
#endif
                if (collide == true) 
                {
                    gMenu.nIdx = i;
                    break;
                }
            }

            break;

        case e_Menu_FadeOut:
            gGen.isTransition=true;
            gFade.nFadeVal-=FADE_STEP;
            if (gFade.nFadeVal < 0)
            {
                gFade.nState=e_Menu_FadeIn;
                gGen.isTransition=false;
                nMenuChoice=gpMenu[gMenu.nIdx].flag;
            }
            break;
    }

    // Note : Pas besoin de mettre collide à false car il est mis au début de la fonction.
    if(collide == true)
    {
        // Pour éviter la répétition de Sound_Play.
        if(gMenu.nIdx != nOldIdx)
        {
            Sound_Play(e_Sfx_MenuClick, SOUND_CHANNEL_EFFECT);
        }
        
        if(gGen.nMouseBtnLeft == MOUSE_BTN_LEFT)
        {
            gSound.nSoundSaveVolume = gSound.nModularitySound;
            Sound_Play(e_Sfx_BatMagnet, SOUND_CHANNEL_EFFECT);
            gGen.nMouseBtnLeft = 0;
            gFade.nState=e_Menu_FadeOut;
            gFade.nFadeVal = 256;
        }
    }
    // ATTENTION : revoir texte, se met en noir, ça venait de la répétition de touche idem pour le son qui faisait un bruit exécrable et idem aussi quand on
    // arrivait sur le game la musique ce mettait sur le zéro.
    else if(gGen.pKeys[SDLK_RETURN] && gFade.nState!=e_Menu_FadeOut) 
    {
        if(gMenu.nIdx != nOldIdx)
        {
            Sound_Play(e_Sfx_MenuClick, SOUND_CHANNEL_EFFECT);
        }
        gSound.nSoundSaveVolume = gSound.nModularitySound;
        Sound_Play(e_Sfx_BatMagnet, SOUND_CHANNEL_EFFECT);
        gGen.nMouseBtnLeft = 0;
        gFade.nState=e_Menu_FadeOut;
        gFade.nFadeVal = 256;
    }
    else
    {
        gGen.nMouseBtnLeft = 0;
        gMenu.nIdx = 0; // 0 au lieu de -1, on se met sur GAME par défaut;.
    }

    return nMenuChoice;
}

void Menu_Init(void)
{

    gGen.nMenuChoice = e_Menu_Null;
    gGen.pBackground = gGen.pBkg[0];
    gFade.nState = e_Menu_FadeIn;
    gFade.nFadeVal = -1;
    gMenu.nIdx=0; // 0 au lieu de -1, on se met sur GAME par défaut.

    for (int i = 0; i < 256; i++)
    {
        memset(&gFade.pColor[i], 0, sizeof(gFade.pColor[0]));
    }
    Sound_Play(e_Music_Menu, SOUND_CHANNEL_MUSIC);

    for (int i = 0; i < NBELEM(gpMenu); i++)
    {
        gpMenu[i].nLg=Font_PhraseStockedForBlitting(gpMenu[i].pStr, 0, 0, FONT_NO_DISPO);
    }
    SDL_FillRect(gGen.pScreen, NULL, COLOR_BLACK_IDX);
    Frame_Init();
    
    SDL_SetEventFilter(&EventHandler_EventFilter);
}

int Menu(void)
{
    Menu_Init();
    char pStr[4]={"000"};
    char *pDstStr=NULL;
    int count=0;
    bool isKeyPlus=false;

    while (gGen.nMenuChoice == e_Menu_Null)
    {
        if(EventHandler_EventHandler(0) == EXIT) {gGen.nMenuChoice = e_Menu_Quit; break;}
        Sound_VolumeSpeed();
        Sound_ReplayMusic(e_Music_Menu);
        SDL_BlitSurface(gGen.pBackground, 0, gGen.pScreen, 0); 
        gGen.nMenuChoice = Menu_Main(EVENTFILTER_NO_DISPO);

        // Pour le son.
        if(gGen.pKeys[SDLK_KP_PLUS] || gGen.pKeys[SDLK_KP_MINUS])
        {
            isKeyPlus=true;
            if(count > 0)
                count=0;
        }
        if(isKeyPlus)
        {
            pDstStr=Tools_IntToASCII(gSound.nModularitySound, pStr);
            int sizeStrVolumeSnd = Font_PhraseStockedForBlitting(pDstStr, 0, 0, FONT_NO_DISPO);
            Font_PhraseStockedForBlitting(pDstStr, 24-sizeStrVolumeSnd, SCR_HEIGHT-FONT_HEIGHT*2, FONT_DISPO);
        }

        if( ! gGen.pKeys[SDLK_KP_PLUS] && count++>240 &&  ! gGen.isTransition)
        {
            count=0;
            isKeyPlus=false;
        }
        
        Sprites_BlitAll();
        Render_Flip();
        Fade();
    }
    return gGen.nMenuChoice; 
}