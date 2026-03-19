#include "includes.h"

void Render_ModeVideo2x(void)
{
    u8 *pix2x=gRender.pScreen2x->pixels;
    u16 pitch2x=gRender.pScreen2x->pitch;

    u8 *pix=gGen.pScreen->pixels; // pScreen donc pScreenBuf.

    int w = gGen.pScreen->w;
    int h = gGen.pScreen->h;

    for (int iy = 0; iy < h; iy++)
    {
        u8 *pix2xL1=pix2x;
        u8 *pix2xL2=pix2x+pitch2x;

        for (int ix = 0; ix < w; ix++)
        {
            *pix2xL1++=*pix;        
            *pix2xL1++=*pix;        
            *pix2xL2++=*pix;        
            *pix2xL2++=*pix++;        
        }
        pix2x+=pitch2x*2;
    }
} 

void Render_ModeVideoResize(void)
{
    //printf("Render_ModeVideoResize : SDL_GetVideoSurface() %p", SDL_GetVideoSurface());lf
    u8 *pixResize=gRender.pScreenResize->pixels;
    u16 pitchResize=gRender.pScreenResize->pitch;

    u8 *pix=gGen.pScreen->pixels; // pScreen donc pScreenBuf.
    u16 pitch=gGen.pScreen->pitch;

    // Largeur et hauteur de la surface à blitter.
    int w = gGen.pScreen->w;
    int h = gGen.pScreen->h;

    float coefResizeX= gGen.nResizeW*1.0/w;
    float coefResizeY= gGen.nResizeH*1.0/h;

    // Si on passe pas par l'écran de destination on n'est pas sûr de remplir tout les pixels. Donc on 
    // calcul la position du pixel de la source qu'on recopie dans la destination.
    for (int iy = 0; iy < gGen.nResizeH; iy++)
    {
        for (int ix = 0; ix < gGen.nResizeW; ix++)
        {
            int pixPosX = ix/coefResizeX; 
            int pixPosY = iy/coefResizeY;
            *(pixResize+ iy*pitchResize +ix)=*(pix+ pixPosY*pitch +pixPosX);
        }
    }
} 

void Render_InitVideo(void)
{
    gGen.nModeVideo = VIDEO_MODE_DEFAULT;
    gGen.pScreen = NULL;
    gRender.pScreenBuf = NULL;
    gRender.pScreen2x = NULL;
    gRender.pScreenResize = NULL;

    gRender.pScreenBuf = SDL_CreateRGBSurface(SCR_FLAGS ^ SDL_RESIZABLE, SCR_WIDTH, SCR_HEIGHT, SCR_BPP, 0, 0, 0, 0);
    if (gRender.pScreenBuf == NULL)
    {
        fprintf(stdout, "Failed to create RGB surface %s", SDL_GetError());lf
        exit(EXIT_FAILURE);
    }
}

void Render_SetModeVideo(void)
{
    switch (gGen.nModeVideo)
    {
        // ATTENTION lors de la création de la surface l'ancienne adresse de la surface ici pScreen pour le mode normal est 
        // réutilisé pour SDL_SetVideoMode.
        case e_ModeVideoResize: 
            if (gRender.nFullScreenMode != 1)
            {
                gRender.pScreenResize = SDL_SetVideoMode(gGen.nResizeW, gGen.nResizeH, SCR_BPP, SCR_FLAGS);
                if(gRender.pScreenResize == NULL)
                {
                    fprintf(stdout, "Resizing failed: %s", SDL_GetError());lf
                }else
                {
                    gGen.pScreen = gRender.pScreenBuf;
                    SDL_FillRect(gRender.pScreenResize, NULL, COLOR_BLACK_IDX);
                    SDL_SetPalette(gGen.pScreen, SDL_LOGPAL|SDL_PHYSPAL, gGen.pColor, 0, 256);
                    SDL_SetPalette(gRender.pScreenResize, SDL_LOGPAL|SDL_PHYSPAL, gGen.pColor, 0, 256);
                    return;
                }
            }
            gGen.nModeVideo = e_ModeVideo2x;

        case e_ModeVideo2x:
            gRender.pScreen2x = SDL_SetVideoMode(SCR_WIDTH*2, SCR_HEIGHT*2, SCR_BPP, gRender.nFullScreenMode ? SDL_FULLSCREEN:SCR_FLAGS);
            if (gRender.pScreen2x == NULL)
            {
                fprintf(stdout, "Failed to create screen surface 640x480: %s", SDL_GetError());lf
            }else
            {
                gGen.pScreen = gRender.pScreenBuf;
                SDL_FillRect(gGen.pScreen, NULL, COLOR_BLACK_IDX);
                // J'ajoute setPalette pour évité quand on fait un appel à Render_SetModeVideo d'avoir à remettre setPalette.
                SDL_SetPalette(gGen.pScreen, SDL_LOGPAL|SDL_PHYSPAL, gGen.pColor, 0, 256);
                SDL_SetPalette(gRender.pScreen2x, SDL_LOGPAL|SDL_PHYSPAL, gGen.pColor, 0, 256);
                return;
            }
            
            gGen.nModeVideo = e_ModeVideoNormal;
    
        case e_ModeVideoNormal:
            gGen.pScreen = SDL_SetVideoMode(SCR_WIDTH, SCR_HEIGHT, SCR_BPP, gRender.nFullScreenMode ? SDL_FULLSCREEN:SCR_FLAGS);
            if(gGen.pScreen == NULL)
            {
                fprintf(stdout, "Failed to create screen surface 320x240: %s", SDL_GetError());lf
                exit(EXIT_FAILURE);
            }
            // SDL_FillRect permet de supprimer le flash rose, quand la fenêtre s'affiche, car quand on sauvegarde la palette les couleurs
            // sont modifiées, ex. : à l'index 0 qui avant contenait la couleur noir devient le rose. Donc en mettant COLOR_BLACK_IDX à la 
            // création de la fenêtre la valeur pour chaque pixel sera de COLOR_BLACK_IDX ce qui fait que quand SDL_SetPallette sera appelé
            // à l'affichage on aura un écran noir.
            SDL_FillRect(gGen.pScreen, NULL, COLOR_BLACK_IDX);
            SDL_SetPalette(gGen.pScreen, SDL_LOGPAL|SDL_PHYSPAL, gGen.pColor, 0, 256);
            break;
    }
}

void Render_Flip(void)
{
    typedef void (*pPtrFctModeVideo) (void);
    static pPtrFctModeVideo pFctModeVideo[e_ModeVideo_MAX] = {NULL, Render_ModeVideo2x, Render_ModeVideoResize};

    if(pFctModeVideo[gGen.nModeVideo] != NULL) pFctModeVideo[gGen.nModeVideo]();
    
    Frame_Wait();
    //printf("Render_Flip : gGen.nModeVideo  %d SDL_GetVideoSurface() : %p, pScreen %p, gRender.pScreenResize %p", gGen.nModeVideo, SDL_GetVideoSurface(), gGen.pScreen, gRender.pScreenResize);lf
    SDL_Flip(SDL_GetVideoSurface());
    
}

void Render_FreeSurface(void)
{
    SDL_free(gRender.pScreenBuf);
}