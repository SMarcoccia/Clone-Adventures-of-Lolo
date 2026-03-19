#include "includes.h"

// ATTENTION avec les variables global si déclarées dans 2 fichiers .c avec le même nom sera exactement la même variable bien différencier les variables global en
// leurs donnant un nom différent à chacune.

// Taille maximal entre le joueur et le monstre pour la collision. (16 en X 8 en Y ou 8 en X et 16 en Y)
#define DIST_MAX_MTOP 320
const bool bIsCommentaryMonster=false;


// Init une anim d'un monstre
typedef void (*pAnimInit)(SMonster *pMst);
extern pAnimInit gpMstAnimInitTb[];

struct SAreaBox gArea[AREA_WIDTH * AREA_HEIGHT];

// Nombres de blocks qui séparent M et S inclue à la vertical, ex : M à la position 12, S à la position 10, il y a 2 blocs le bloc 11 et 10 (celui du solide).
enum ENbBlk{
    e_NbBlk_1 = 1,
    e_NbBlk_2,
};

// Permettra de rechercher un slot libre en partant du slot suivant après le dernier slot utilisé.
u32 gnMstLastSlotUsed; 
SMonster gMst[MST_MAX_SLOTS];

// Monsters :
// (n° de sprite, nom de l'anim (si pas d'anim NULL) on cast car la paramètre formel est en u64, direction, position en case, si inoffensif ou dangereux) : 
SMstLvl gMstLvl1[]={
    {e_Spr_Snakey_Stand_Left, NULL, e_Dir_Down, 12, 3, e_Mst_Harmless, 0, e_Mst_Snakey},
    //{e_Spr_Rocky_Stand_Down, gAnim_Rocky_Idle_Down, e_Dir_Down, 10, 8, e_Mst_Harmless, MST_SPEED_INIT, e_Mst_Rocky},
    //{e_Spr_Leeper_Down_Stand, gAnim_Leeper_Idle_Down, e_Dir_Down, 11, 2, e_Mst_Harmless, MST_SPEED_INIT, e_Mst_Leeper},
};

SMstLvl gMstLvl2[]={
    {e_Spr_Snakey_Rotate_Left, NULL, e_Dir_Down, 11, 7, e_Mst_Harmless, 0, e_Mst_Snakey},
    {e_Spr_Rocky_Stand_Up, gAnim_Rocky_Idle_Up, e_Dir_Up, 12, 11, e_Mst_Harmless, MST_SPEED_INIT, e_Mst_Rocky},
    //{e_Spr_Leeper_Down_Stand, gAnim_Leeper_Idle_Down, e_Dir_Down, 11, 2, e_Mst_Harmless, MST_SPEED_INIT, e_Mst_Leeper},
};

// TODO : calculer le nombre de monstres au lieu de mettre en dure voir avec NBELEM
SMstsLvls gMstsLvls[]={
    {gMstLvl1, NBELEM(gMstLvl1)},
    {gMstLvl2, 2},
};

void Monster_CollideAdjustingX(u32 nPX, u32 nMX, SMonster *pMst)
{
    // Recalage
    // P gauche M (En X P < M, à Gauche de l'écran par rapport à M)
    if(SGN(nPX-nMX) == -1)
    {
        info_context lf
        gPlyr.nPosX = pMst->nPosX - 0x1000;
        gPlyr.nLockedDir = e_Kb_Right;
    // P droite M (En X P > M, à Droite de l'écran par rapport à M)
    }
    else if(SGN(nPX-nMX) == 1)
    {
        info_context lf
        gPlyr.nPosX = pMst->nPosX + 0x1000;
        gPlyr.nLockedDir = e_Kb_Left;
    }
}

void Monster_CollideAdjustingY(u32 nPY, u32 nMY, SMonster *pMst)
{
    // P au-dessus de M (En Y P < M, en haut de l'écran par rapport à M)                        
    if(SGN(nPY-nMY) == -1){
        info_context lf
        gPlyr.nPosY = pMst->nPosY - 0x1000;
        gPlyr.nLockedDir = e_Kb_Down;
    // P en-dessous de M (En Y P > M, en bas de l'écran par rapport à M)
    }else if(SGN(nPY-nMY) == 1){
        info_context lf
        gPlyr.nPosY = pMst->nPosY + 0x1000;
        gPlyr.nLockedDir = e_Kb_Up;
    }   
}

void Game_MstRecalage(SMonster* pMst){
    //info_context lf
    switch (pMst->nDir)
    {
        // 0xF00 permet de supprimer les valeurs de gauche, ex. : 1010 0001 0... devien 0000 0001 0...
        case e_Dir_Up:
        info_context lf
            // Sur un demi-bloc ?
            if((pMst->nLastPosY & 0xF00) != 0) pMst->nPosY=(pMst->nLastPosY & ~0xF00)+0x800;
            // Sur un bloc plein ?
            else pMst->nPosY=pMst->nLastPosY & ~0xF00;
            break;
        case e_Dir_Right:
        info_context lf
            if((pMst->nPosX & 0xF00) != 0) pMst->nPosX &= ~0xF00-0x800;
            else pMst->nPosX &= ~0xF00;
            break;
        case e_Dir_Down:
        info_context lf
            if((pMst->nPosY & 0xF00) != 0) pMst->nPosY &= ~0xF00+0x800;
            else pMst->nPosY &= ~0xF00;
            break;
        case e_Dir_Left:
        info_context lf
            if((pMst->nLastPosX & 0xF00) != 0) pMst->nPosX=(pMst->nLastPosX & ~0xF00)+0x800;
            else pMst->nPosX = pMst->nLastPosX & ~0xF00;
            break;
    }
}

bool Monsters_CollideDecor(SMonster *pMst, u32 nLvl)
{
    u32 nIsSolid=false;
    u32 nDir=e_Dir_Null;
    // Coordonnées du block ou se trouve le monstre
    // Ne vaut que pour un test sur un bloc plein
    u32 nPosBlkX=pMst->nPosX >> 12;
    u32 nPosBlkY=pMst->nPosY >> 12;

    switch (pMst->nDir)
    {
    case e_Dir_Up:
        if(bIsCommentaryMonster){info_context lf}
        if((pMst->nPosX & 0xF00) != 0 && (pMst->nPosX & 0xF00) != 0x800) return false;
        if((pMst->nPosY & 0xF00) == 0) {
            // Ici on verifie si on est sur un demi-bloc en x et s'il y a un solide au-dessus en utilisant posX+0xF00
            if((pMst->nPosX & 0xF00) == 0x800){
                nPosBlkX=(pMst->nPosX+0xF00) >> 12;
                nPosBlkX=gArea[((nPosBlkY-1) * AREA_WIDTH) + nPosBlkX].isSolid ? nPosBlkX : pMst->nPosX >> 12;
            }
            nPosBlkY--;
        }
        nDir=e_Dir_Left;
        if(bIsCommentaryMonster){info_context lf}
        break;
    case e_Dir_Right:
        if(bIsCommentaryMonster){info_context lf}
        if((pMst->nPosY & 0xF00) != 0 && (pMst->nPosY & 0xF00) != 0x800) return false;
        if((pMst->nPosY & 0xF00) == 0x800){
            nPosBlkY=(pMst->nPosY+0xF00) >> 12;
            nPosBlkY=gArea[((nPosBlkY) * AREA_WIDTH) + nPosBlkX+1].isSolid ? nPosBlkY : pMst->nPosY >> 12;            
        }
        nPosBlkX++;
        nDir=e_Dir_Up;
        if(bIsCommentaryMonster){info_context lf}
        break;
    case e_Dir_Down:
        if(bIsCommentaryMonster){info_context lf}
        if((pMst->nPosX & 0xF00) != 0 && (pMst->nPosX & 0xF00) != 0x800) return false;
        if((pMst->nPosX & 0xF00) == 0x800){
            nPosBlkX=(pMst->nPosX+0xF00) >> 12;
            nPosBlkX=gArea[((nPosBlkY+1) * AREA_WIDTH) + nPosBlkX].isSolid ? nPosBlkX : pMst->nPosX >> 12;            
        }
        nPosBlkY++;
        nDir=e_Dir_Right;
        if(bIsCommentaryMonster){info_context lf}
        break;
    case e_Dir_Left:
        if(bIsCommentaryMonster){info_context lf}
        if((pMst->nPosY & 0xF00) != 0 && (pMst->nPosY & 0xF00) != 0x800) return false;
        if((pMst->nPosX & 0xF00) == 0) {
            if((pMst->nPosY & 0xF00) == 0x800){
                nPosBlkY=(pMst->nPosY+0xF00) >> 12;
                nPosBlkY=gArea[((nPosBlkY) * AREA_WIDTH) + nPosBlkX-1].isSolid ? nPosBlkY : pMst->nPosY >> 12;
            }                 
            nPosBlkX--;            
        }
        nDir=e_Dir_Down;
        if(bIsCommentaryMonster){info_context lf}
        break;
    }

    if(((pMst->nPosX & 0xF00) == 0 || (pMst->nPosX & 0xF00) == 0x800) && ((pMst->nPosY & 0xF00) == 0 || (pMst->nPosY & 0xF00) == 0x800))
    {
        SAreaBox sArea=gArea[(nPosBlkY*AREA_WIDTH)+nPosBlkX];
        nIsSolid=sArea.isSolid;

        if(sArea.isSolid){
            pMst->nDir=nDir;
            return true;
        }
    }
    
    return false;
}

u32 Monsters_IfHasAnAnim(u32 i)
{
    u32 nNoSpr=0;
    if(gMst[i].pAnim != NULL)
    {
        nNoSpr=Animspr_GetImgLast(gMst[i].nAnimNoSlot);
    }
    else
    {
        nNoSpr=gMst[i].nNoSpr;
    }
    return nNoSpr;
}

void Monsters_InitOfEnd(void)
{
    for (u32 i = 0; i < MST_MAX_SLOTS; i++)
    {
        if(gMst[i].nUsed == true)
        {
            gMst[i].nSpeed=0;
            gGen.nIsStartPlyr=false;
            gMst[i].nState=e_MstAnim_Idle;
            if(gMst[i].nDir == e_Dir_Down)
            {
                gMst[i].pAnim=gAnim_Rocky_Idle_Down; 
            }
            else if(gMst[i].nDir == e_Dir_Left)
            {
                gMst[i].pAnim=gAnim_Rocky_Idle_Left; 
            }
            else if(gMst[i].nDir == e_Dir_Up)
            {
                gMst[i].pAnim=gAnim_Rocky_Idle_Up; 
            }
            else if(gMst[i].nDir == e_Dir_Right)
            {
                gMst[i].pAnim=gAnim_Rocky_Idle_Right; 
            }
                
            Animspr_AnimSetIfNew(gMst[i].pAnim, gMst[i].nAnimNoSlot); 
        }
    }
}

void Monsters_ClearSlot(void)
{
    for (int i = 0; i < MST_MAX_SLOTS; i++)
    {
        gMst[i].nUsed = false;
    }
    gnMstLastSlotUsed=0;    
}

// TODO : faire avec la comparaison avec les cases.
void Monsters_CollideWalls(u32 i)
{
    //info_context lf
    u32 nPosX = gMst[i].nPosX >> 8;
    u32 nPosY = gMst[i].nPosY >> 8;
    
    // Position X == 0 :
    // Dir vers la gauche
    if(nPosX < WALL_COLMin)
    { 
        // Recalage
        gMst[i].nPosX = WALL_COLMin << 8;
        gMst[i].nDir=e_Dir_Down;
    }
    // Mettre < au lieu de <= sinon le sprite Idle lorsque le monstre touche le perso ne s'enclenche pas car on est
    // toujours dans le test de collision
    else if(nPosY < WALL_LINEMin) 
    {
        gMst[i].nPosY = WALL_LINEMin << 8;
        gMst[i].nDir=e_Dir_Left;
    }
    if(nPosX+SPR_SIZE > WALL_COLMax)
    {
        gMst[i].nPosX = (WALL_COLMax-SPR_SIZE) << 8;
        gMst[i].nDir=e_Dir_Up;
    }
    if(nPosY+SPR_SIZE > WALL_LINEMax)
    {
        gMst[i].nPosY = (WALL_LINEMax-SPR_SIZE) << 8;
        gMst[i].nDir=e_Dir_Right;
    }
}
// ATTENTION ON NE DOIT PAS SE STOPER EN M P S MAIS EN M P sur S (P et S doivent ê à la même position là P est au-dessus ou en-dessous de S)
bool Monster_CollidePlyrItem(SMonster *pMst)
{
    u32 nType=0;
    // Position du M en bloc
    u32 nMBlkX=pMst->nPosX >> 12;
    u32 nMBlkY=pMst->nPosY >> 12;
    info_context printf("pMst->nPosX : %d >> 12 = %d, pMst->nPosY : %d >> 12 = %d", pMst->nPosX, pMst->nPosX >> 12, pMst->nPosY, pMst->nPosY >> 12); lf
    switch (pMst->nDir)
    {
    case e_Dir_Up:
        info_context lf
        // Si M n'est pas sur un bloc plein on quite évite de se retrouver tout en bas avec un return true.
        if((pMst->nPosY & 0xF00) != 0) return false;
        //if((pMst->nPosY & 0xF00) == 0x800) return false;
        // Si M est sur un bloc plein
        if((pMst->nPosY & 0xF00) == 0) nMBlkY--;
        info_context lf
        break;
    case e_Dir_Down:
        info_context lf
        if((pMst->nPosY & 0xF00) != 0) return false;
        //if((pMst->nPosY & 0xF00) == 0x800) return false;
        if((pMst->nPosY & 0xF00) == 0) nMBlkY++;
        info_context lf                             
        break;
    }

    info_context printf("nMBlkY %d", nMBlkY);
    if((pMst->nPosY & 0xF00) == 0)
    {
        info_context lf
        if(gArea[(nMBlkY*AREA_WIDTH)+nMBlkX].isSolid)
        {
            info_context lf
            nType=gArea[(nMBlkY*AREA_WIDTH)+(pMst->nPosX >> 12)].nType;
            if(nType != e_Area_Heart && nType != e_Area_Chest && nType != e_Area_Grass) return false;
        }
        else if (gArea[(nMBlkY*AREA_WIDTH)+((pMst->nPosX+0xF00) >> 12)].isSolid)
        {
            info_context lf
            nType=gArea[(nMBlkY*AREA_WIDTH)+((pMst->nPosX+0xF00) >> 12)].nType;
            if(nType != e_Area_Heart && nType != e_Area_Chest && nType != e_Area_Grass) return false;
        }
        else
        {
            return false;
        }
    }
    info_context lf
    return true;        
}

bool Monster_CollideDecorPlyr(SMonster *pMst, u32 nNbBlk)
{
    u32 nType=0;
    // Position du M en bloc
    u32 nMBlkX=pMst->nPosX >> 12;
    u32 nMBlkY=pMst->nPosY >> 12;
    info_context printf("%d >> 12 = %d", pMst->nPosX, pMst->nPosX >> 12); lf
    switch (pMst->nDir)
    {
    case e_Dir_Up:
        info_context lf
        // Si M est sur un bloc plein
        if((pMst->nPosY & 0xF00) == 0) nMBlkY-=nNbBlk;
        info_context lf
        break;
    case e_Dir_Down:
        info_context lf
        if((pMst->nPosY & 0xF00) == 0) nMBlkY+=nNbBlk;
        info_context lf                             
        break;
    }

    if((pMst->nPosY & 0xF00) == 0)
    {
        info_context lf
        // Est-ce que c'est un solide ?
        if(gArea[(nMBlkY*AREA_WIDTH)+nMBlkX].isSolid)
        {
            info_context lf
            //nType=gArea[(nMBlkY*AREA_WIDTH)+(pMst->nPosX >> 12)].nType;
            //if(nType == e_Area_Ground || nType == e_Area_Sand)
             return true;
        }
        else if (gArea[(nMBlkY*AREA_WIDTH)+((pMst->nPosX+0xF00) >> 12)].isSolid)
        {
            info_context lf
            //nType=gArea[(nMBlkY*AREA_WIDTH)+((pMst->nPosX+0xF00) >> 12)].nType;
            //if(nType != e_Area_Heart && nType != e_Area_Chest && nType != e_Area_Grass) 
            return true;
        }
    }
    
    return false;
}

bool Monster_CollidePlyrDecor(SMonster *pMst, u32 nNbBlk)
{
    u32 nType=0;
    // Position du M en bloc
    u32 nMBlkX=pMst->nPosX >> 12;
    u32 nMBlkY=pMst->nPosY >> 12;
    info_context printf("%d >> 12 = %d", pMst->nPosX, pMst->nPosX >> 12); lf
    switch (pMst->nDir)
    {
    case e_Dir_Up:
        info_context lf
        // Si M est sur un bloc plein
        if((pMst->nPosY & 0xF00) == 0) nMBlkY-=nNbBlk;
        info_context lf
        break;
    case e_Dir_Down:
        info_context lf
        if((pMst->nPosY & 0xF00) == 0) nMBlkY+=nNbBlk;
        info_context lf                             
        break;
    }

    if((pMst->nPosY & 0xF00) == 0)
    {
        info_context lf
        if(gArea[(nMBlkY*AREA_WIDTH)+nMBlkX].isSolid)
        {
            info_context lf
            nType=gArea[(nMBlkY*AREA_WIDTH)+(pMst->nPosX >> 12)].nType;
            if(nType != e_Area_Heart && nType != e_Area_Chest && nType != e_Area_Grass) return false;
        }
        else if (gArea[(nMBlkY*AREA_WIDTH)+((pMst->nPosX+0xF00) >> 12)].isSolid)
        {
            info_context lf
            nType=gArea[(nMBlkY*AREA_WIDTH)+((pMst->nPosX+0xF00) >> 12)].nType;
            if(nType != e_Area_Heart && nType != e_Area_Chest && nType != e_Area_Grass) return false;
        }
    }
    
    return true;    
}

//bool Monster_CollideSnake(SMonster *pMst)
//{

//}

void Monster_CollidePlyr(void)
{
    // Position Plyr au Centre du sprite en pixel.
    s32 nPX=(gPlyr.nPosX  + 0x800) >> 8; 
    s32 nPY=(gPlyr.nPosY  + 0x800) >> 8;    

    // Position d'un bloc dans le jeu, pour rechercher s'il y a un obstacle après ou avant le Plyr.
    u32 nPBlkX=nPX >> 4;
    u32 nPBlkY=0;
    u32 nPBlkFullY=0;

    // Position Mst en pixel.
    s32 nMX = 0;
    s32 nMY = 0;

    u32 nMBlkX=0;
    u32 nMBlkY=0;
    u32 nMBlkFullY=0;

    // Coordonnées en pixel du solide.
    s32 nSX=0;
    s32 nSY=0;

    for (int i = 0; i < MST_MAX_SLOTS; i++)
    {
        //info_context printf("i = %d, gMst[i].nName %d, gMst[i].nUsed %d", i, gMst[i].nName, gMst[i].nUsed);lf
        if(gMst[i].nUsed)
        {
            nMX=(gMst[i].nPosX + 0x800) >> 8;
            nMY=(gMst[i].nPosY + 0x800) >> 8;

            if(gMst[i].nProperty == e_Mst_Harmless)
            {
                // SNAKE
                if(gMst[i].nName == e_Mst_Snakey)
                {
                    //// Calcul de la distance entre le M et le P s'il y a collision.
                    //if((nMX-nPX)*(nMX-nPX)+(nMY-nPY)*(nMY-nPY) <= DIST_MAX_MTOP)
                    //{
                    //    info_context lf
                    //    switch (gPlyr.nDir)
                    //    {
                    //    case e_Dir_Up:
                    //        gPlyr.nLockedDir=e_Kb_Up;
                    //        break;
                    //    case e_Dir_Right:
                    //        gPlyr.nLockedDir=e_Kb_Right;
                    //        break;
                    //    case e_Dir_Down:
                    //        gPlyr.nLockedDir=e_Kb_Down;
                    //        break;
                    //    case e_Dir_Left:
                    //        gPlyr.nLockedDir=e_Kb_Left;
                    //        break;
                    //    }
                    //}else
                    //{
                    //    gPlyr.nLockedDir=e_Kb_Null;
                    //}
                    // NE MARCHE PAS MANQUE LOCKDIR
                    //if(Game_PlyrCheckDepl(&gPlyr,gPlyr.nDir))
                    //{
                    //    gPlyr.nSpeed=0;
                    //}
                }

                // ROCKY
                if(gMst[i].nName == e_Mst_Rocky)
                {
                    info_context printf("%d >> 12 = %d", gMst[i].nPosX, gMst[i].nPosX >> 12); lf

                    info_context printf("abs(%d-%d) %d == 0 : %d", nMX, nPX, abs(nMX-nPX), abs(nMX-nPX) == 0); lf
                    info_context printf("(%d == 0 && %d == 0) : %d", (gMst[i].nPosX & 0xF00), (gPlyr.nPosX & 0xF00), (gMst[i].nPosX & 0xF00)==0 && (gPlyr.nPosX & 0xF00)==0);lf
                    info_context printf("(%d == 0x800 && %d == 0x800)) %d", (gMst[i].nPosX & 0xF00), (gPlyr.nPosX & 0xF00), (gMst[i].nPosX & 0xF00)==0x800 && (gPlyr.nPosX & 0xF00)==0x800);lf

                    // Si collision
                    // Horizontal Ok !
                    if(abs(nMX-nPX) <= SPR_SIZE*2 && abs(nMY-nPY) <= SPR_SIZE/2)
                    {
                        info_context lf
                        if(((gMst[i].nPosX & 0xF00) == 0 || (gMst[i].nPosX & 0xF00) == 0x800) && ((gMst[i].nPosY & 0xF00) == 0 || (gMst[i].nPosY & 0xF00) == 0x800))
                        {
                            gMst[i].nSpeed=0;
                            gMst[i].nState=e_MstAnim_Idle;
                        }
                        
                        if(abs(nMX-nPX) <= SPR_SIZE)
                        {
                            //gPlyr.nSpeed=0;
                            // Recalage
                            // P gauche M (En X P < M, à Gauche de l'écran par rapport à M)
                            if(SGN(nPX-nMX) == -1)
                            {
                                info_context lf
                                gPlyr.nPosX = gMst[i].nPosX - 0x1000;
                                gPlyr.nLockedDir = e_Kb_Right;
                            // P droite M (En X P > M, à Droite de l'écran par rapport à M)
                            }
                            else if(SGN(nPX-nMX) == 1)
                            {
                                info_context lf
                                gPlyr.nPosX = gMst[i].nPosX + 0x1000;
                                gPlyr.nLockedDir = e_Kb_Left;
                            }
                        }else
                        {
                            gPlyr.nLockedDir=e_Kb_Null;
                        }
                    }
                    // Vertical, pas sur la même colonne, décalé d'un demi-bloc Ok !
                    else if (abs(nMX-nPX) != 0 && abs(nMX-nPX) <= SPR_SIZE/2 && abs(nMY-nPY) <= SPR_SIZE)
                    {
                        // Recalage
                        // P au-dessus de M (En Y P < M, en haut de l'écran par rapport à M)                        
                        if(SGN(nPY-nMY) == -1){
                            info_context lf
                            gPlyr.nPosY = gMst[i].nPosY - 0x1000;
                            if((gPlyr.nPosY & 0xF00) == 0 || (gPlyr.nPosY & 0xF00) == 0x800) gPlyr.nLockedDir = e_Kb_Down;
                        // P en-dessous de M (En Y P > M, en bas de l'écran par rapport à M)
                        }else if(SGN(nPY-nMY) == 1){
                            info_context lf
                            gPlyr.nPosY = gMst[i].nPosY + 0x1000;
                            if((gPlyr.nPosY & 0xF00) == 0 || (gPlyr.nPosY & 0xF00) == 0x800) gPlyr.nLockedDir = e_Kb_Up;
                        }   
                        
                        info_context lf
                        // NOTE : si on met juste ça M et P => P se retrouve à la moitié de M en Y
                        if(((gMst[i].nPosX & 0xF00) == 0 || (gMst[i].nPosX & 0xF00) == 0x800) && ((gMst[i].nPosY & 0xF00) == 0 || (gMst[i].nPosY & 0xF00) == 0x800))
                        {
                            info_context lf
                            gMst[i].nSpeed=0;
                            gMst[i].nState=e_MstAnim_Idle;
                        }
                    }
                    // Column
                    else if (abs(nMX-nPX) == 0 && ((gMst[i].nPosX & 0xF00) == 0 || (gMst[i].nPosX & 0xF00) == 0x800))
                    {
                        info_context lf
                        gMst[i].nSpeed=PLYR_SPEED_INIT;
                        gMst[i].nState=e_MstAnim_Walk;

                        // En Y P < M
                        if(SGN(nPY-nMY) == -1)
                        {
                            info_context lf
                            gMst[i].nDir=e_Dir_Up;
                        // En Y P > M
                        }else if(SGN(nPY-nMY) == 1)
                        {
                            info_context lf
                            gMst[i].nDir=e_Dir_Down;
                        } 
                    
                        info_context printf("gPlyr.nKb %d, gPlyr.nLockedDir %d, gPlyr.nDir %d, gPlyr.nSpeed %d, gPlyr.nState %d", gPlyr.nKb, gPlyr.nLockedDir, gPlyr.nDir, gPlyr.nSpeed, gPlyr.nState);lf

                        // Si on est en collision avec le player et si speed est != 0 permet que lorsque l'on est sur un solide on ne rentre plus et plyr n'avance plus.
                        // NOTE : Voir pour mettre une variable collision décore dans la struct gMst et la mettre à la place de speed
                        if(abs(nMY-nPY) <= SPR_SIZE && gMst[i].nSpeed)
                        {
                            info_context lf
                            gPlyr.nState=e_PlyrAnim_Walk; // Peut-ê mettre speed

                            // Recalage
                            // P au-dessus de M (En Y P < M, en haut de l'écran par rapport à M)                        
                            if(SGN(nPY-nMY) == -1)
                            {
                                info_context lf
                                gPlyr.nPosY = gMst[i].nPosY - 0x1000;
                                gPlyr.nLockedDir = e_Kb_Down;
                            // P en-dessous de M (En Y P > M, en bas de l'écran par rapport à M)
                            }else if(SGN(nPY-nMY) == 1)
                            {
                                info_context lf
                                gPlyr.nPosY = gMst[i].nPosY + 0x1000;
                                gPlyr.nLockedDir = e_Kb_Up;
                            }
                            
                            info_context printf("%d >> 8 = %d, %d >> 12 = %d, gMst[i].nPosY >> 8 = %d, gMst[i].nPosY >> 12 = %d", gMst[i].nPosX, gMst[i].nPosX >> 8, gMst[i].nPosX, gMst[i].nPosX >> 12, gMst[i].nPosY >> 8, gMst[i].nPosY >> 12); lf
                            info_context printf("gMst[i].nDir %d, gMst[i].nSpeed %d, gMst[i].nState %d", gMst[i].nDir, gMst[i].nSpeed, gMst[i].nState);lf
                            
                            // Si on est en collision avec un solide (M P S) Mais ne dois pas ê un coeur, coffre, herbe.
                            if( ! Monster_CollidePlyrDecor(&gMst[i], e_NbBlk_2))
                            {
                                // Ici peut-ê mettre une varialbe gMst[i].isCollideDecor
                                info_context lf
                                gMst[i].nSpeed=0;
                                gMst[i].nState=e_MstAnim_Idle;
                            }
                            // Si coeur ou coffre ou herbe on stop. 
                            // ATTENTION PAS ENCORE AU POINT SI ON APPUY A NOUVEAU SUR UP OU DOWN M PASSE SUR LES S, ET SUR 
                            else if(Monster_CollidePlyrItem(&gMst[i]))
                            {
                                info_context lf
                                gMst[i].nSpeed=0;
                                gMst[i].nState=e_MstAnim_Idle;
                            }
                            
                            info_context printf("gMst[i].nDir %d, gMst[i].nSpeed %d, gMst[i].nState %d", gMst[i].nDir, gMst[i].nSpeed, gMst[i].nState);lf
                            info_context printf("gPlyr.nKb %d, gPlyr.nLockedDir %d, gPlyr.nDir %d, gPlyr.nSpeed %d, gPlyr.nState %d", gPlyr.nKb, gPlyr.nLockedDir, gPlyr.nDir, gPlyr.nSpeed, gPlyr.nState);lf
                        }
                        else
                        {
                            info_context lf
                            if(Monster_CollideDecorPlyr(&gMst[i], e_NbBlk_1))
                            {
                                gMst[i].nSpeed=0;
                                gMst[i].nState=e_MstAnim_Idle;
                            }
                        }
                    }
                    // P au-dessus/au-dessous de M, direction de P (down/up), de M (left/right) Ok ?
                    else if (abs(nPY-nMY) == SPR_SIZE && abs(nPX-nMX) > SPR_SIZE/2 && abs(nPX-nMX) < SPR_SIZE)
                    {
                        info_context lf
                        // Recalage
                        // P au-dessus de M (En Y P < M, en haut de l'écran par rapport à M)                        
                        if(SGN(nPY-nMY) == -1){
                            info_context lf
                            gPlyr.nPosY = gMst[i].nPosY - 0x1000;
                            gPlyr.nLockedDir = e_Kb_Down;
                        // P en-dessous de M (En Y P > M, en bas de l'écran par rapport à M)
                        }else if(SGN(nPY-nMY) == 1){
                            info_context lf
                            gPlyr.nPosY = gMst[i].nPosY + 0x1000;
                            gPlyr.nLockedDir = e_Kb_Up;
                        }   
                    }
                    // P à gauche/droite de M, direction de P (down/up), de M (left/right) Ok ?
                    else if (abs(nPX-nMX) == SPR_SIZE && abs(nPY-nMY) > SPR_SIZE/2 && abs(nPY-nMY) < SPR_SIZE)
                    {
                        info_context lf
                        // Recalage
                        // P gauche M (En X P < M, à Gauche de l'écran par rapport à M)
                        if(SGN(nPX-nMX) == -1)
                        {
                            info_context lf
                            gPlyr.nPosX = gMst[i].nPosX - 0x1000;
                            gPlyr.nLockedDir = e_Kb_Right;
                        // P droite M (En X P > M, à Droite de l'écran par rapport à M)
                        }
                        else if(SGN(nPX-nMX) == 1)
                        {
                            info_context lf
                            gPlyr.nPosX = gMst[i].nPosX + 0x1000;
                            gPlyr.nLockedDir = e_Kb_Left;
                        }                        
                    }
                    // P et M tous les deux en collision JE SAIS PAS SI OK ?
                    else if (abs(nPX-nMX) > SPR_SIZE/2 && abs(nPX-nMX) < SPR_SIZE && abs(nPY-nMY) > SPR_SIZE/2 && abs(nPY-nMY) < SPR_SIZE)
                    {
                        info_context lf
                        gPlyr.nSpeed=0;
                        gPlyr.nState=e_PlyrAnim_Idle;
                    }
                    // Pas de collision
                    else
                    {
                        info_context lf
                        gMst[i].nSpeed=MST_SPEED_INIT;
                        gPlyr.nLockedDir=e_Dir_Null;

                        Monsters_CollideDecor(&gMst[i], gGen.nLevel);
                    }
                }
            }
        }
    }    
}

bool Monster_CheckDepl(SMonster *pMst, u32 nDir, bool bIsCollide)
{
    u32 nType=0;

    // Coordonnées du block ou se trouve le monstre
    // Ne vaut que pour un test sur un bloc plein
    u32 nPosBlkX=pMst->nPosX >> 12;
    u32 nPosBlkY=pMst->nPosY >> 12;
    info_context printf("pMst->nName %d, nPosBlkX %d, nPosBlkY %d",pMst->nName,  nPosBlkX, nPosBlkY);lf

    switch (nDir)
    {
    case e_Dir_Up:
        info_context lf
        if((pMst->nPosX & 0xF00) != 0 && (pMst->nPosX & 0xF00) != 0x800) return false;
        if((pMst->nPosY & 0xF00) == 0) {
            // Ici on verifie si on est sur un demi-bloc en x et s'il y a un solide au-dessus en utilisant posX+0xF00
            if((pMst->nPosX & 0xF00) == 0x800){
                nPosBlkX=(pMst->nPosX+0xF00) >> 12;
                nPosBlkX=gArea[((nPosBlkY-1) * AREA_WIDTH) + nPosBlkX].isSolid ? nPosBlkX : pMst->nPosX >> 12;
            }
            nPosBlkY--;
        }
        info_context lf
        break;
    case e_Dir_Right:
        info_context lf
        if((pMst->nPosY & 0xF00) != 0 && (pMst->nPosY & 0xF00) != 0x800) return false;
        if((pMst->nPosY & 0xF00) == 0x800){
            nPosBlkY=(pMst->nPosY+0xF00) >> 12;
            nPosBlkY=gArea[((nPosBlkY) * AREA_WIDTH) + nPosBlkX+1].isSolid ? nPosBlkY : pMst->nPosY >> 12;            
        }
        nPosBlkX++;
        info_context lf
        break;
    case e_Dir_Down:
        info_context lf
        if((pMst->nPosX & 0xF00) != 0 && (pMst->nPosX & 0xF00) != 0x800) return false;
        if((pMst->nPosX & 0xF00) == 0x800){
            nPosBlkX=(pMst->nPosX+0xF00) >> 12;
            nPosBlkX=gArea[((nPosBlkY+1) * AREA_WIDTH) + nPosBlkX].isSolid ? nPosBlkX : pMst->nPosX >> 12;            
        }
        nPosBlkY++;
        info_context printf("pMst->nName %d, nPosBlkY %d", pMst->nName, nPosBlkY);  lf
        break;
    case e_Dir_Left:
        info_context lf
        if((pMst->nPosY & 0xF00) != 0 && (pMst->nPosY & 0xF00) != 0x800) return false;
        if((pMst->nPosX & 0xF00) == 0) {
            if((pMst->nPosY & 0xF00) == 0x800){
                nPosBlkY=(pMst->nPosY+0xF00) >> 12;
                nPosBlkY=gArea[((nPosBlkY) * AREA_WIDTH) + nPosBlkX-1].isSolid ? nPosBlkY : pMst->nPosY >> 12;
            }                 
            nPosBlkX--;            
        }
        info_context lf
        break;
    }

    info_context printf("pMst->nName %d, pMst->nPosX %d, pMst->nPosY %d", pMst->nName, pMst->nPosX, pMst->nPosY);lf
    if(((pMst->nPosX & 0xF00) == 0 || (pMst->nPosX & 0xF00) == 0x800) && ((pMst->nPosY & 0xF00) == 0 || (pMst->nPosY & 0xF00) == 0x800))
    {
        SAreaBox sArea=gArea[(nPosBlkY*AREA_WIDTH)+nPosBlkX];
        nType=sArea.nType;

        info_context printf("sArea.nType %d", sArea.nType);lf
        info_context printf("nPosBlkX %d, nPosBlkY %d", nPosBlkX, nPosBlkY);lf
        info_context printf("nType != e_Area_Ground %d nType != e_Area_Sand %d", nType != e_Area_Ground, nType != e_Area_Sand);lf

		// Monster est sur un bloc plein. Il faut que la case d'à côté soit vide.
        if(bIsCollide && nType != e_Area_Ground && nType != e_Area_Sand){
            info_context lf
            return false;
        }
    }
    info_context lf
    return true;
}

// Monsters_CollideDecor est dans Monster_CollidePlyr
void Monsters_MonstersMove(u32 nLvl)
{
    // Dernière direction
    u32 nLastDir=e_Dir_Null;

    // Dernière position
    s32 nLastPosX=0;
    s32 nLastPosY=0;

    // Sert à vérifier s'il y a un changement de bloc ou de demi-block
    s32 nChgBlkX=0;
    s32 nChgBlkY=0;

    struct SMonster *pMst=NULL;

    if (! gGen.nIsStartPlyr)
    {
        // Mise en mouvement des Msts au départ.
        // En début de partie le player est en état idle les monstre aussi, quand le joueur bougera la première fois les
        // monstres bougeront.
        for (u32 i = 0; i < MST_MAX_SLOTS; i++)
        {
            if(gMst[i].nName != e_Mst_Snakey && gMst[i].nName != e_Mst_Gol && gMst[i].nName != e_Mst_Whale){
                //info_context lf
                gMst[i].nState=e_MstAnim_Walk;
            }
        }
    }

    // Test du mouvement pour chaque monstres avec collision decore, murs, joueur
    for (u32 i = 0; i < MST_MAX_SLOTS; i++)
    {
        if(gGen.nIsStartPlyr && gMst[i].nUsed)
        {
            nLastPosX=gMst[i].nLastPosX=gMst[i].nPosX;
            nLastPosY=gMst[i].nLastPosY=gMst[i].nPosY;            
            if(gMst[i].nName==e_Mst_Rocky){
            }

            switch (gMst[i].nDir)
            {
            case e_Dir_Up:
                gMst[i].nPosY-=gMst[i].nSpeed;
                nChgBlkY=(((gMst[i].nPosY+0xF00) ^ (nLastPosY+0xF00)) & 0xF00) == 0xF00 ? 1 : 0;
                break;
            case e_Dir_Right:
                gMst[i].nPosX+=gMst[i].nSpeed;
                nChgBlkX=((gMst[i].nPosX ^ nLastPosX) & 0xF00) == 0xF00 ? 1 : 0;
                break;
            case e_Dir_Down:
                gMst[i].nPosY+=gMst[i].nSpeed;
                nChgBlkY=((gMst[i].nPosY ^ nLastPosY) & 0xF00) == 0xF00 ? 1 : 0;
                break;
            case e_Dir_Left:
                gMst[i].nPosX-=gMst[i].nSpeed;
                nChgBlkX=(((gMst[i].nPosX + 0xF00) ^ (nLastPosX+0xF00)) & 0xF00) == 0xF00 ? 1 : 0;
                break;
            }

            if(nChgBlkX || nChgBlkY){
                Monster_Recalage(&gMst[i], nLastPosX, nLastPosY);
            }
            
            gpMstAnimInitTb[gMst[i].nName](&gMst[i]); 

            gMst[i].nState=gMst[i].nSpeed ? e_MstAnim_Walk : e_MstAnim_Idle;

            Monster_CollidePlyr();
            Monsters_CollideWalls(i); 
            //Monsters_CollideDecor(&gMst[i], gGen.nLevel); // Génère un blocage au départ avec une vitesse de 0x80

            Sprites_Stock(Monsters_IfHasAnAnim(i), gMst[i].nPosX >> 8, gMst[i].nPosY >> 8, e_Prio_Monsters);
        }
    } 
}

// Recalage du joueur sur un bloc.
void Monster_Recalage(struct SMonster *pMst, u32 nLastPosX, u32 nLastPosY)
{
	switch (pMst->nDir)
	{
	case e_Dir_Up:
        if((pMst->nPosY & 0xF00) == 0x800) return; // On recale que sur un bloc plein.
		pMst->nPosY = nLastPosY & ~0xF00;
		break;
	case e_Dir_Right:
        if((pMst->nPosX & 0xF00) == 0x800) return;
		pMst->nPosX = pMst->nPosX & ~0xF00;
		break;
	case e_Dir_Down:
        if((pMst->nPosY & 0xF00) == 0x800) return;
		pMst->nPosY = pMst->nPosY & ~0xF00;
		break;
	case e_Dir_Left:
        if((pMst->nPosX & 0xF00) == 0x800) return;
		pMst->nPosX = nLastPosX & ~0xF00;
		break;
	}
}

void Monsters_Manage(void)
{

}

// Init des Monstres :
// Note on récupère gMstsLvls qui contient les info des monstres (placement, n° de sprites, etc).
void Monsters_InitMonsters(u32 nLvl)
{   
    for (int i = 0; i < gMstsLvls[nLvl].nNbMsts; i++)
    {
        Monsters_InitMonsters_Aux(
            -1, 
            gMstsLvls[nLvl].pMstsLvl[i].nNoSpr, 
            gMstsLvls[nLvl].pMstsLvl[i].pAnm, 
            -1, 
            gMstsLvls[nLvl].pMstsLvl[i].nDir, 
            gMstsLvls[nLvl].pMstsLvl[i].nColumns, 
            gMstsLvls[nLvl].pMstsLvl[i].nLines, 
            gMstsLvls[nLvl].pMstsLvl[i].nProperty, 
            gMstsLvls[nLvl].pMstsLvl[i].nSpeed,
            gMstsLvls[nLvl].pMstsLvl[i].nName
        );
    }
}    

s32 Monsters_InitMonsters_Aux(u32 nNoSlotMst, u32 nNoMst, u64 *pAnim, u64 nAnimNoSlot, u32 nDir, u32 nBlkX, u32 nBlkY, u8 nProperty, s16 nSpeed, u32 nName)
{
    if(nNoSlotMst == - 1)
    {
        if((nNoSlotMst = Monsters_GetSlot()) == -1)
        {
            printf("%s %s %d : Warring, more free slots.", __FILE__, __FUNCTION__, __LINE__);lf
            return -1;
        }
    }

    // Eventuellement faire une fonction Monsters_SetMonster comme Items_SetItem.
    gMst[nNoSlotMst].nNoSpr=nNoMst;
    gMst[nNoSlotMst].nAnimNoSlot=nAnimNoSlot;
    gMst[nNoSlotMst].nDir=nDir;
    gMst[nNoSlotMst].nSpeed=nSpeed;
    gMst[nNoSlotMst].nPosX=nBlkX << 12;
    gMst[nNoSlotMst].nPosY=nBlkY << 12;
    gMst[nNoSlotMst].nState=e_MstAnim_Idle;
    gMst[nNoSlotMst].pAnim = pAnim;
    if(gMst[nNoSlotMst].pAnim != NULL)
    {
        gMst[nNoSlotMst].nAnimNoSlot=Animspr_AnimSet(gMst[nNoSlotMst].pAnim, gMst[nNoSlotMst].nAnimNoSlot);
    }
    gMst[nNoSlotMst].nFlag=0;
    gMst[nNoSlotMst].nProperty=nProperty;
    gMst[nNoSlotMst].nName=nName;
    gMst[nNoSlotMst].bCollidePlyr=false;

    return nNoSlotMst;
}

void Monsters_InitSlots(void)
{
    for (u32 i = 0; i < MST_MAX_SLOTS; i++)
    {
        gMst[i].nUsed=0;
    }
    gnMstLastSlotUsed=0;    
}

u32 Monsters_GetSlot(void)
{   
    for (u32 i = gnMstLastSlotUsed; i < MST_MAX_SLOTS; i++)
    {
        if(gMst[i].nUsed == false)
        {
            gnMstLastSlotUsed=i+1;
            gMst[i].nUsed=true;
            return i;
        }
    }
    
    return -1;
}



