#include "includes.h"

SGame gGame;

int EventHandler_EventFilter(const SDL_Event *pEvent)
{
    if(pEvent->type == SDL_VIDEORESIZE)
    {
        // Récupérer l'ancienne taille de l'écran.
        gGen.nResizeW=pEvent->resize.w;
        gGen.nResizeH=pEvent->resize.h;

        if (
        ! (pEvent->resize.w==SCR_WIDTH && pEvent->resize.h==SCR_HEIGHT) && 
        ! (pEvent->resize.w==SCR_WIDTH*2 && pEvent->resize.h==SCR_HEIGHT*2)
        )
        {// A REVOIR EN FONCTION DU MODE.
            gGen.nModeVideo = e_ModeVideoResize;
            Render_SetModeVideo();
            if(gGen.nMenuChoice == e_Menu_Null)
            {
                //printf("EventHandler_EventFilter : e_Menu_Main : SDL_GetVideoSurface() : %p, pScreen %p, gRender.pScreenResize %p", SDL_GetVideoSurface(), gGen.pScreen, gRender.pScreenResize);lf
                SDL_BlitSurface(gGen.pBackground, 0, gGen.pScreen, 0);
                Menu_Main(1);
            }
            else if (gGen.nMenuChoice == e_Menu_Game)
            {
                SDL_BlitSurface(gGen.pBackground, 0, gGen.pScreen, 0);
            }
            
            Sprites_BlitAll();
            Render_Flip();
        }
        // Quand SDL_SetEventFilter appelera EventHandler_EventFilter qui retournera 1 et ainsi  sera placé dans la liste des év" en 1er.
    }
    return 1;
}

int EventHandler_EventHandler(u32 nInGame )
{
    SDL_Event event;
    static bool oldPauseAudio=false;
    static u32 nLastPhase;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:

                // Gestion de la pause
                if(nInGame == 1 && gGen.pKeys[SDLK_p]){
                    if(gGame.nPhase == e_Game_Pause){
                        gGame.nPhase = nLastPhase;
                    }else{
                        nLastPhase = gGame.nPhase;
                        gGame.nPhase = e_Game_Pause;
                    }
                }
                // Les touches arrow left, right, up, down son pris directement via gGen.pKeys (voir Game_PlayerMove)
                if(gGen.pKeys[SDLK_a] && oldPauseAudio==false)
                {
                    SDL_PauseAudio(1);
                    oldPauseAudio=true;
                }
                else if(gGen.pKeys[SDLK_a] && oldPauseAudio==true)
                {
                    SDL_PauseAudio(0);
                    oldPauseAudio=false;
                }
                
                if(gGen.pKeys[SDLK_ESCAPE])
                {    
                    return EXIT;
                }
                // Full screen
                if (gGen.pKeys[SDLK_F8])
                {
                    gRender.nFullScreenMode ^= 1;    
                    Render_SetModeVideo();
                }
                
                // Redimenssionnement du screen
                if (gGen.pKeys[SDLK_F7] && gGen.nResizeW != 1280 && gGen.nResizeH != 961)
                {
                    if(gGen.nModeVideo == e_ModeVideoResize && gGen.nResizeW == SCR_WIDTH && gGen.nResizeH == SCR_HEIGHT) 
                    {
                        gGen.nModeVideo = e_ModeVideoNormal;
                    }
                    if (gGen.nModeVideo==e_ModeVideoNormal)
                    {
                        gGen.nModeVideo = e_ModeVideo2x;
                    }
                    else if (gGen.nModeVideo==e_ModeVideo2x)
                    {
                        gGen.nModeVideo = e_ModeVideoNormal;
                    }
                    else if (gGen.nModeVideo==e_ModeVideoResize && gRender.nOldModeVideo == e_ModeVideoNormal)
                    {
                        SDL_BlitSurface(gGen.pScreen, NULL, gGen.pScreen, NULL);
                        gGen.nModeVideo = e_ModeVideoNormal;
                    }
                    else if (gGen.nModeVideo==e_ModeVideoResize && gRender.nOldModeVideo == e_ModeVideo2x)
                    {
                        SDL_BlitSurface(gGen.pScreen, NULL, gGen.pScreen, NULL);
                        gGen.nModeVideo = e_ModeVideo2x;
                    }
                    else // Ici on fait un 2e redimenssionnement avec resize donc nOldModeVideo assigné avec le mode resize.
                    {
                        gGen.nModeVideo=e_ModeVideo2x;
                    }
                    
                    Render_SetModeVideo();
                } // FIN Redimenssionnement du screen.

                // Controle volume pas à pas.
                {
                    if(gGen.pKeys[SDLK_KP_PLUS])
                    {
                        if(gSound.nModularitySound < SDL_MIX_MAXVOLUME)
                        {
                            gSound.nModularitySound++;
                            printf("gSound.nModularitySound %d", gSound.nModularitySound);lf
                        }
                    }

                    if (gGen.pKeys[SDLK_KP_MINUS])
                    {
                        if(gSound.nModularitySound > 0)
                        {
                            gSound.nModularitySound--;
                            printf("gSound.nModularitySound %d", gSound.nModularitySound);lf
                        }
                    }
                }

                if (gGen.pKeys[SDLK_q])
                {
                    printf("SDLK_a");lf
                    Sound_Play(e_Sfx_MenuClick, SOUND_CHANNEL_EFFECT);
                }
                if (gGen.pKeys[SDLK_w])
                {
                    printf("SDLK_w");lf
                    Sound_Play(e_Sfx_BatMagnet, SOUND_CHANNEL_EFFECT);
                }
                if (gGen.pKeys[SDLK_e])
                {
                    printf("SDLK_e");lf
                    Sound_Play(e_Sfx_BallBounce, SOUND_CHANNEL_EFFECT);
                }
                
                break;
            case SDL_KEYUP:
                if (gGen.pKeys[SDLK_KP_MINUS]==0 || gGen.pKeys[SDLK_KP_PLUS]==0)
                {
                    gnCountTimeDownKey=0;
                }
                break;
            case SDL_MOUSEMOTION:
                gGen.nMouseX = event.motion.x;
                gGen.nMouseY = event.motion.y;
                break;

            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        gGen.nMouseBtnLeft = MOUSE_BTN_LEFT;
                        break;
                }
                break;

            case SDL_QUIT:
                exit(0);
                break;
        }
    }
    return NO_EXIT;
}
