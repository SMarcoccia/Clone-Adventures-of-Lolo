#include "includes.h"

#define MAX_VALUES 7 // Nb de valeur dans la structure SITEM
// Pour accélérer la recherche.
u32 gnItemLastUsed; 

// ITEMS
SItem pItemsLvl1[]={
    {e_Spr_Heart, -1, 14, 8, -1, -1, -1},
    {e_Spr_Heart, -1, 15, 8, -1, -1, -1},
    {e_Spr_Heart, -1, 11, 9, -1, -1, -1},
    {e_Spr_Heart, -1, 13, 10, -1, -1, -1},
    {e_Spr_Heart, -1, 6, 8, -1, -1, -1},
    {e_Spr_Heart, -1, 5, 11, -1, -1, -1},
    {e_Spr_Chest_Lock, -1, 9, 4, -1, -1, -1},
};

SItem pItemsLvl2[]={
    {e_Spr_Heart, -1, 9, 3, -1, -1, -1},
    {e_Spr_Heart, -1, 14, 9, -1, -1, -1},
    {e_Spr_Heart, -1, 6, 8, -1, -1, -1},
    {e_Spr_Chest_Lock, -1, 9, 11, -1, -1, -1},
};

SItemsLvls gItemsLvls[]={
    {pItemsLvl1, NBELEM(pItemsLvl1), {0, 3, 1, 0}},
    {pItemsLvl2, NBELEM(pItemsLvl2), {0, 3, 1, 0}},
};

void Items_InitSlots(void)
{
    for (u32 i = 0; i < gItemsLvls[gGen.nLevel].nNbItems; i++)
    {
        gItemsLvls[gGen.nLevel].pItemsLvl[i].nUsed = false;
    }

    gnItemLastUsed=0;
}

// TODO : A REVOIR POUR FAIRE COMME DANS Monsters_InitMonsters_Aux
void Items_InitItems(u32 nLvl)
{
    for (int i = 0; i < gItemsLvls[nLvl].nNbItems; i++)
    {
        u32 nNoSlot = Items_GetSlot(); //  On réserve un slot.
        Items_SetItem(gItemsLvls[nLvl].pItemsLvl[i].nNoSpr, nNoSlot, gItemsLvls[nLvl].pItemsLvl[i].nColumns << 4, gItemsLvls[nLvl].pItemsLvl[i].nLines << 4);
    }

    // Placement des items sur la map d'origine contenu dans gpLevels :
    for (int i = 0; i < gItemsLvls[nLvl].nNbItems; i++)
    {
        u32 nBlkX=gItemsLvls[nLvl].pItemsLvl[i].nPosX >> 4; 
        u32 nBlkY=gItemsLvls[nLvl].pItemsLvl[i].nPosY >> 4;
        gpLevels[nLvl][nBlkY * AREA_WIDTH + nBlkX] = gItemsLvls[nLvl].pItemsLvl[i].nNoSpr;
    }

}

void Items_SetItem(u32 nNoItem, u32 nNoSlot, u32 nPosX, u32 nPosY)
{
    gItemsLvls[gGen.nLevel].pItemsLvl[nNoSlot].nNoSpr = nNoItem;
    gItemsLvls[gGen.nLevel].pItemsLvl[nNoSlot].nPosX=nPosX; 
    gItemsLvls[gGen.nLevel].pItemsLvl[nNoSlot].nPosY=nPosY; 
    gItemsLvls[gGen.nLevel].pItemsLvl[nNoSlot].nNoSlot=nNoSlot; 
}

u32 Items_GetSlot(void)
{
    for (u32 i = gnItemLastUsed; i < gItemsLvls[gGen.nLevel].nNbItems; i++)
    {
        if (gItemsLvls[gGen.nLevel].pItemsLvl[i].nUsed == false)
        {
            gItemsLvls[gGen.nLevel].pItemsLvl[i].nUsed = true;
            gnItemLastUsed++;
            return i;
        }
    }
    return -1;
}

void Items_ReleaseSlot(u32 nNoSlot)
{
    if(nNoSlot < gnItemLastUsed)
    {
        //info_context lf
        gnItemLastUsed=nNoSlot;
    }
    gItemsLvls[gGen.nLevel].pItemsLvl[nNoSlot].nUsed=false;
}
