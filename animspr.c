
#include "includes.h"

SAnim pAnimSlots[ANIM_MAX_SLOT];
u32 gnAnimLastSlotUsed;


u32 Animspr_GetImgLast(u32 nNoSlot)
{
    return pAnimSlots[nNoSlot].nCurSpr;
}

void Animspr_GetKey(void)
{

}

void Animspr_InitSlots(void)
{
    for (u32 i = 0; i < ANIM_MAX_SLOT; i++)
    {
        pAnimSlots[i].nUsed=false;
    }
    gnAnimLastSlotUsed = 0;
}

bool Animspr_CheckEnd(s32 nSlotNo)
{
    return 0;
}

s32 Animspr_AnimSetIfNew(u64 *pAnim, u32 nNoSlot)
{
    // Il ne faut surtout pas faire AnimSet si pOrg != pAnm n'est pas utilisé, sinon on réinitialise à chaque fois toutes 
    // les valeurs du slot et on à toujours l'image de départ affiché. Faire ceci permet de simplifier le code évite 
    // d'avoir à déclarer toutes les variables pour chaque anim.
    if(pAnimSlots[nNoSlot].pOrg != pAnim)
    {
        nNoSlot=Animspr_AnimSet(pAnim, nNoSlot); 
    }
    return nNoSlot;
}

s32 Animspr_GetSlot(void)
{
    for (int i = gnAnimLastSlotUsed; i < ANIM_MAX_SLOT; i++)
    {         
        if( ! pAnimSlots[i].nUsed)
        {
            gnAnimLastSlotUsed=i+1;
            return i;
        }
    }
    return -1;
}

// Anim player
void AnimSpr_PlyrAnimSetIfNew(SPlayer *pPlyr)
{
    u64 *pPlyrAnm [e_PlyrAnim_Max][4]={
        {gAnim_Plyr_Idle_Down, gAnim_Plyr_Idle_Left, gAnim_Plyr_Idle_Up, gAnim_Plyr_Idle_Right},
        {gAnim_Plyr_Sleeping_Down, gAnim_Plyr_Sleeping_Left, gAnim_Plyr_Sleeping_Up, gAnim_Plyr_Sleeping_Right},
        {gAnim_Plyr_Walk_Down, gAnim_Plyr_Walk_Left, gAnim_Plyr_Walk_Up, gAnim_Plyr_Walk_Right},
        {gAnim_Plyr_Win, gAnim_Plyr_Win, gAnim_Plyr_Win, gAnim_Plyr_Win},
        {gAnim_Plyr_DeathArrow, gAnim_Plyr_DeathArrow, gAnim_Plyr_DeathArrow, gAnim_Plyr_DeathArrow},
        {gAnim_Plyr_DeathBurnt, gAnim_Plyr_DeathBurnt, gAnim_Plyr_DeathBurnt, gAnim_Plyr_DeathBurnt},
        {gAnim_Plyr_Death, gAnim_Plyr_Death, gAnim_Plyr_Death, gAnim_Plyr_Death},
    };

    if(pPlyr->nDir != e_Dir_Null){
        pPlyr->nAnimNoSlot=Animspr_AnimSetIfNew(pPlyrAnm[pPlyr->nState][pPlyr->nDir], pPlyr->nAnimNoSlot);
    }
}

// Anim monstres
void AnimSpr_MstAnimSetIfNew(SMonster *pMst){
    u64 *pAnims[][4]={
        {gAnim_Alma_Walk_Down, gAnim_Alma_Walk_Left, gAnim_Alma_Walk_Up, gAnim_Alma_Walk_Right},
        {gAnim_Leeper_Jumping_Down, gAnim_Leeper_Jumping_Left, gAnim_Leeper_Jumping_Up, gAnim_Leeper_Jumping_Right},
        {gAnim_Rocky_Walk_Down, gAnim_Rocky_Walk_Left, gAnim_Rocky_Walk_Up, gAnim_Rocky_Walk_Right},
        {gAnim_Skull_Move_Down, gAnim_Skull_Move_Left, gAnim_Skull_Move_Up, gAnim_Skull_Move_Right},
        {gAnim_DonMedusa_Move, gAnim_DonMedusa_Move, gAnim_DonMedusa_Move, gAnim_DonMedusa_Move},
    };

    if(pMst->nDir != e_Dir_Null){
        pMst->nAnimNoSlot=Animspr_AnimSetIfNew(pAnims[pMst->nState][pMst->nDir], pMst->nAnimNoSlot);
    }
}

s32 Animspr_AnimSet(u64 *pAnim, u32 nNoSlot)
{
    if(nNoSlot == -1)
    {
        if((nNoSlot=Animspr_GetSlot()) == -1) return -1;
    }
    pAnimSlots[nNoSlot].pOrg=pAnim;
    pAnimSlots[nNoSlot].nKey=*pAnim; 
    pAnimSlots[nNoSlot].pAnim=pAnim-1; // On se met à -1 car dans getImg on fait un +=2 pour ê à la 1er frame.
    pAnimSlots[nNoSlot].nFramesCnt=1;
    pAnimSlots[nNoSlot].nFlags=0; 

    Animspr_GetImg(nNoSlot); // Pour avoir le premier sprite dans le slot.

    return nNoSlot;
}

u32 Animspr_GetImg(u32 nNoSlot)
{
    //printf("pAnimSlots[nNoSlot].nFramesCnt %d", pAnimSlots[nNoSlot].nFramesCnt);lf
    if (--pAnimSlots[nNoSlot].nFramesCnt == 0)
    {
        pAnimSlots[nNoSlot].pAnim+=2;

        if(((*pAnimSlots[nNoSlot].pAnim) & BIT31) != 0)
        {
            switch (*pAnimSlots[nNoSlot].pAnim)
            {
                case e_Anim_Jump :
                    pAnimSlots[nNoSlot].pAnim += *(s64*)(pAnimSlots[nNoSlot].pAnim+1); // On se remet au dernier nombre de frames.
                    break;
                case e_Anim_Goto : // A FINIR.
                    pAnimSlots[nNoSlot].pAnim = pAnimSlots[nNoSlot].pOrg+1; // On se recale sur le nombre de frames.
                    break;
                case e_Anim_End :
                    gGen.nPhase = e_Game_GameOver;
                    break;
                case e_Anim_Kill :
                    break;
                case e_Anim_Sfx: // ATTENTION : e_Sfx_LoloDead, e_Anim_Sfx, dans le tableau d'anim sont vue comme
                                //des sprites donc interdire que e_Sfx soit lu comme des sprites en faisant comme ci-dessous. 
                    Sound_Play(*(++pAnimSlots[nNoSlot].pAnim), SOUND_CHANNEL_MUSIC);
                    pAnimSlots[nNoSlot].pAnim++;
                    break;
            }
        }

        pAnimSlots[nNoSlot].nFramesCnt=*pAnimSlots[nNoSlot].pAnim;
        pAnimSlots[nNoSlot].nCurSpr=*(pAnimSlots[nNoSlot].pAnim+1);
    }
    
    return pAnimSlots[nNoSlot].nCurSpr;
}

void Animspr_ClearSlots(void)
{
    memset(pAnimSlots, 0, sizeof(SAnim));
}