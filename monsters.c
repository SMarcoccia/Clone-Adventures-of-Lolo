#include "includes.h"

// ATTENTION avec les variables global si déclarées dans 2 fichiers .c avec le même nom sera exactement la même variable bien différencier les variables global en
// leurs donnant un nom différent à chacune.

struct SAreaBox gArea[AREA_WIDTH * AREA_HEIGHT];

// Permettra de rechercher un slot libre en partant du slot suivant après le dernier slot utilisé.
u32 gnMstLastSlotUsed; 
SMonster gMst[MST_MAX_SLOTS];

// Monsters :
// (n° de sprite, nom de l'anim (si pas d'anim NULL) on cast car la paramètre formel est en u64, direction, position en case, si inoffensif ou dangereux) : 
SMstLvl gMstLvl1[]={
    {e_Spr_Snakey_Rotate_Left, NULL, e_Dir_Down, 12, 3, e_Mst_Harmless, 0, e_Mst_Snakey},
    {e_Spr_Rocky_Stand_Down, gAnim_Rocky_Idle_Down, e_Dir_Down, 10, 8, e_Mst_Harmless, MST_SPEED_INIT, e_Mst_Rocky},
    //{e_Spr_Leeper_Down_Stand, gAnim_Leeper_Idle_Down, e_Dir_Down, 11, 2, e_Mst_Harmless, MST_SPEED_INIT, e_Mst_Leeper},
};

SMstLvl gMstLvl2[]={
    {e_Spr_Snakey_Rotate_Left, NULL, e_Dir_Down, 11, 7, e_Mst_Harmless, MST_SPEED_NOT, e_Mst_Snakey},
    {e_Spr_Rocky_Stand_Up, gAnim_Rocky_Idle_Up, e_Dir_Up, 12, 11, e_Mst_Harmless, MST_SPEED_INIT, e_Mst_Rocky},
    //{e_Spr_Leeper_Down_Stand, gAnim_Leeper_Idle_Down, e_Dir_Down, 11, 2, e_Mst_Harmless, MST_SPEED_INIT, e_Mst_Leeper},
};

SMstsLvls gMstsLvls[]={
    {gMstLvl1, 2},
    {gMstLvl2, 2},
};

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

//bool Monsters_CollideDecor(u32 nIdx, u32 nLvl)
//{
//    // nColMin correspond au sprite coin supérieur gauche
//    // nColMax correspond au sprite coin supérieur droit
//    // nLineMin correspond au sprite coin supérieur gauche
//    // nLineMax correspond au sprite coin inférieur gauche
    
//    // Coordonnées min et max du monstre en pixels
//    s32 nXMin=gMst[nIdx].nPosX >> 8;
//    s32 nXMax=(gMst[nIdx].nPosX >> 8)+SPR_SIZE-1;
//    s32 nYMin=gMst[nIdx].nPosY >> 8;
//    s32 nYMax=(gMst[nIdx].nPosY >> 8)+SPR_SIZE-1;
//    // Position du monstreau centre
//    s32 nMX=nXMin+SPR_SIZE/2;
//    s32 nMY=nXMin+SPR_SIZE/2;

//    // Coordonnées min et max du Monstre en bloc
//    u32 nBlkXMin=nXMin >> 4;
//    u32 nBlkYMin=nYMin >> 4;
//    u32 nBlkXMax=nXMax >> 4;
//    u32 nBlkYMax=nYMax >> 4;

//    // Coordonnées du solide en pixel
//    s32 nSX=0;
//    s32 nSY=0;
    
//    //if((gMst[nIdx].nPosY & 0xF00) != 0 && ((gMst[nIdx].nPosX & 0xF00) != 0 || (gMst[nIdx].nPosX & 0xF00) != 0)) return false;
    
//    // Position du coffre en-dessous
//    // Chest to right ?
//    if(gArea[(nBlkYMin+1)*AREA_WIDTH + nBlkXMin].isSolid){ // && != de wall
//        info_context lf
//        nSX=gArea[(nBlkYMin+1)*AREA_WIDTH + nBlkXMin].nBlkX << 4;
//        nSY=gArea[(nBlkYMin+1)*AREA_WIDTH + nBlkYMin].nBlkY << 4;
//    // Chest to left ?
//    }else if (gArea[(nBlkYMin+1)*AREA_WIDTH + nBlkXMax].isSolid){
//        info_context lf        
//        nSX=gArea[(nBlkYMin+1)*AREA_WIDTH + nBlkXMax].nBlkX << 4;
//        nSY=gArea[(nBlkYMin+1)*AREA_WIDTH + nBlkYMax].nBlkY << 4;
//    }
//    // Position du coffre au-dessus    
//    // Chest to right ?
//    else if (gArea[(nBlkYMin-1)*AREA_WIDTH + nBlkXMin].isSolid){
//        info_context lf        
//        nSX=gArea[(nBlkYMin-1)*AREA_WIDTH + nBlkXMax].nBlkX << 4;
//        nSY=gArea[(nBlkYMin-1)*AREA_WIDTH + nBlkYMax].nBlkY << 4;
//    // Chest to left ?
//    }else if (gArea[(nBlkYMin-1)*AREA_WIDTH + nBlkXMax].isSolid){
//        info_context lf        
//        nSX=gArea[(nBlkYMin-1)*AREA_WIDTH + nBlkXMax].nBlkX << 4;
//        nSY=gArea[(nBlkYMin-1)*AREA_WIDTH + nBlkYMax].nBlkY << 4;
//    }
    
//    info_context printf("nSX %d, nSY %d, nMX %d, nMY %d", nSX, nSY, nMX, nMY);lf
    
//    // Position du solide au centre
//    nSX+=SPR_SIZE/2;
//    nSY+=SPR_SIZE/2;

//    // Si direction Left :
//    u32 nColMin = gMst[nIdx].nPosX >> 12;
//    // Si direction Right :
//    u32 nColMax = ((gMst[nIdx].nPosX >> 8)+SPR_SIZE) >> 4;
//    // Si direction Up :
//    u32 nLineMin = gMst[nIdx].nPosY >> 12;
//    // Si direction Bottom :
//    u32 nLineMax = ((gMst[nIdx].nPosY >> 8)+SPR_SIZE) >> 4;


//        info_context printf("gArea[%d*%d + %d].nType %d == e_Area_Border", (nSY >> 4), AREA_WIDTH, (nSX >> 4), gArea[(nSY >> 4)*AREA_WIDTH + (nSX >> 4)].nType);lf
//        if((gArea[(nSY >> 4)*AREA_WIDTH + (nSX >> 4)].nType == e_Area_Border || gArea[(nSY >> 4)*AREA_WIDTH + (nSX >> 4)].nType == e_Area_Ground)) return false;
    
//        if(gMst[nIdx].nName==e_Mst_Rocky){
//            info_context printf("gMst[nIdx].nDir %d, nSX %d, nSY %d, nMX %d, nMY %d", gMst[nIdx].nDir, nSX, nSY, nMX, nMY);lf
//        }
//        switch (gMst[nIdx].nDir)
//        {
//            case e_Dir_Down:
//                if(gMst[nIdx].nName==e_Mst_Rocky){
//                    info_context printf("type %d, gArea[%d*%d + %d].isSolid  %d != 0", gArea[(nSY >> 4)*AREA_WIDTH + (nSX >> 4)].nType, nSY >> 4, AREA_WIDTH, nSX >> 4, gArea[(nSY >> 4)*AREA_WIDTH + (nSX >> 4)].isSolid); lf
//                }
//                // On test si on est sur une case solide :
//                //(gMst[nIdx].nPosX & 0xF00) == 0x800
//                if (gArea[(nSY >> 4)*AREA_WIDTH + (nSX >> 4)].isSolid != 0)
//                {
//                    info_context lf
//                    gMst[nIdx].nPosY=nYMin << 8;
//                    gMst[nIdx].nDir=e_Dir_Right;
//                }
//                break;
//            case e_Dir_Left:
//                info_context lf
//                if (gArea[(nSY >> 4)*AREA_WIDTH + (nSX >> 4)].isSolid != 0)
//                {
//                    gMst[nIdx].nPosX=nXMin << 8;
//                    gMst[nIdx].nDir=e_Dir_Down;
//                }
//                break;
//            case e_Dir_Up:
//                info_context lf
//                // On regarde la case au-dessus.
//                //if (gArea[(nSY >> 4)*AREA_WIDTH + (nSX >> 4)].isSolid != 0 || (gMst[nIdx].nPosX & 0xF00) == 0x800)
//                info_context printf("type %d, gArea[%d*%d + %d].isSolid  %d != 0", gArea[(nSY >> 4)*AREA_WIDTH + (nSX >> 4)].nType, nSY >> 4, AREA_WIDTH, nSX >> 4, gArea[(nSY >> 4)*AREA_WIDTH + (nSX >> 4)].isSolid); lf

//                if (gArea[(nSY >> 4)*AREA_WIDTH + (nSX >> 4)].isSolid != 0 || gArea[(nSY >> 4)*AREA_WIDTH + ((gMst[nIdx].nPosX + 0x800) >> 12)].isSolid != 0)
//                {
//                    info_context lf
//                    gMst[nIdx].nPosY=nYMin << 8;
//                    gMst[nIdx].nDir=e_Dir_Left;
//                }
//                break;
//            case e_Dir_Right:
//                info_context lf
//                if (gArea[(nSY >> 4)*AREA_WIDTH + (nSX >> 4)].isSolid != 0)
//                {
//                    gMst[nIdx].nPosX=nXMin << 8;
//                    gMst[nIdx].nDir=e_Dir_Up;
//                }
//                break;
//        }
    
//    //else
//    //{
//    //    gMst[nIdx].nState=e_MstAnim_Idle;
//    //    gMst[nIdx].nSpeed=MST_SPEED_NOT;        
//    //}
    
//    return true;
//}

bool Monsters_CollideDecor(u32 nIdx, u32 nLvl)
{
    //s32 nPosX=gMst[nIdx].nPosX >> 8;
    //s32 nPosY=gMst[nIdx].nPosY >> 8;
    
    // nColMin correspond au sprite coin supérieur gauche
    // nColMax correspond au sprite coin supérieur droit
    // nLineMin correspond au sprite coin supérieur gauche
    // nLineMax correspond au sprite coin inférieur gauche

    // Si direction Left :
    u32 nColMin = gMst[nIdx].nPosX >> 12;
    // Si direction Right :
    u32 nColMax = ((gMst[nIdx].nPosX >> 8)+SPR_SIZE) >> 4;
    // Si direction Up :
    u32 nLineMin = gMst[nIdx].nPosY >> 12;
    // Si direction Bottom :
    u32 nLineMax = ((gMst[nIdx].nPosY >> 8)+SPR_SIZE) >> 4;
    //info_context printf("gMst[nIdx].nPosY %d, gMst[nIdx].nPosY >> 8 : %d", gMst[nIdx].nPosY, gMst[nIdx].nPosY >> 8);lf

    // On test si on est sur une case solide :
    switch (gMst[nIdx].nDir)
    {
        case e_Dir_Down:
            if (gArea[nLineMax*AREA_WIDTH + nColMin].isSolid != 0)
            {
                gMst[nIdx].nPosY=nLineMin << 12;
                gMst[nIdx].nDir=e_Dir_Right;
            }
            break;
        case e_Dir_Left:
            if (gArea[nLineMin*AREA_WIDTH + nColMin].isSolid != 0)
            {
                gMst[nIdx].nPosX=nColMax << 12;
                gMst[nIdx].nDir=e_Dir_Down;
            }
            break;
        case e_Dir_Up:
            // On regarde la case au-dessus.
            if (gArea[nLineMin*AREA_WIDTH + nColMin].isSolid != 0)
            {
                gMst[nIdx].nPosY=nLineMax << 12;
                gMst[nIdx].nDir=e_Dir_Left;
            }
            break;
        case e_Dir_Right:
            if (gArea[nLineMin*AREA_WIDTH + nColMax].isSolid != 0)
            {
                gMst[nIdx].nPosX=nColMin << 12;
                gMst[nIdx].nDir=e_Dir_Up;
            }
            break;
    }
    
    return true;
}

u32 Monsters_IfHasAnAnim(u32 nIdx)
{
    u32 nNoSpr=0;
    if(gMst[nIdx].pAnim != NULL)
    {
        nNoSpr=Animspr_GetImgLast(gMst[nIdx].nAnimNoSlot);
    }
    else
    {
        nNoSpr=gMst[nIdx].nNoSpr;
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

// TODO : faire avec la comparaison avec les cases.
void Monsters_CollideWalls(u32 nIdx)
{
    //info_context lf
    u32 nPosX = gMst[nIdx].nPosX >> 8;
    u32 nPosY = gMst[nIdx].nPosY >> 8;
    
    // Position X == 0 :
    // Dir vers la gauche
    if(nPosX < WALL_COLMin)
    { 
        // Recalage
        gMst[nIdx].nPosX = WALL_COLMin << 8;
        gMst[nIdx].nDir=e_Dir_Down;
    }
    // Mettre < au lieu de <= sinon le sprite Idle lorsque le monstre touche le perso ne s'enclenche pas car on est
    // toujours dans le test de collision
    else if(nPosY < WALL_LINEMin) 
    {
        gMst[nIdx].nPosY = WALL_LINEMin << 8;
        gMst[nIdx].nDir=e_Dir_Left;
    }
    if(nPosX+SPR_SIZE > WALL_COLMax)
    {
        gMst[nIdx].nPosX = (WALL_COLMax-SPR_SIZE) << 8;
        gMst[nIdx].nDir=e_Dir_Up;
    }
    if(nPosY+SPR_SIZE > WALL_LINEMax)
    {
        gMst[nIdx].nPosY = (WALL_LINEMax-SPR_SIZE) << 8;
        gMst[nIdx].nDir=e_Dir_Right;
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
/*
//void Monsters_MonstersMove(u32 nLvl)
//{
//    u64 *pAnims[][4]={
//        {gAnim_Alma_Walk_Down, gAnim_Alma_Walk_Left, gAnim_Alma_Walk_Up, gAnim_Alma_Walk_Right},
//        {gAnim_Leeper_Jumping_Down, gAnim_Leeper_Jumping_Left, gAnim_Leeper_Jumping_Up, gAnim_Leeper_Jumping_Right},
//        {gAnim_Rocky_Walk_Down, gAnim_Rocky_Walk_Left, gAnim_Rocky_Walk_Up, gAnim_Rocky_Walk_Right},
//        {gAnim_Skull_Move_Down, gAnim_Skull_Move_Left, gAnim_Skull_Move_Up, gAnim_Skull_Move_Right},
//        {gAnim_DonMedusa_Move, gAnim_DonMedusa_Move, gAnim_DonMedusa_Move, gAnim_DonMedusa_Move},
//    };

//    for (u32 i = 0; i < MST_MAX_SLOTS; i++)
//    {
//        // En début de partie le player est en état idle les monstre aussi, quand le joueur bougera la première fois les
//        // monstres bougeront.
//        gMst[i].nLastPosX=gMst[i].nPosX;
//        gMst[i].nLastPosY=gMst[i].nPosY;
        
//        if(gGen.nIsStartPlyr == true && gMst[i].nUsed == true)
//        {
//            if(gMst[i].pAnim != NULL && gMst[i].nState==e_MstAnim_Walk)
//            {
//                if(gMst[i].nDir == e_Dir_Down)
//                {
//                    if(gMst[i].bCollidePlyr && ((gMst[i].nPosY & 0xF00) != 0 || (gMst[i].nPosY & 0xF00) != 0x800)){
//                        gMst[i].nPosY+=gMst[i].nSpeed;
//                    }else if(gMst[i].bCollidePlyr && ((gMst[i].nPosY & 0xF00) == 0 || (gMst[i].nPosY & 0xF00) == 0x800)){
//                        //gMst[i].nPosY+=gMst[i].nSpeed;
//                        gMst[i].nState=e_MstAnim_Idle;
//                        gMst[i].nSpeed=MST_SPEED_NOT;
//                    }else if( ! gMst[i].bCollidePlyr){
//                        gMst[i].nPosY+=gMst[i].nSpeed;
//                    }
//                    //info_context printf("DOWN gMst[i].nPosY %d, gMst[i].nPosY >> 8 : %d", gMst[i].nPosY, gMst[i].nPosY >> 8);lf
//                }
//                if(gMst[i].nDir == e_Dir_Left)
//                {
//                    if(gMst[i].bCollidePlyr && ((gMst[i].nPosX & 0xF00) != 0 || (gMst[i].nPosX & 0xF00) != 0x800)){
//                        gMst[i].nPosX-=gMst[i].nSpeed;
//                    }else if(gMst[i].bCollidePlyr && ((gMst[i].nPosX & 0xF00) == 0 || (gMst[i].nPosX & 0xF00) == 0x800)){
//                        //gMst[i].nPosX-=gMst[i].nSpeed;
//                        gMst[i].nState=e_MstAnim_Idle;
//                        gMst[i].nSpeed=MST_SPEED_NOT;
//                    }else if( ! gMst[i].bCollidePlyr){
//                        gMst[i].nPosX-=gMst[i].nSpeed;
//                    }
//                    //info_context printf("LEFT gMst[i].nPosX %d, gMst[i].nPosX >> 8 : %d", gMst[i].nPosX, gMst[i].nPosX >> 8);lf
//                }
//                if(gMst[i].nDir == e_Dir_Up)
//                {
//                    if(gMst[i].bCollidePlyr && ((gMst[i].nPosY & 0xF00) != 0 || (gMst[i].nPosY & 0xF00) != 0x800)){
//                        gMst[i].nPosY-=gMst[i].nSpeed;
//                    }else if(gMst[i].bCollidePlyr && ((gMst[i].nPosY & 0xF00) == 0 || (gMst[i].nPosY & 0xF00) == 0x800)){
//                        //gMst[i].nPosY-=gMst[i].nSpeed;
//                        gMst[i].nState=e_MstAnim_Idle;
//                        gMst[i].nSpeed=MST_SPEED_NOT;
//                    }else if( ! gMst[i].bCollidePlyr){
//                        gMst[i].nPosY-=gMst[i].nSpeed;
//                    }
//                }
//                if(gMst[i].nDir == e_Dir_Right)
//                {
//                    info_context printf("gMst[i].bCollidePlyr %d && ((gMst[i].nPosX & 0xF00) %d != 0 && (gMst[i].nPosX & 0xF00) %d != 0x800)", gMst[i].bCollidePlyr, (gMst[i].nPosX & 0xF00), (gMst[i].nPosX & 0xF00)); lf
//                    if(gMst[i].bCollidePlyr && ((gMst[i].nPosX & 0xF00) != 0 && (gMst[i].nPosX & 0xF00) != 0x800)){
//                        gMst[i].nPosX+=gMst[i].nSpeed;
//                        info_context lf
//                    }else if(gMst[i].bCollidePlyr && ((gMst[i].nPosX & 0xF00) == 0 || (gMst[i].nPosX & 0xF00) == 0x800)){
//                        //gMst[i].nPosX+=gMst[i].nSpeed;
//                        info_context lf
//                        gMst[i].nState=e_MstAnim_Idle;
//                        gMst[i].nSpeed=MST_SPEED_NOT;
//                    }else if( ! gMst[i].bCollidePlyr){
//                        info_context lf
//                        gMst[i].nState=e_MstAnim_Walk;
//                        gMst[i].nSpeed=MST_SPEED_INIT;
//                        gMst[i].nPosX+=gMst[i].nSpeed;
//                    }
//                }
//                Animspr_AnimSetIfNew(pAnims[gMst[i].nName][gMst[i].nDir], gMst[i].nAnimNoSlot);
//            // Si rock est en collision avec le plyr
//            }else{ 
//                u64 *nDir=NULL;

//                switch (gMst[i].nDir)
//                {
//                    case e_Dir_Down:
//                        nDir=gAnim_Rocky_Idle_Down;
//                        break;
//                    case e_Dir_Left:
//                        nDir=gAnim_Rocky_Idle_Left;
//                        break;
//                    case e_Dir_Right:
//                        nDir=gAnim_Rocky_Idle_Right;
//                        break;
//                    case e_Dir_Up:
//                        nDir=gAnim_Rocky_Idle_Up;
//                        break;
//                }
//                Animspr_AnimSet(nDir, gMst[i].nAnimNoSlot);
//            }
//            // Ici on met bien en dernier le test sinon dépassement de mémoire. Sinon voir en faisant un split du sprite.
//            Monsters_CollideWalls(i); 
//            Monsters_CollideDecor(i, gGen.nLevel); // Génère un blocage au départ avec une vitesse de 0x80
//            Sprites_Stock(Monsters_IfHasAnAnim(i), gMst[i].nPosX >> 8, gMst[i].nPosY >> 8, e_Prio_Monsters);
//        }
//    } 
//}
*/

void Monsters_MonstersMove(u32 nLvl)
{
    ////info_context lf
    //u64 *pAnims[][4]={
    //    {gAnim_Alma_Walk_Down, gAnim_Alma_Walk_Left, gAnim_Alma_Walk_Up, gAnim_Alma_Walk_Right},
    //    {gAnim_Leeper_Jumping_Down, gAnim_Leeper_Jumping_Left, gAnim_Leeper_Jumping_Up, gAnim_Leeper_Jumping_Right},
    //    {gAnim_Rocky_Walk_Down, gAnim_Rocky_Walk_Left, gAnim_Rocky_Walk_Up, gAnim_Rocky_Walk_Right},
    //    {gAnim_Skull_Move_Down, gAnim_Skull_Move_Left, gAnim_Skull_Move_Up, gAnim_Skull_Move_Right},
    //    {gAnim_DonMedusa_Move, gAnim_DonMedusa_Move, gAnim_DonMedusa_Move, gAnim_DonMedusa_Move},
    //};

    s32 nBlkX=0;
    s32 nBlkY=0;

    if (! gGen.nIsStartPlyr)
    {
        // Mise en mouvement des Msts au départ.
        for (u32 i = 0; i < MST_MAX_SLOTS; i++)
        {
            if(gMst[i].nName != e_Mst_Snakey && gMst[i].nName != e_Mst_Gol && gMst[i].nName != e_Mst_Whale){
                gMst[i].nState=e_MstAnim_Walk;
                //info_context lf
            }
        }
    }

    for (u32 i = 0; i < MST_MAX_SLOTS; i++)
    {
        // En début de partie le player est en état idle les monstre aussi, quand le joueur bougera la première fois les
        // monstres bougeront.
        gMst[i].nLastPosX=gMst[i].nPosX;
        gMst[i].nLastPosY=gMst[i].nPosY;
        
        if(gGen.nIsStartPlyr && gMst[i].nUsed)
        {
            if(gMst[i].nName==e_Mst_Rocky){
                //info_context lf
            }
            // Obliger de mettre gMst[i].nState==e_MstAnim_Walk sinon on rentre pas dans le else. gMst[i].nState si collision est mis à e_MstAnim_Idle.
            if(gMst[i].pAnim != NULL && gMst[i].nState==e_MstAnim_Walk)
            {
                if(gMst[i].nName==e_Mst_Rocky){
                    //info_context printf("gMst[%d].bCollidePlyr %d", i, gMst[i].bCollidePlyr);lf
                }

                if(gMst[i].bCollidePlyr){
                    if(gMst[i].nName==e_Mst_Rocky){
                        //info_context lf
                    }
                    // Si Monster est sur la vertical avec Player permet de faire un polish de collision plus agréable à l'oeil.
                    if(((gMst[i].nPosY & 0xF00) != 0 && (gMst[i].nPosY & 0xF00) != 0x800) || ((gMst[i].nPosX & 0xF00) != 0 && (gMst[i].nPosX & 0xF00) != 0x800)){
                        switch (gMst[i].nDir)
                        {
                        case e_Dir_Up:
                            if(gMst[i].nName==e_Mst_Rocky){
                                //info_context lf
                            }
                            gMst[i].nPosY-=gMst[i].nSpeed;
                			nBlkY = (((gMst[i].nPosY + 0xF00) & ~0xFFF) != ((gMst[i].nLastPosY + 0xF00) & ~0xFFF) ? 1 : 0);
                            break;
                        case e_Dir_Right:
                            if(gMst[i].nName==e_Mst_Rocky){
                                //info_context lf
                            }
                            gMst[i].nPosX+=gMst[i].nSpeed;
                			nBlkX = ((gMst[i].nPosX & ~0xFFF) != (gMst[i].nLastPosX & ~0xFFF) ? 1 : 0);
                            break;                            
                        case e_Dir_Down:
                            if(gMst[i].nName==e_Mst_Rocky){
                                //info_context lf
                            }
                            gMst[i].nPosY+=gMst[i].nSpeed;
                			nBlkY = ((gMst[i].nPosY & ~0xFFF) != (gMst[i].nLastPosY & ~0xFFF) ? 1 : 0);
                            break;
                        case e_Dir_Left:
                            if(gMst[i].nName==e_Mst_Rocky){
                                //info_context lf
                            }
                            gMst[i].nPosX-=gMst[i].nSpeed;
                			nBlkX = (((gMst[i].nPosX + 0xF00) & ~0xFFF) != ((gMst[i].nLastPosX + 0xF00) & ~0xFFF) ? 1 : 0);
                            break;                            
                        }
                        // Si changement de bloc, stop.
                        //if (nBlkX || nBlkY)
                        //{
                        //    gMst[i].nSpeed = 0;
                        //    Monster_Recalage(&gMst[i], gMst[i].nLastPosX, gMst[i].nLastPosY);
                        //}                              
                    }else{
                        //info_context lf
                        gMst[i].nState=e_MstAnim_Idle;
                        gMst[i].nSpeed=MST_SPEED_NOT;                        
                    }
                }
                else if(gMst[i].nSpeed){
                    //info_context lf
                    switch (gMst[i].nDir)
                    {
                    case e_Dir_Up:
                        if(gMst[i].nName==e_Mst_Rocky){  
                            //info_context lf
                        }
                        // Pas de test Y si X n'est pas sur un bloc
                        if((gMst[i].nPosX & 0xF00) != 0 && (gMst[i].nPosX & 0xF00) != 0x800) {
                            if(gMst[i].nName==e_Mst_Rocky){  
                                //info_context lf
                            }
                            return;
                        }; 
                        gMst[i].nPosY-=gMst[i].nSpeed;
            			nBlkY = (((gMst[i].nPosY + 0xF00) & ~0xFFF) != ((gMst[i].nLastPosY + 0xF00) & ~0xFFF) ? 1 : 0);

                        if(gMst[i].nName==e_Mst_Rocky){  
                            //info_context lf
                        }                          
                        break;
                    case e_Dir_Right:
                        if(gMst[i].nName==e_Mst_Rocky){    
                            //info_context lf
                        }
                        if((gMst[i].nPosY & 0xF00) != 0 && (gMst[i].nPosY & 0xF00) != 0x800) {
                            if(gMst[i].nName==e_Mst_Rocky){    
                                //info_context lf
                            }
                            return; }
                        gMst[i].nPosX+=gMst[i].nSpeed;
            			nBlkX = ((gMst[i].nPosX & ~0xFFF) != (gMst[i].nLastPosX & ~0xFFF) ? 1 : 0);

                        if(gMst[i].nName==e_Mst_Rocky){
                            //info_context lf
                        }
                        break;
                    case e_Dir_Down:
                        if(gMst[i].nName==e_Mst_Rocky){    
                            //info_context lf
                        }
                        if((gMst[i].nPosX & 0xF00) != 0 && (gMst[i].nPosX & 0xF00) != 0x800) {
                            if(gMst[i].nName==e_Mst_Rocky){    
                                //info_context lf
                            }                            
                            //goto _Skip; 
                            return;
                        }
                        gMst[i].nPosY+=gMst[i].nSpeed;
            			nBlkY = ((gMst[i].nPosY & ~0xFFF) != (gMst[i].nLastPosY & ~0xFFF) ? 1 : 0);
                        if(gMst[i].nName==e_Mst_Rocky){
                            //info_context printf("gMst[i].nSpeed %d", gMst[i].nSpeed); lf
                        }
                        break;
                    case e_Dir_Left:
                        if(gMst[i].nName==e_Mst_Rocky){    
                            //info_context lf
                        }
                        if((gMst[i].nPosY & 0xF00) != 0 && (gMst[i].nPosY & 0xF00) != 0x800) {
                            if(gMst[i].nName==e_Mst_Rocky){    
                                //info_context lf
                            }                            
                            return;
                        }
                        gMst[i].nPosX-=gMst[i].nSpeed;
            			nBlkX = (((gMst[i].nPosX + 0xF00) & ~0xFFF) != ((gMst[i].nLastPosX + 0xF00) & ~0xFFF) ? 1 : 0);
                        if(gMst[i].nName==e_Mst_Rocky){
                            //info_context lf
                        }
                        break;
                    }

                    //// Si changement de bloc, stop.
                    //if (nBlkX || nBlkY)
                    //{
                    //    gMst[i].nSpeed = 0;
                    //    Monster_Recalage(&gMst[i], gMst[i].nLastPosX, gMst[i].nLastPosY);
                    //}                    
                }
                AnimSpr_MstAnimSetIfNew(&gMst[i]);

                //Animspr_AnimSetIfNew(pAnims[gMst[i].nName][gMst[i].nDir], gMst[i].nAnimNoSlot);
            // Si rock est en collision avec le plyr
            }else if((gMst[i].nPosY & 0xF00) == 0 || (gMst[i].nPosY & 0xF00) == 0x800){ 
                if(gMst[i].nName==e_Mst_Rocky){
                    //info_context lf
                }
                u64 *nAnmDir=NULL;

                switch (gMst[i].nDir)
                {
                    case e_Dir_Down:
                        nAnmDir=gAnim_Rocky_Idle_Down;
                        break;
                    case e_Dir_Left:
                        nAnmDir=gAnim_Rocky_Idle_Left;
                        break;
                    case e_Dir_Right:
                        nAnmDir=gAnim_Rocky_Idle_Right;
                        break;
                    case e_Dir_Up:
                        nAnmDir=gAnim_Rocky_Idle_Up;
                        break;
                }
                Animspr_AnimSet(nAnmDir, gMst[i].nAnimNoSlot);
            }
            // Ici on met bien en dernier le test sinon dépassement de mémoire. Sinon voir en faisant un split du sprite.
            Monsters_CollideWalls(i); 
            Monsters_CollideDecor(i, gGen.nLevel); // Génère un blocage au départ avec une vitesse de 0x80
            Sprites_Stock(Monsters_IfHasAnAnim(i), gMst[i].nPosX >> 8, gMst[i].nPosY >> 8, e_Prio_Monsters);
            //info_context printf("gMst[i].nPosY %d", gMst[i].nPosY);lf
        }
    } 
}

// Recalage du joueur sur un bloc.
void Monster_Recalage(struct SMonster *pMst, u32 nLastPosX, u32 nLastPosY)
{
	switch (pMst->nDir)
	{
	case e_Dir_Up:		// Haut
		pMst->nPosY = nLastPosY & ~0xF00;
		break;
	case e_Dir_Right:		// Droite
		pMst->nPosX = pMst->nPosX & ~0xF00;
		break;
	case e_Dir_Down:		// Bas
		pMst->nPosY = pMst->nPosY & ~0xF00;
		break;
	case e_Dir_Left:		// Gauche
		pMst->nPosX = nLastPosX & ~0xF00;
		break;
	}
}

//void Monsters_MonstersMove(u32 nLvl)
//{
//    info_context lf
//    u64 *pAnims[][4]={
//        {gAnim_Alma_Walk_Down, gAnim_Alma_Walk_Left, gAnim_Alma_Walk_Up, gAnim_Alma_Walk_Right},
//        {gAnim_Leeper_Jumping_Down, gAnim_Leeper_Jumping_Left, gAnim_Leeper_Jumping_Up, gAnim_Leeper_Jumping_Right},
//        {gAnim_Rocky_Walk_Down, gAnim_Rocky_Walk_Left, gAnim_Rocky_Walk_Up, gAnim_Rocky_Walk_Right},
//        {gAnim_Skull_Move_Down, gAnim_Skull_Move_Left, gAnim_Skull_Move_Up, gAnim_Skull_Move_Right},
//        {gAnim_DonMedusa_Move, gAnim_DonMedusa_Move, gAnim_DonMedusa_Move, gAnim_DonMedusa_Move},
//    };

//    for (u32 i = 0; i < MST_MAX_SLOTS; i++)
//    {
//        // En début de partie le player est en état idle les monstre aussi, quand le joueur bougera la première fois les
//        // monstres bougeront.
                
//        if(gGen.nIsStartPlyr && gMst[i].nUsed)
//        {
//            if(gMst[i].nName==e_Mst_Rocky){
//                info_context lf
//            }

//            gMst[i].nState=e_MstAnim_Walk;

//            switch (gMst[i].nDir)
//            {
//            case e_Dir_Up:
//                gMst[i].nPosY-=gMst[i].nSpeed;
//                break;
//            case e_Dir_Right:
//                gMst[i].nPosX+=gMst[i].nSpeed;
//                break;
//            case e_Dir_Down:
//                gMst[i].nPosY+=gMst[i].nSpeed;
//                break;
//            case e_Dir_Left:
//                gMst[i].nPosX-=gMst[i].nSpeed;
//                break;
            
//            }

//            Animspr_AnimSetIfNew(pAnims[gMst[i].nName][gMst[i].nDir], gMst[i].nAnimNoSlot);

//            Monsters_CollideWalls(i); 
//            Monsters_CollideDecor(i, gGen.nLevel); // Génère un blocage au départ avec une vitesse de 0x80
//            Sprites_Stock(Monsters_IfHasAnAnim(i), gMst[i].nPosX >> 8, gMst[i].nPosY >> 8, e_Prio_Monsters);
//        }
//    } 
//}   

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



