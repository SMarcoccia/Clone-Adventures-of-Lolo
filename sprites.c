#include "includes.h"

SSprite gpSpr[SPR_MAX];
SStockSpr gpStockSpr[SPR_STOCK_MAX];
// Tableau de pointeur pour récupérer l'adresse des cases du tableau gpStockSpr.
SStockSpr *gpSprSort[SPR_STOCK_MAX];

// Nb de sprites récupéré dans la sprite sheet.
int gnNbSpr = 0;
int gnNbSprStock=0;

bool Sprites_CollideSprs(u32 noSpr1, u32 noSpr2)
{
    //gpSpr[noSpr1].
    return true;
}

void Sprites_DisplayIdxPalette(SDL_Color *color)
{
    printf("Palette :"); lf
    for (int j = 0; j < 16; j++)
    {
        for (int i = 0; i < 16; i++)
        {
            u8 r = color[j*16+i].r;
            u8 g = color[j*16+i].g;
            u8 b = color[j*16+i].b;
            if(r < 10)
                printf("  %d",  r); 
            else if(r < 100 )
                printf(" %d",  r); 
            else
                printf("%d",  r); 

            if(g < 10)
                printf("   %d",  g); 
            else if(g < 100 )
                printf("  %d",  g); 
            else
                printf(" %d",  g); 

            if(b < 10)
                printf("   %d",  b); 
            else if(b < 100 )
                printf("  %d",  b); 
            else
                printf(" %d",  b); 

            printf("|"); 
            if(i == 7 && i != 0) lf
        } 
        lf lf
        if(j == 8) {lf lf}
    }
    lf lf
}

int Sprites_ComparQSort(const void *pElem1, const void *pElem2)
{
    //printf("(*(SStockSpr**) pElem1)->nPrio %d ; (*(SStockSpr**) pElem2)->nPrio) %d", (*(SStockSpr**) pElem1)->nPrio, (*(SStockSpr**) pElem2)->nPrio);lf
    return ((*(struct SStockSpr**)pElem1)->nPrio - (*(struct SStockSpr**) pElem2)->nPrio);
}

void Sprites_BlitBkgGrid(void){
    u8 *screen = gGen.pScreen->pixels;
    u16 pitch  = gGen.pScreen->pitch;

    u8 *pGrid = gGen.pBackground_Grid->pixels;

    int ik=0;
    for (int i = 0; i < 240; i++)
    {
        for (int j=0; j < 320; j++)
        {
            int color = pGrid[ik++];
            if(color != COLOR_PINK_IDX){
                *(screen + (i*pitch) + j) = color;
            }
        }
    }
}

void Sprites_BlitAll(void)
{
    qsort(gpSprSort, gnNbSprStock, sizeof(struct SStockSpr *), Sprites_ComparQSort);

    u8 *screen = gGen.pScreen->pixels;
    u16 pitch  = gGen.pScreen->pitch;

    // nbSprstock sera RAZ à la fin.
    for (int idx = 0; idx < gnNbSprStock; idx++)
    {
        SSprite *pSpr = Sprites_GetDesc(gpSprSort[idx]->nNoSpr);
        SStockSpr *stock = gpSprSort[idx];

        int ik=0;
        for (int iy = stock->nPosY, j=0; j < pSpr->h; iy++, j++)
        {
            for (int ix = stock->nPosX, i=0; i < pSpr->w; ix++, i++)
            {
                int color = pSpr->pGfx[ik++];
                if(color != COLOR_PINK_IDX){
                    *(screen + (iy*pitch) + ix) = color;
                }
            }
        }
    }

    gnNbSprStock = 0;
}

void Sprites_Stock(s32 noSpr, s32 x, s32 y, s32 prio) 
{   
    if(noSpr == SPR_NOSPRITE) {
        return;
    };

    gpStockSpr[gnNbSprStock].nNoSpr=noSpr;
    gpStockSpr[gnNbSprStock].nPosX=x;
    gpStockSpr[gnNbSprStock].nPosY=y;
    gpStockSpr[gnNbSprStock].nPrio=prio;
    gpSprSort[gnNbSprStock] = &gpStockSpr[gnNbSprStock]; // Pour le tri.
    gnNbSprStock++;
}

void Sprites_ExtractBkgs(char *pFilenames[])
{
    for (int i = 0; i < BKGs_MAX; i++)
    {
        gGen.pBkg[i] = SDL_LoadBMP(pFilenames[i]);
        if (gGen.pBkg[i] == NULL)
        {
            fprintf(stdout, "%s line %d : File %s upload failed : %s", __FILE__, __LINE__, pFilenames[i], SDL_GetError());
            exit(EXIT_FAILURE);
        }
    }
    Sprites_SetPalette(gGen.pBkg[0], PALETTE_IDX_BKG);
}

SSprite *Sprites_GetDesc(int noSpr)
{
    return &gpSpr[noSpr];
}

void Sprites_DisplayData(void)
{
    char* pNameSprStart=NULL;

    if(gnNbSpr==e_Spr_Lolo_Down_Stand)
    {
        pNameSprStart="Lolo_Down_Stand";
    }
    else if(gnNbSpr==e_Spr_Lolo_Walk_Down)
    {
        pNameSprStart="Lolo_Walk_Down";
    }
    else if(gnNbSpr==e_Spr_Lolo_Left_Stand)
    {
        pNameSprStart="Lolo_Left_Stand";
    }
    else if(gnNbSpr==e_Spr_Lolo_Walk_Left)
    {
        pNameSprStart="Lolo_Walk_Left";
    }
    else if(gnNbSpr==e_Spr_Lolo_Up_Stand)
    {
        pNameSprStart="Lolo_Up_Stand";
    }
    else if(gnNbSpr==e_Spr_Lolo_Walk_Up)
    {
        pNameSprStart="Lolo_Walk_Up";
    }
    else if(gnNbSpr==e_Spr_Lolo_Right_Stand)
    {
        pNameSprStart="Lolo_Right_Stand";
    }
    else if(gnNbSpr==e_Spr_Lolo_Walk_Right)
    {
        pNameSprStart="Lolo_Walk_Right";
    }
    else if(gnNbSpr==e_Spr_Lolo_Sleep_Down)
    {
        pNameSprStart="Lolo_Sleep_Down";
    }
    else if(gnNbSpr==e_Spr_Lolo_Sleep_Left)
    {
        pNameSprStart="Lolo_Sleep_Left";
    }
    else if(gnNbSpr==e_Spr_Lolo_Sleep_Up)
    {
        pNameSprStart="Lolo_Sleep_Up";
    }
    else if(gnNbSpr==e_Spr_Lolo_Sleep_Right)
    {
        pNameSprStart="Lolo_Sleep_Right";
    }
    else if(gnNbSpr==e_Spr_Lolo_Win)
    {
        pNameSprStart="Lolo_Win";
    }
    else if(gnNbSpr==e_Spr_Lolo_DeadByArrow)
    {
        pNameSprStart="Lolo_DeadByArrow";
    }
    else if(gnNbSpr==e_Spr_Lolo_DeadByBurnt)
    {
        pNameSprStart="Lolo_DeadByBurnt";
    }
    else if(gnNbSpr==e_Spr_Lolo_DeadFinal)
    {
        pNameSprStart="Lolo_DeadFinal";
    }
    else
    {
        pNameSprStart=" ";
    }

    printf("Spr no %d :\t, lg %d, ht %d, refX %d, refY %d, %s", gnNbSpr+1, gpSpr[gnNbSpr].w, gpSpr[gnNbSpr].h, gpSpr[gnNbSpr].PtRefX, gpSpr[gnNbSpr].PtRefY, pNameSprStart);lf
}

void Sprites_DisplaySpr(void)
{
    int ik=0;
    for (int iy = 0; iy < gpSpr[gnNbSpr].h; iy++)
    {
        for (int ix = 0; ix < gpSpr[gnNbSpr].w; ix++)
        {
            printf("%d \t", gpSpr[gnNbSpr].pGfx[ik++]);
        } lf
    } lf 
}

void Sprites_DisplayMaskSpr(void)
{
    int ik=0;
    for (int iy = 0; iy < gpSpr[gnNbSpr].h; iy++)
    {
        for (int ix = 0; ix < gpSpr[gnNbSpr].w; ix++)
        {
            printf("%d \t", gpSpr[gnNbSpr].pMask[ik++]);
        } lf
    } lf
}

void Sprites_Init(void)
{
    memset(gpSpr, 0, (NBELEM(gpSpr)*sizeof(SSprite)));
    gnNbSpr=0;
    gnNbSprStock=0;
}

void Sprites_SetPalette(SDL_Surface *pPlanche, int paletteIdx)
{
    SDL_Color *pSrc = pPlanche->format->palette->colors;

    if(paletteIdx == PALETTE_IDX_BKG)
    {
        for (int i = paletteIdx; i < 128; i++)
        {
            gGen.pColor[i] = pSrc[i];
        }
    }
    else
    {
        for (int i = paletteIdx; i < 256; i++)
        {
            gGen.pColor[i] = pSrc[i];
        }
    }

    SDL_SetPalette(gGen.pScreen, SDL_LOGPAL|SDL_PHYSPAL, gGen.pColor, 0, 255);
     
#ifdef DEBUG
    Sprites_DisplayIdxPalette(gGen.pColor);
#endif
}

void Sprites_ExtractSprSheet(char *pFilename)
{
    #ifdef DEBUG
        u32 nOldNbSprPlanche = gnNbSpr; // Nb de sprites par planche voir ligne 264.
    #endif    

    SDL_Surface *pPlanche = Sprites_LoadBMP(pFilename);
    
    //if(gGen.pColor == NULL) // Voir pourquoi pColor est pas NULL au départ.
    {
        Sprites_SetPalette(pPlanche, PALETTE_IDX_SPR);
    }

    u8 *pix = pPlanche->pixels;
    u16 pitch = pPlanche->pitch;

    int nSizePlanche = pitch*pPlanche->h;
    
    // Extraction of the sprites.
    // Note : pour le point de ref en X et Y on compte à partir de 0 donc si sprite de 16 le pt de ref X est comme ici de 7 et non de 8.
    for (int i = 0; i < nSizePlanche; i++)
    {
        if (*pix == COLOR_PINK_IDX)
        {
            u8 *pix1 = pix;
           // Recovery width, height and points references :
           // Width + ref in x :
           int lg = 1, refX __attribute__((unused)) = 0 ;
            while (*pix1 != COLOR_BLUE_IDX || *(pix1+1) != COLOR_BLUE_IDX)
            {
                if(*pix1 == COLOR_BLUE_IDX)
                {
                    refX = lg-1;
                }
                lg++; // Placé ici car on part de 0 quand on compte les pixels du sprites. Sinon ptRefX et Y seront à la position +1 au lieu de 0.
                pix1++;
            }
            lg--; // Sinon 17 au lieu de 16

            pix1 = pix;
            // Height + ref in y :
            int ht = 1, refY  __attribute__((unused)) = 0;
            while (*pix1 != COLOR_BLUE_IDX || *(pix1+pitch) != COLOR_BLUE_IDX)
            {
                if (*pix1 == COLOR_BLUE_IDX)
                {
                    refY = ht-1;
                }
                ht++;
                pix1+=pitch;
            }
            ht--; // Sinon 17 au lieu de 16

            // Recovery w, h and refx and y in struct gpSpr. 
            gpSpr[gnNbSpr].PtRefX = refX; 
            gpSpr[gnNbSpr].PtRefY = refY;
            gpSpr[gnNbSpr].w = lg-2; // -2 for remove border.
            gpSpr[gnNbSpr].h = ht-2;

            // Recovery gfx :
            int nbPix = gpSpr[gnNbSpr].w * gpSpr[gnNbSpr].h; // Number pixels per sprites.
            gpSpr[gnNbSpr].pGfx=malloc(sizeof(u8)*nbPix*2); // *2 beacause add mask.
            if (gpSpr[gnNbSpr].pGfx == NULL)
            {
                printf("Memory allocation for sprite numero : %d failed  memory for sprite.", gnNbSpr);
                Sprites_Release();
                exit(EXIT_FAILURE);
            }
            
            gpSpr[gnNbSpr].pMask=gpSpr[gnNbSpr].pGfx+nbPix;

            int ik=0;
            for (int iy = 1; iy < ht-1; iy++) // -1 car on s'arrête avant la bordure.
            {
                for (int ix = 1; ix < lg-1; ix++) // -1 aussi Idem.
                {
                    u8 color = *(pix+(iy*pitch)+ix);
                    gpSpr[gnNbSpr].pGfx[ik] = color;
                    gpSpr[gnNbSpr].pMask[ik++] = color != COLOR_PINK_IDX ? COLOR_WHITE_IDX : COLOR_BLACK_IDX;
                }
            }

            // Remove spr.
            for (int iy = 0; iy < ht; iy++)
            {
                for (int ix = 0; ix < lg; ix++)
                {
                    *(pix+(iy*pitch)+ix)=COLOR_BLUE_IDX;
                }
            }
            #ifdef DEBUG
                Sprites_DisplayData();
                //Sprites_DisplaySpr();
                //Sprites_DisplayMaskSpr();
                //printf("gnNbSpr %d", gnNbSpr);lf
            #endif        
            gnNbSpr++;
        }
        pix++;
    }
#ifdef DEBUG
        printf("Nb de sprites pour la planche %s : %d", pFilename, gnNbSpr-nOldNbSprPlanche); lf
#endif        
}

SDL_Surface *Sprites_LoadBMP(char *pFilename)
{
    SDL_Surface *BMP = SDL_LoadBMP(pFilename);
    if (BMP == NULL)
    {
        fprintf(stdout, "failed to Load BMP file: %s ", SDL_GetError());
        exit(0);
    }
    return BMP;
} 

void Sprites_FreeAllBMPs(SDL_Surface *pBMPs, int size)
{
    for (int i = 0; i < size; i++)
    {
        SDL_FreeSurface(&pBMPs[i]);
    }
}

void Sprites_Release(void)
{
    for (int i = 0; i < gnNbSpr; i++)
    {
        free(gpSpr[i].pGfx);
        gpSpr[i].pGfx = NULL;
    }
    
}
