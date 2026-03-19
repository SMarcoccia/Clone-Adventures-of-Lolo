
#include "includes.h"
// Valeur en largeur de la Moitié d'un sprite 8
#define SPR_WIDTTH_HALF 8

const bool bIsCommentary=true;

SExg gExg;
SPlayer gPlyr;

u32 gnMstNoSlot;
u32 gnOldPosPlyrX;
u32 gnOldPosPlyrY;

const u32 SPACE_CASE = 3;

static bool isKeyPressed=false; // Appuie sur une touche ?

// Ne devrait pas être là
void Game_DisplayMonster(void)
{
    for (int i = 0; i < MST_MAX_SLOTS; i++)
    {
        printf(" MONSTERS : No spr %d, posX %d, posY %d",
        gMst[i].nNoSpr,
        gMst[i].nPosX,
        gMst[i].nPosY
        ); lf
    }
}
// Ne devrait pas être là
void Game_DisplayItems(void)
{
    for (int i = 0; i < gItemsLvls[gGen.nLevel].nNbItems; i++)
    {
        printf("ITEMS : No spr %d, posX %d, posY %d",
        gItemsLvls[gGen.nLevel].pItemsLvl[i].nNoSpr,
        gItemsLvls[gGen.nLevel].pItemsLvl[i].nPosX,
        gItemsLvls[gGen.nLevel].pItemsLvl[i].nPosY
        ); lf
    }
}

u32 Game_IdxMapToCoordinatesX(u32 nIdx){
    return nIdx % AREA_WIDTH;
}

u32 Game_IdxMapToCoordinatesY(u32 nIdx){
    return nIdx / AREA_WIDTH;
}

void Game_InitLevel(u32 nLvl)
{
    gGame.nRemainingHearts=gItemsLvls[nLvl].pItemsType.nHearts;
    gGame.nPhase=e_Game_Normal;
    gGame.nLevel=0;
    gGame.nTimerLevelDisplay=TIMER_DISPLAY_LEVEL; // Pas encore utilisé


    // Init du level
    for (u32 i = 0; i < AREA_WIDTH*AREA_HEIGHT; i++)
    {
        s16 nBox=gpLevels[nLvl][i];
        if(nBox != -1){
            // Pour les Monstres statique (lié au collision avec le player)
            if(nBox != e_Spr_Lolo_Down_Stand && nBox != e_Spr_Player_Shoot_Left && nBox != e_Spr_Square){
                // Sol
                if(nBox == e_Spr_Ground || nBox == e_Spr_Ground+1 || (nBox >= e_Spr_Grass_End && nBox < e_Spr_Water_Shade)){
                    gArea[i].nSprNo=nBox;
                    gArea[i].nType=e_Area_Ground;
                    gArea[i].isSolid=e_Area_Empty;
                    gArea[i].nDir=-1;
                    gArea[i].nBlkX=Game_IdxMapToCoordinatesX(i);
                    gArea[i].nBlkY=Game_IdxMapToCoordinatesY(i);
                } // Sable
                else if ((nBox >=e_Spr_Sand_End && nBox < e_Spr_Grass_End))
                {
                    gArea[i].nSprNo=nBox;
                    gArea[i].nType=e_Area_Sand;
                    gArea[i].isSolid=e_Area_Empty;
                    gArea[i].nDir=-1;
                    gArea[i].nBlkX=Game_IdxMapToCoordinatesX(i);
                    gArea[i].nBlkY=Game_IdxMapToCoordinatesY(i);
                } // Footbridge
                else if (nBox >= e_Spr_Footbridge && nBox < e_Spr_Door){
                    gArea[i].nSprNo=nBox;
                    gArea[i].nType=e_Area_Bridge;
                    gArea[i].isSolid=e_Area_Empty;
                    gArea[i].nDir=-1;
                    gArea[i].nBlkX=Game_IdxMapToCoordinatesX(i);
                    gArea[i].nBlkY=Game_IdxMapToCoordinatesY(i);
                } // Stone
                else if (nBox == e_Spr_Stone || nBox == e_Spr_Stone+1)
                {
                    gArea[i].nSprNo=nBox;
                    gArea[i].nType=e_Area_Stone;
                    gArea[i].isSolid=e_Area_Solid;
                    gArea[i].nDir=-1;
                    gArea[i].nBlkX=Game_IdxMapToCoordinatesX(i);
                    gArea[i].nBlkY=Game_IdxMapToCoordinatesY(i);
                } // Tree
                else if (nBox == e_Spr_Tree || nBox == e_Spr_Tree+1)
                {
                    gArea[i].nSprNo=nBox;
                    gArea[i].nType=e_Area_Tree;
                    gArea[i].isSolid=e_Area_Solid;
                    gArea[i].nDir=-1;
                    gArea[i].nBlkX=Game_IdxMapToCoordinatesX(i);
                    gArea[i].nBlkY=Game_IdxMapToCoordinatesY(i);
                } // Emerald Block
                else if (nBox == e_Spr_Emerald_Block)
                {
                    gArea[i].nSprNo=nBox;
                    gArea[i].nType=e_Area_Block;
                    gArea[i].isSolid=e_Area_Solid;
                    gArea[i].nDir=-1;                    
                    gArea[i].nBlkX=Game_IdxMapToCoordinatesX(i);
                    gArea[i].nBlkY=Game_IdxMapToCoordinatesY(i);
                } // Heart
                else if (nBox == e_Spr_Heart || nBox == e_Spr_Heart+1)
                {
                    gArea[i].nSprNo=nBox;
                    gArea[i].nType=e_Area_Heart;
                    gArea[i].isSolid=e_Area_Solid;
                    gArea[i].nDir=-1; 
                    gArea[i].nBlkX=Game_IdxMapToCoordinatesX(i);
                    gArea[i].nBlkY=Game_IdxMapToCoordinatesY(i);
                } // Chest
                else if (nBox >= e_Spr_Chest_Lock && nBox < e_Spr_Hammer)
                {
                    gArea[i].nSprNo=nBox;
                    gArea[i].nType=e_Area_Chest;
                    gArea[i].isSolid=e_Area_Solid;
                    gArea[i].nDir=-1; 
                    gArea[i].nBlkX=Game_IdxMapToCoordinatesX(i);
                    gArea[i].nBlkY=Game_IdxMapToCoordinatesY(i);
                } // Arrow
                else if (nBox >= e_Spr_Arrow_Changer && nBox < e_Spr_Footbridge)
                {
                    gArea[i].nSprNo=nBox;
                    gArea[i].nType=e_Area_Arrow;
                    gArea[i].isSolid=e_Area_Solid;

                    switch (nBox)
                    {
                        // Down
                        case e_Spr_Arrow_Changer:
                            // On inverse les bits pour effectuer la comparaison avec la direction du joueur, permettra de savoir si la direction du joueur 
                            // est opposé à celle de la flèche pour empêcher de passer (Voir Game_PlyrCheckDepl ligne 486)
                            // Note : Pour savoir la direction de la flèche il suffira d'inverser les bits à nouveau.
                            gArea[i].nDir = ~e_Dir_Down; 
                            break;
                        // Left
                        case e_Spr_Arrow_Changer+1:
                            gArea[i].nDir = ~e_Dir_Right; 
                            break;
                        // Up
                        case e_Spr_Arrow_Changer+2:
                            gArea[i].nDir = ~e_Dir_Up; 
                            break;
                        // Right
                        case e_Spr_Arrow_Changer+3:
                            gArea[i].nDir = ~e_Dir_Left; 
                            break;
                    }
                    gArea[i].nBlkX=Game_IdxMapToCoordinatesX(i);
                    gArea[i].nBlkY=Game_IdxMapToCoordinatesY(i);
                } // Porte
                else if (nBox >= e_Spr_Door && nBox < e_Spr_Wall_Corner_TopView)
                {
                    gArea[i].nSprNo=nBox;
                    gArea[i].nType=e_Area_Door;
                    gArea[i].isSolid=e_Area_Solid;
                    gArea[i].nDir=-1; 
                    gArea[i].nBlkX=Game_IdxMapToCoordinatesX(i);
                    gArea[i].nBlkY=Game_IdxMapToCoordinatesY(i);                    
                } // Murs
                else if (nBox >= e_Spr_Wall_Corner_TopView && nBox < e_Spr_Sand_End)
                {
                    gArea[i].nSprNo=nBox;
                    gArea[i].nType=e_Area_Border;
                    gArea[i].isSolid=e_Area_Solid;
                    gArea[i].nDir=-1; 
                    gArea[i].nBlkX=Game_IdxMapToCoordinatesX(i);
                    gArea[i].nBlkY=Game_IdxMapToCoordinatesY(i);
                }
                // Eau
                else if (nBox >= e_Spr_Water_Shade && nBox < e_Spr_Lava_Shade)
                {
                    gArea[i].nSprNo=nBox;
                    gArea[i].nType=e_Area_Water;
                    gArea[i].isSolid=e_Area_Solid;
                    gArea[i].nDir=-1; 
                    gArea[i].nBlkX=Game_IdxMapToCoordinatesX(i);
                    gArea[i].nBlkY=Game_IdxMapToCoordinatesY(i);                    
                } // Lave
                else if (nBox >= e_Spr_Lava_Shade && nBox < e_Spr_Snakey_Stand_Left)
                {
                    gArea[i].nSprNo=nBox;
                    gArea[i].nType=e_Area_Lava;
                    gArea[i].isSolid=e_Area_Solid;
                    gArea[i].nDir=-1; 
                    gArea[i].nBlkX=Game_IdxMapToCoordinatesX(i);
                    gArea[i].nBlkY=Game_IdxMapToCoordinatesY(i);                    
                } // Monstres             
                else if(
                    (nBox >= e_Spr_Snakey_Stand_Left && nBox < e_Spr_Alma_Down_Stand) ||
                    (nBox >= e_Spr_Leeper_Sleeping_Down && nBox < e_Spr_Rocky_Stand_Down) ||
                    (nBox >= e_Spr_Skull_Stand_Down && nBox < e_Spr_DonMedusa_Stand) ||
                    (nBox >= e_Spr_Whale_Stand_Down && nBox < e_Spr_Square)
                ){
                    gArea[i].nSprNo=nBox;
                    gArea[i].nType=e_Area_Mst;
                    gArea[i].isSolid=e_Area_Solid;
                    gArea[i].nDir=-1;
                    gArea[i].nBlkX=Game_IdxMapToCoordinatesX(i);
                    gArea[i].nBlkY=Game_IdxMapToCoordinatesY(i);                    
                }
            }
        }
    }

    for (u32 i = 0; i < gMstsLvls[nLvl].nNbMsts; i++)
    {
        if(gMst[i].nUsed){

            SMonster sMst=gMst[i];

            // Ajout des mst static dans la scène
            if(
                sMst.nName == e_Mst_Leeper || sMst.nName == e_Mst_Skull ||
                sMst.nName == e_Mst_Snakey || sMst.nName == e_Mst_Gol ||
                sMst.nName == e_Mst_Whale
            ){
                u32 nBlkX=sMst.nPosX >> 12;
                u32 nBlkY=sMst.nPosY >> 12;
                gArea[nBlkY*AREA_WIDTH+nBlkX].nSprNo=sMst.nNoSpr;
                gArea[nBlkY*AREA_WIDTH+nBlkX].nType=e_Area_Mst;
                gArea[nBlkY*AREA_WIDTH+nBlkX].isSolid=e_Area_Solid;
                gArea[nBlkY*AREA_WIDTH+nBlkX].nDir=sMst.nDir; 
                gArea[nBlkY*AREA_WIDTH+nBlkX].nBlkX=nBlkX;
                gArea[nBlkY*AREA_WIDTH+nBlkX].nBlkY=nBlkY;
            }
        }
    }
    //Level_Display(gpLevels[gGame.nLevel], false);
}

void Game_CollidePlyrRecalage(SPlayer* pPlyr, u32 nLastPosX, u32 nLastPosY){

    switch (pPlyr->nDir)
    {
        case e_Dir_Up:
            if(bIsCommentary) {info_context lf} 
            if(gPlyr.nLockedDir == e_Kb_Up) gPlyr.nPosY=nLastPosY;
            break;
        case e_Dir_Right:
            if(bIsCommentary) {info_context lf} 
            if(gPlyr.nLockedDir == e_Kb_Right) gPlyr.nPosX=nLastPosX;
            break;
        case e_Dir_Down:
            if(bIsCommentary) {info_context lf} 
            if(gPlyr.nLockedDir == e_Kb_Down) gPlyr.nPosY=nLastPosY;
            break;
        case e_Dir_Left:
            if(bIsCommentary) {info_context lf} 
            if(gPlyr.nLockedDir == e_Kb_Left) gPlyr.nPosX=nLastPosX;
            break;
    }
}

void Game_PlyrRecalage(SPlayer* pPlyr, u32 nLastPosX, u32 nLastPosY){

    switch (pPlyr->nDir)
    {
        case e_Dir_Up:
            if(bIsCommentary){info_context lf}
            if((gPlyr.nPosY & 0xF00) == 0x800) return; // On recale que sur un bloc plein.
            gPlyr.nPosY = (nLastPosY & ~0xF00);
            if(bIsCommentary){info_context lf}
            break;
        case e_Dir_Right:
            if((gPlyr.nPosX & 0xF00) == 0x800) return; // On recale que sur un bloc plein.
            gPlyr.nPosX &= ~0xF00;
            break;
        case e_Dir_Down:
            if((gPlyr.nPosY & 0xF00) == 0x800) return; // On recale que sur un bloc plein.
            gPlyr.nPosY &= ~0xF00;
            break;
        case e_Dir_Left:
            if((gPlyr.nPosX & 0xF00) == 0x800) return; // On recale que sur un bloc plein.
            gPlyr.nPosX = nLastPosX & ~0xF00;
            break;
    }
}

void Game_CollidePlyrItem(u32 nLvl)
{
    s16 *pLvls=gpLevels[nLvl];
    // Comma fixed to pixel
    s32 nPlyrPosRefX=(gPlyr.nPosX + 0x800) >> 8;
    s32 nPlyrPosRefY=(gPlyr.nPosY + 0x800) >> 8;

    s32 nPlyrCol=nPlyrPosRefX >> 4;
    s32 nPlyrLine=nPlyrPosRefY >> 4;

    s32 nSolidCol=nPlyrCol;        
    s32 nSolidLine=nPlyrLine;

    s32 nSolidPosRefY=0;
    //s32 nSolidPosRefX=0;    


    //Level_DisplayLevel(gpLevels[nLvl]);
    // Sur un coeur ?
    if(gArea[(nPlyrLine)*AREA_WIDTH+nPlyrCol].isSolid==true && pLvls[(nPlyrLine)*AREA_WIDTH+nPlyrCol]){
        nSolidPosRefY=((nPlyrLine) << 4) + SPR_SIZE/2;
        //nSolidPosRefX=(nPlyrCol << 4) + SPR_SIZE/2;
    }

    // On test le player avec les items se trouvant dans gItemsLvls.
    // i==3 et le nb d'él" avec -1 car on ne test pas le perso avec lui-même.
    for (int i = 0; i < gItemsLvls[nLvl].nNbItems; i++)
    {
        // Sur la même case (en x on ne doit pas être sur une demi-case) ?
        if(abs(nPlyrPosRefY-nSolidPosRefY) == 0 && (gPlyr.nPosX & 0xF00) == 0)
        {
            u32 nCol=gItemsLvls[nLvl].pItemsLvl[i].nColumns;
            u32 nLine=gItemsLvls[nLvl].pItemsLvl[i].nLines;
            if(gItemsLvls[nLvl].pItemsLvl[i].nNoSpr == e_Spr_Heart && gItemsLvls[nLvl].pItemsLvl[i].nUsed && nSolidCol == nCol && nSolidLine == nLine)
            {
                gGame.nRemainingHearts--;
                Items_ReleaseSlot(gItemsLvls[nLvl].pItemsLvl[i].nNoSlot);
                gArea[nLine*AREA_WIDTH + nCol].isSolid=false;
                gArea[nLine*AREA_WIDTH + nCol].nType=e_Area_Empty;
                gpLevels[nLvl][nLine*AREA_WIDTH + nCol]=e_Spr_Ground+1;
            }else{

            }
        }
    }
}

bool Game_Collide(u32 nNoSpr1, u32 nPosX1, u32 nPosY1, u32 nNoSpr2, u32 nPosX2, u32 nPosY2)
{
    struct SSprite *pSpr1 = Sprites_GetDesc(nNoSpr1);
    struct SSprite *pSpr2 = Sprites_GetDesc(nNoSpr2);
    // Calcul fait à partir du centre des 2 sprites. On pourrai le faire avec les cases.
    s32 nX1=nPosX1+pSpr1->PtRefX;
    s32 nY1=nPosY1+pSpr1->PtRefY;
    s32 nX2=nPosX2+pSpr2->PtRefX;
    s32 nY2=nPosY2+pSpr2->PtRefY;
    s32 nGapX1_X2 = abs(nX1-nX2); // Distance entre les 2 points de référence des sprites.
    s32 nGapY1_Y2 = abs(nY1-nY2);
    s32 nGapMaxSprsX = (pSpr1->w+pSpr2->w)/2; // Distance max entre les 2 sprites pour qu'il soit en collision.
    s32 nGapMaxSprsY = (pSpr1->h+pSpr2->h)/2;
    // ATTENTION manque des valeurs
    if(nGapX1_X2 < nGapMaxSprsX && nGapY1_Y2 < nGapMaxSprsY)
    {
        return true;
    }
    return false;
}

// Ancienne fonction mais toujours utiilsé, qui n'utilise pas le tableau des cases solides.
bool Game_CollidePlyrDecor(u32 nLvl)
{
    u32 k=0;
    u32 nCasePlyrX=0;
    u32 nCasePlyrY=0;
    u32 nCasePlyrMinX=((float)(gPlyr.nPosX >> 8)/SCR_WIDTH)*AREA_WIDTH;
    u32 nCasePlyrMaxX=((float)((gPlyr.nPosX >> 8)+(SPR_SIZE-1))/SCR_WIDTH)*AREA_WIDTH;
    u32 nCasePlyrMinY=((float)(gPlyr.nPosY >> 8)/SCR_HEIGHT)*AREA_HEIGHT;
    u32 nCasePlyrMaxY=((float)((gPlyr.nPosY >> 8)+(SPR_SIZE-1))/SCR_HEIGHT)*AREA_HEIGHT;
    u32 nKMin=0;
    u32 nKMax=0;
    bool isCollide=false;
    // Attention on compte les case à partir de 0.
    // On calcul à partir de l'origine du sprite, i.e coin supérieur gauche et on ajoute SPR_SIZE-1 pour avoir une collision du 
    // sprite coin supérieur droit. -1 pour évité que le sprite se retrouve virtuellement sur la case suivante.
    if (gPlyr.nDir == e_Dir_Right)
    {
        nCasePlyrX=nCasePlyrMaxX;
        // On calcul les cases de la ligne ou se trouve le player et celle du dessous (Ligne + 1).
        nKMin=(nCasePlyrX)+(nCasePlyrMinY)*20;
        nKMax=(nCasePlyrX)+(nCasePlyrMaxY)*20;
        if (gpLevels[nLvl][nKMin] == e_Spr_Ground+1 || gpLevels[nLvl][nKMax] != e_Spr_Ground+1)
        {
            nCasePlyrY=nCasePlyrMaxY;
        }
        else
        {
            nCasePlyrY=nCasePlyrMinY;
        }
    }
    else if (gPlyr.nDir==e_Dir_Down)
    {
        nCasePlyrY=nCasePlyrMaxY;
        nKMin=(nCasePlyrMinX)+(nCasePlyrY)*20;
        nKMax=(nCasePlyrMaxX)+(nCasePlyrY)*20;  
        if (gpLevels[nLvl][nKMin] == e_Spr_Ground+1 || gpLevels[nLvl][nKMax] != e_Spr_Ground+1)
        {
            nCasePlyrX=nCasePlyrMaxX;
        }
        else
        {
            nCasePlyrX=nCasePlyrMinX;
        }
    }
    else if (gPlyr.nDir==e_Dir_Left)
    {
        nCasePlyrX=nCasePlyrMinX;
        nKMin=(nCasePlyrX)+(nCasePlyrMinY)*20;
        nKMax=(nCasePlyrX)+(nCasePlyrMaxY)*20;
        if (gpLevels[nLvl][nKMin] == e_Spr_Ground+1 || gpLevels[nLvl][nKMax] != e_Spr_Ground+1)
        {
            nCasePlyrY=nCasePlyrMaxY;
        }
        else
        {
            nCasePlyrY=nCasePlyrMinY;
        }
    }
    else if (gPlyr.nDir==e_Dir_Up)
    {
        nCasePlyrY=nCasePlyrMinY;
        nKMin=(nCasePlyrMinX)+(nCasePlyrY)*20;
        nKMax=(nCasePlyrMaxX)+(nCasePlyrY)*20;  
        if ((gpLevels[nLvl][nKMin] == e_Spr_Ground+1 || gpLevels[nLvl][nKMax] != e_Spr_Ground+1 ) && (gpLevels[nLvl][nKMin] == e_Spr_Heart  || gpLevels[nLvl][nKMax] != e_Spr_Heart))
        {
            nCasePlyrX=nCasePlyrMaxX;
        }
        else
        {
            nCasePlyrX=nCasePlyrMinX;
        }
    }
    
    // Décor :
    k=(nCasePlyrX)+(nCasePlyrY)*20;
    if(gpLevels[nLvl][k]==e_Spr_Stone || gpLevels[nLvl][k]==e_Spr_Stone+1)
    {
        gPlyr.nPosX=gnOldPosPlyrX ;
        gPlyr.nPosY=gnOldPosPlyrY;
        isCollide=true;
    }
    if(gpLevels[nLvl][k]==e_Spr_Tree || gpLevels[nLvl][k]==e_Spr_Tree+1)
    {
        gPlyr.nPosX=gnOldPosPlyrX;
        gPlyr.nPosY=gnOldPosPlyrY;
        isCollide=true;
    }
    // TODO : lava and water.

    gnOldPosPlyrX=gPlyr.nPosX;
    gnOldPosPlyrY=gPlyr.nPosY;
    return isCollide;
}

bool Game_CollidePlyrWalls(void)
{
    bool isCollide=false;
    
    s32 nPlyrX=gPlyr.nPosX >> 8;
    s32 nPlyrY=gPlyr.nPosY >> 8;;
    if(bIsCommentary){info_context printf("gPlyr.nSpeed %d", gPlyr.nSpeed);lf}

    // Player-murs :
    // Position X = 0 :
    if(nPlyrX < WALL_COLMin)
    {    
        nPlyrX=WALL_COLMin; // On repositionne le sprite.
        gPlyr.nPosX = nPlyrX << 8;
        isCollide=true;
    }
    // Position Y = 0 :
    else if(nPlyrY < WALL_LINEMin)
    {    
        nPlyrY=WALL_LINEMin;
        gPlyr.nPosY = nPlyrY << 8;
        isCollide=true;
    }
    // Position X = 320 :
    else if(nPlyrX + SPR_SIZE > WALL_COLMax)
    {    
        nPlyrX=WALL_COLMax-SPR_SIZE;
        gPlyr.nPosX = nPlyrX << 8;
        isCollide=true;
    }
    // Position Y = 240 :
    else if(nPlyrY + SPR_SIZE > WALL_LINEMax)
    {    
        nPlyrY=WALL_LINEMax-SPR_SIZE;
        gPlyr.nPosY = nPlyrY << 8;
        isCollide=true;
    }

    return isCollide;
}

bool Game_PlyrCheckDepl(SPlayer *pPlyr, u32 nDir){

    u32 nPosBlkX=0, nPosBlkY=0;
    u32 nType=0;

    // Ne vaut que pour un test sur un bloc plein.
    nPosBlkX = pPlyr->nPosX >> 12;
	nPosBlkY = pPlyr->nPosY >> 12;

    switch (nDir)
    {
    case e_Dir_Up:
        if(bIsCommentary){info_context lf}
        if((pPlyr->nPosX & 0xF00) != 0 && (pPlyr->nPosX & 0xF00) != 0x800) return false;
        if((pPlyr->nPosY & 0xF00) == 0) {
            // Ici on verifie si on est sur un demi-bloc en x et s'il y a un solide au-dessus en utilisant posX+0xF00
            if((pPlyr->nPosX & 0xF00) == 0x800){
                nPosBlkX=(pPlyr->nPosX+0xF00) >> 12;
                nPosBlkX=gArea[((nPosBlkY-1) * AREA_WIDTH) + nPosBlkX].isSolid ? nPosBlkX : pPlyr->nPosX >> 12;
            }
            nPosBlkY--;
        }
        if(bIsCommentary){info_context lf}
        break;
    case e_Dir_Right:
        if(bIsCommentary){info_context lf}
        if((pPlyr->nPosY & 0xF00) != 0 && (pPlyr->nPosY & 0xF00) != 0x800) return false;
        if((pPlyr->nPosY & 0xF00) == 0x800){
            nPosBlkY=(pPlyr->nPosY+0xF00) >> 12;
            nPosBlkY=gArea[((nPosBlkY) * AREA_WIDTH) + nPosBlkX+1].isSolid ? nPosBlkY : pPlyr->nPosY >> 12;
        }        
        nPosBlkX++;
        if(bIsCommentary){info_context lf}
        break;
    case e_Dir_Down:
        if(bIsCommentary){info_context lf}
        if((pPlyr->nPosX & 0xF00) != 0 && (pPlyr->nPosX & 0xF00) != 0x800) return false;
        if((pPlyr->nPosX & 0xF00) == 0x800){
            nPosBlkX=(pPlyr->nPosX+0xF00) >> 12;
            nPosBlkX=gArea[((nPosBlkY+1) * AREA_WIDTH) + nPosBlkX].isSolid ? nPosBlkX : pPlyr->nPosX >> 12;
        }
        nPosBlkY++;
        if(bIsCommentary){info_context lf}
        break;
    case e_Dir_Left:
        if(bIsCommentary){info_context lf}
        if((pPlyr->nPosY & 0xF00) != 0 && (pPlyr->nPosY & 0xF00) != 0x800) return false;
        if((pPlyr->nPosX & 0xF00) == 0) {
            if((pPlyr->nPosY & 0xF00) == 0x800){
                nPosBlkY=(pPlyr->nPosY+0xF00) >> 12;
                nPosBlkY=gArea[((nPosBlkY) * AREA_WIDTH) + nPosBlkX-1].isSolid ? nPosBlkY : pPlyr->nPosY >> 12;
            }                 
            nPosBlkX--;
        }
        if(bIsCommentary){info_context lf}
        break;
    }

    // Test des blocs pleins
    if(bIsCommentary){info_context printf("pPlyr->nPosX %d, pPlyr->nPosY %d, %d", pPlyr->nPosX, pPlyr->nPosY, ((pPlyr->nPosX & 0xF00) == 0 || (pPlyr->nPosX & 0xF00) == 0x800) && ((pPlyr->nPosY & 0xF00) == 0 || (pPlyr->nPosY & 0xF00) == 0x800));lf}
    if(((pPlyr->nPosX & 0xF00) == 0 || (pPlyr->nPosX & 0xF00) == 0x800) && ((pPlyr->nPosY & 0xF00) == 0 || (pPlyr->nPosY & 0xF00) == 0x800))
    {
        if(bIsCommentary){info_context lf}
        SAreaBox sArea=gArea[(nPosBlkY * AREA_WIDTH) + nPosBlkX];
        nType = sArea.nType;

        if(bIsCommentary){info_context printf("nType %d", nType);lf}
        // On est sur un bloc plein. Il faut que la case d'à côté soit vide.
        if(nType != e_Area_Ground && nType != e_Area_Sand && nType != e_Area_Chest &&
           nType != e_Area_Heart  && nType != e_Area_Arrow
        ){
            if(bIsCommentary){info_context lf}
            return false;
        }
        // Est-ce que la direction du joueur est opposé à la direction de l'item de la flèche.
        else if ( nType == e_Area_Arrow && pPlyr->nDir == ~sArea.nDir)
        if(bIsCommentary){{info_context lf}
            return false;
        }
    }
    if(bIsCommentary){info_context lf}
    return true;
}

void Game_PlyrMove(void)
{
    if(bIsCommentary){info_context printf("gPlyr.nKb %d, gPlyr.nLockedDir %d, gPlyr.nDir %d, gPlyr.nSpeed %d, gPlyr.nState %d", gPlyr.nKb, gPlyr.nLockedDir, gPlyr.nDir, gPlyr.nSpeed, gPlyr.nState);lf}

    u32 nLastDir=e_Dir_Null;
    u32 nLastKb=e_Kb_Null;

    s32 nLastPosX=gPlyr.nPosX;
    s32 nLastPosY=gPlyr.nPosY;

    // Sert à vérifier si le plyr à changer de bloc ou de demi-bloc.
    u32 nChgBlkX=0;
    u32 nChgBlkY=0;

    if(gPlyr.nState == e_PlyrAnim_Win){
        return;
    }

    if(gPlyr.nState == e_PlyrAnim_Death){
        return;
    }

    gPlyr.nKb=(
          gGen.pKeys[SDLK_UP] ? e_Kb_Up
        : gGen.pKeys[SDLK_RIGHT] ? e_Kb_Right 
        : gGen.pKeys[SDLK_DOWN] ? e_Kb_Down 
        : gGen.pKeys[SDLK_LEFT] ? e_Kb_Left : 0
    );

    // Simuler le clic mettre une variable dans gPlyr nKbSimul

    // Le joueur a-t-il appuyé ?
    if(gPlyr.nKb)
    {
        gPlyr.nCountFrames=TIMER_FRAMES_SLEEPING;
        gGen.nIsStartPlyr=true;
        isKeyPressed=true;           
        nLastDir=gPlyr.nDir;
        gPlyr.nSpeed=PLYR_SPEED_INIT;
        gPlyr.nState=e_PlyrAnim_Walk;

        switch (gPlyr.nKb)
        {
        case e_Kb_Up:
            if(bIsCommentary){info_context lf}
            // On a pas le droit de modifier la direction tant que l'on est pas sur un bloc plein ou un demi-bloc.
            if((gPlyr.nPosX & 0xF00) != 0 && (gPlyr.nPosX & 0xF00) != 0x800) break;
            gPlyr.nDir=e_Dir_Up;
            if(bIsCommentary){info_context lf}
            break;
        case e_Kb_Right:
            if(bIsCommentary){info_context printf("gPlyr.nPosX %d, gPlyr.nPosX >> 8 = %d, BlkX %d, gPlyr.nPosY %d, gPlyr.nPosY >> 8 = %d, BlkY %d", gPlyr.nPosX, gPlyr.nPosX >> 8, gPlyr.nPosX >> 12, gPlyr.nPosY, gPlyr.nPosY >> 8, gPlyr.nPosY >> 12);lf}
            if(bIsCommentary){info_context lf}
            if((gPlyr.nPosY & 0xF00) != 0 && (gPlyr.nPosY & 0xF00) != 0x800) break;
            gPlyr.nDir=e_Dir_Right;
            if(bIsCommentary){info_context lf}
            break;
        case e_Kb_Down:
            if(bIsCommentary){info_context lf}
            if((gPlyr.nPosX & 0xF00) != 0 && (gPlyr.nPosX & 0xF00) != 0x800) break;
            gPlyr.nDir=e_Dir_Down;
            if(bIsCommentary){info_context lf}
            break;
        case e_Kb_Left:
            if(bIsCommentary){info_context printf("(%d & 0xF00) %x != 0,  (%d & 0xF00) %x != 0x800", (gPlyr.nPosY), (gPlyr.nPosY & 0xF00), (gPlyr.nPosY), (gPlyr.nPosY & 0xF00)); lf}
            if((gPlyr.nPosY & 0xF00) != 0 && (gPlyr.nPosY & 0xF00) != 0x800) break;
            gPlyr.nDir=e_Dir_Left;
            if(bIsCommentary){info_context lf}
            break;
        }

        if( ! Game_PlyrCheckDepl(&gPlyr, gPlyr.nDir))
        {
            gPlyr.nSpeed=0;
        }
    }
    else
    {
        isKeyPressed=false;
        if(--gPlyr.nCountFrames <= 0)
        {
            gPlyr.nState=e_PlyrAnim_Sleeping;
        }

        if(((gPlyr.nPosX & 0xF00) == 0 || (gPlyr.nPosX & 0xF00) == 0x800) && ((gPlyr.nPosY & 0xF00) == 0 || (gPlyr.nPosY & 0xF00) == 0x800))
        {
            gPlyr.nSpeed=0;
            gPlyr.nState=e_PlyrAnim_Idle;
        }

    }
    
    if(gPlyr.nSpeed){

        switch (gPlyr.nDir)
        {
        case e_Dir_Up:
            // Sur un bloc plein ou un demi-bloc ? Non on break.
            if((gPlyr.nPosX & 0xF00) != 0 && (gPlyr.nPosX & 0xF00) != 0x800) break;
            if(bIsCommentary){info_context lf}
            // Permet si collision avec M de se déplacer dans les autres directions opposé à la collision.
            if(gPlyr.nLockedDir == e_Kb_Up) break;
            if(bIsCommentary){info_context lf}
            gPlyr.nPosY -= gPlyr.nSpeed;
            nChgBlkY=(((gPlyr.nPosY+0xF00) ^ (nLastPosY+0xF00)) & 0xF00) == 0xF00 ? 1 : 0;
            break;
        case e_Dir_Right:
            if((gPlyr.nPosY & 0xF00) != 0 && (gPlyr.nPosY & 0xF00) != 0x800) break;
            if(gPlyr.nLockedDir == e_Kb_Right) break;
            if(bIsCommentary){info_context lf}
            gPlyr.nPosX += gPlyr.nSpeed;
            nChgBlkX=((gPlyr.nPosX ^ nLastPosX) & 0xF00) == 0xF00 ? 1 : 0;
            break;
        case e_Dir_Down:
            if((gPlyr.nPosX & 0xF00) != 0 && (gPlyr.nPosX & 0xF00) != 0x800) break;
            if(gPlyr.nLockedDir == e_Kb_Down) break;
            if(bIsCommentary){info_context lf}
            gPlyr.nPosY += gPlyr.nSpeed;
            nChgBlkY=((gPlyr.nPosY ^ nLastPosY) & 0xF00) == 0xF00 ? 1 : 0;
            break;
        case e_Dir_Left:
            if((gPlyr.nPosY & 0xF00) != 0 && (gPlyr.nPosY & 0xF00) != 0x800) break;
            if(gPlyr.nLockedDir == e_Kb_Left) break;
            if(bIsCommentary){info_context lf}
            gPlyr.nPosX -= gPlyr.nSpeed;
            nChgBlkX=(((gPlyr.nPosX + 0xF00) ^ (nLastPosX+0xF00)) & 0xF00) == 0xF00 ? 1 : 0;
            break;
        }

        // NOTE : Faire un recalage ?
        if(nChgBlkX || nChgBlkY)
        {
            Game_PlyrRecalage(&gPlyr, nLastPosX, nLastPosY);
        }
    }

    if(bIsCommentary){info_context printf("gPlyr.nKb %d, gPlyr.nLockedDir %d, gPlyr.nDir %d, gPlyr.nSpeed %d, gPlyr.nState %d", gPlyr.nKb, gPlyr.nLockedDir, gPlyr.nDir, gPlyr.nSpeed, gPlyr.nState);lf}

    Game_CollidePlyrWalls();
    //Game_CollidePlyrDecor(gGen.nLevel); // Remplacé par Game_PlyrCheckDepl
    Game_CollidePlyrItem(gGen.nLevel);
    AnimSpr_PlyrAnimSetIfNew(&gPlyr);

    if(bIsCommentary){info_context printf("gPlyr.nKb %d, gPlyr.nLockedDir %d, gPlyr.nDir %d, gPlyr.nSpeed %d, gPlyr.nState %d", gPlyr.nKb, gPlyr.nLockedDir, gPlyr.nDir, gPlyr.nSpeed, gPlyr.nState);lf}
}

void LoloAdventureGame(void)
{
    static u32 count=0;
    switch (gGame.nPhase)
    {
        case e_Game_Normal:
            // Note : j'ai mis Monster_... avant pour éviter que Monster bouge si player bouge et si on est en collision.
            printf("%d - ", count++); info_context printf(">>>>>>>>>>>>>>>>>>>");lf
            Game_PlyrMove();
            printf("%d - ", count++); info_context printf("===================");lf
            Monsters_MonstersMove(gGen.nLevel);
            if(bIsCommentary){info_context printf("gPlyr.nKb %d, gPlyr.nLockedDir %d, gPlyr.nDir %d, gPlyr.nSpeed %d, gPlyr.nState %d", gPlyr.nKb, gPlyr.nLockedDir, gPlyr.nDir, gPlyr.nSpeed, gPlyr.nState);lf}
            printf("%d - ", count++); info_context printf("<<<<<<<<<<<<<<<<<<<");lf
            break;
        case e_Game_GameOver:
            Game_ExgExit(e_Game_AllClear);
            break;
        case e_Game_LevelCompleted:
            if (gGame.nLevel++ < LEVEL_MAX)
            {
                Game_Init();
                gGame.nPhase = e_Game_Normal;
            // Si on a terminé le jeu.
            }else{ 
                Game_ExgExit(e_Game_AllClear);
            }
            break;
    }
}

void LoloAdventureDraw(void)
{
    u32 nPosX=0, nPosY=0;
    u32 k=0;

    // Placement du décore :
    for (int i = 0; i < AREA_HEIGHT; i++)
    {
        for (int j = 0; j < AREA_WIDTH; j++)
        {
            if(gpLevels[gGame.nLevel][k] != -1)
            {
                Sprites_Stock(gpLevels[gGame.nLevel][k], nPosX, nPosY, e_Prio_Decor);
            }
            k++;
            nPosX+=SPR_SIZE;
        }
        nPosY+=SPR_SIZE;
        nPosX=0;
    }

    // Placement des items :
    // TODO : Optimisation avec le qsort (1 1 1 1 0 0 0 0 ..., si 0 on break).
    for (int i = 0; i < gItemsLvls[gGen.nLevel].nNbItems; i++)
    {
        if(gItemsLvls[gGen.nLevel].pItemsLvl[i].nUsed)
        {
            Sprites_Stock(gItemsLvls[gGen.nLevel].pItemsLvl[i].nNoSpr, gItemsLvls[gGen.nLevel].pItemsLvl[i].nPosX, gItemsLvls[gGen.nLevel].pItemsLvl[i].nPosY, e_Prio_Items);
        }
    }

    // Placement des monstres :
    for (int i = 0; i < MST_MAX_SLOTS; i++)
    {
        if(gMst[i].nUsed == true)
        {
            u32 nNoSpr=0;
            if(gMst[i].pAnim != NULL) 
            {
                nNoSpr = Animspr_GetImg(gMst[i].nAnimNoSlot);
            }
            else
            {
                nNoSpr=gMst[i].nNoSpr;
            }
            Sprites_Stock(nNoSpr, gMst[i].nPosX >> 8, gMst[i].nPosY >> 8, e_Prio_Monsters);
        }
    }
    
    // Placement du Player :
    Sprites_Stock(Animspr_GetImg(gPlyr.nAnimNoSlot), gPlyr.nPosX >> 8, gPlyr.nPosY >> 8, e_Prio_Plyr);
}

void LoloAdventure(void) // Correspond à Breaker dans breaker3264, line 1599. Ici gestion du jeu.
{
    // En pause ?
    if(gGame.nPhase == e_Game_Pause) return;

    LoloAdventureGame();
    LoloAdventureDraw();
}

void Game_InitPlyr(u32 nLvl)
{   
    // Au départ on positionne le plyr en attente down.
    gPlyr.nAnimNoSlot=-1;
    gPlyr.nDir=e_Dir_Down;
    gPlyr.nSpeed=0;

    // Calcul la position en x et en y du player.
    for (u32 i = 0; i < gPlyrsLvls[nLvl].nNbPlyrs; i++)
    {
        //gPlyr.nPosX=gPlyrsLvls[nLvl].pPlyrLvl[i].nColumns << 12;

        /* Conversion des n° de cases (ligne, colonne) de la position du joueur, par exemple : 
              - Si le joueur est en position ligne 12 et colonne 12 alors on convertit en posX et Y puis pour le blit on 
                reconvertira en case. Donc 12 << 12
        */
        u32 nCol=gPlyrsLvls[nLvl].pPlyrLvl[i].nColumns;
        u32 nLine=gPlyrsLvls[nLvl].pPlyrLvl[i].nLines;
        
        // On récupère la position du joueur (4 bits pour la case et 8 bits pour variable fixe) ou autre possibilité colonne/ligne multiplier par taille de la case.
        gPlyr.nPosX=nCol << 12;
        gPlyr.nPosY=nLine << 12;
    }
    gPlyr.nLastPosX=gPlyr.nPosX;
    gPlyr.nLastPosY=gPlyr.nPosY;
    gPlyr.bCollideMst=false;
    gPlyr.nKb=e_Kb_Null;
    gPlyr.nState=e_PlyrAnim_Idle;
    gPlyr.pAnim=gAnim_Plyr_Idle_Down;
    gPlyr.nCountFrames=TIMER_FRAMES_SLEEPING;
    gPlyr.nFlags=0;
    gPlyr.nNbLives=PLYR_LIVES;
    gPlyr.nAnimNoSlot=Animspr_AnimSet(gPlyr.pAnim, gPlyr.nAnimNoSlot);
    gPlyr.nLockedDir=e_Kb_Null;
}

void Game_Init(void)
{
    gGen.nIsStartPlyr=false;
    gGame.bSimulKey=false;
    
    // Init des slots
    Animspr_InitSlots();
    Items_InitSlots();
    Monsters_InitSlots();

    // Init Items, Monster, Player
    Items_InitItems(gGen.nLevel);
    Monsters_InitMonsters(gGen.nLevel);
    Game_InitPlyr(gGen.nLevel);

    Game_InitLevel(gGen.nLevel);
    Level_Display(gpLevels[gGame.nLevel], true);
    if(bIsCommentary){info_context printf("%d", gArea[12*AREA_WIDTH+3].nType); lf}
}

void Game_ExgExit(u32 nExitCode){
    gExg.nExitCode=nExitCode;
    gExg.nLevel=gGame.nLevel; 
}

void Game_ExgInit(){

    gGen.nLevel = 0;
    gGen.nPhase=e_Game_Null;
    gExg.nExitCode = 0;

    Game_Init();
}

void Game(void)
{
    SDL_FillRect(gGen.pScreen, NULL, COLOR_BLACK_IDX);
    // Obligé de le mettre pour supprimer le menu qui reste afficher quelque instant.
    Render_Flip(); 
    // On replace la palette d'origine à cause du fade en fadeInOut ou la palette à été mise à 0.
    SDL_SetPalette(SDL_GetVideoSurface(), SDL_PHYSPAL, gGen.pColor, 0, 256);
    SDL_SetEventFilter(&EventHandler_EventFilter);
    // RAZ Canneaux music.
    Sound_Stop();
    gSound.nModularitySound=gSound.nSoundSaveVolume; 
    Sound_Play(e_Music_Game, SOUND_CHANNEL_MUSIC);
    gGen.pBackground = gGen.pBkg[1];
    gGen.pBackground_Grid = gGen.pBkg[2];

    Game_ExgInit();
    Frame_Init();

    while (gExg.nExitCode == e_Game_Null)
    {
        if(EventHandler_EventHandler(1) == true) break;

        if(gGame.nPhase != e_Game_Pause)
        {
            SDL_BlitSurface(gGen.pBackground , NULL, gGen.pScreen, NULL);

            LoloAdventure();
            //if(gPlyr.nFlags != e_AnimFlag_End)
            {
                //Sound_ReplayMusic(e_Music_Game);
            }
            
            Sprites_BlitAll();
            Sprites_BlitBkgGrid();
        }
        Render_Flip();
    }

    if(gExg.nExitCode == e_Game_GameOver || gExg.nExitCode == e_Game_AllClear){
        // TODO : afficher le code secret du niveau.
    }

    if (gGen.nMouseBtnLeft == true)
    {
        gGen.nMouseBtnLeft = 0;
    }

    Monsters_ClearSlot(); 

}

