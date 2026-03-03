#include "includes.h"

u32 gnOldPosY = 0;

u32 Tools_LineToY(u32 nLine)
{
    return ((float)(SCR_HEIGHT*nLine))/AREA_HEIGHT;
}

u32 Tools_ColumnToX(u32 nColumn)
{
    return ((float)(SCR_WIDTH*nColumn))/AREA_WIDTH;
}

u32 Tools_XToColumn(u32 x)
{
    return (float)(x*AREA_WIDTH)/SCR_WIDTH;
}

u32 Tools_YToLine(u32 y)
{
    return (float)(y*AREA_HEIGHT)/SCR_HEIGHT;
}

u32 Tools_XToColumnCeilf(u32 x)
{
    return ceilf((float)(x*AREA_WIDTH)/SCR_WIDTH);
}

u32 Tools_YToLineCeilf(u32 y)
{
    return ceilf((float)(y*AREA_HEIGHT)/SCR_HEIGHT);
}

float Tools_XToColumnFloat(u32 x)
{
    return (float)(x*AREA_WIDTH)/SCR_WIDTH;
}

float Tools_YToLineFloat(u32 y)
{
    return (float)(y*AREA_HEIGHT)/SCR_HEIGHT;
}

void info_dir_plyr(SPlayer gPlyr){
    printf("gPlyr.nDir %s", gPlyr.nDir == e_Dir_Down ? "Down" : gPlyr.nDir == e_Dir_Left ? "Left" : gPlyr.nDir == e_Dir_Right ? "Right" : "Up"); 
}

void info_dir_Mst(SMonster gMst){
    printf("gMst.nDir %s", gMst.nDir == e_Dir_Down ? "Down" : gMst.nDir == e_Dir_Left ? "Left" : gMst.nDir == e_Dir_Right ? "Right" : "Up"); 
}
//u32 Tools_GetSprDecor(u32 nIdx, u32 nLvl)
//{
//    // Si direction Left :
//    u32 nColMin = Tools_XToColumn(gMst[nIdx].nPosX);
//    // Si direction Right (-1 pour évité de déborder sur la case suivante) :
//    u32 nColMax = Tools_XToColumn(gMst[nIdx].nPosX+SPR_SIZE-1);
//    // Si direction Up :
//    u32 nLineMin = Tools_YToLine(gMst[nIdx].nPosY);
//    // Si direction Bottom :
//    u32 nLineMax = Tools_YToLine(gMst[nIdx].nPosY+SPR_SIZE-1);
    
//    u32 nNoSpr=0;

//    //printf("nNoSpr %d, Min %d, Max %d, LMin %d, LMax %d", nNoSpr, nColMin, nColMax, nLineMin, nLineMax);lf
//    // On test si on est sur une case solide :
//    switch (gMst[nIdx].nDir)
//    {
//        case e_Dir_Down:
//            nNoSpr=gLvl[nLineMax*AREA_WIDTH + nColMin];
//            break;
//        case e_Dir_Left:
//            nNoSpr=gLvl[nLineMin*AREA_WIDTH + nColMin];
//            break;
//        case e_Dir_Up:
//            nNoSpr=gLvl[nLineMin*AREA_WIDTH + nColMin];
//            break;
//        case e_Dir_Right:
//            nNoSpr=gLvl[nLineMin*AREA_WIDTH + nColMax];
//            break;
//    }

//    return nNoSpr;
//}

char *Tools_ReplaceOccurence(char *dst)
{
    char *str=dst;
    do
    {
        if(*str == '0')
        {
            *str=' ';
        }else
            break;
    }
    while (*(++str) != '\0');
    // ATTENTION REMETRE STR AU DEBUT DU FICHIER
    
    return dst;
}

char *Tools_IntToASCII(int nb, char *dst)
{
    if(nb == 0) return dst="  0"; 
    memset(dst, '0', 3);
    // On affect la taille de dst. -1 pour enlever le 0 de fin de chaîne.
    char *str=dst+strlen(dst)-1; 

    while (str >= dst)
    {
        //printf("nb %d str %p dst %p strlen(dst) %d", nb, str, dst, strlen(dst));lf
        int num=nb % 10;
        *str=(num+'0');
        str--;
        nb =(nb-num)/10;
    }
    str=Tools_ReplaceOccurence(++str);
    return str ; // On ajoute ++ pour revenir à la 1er case du tableau.

}