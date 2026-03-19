
#include "includes.h"

const bool bAnimSprIsCommentary=false;

SAnim pAnimSlots[ANIM_MAX_SLOT];
u32 gnAnimLastSlotUsed;



// Init une anim sur un monstre spécifique.
// MONSTRE NON STATIQUE
// ALMA
void AnimSpr_AlmaAnimInit(SMonster *pMst)
{
    u64 *pAnims[][4]={
        {gAnim_Alma_Idle_Down, gAnim_Alma_Idle_Left, gAnim_Alma_Idle_Up, gAnim_Alma_Idle_Right},
        {gAnim_Alma_Walk_Down, gAnim_Alma_Walk_Left, gAnim_Alma_Walk_Up, gAnim_Alma_Walk_Right},
        {gAnim_Alma_Roll_Left, gAnim_Alma_Roll_Right, gAnim_Alma_Roll_Right, gAnim_Alma_Roll_Right},
    };

    if(pMst->nDir != e_Dir_Null){
        pMst->nAnimNoSlot=Animspr_AnimSetIfNew(pAnims[pMst->nState][pMst->nDir], pMst->nAnimNoSlot);
    }    
}
// LEEPER
void AnimSpr_LeeperAnimInit(SMonster *pMst)
{
    u64 *pAnims[][4]={
        {gAnim_Leeper_Idle_Down, gAnim_Leeper_Idle_Left, gAnim_Leeper_Idle_Up, gAnim_Leeper_Idle_Right},
        {gAnim_Leeper_Jumping_Down, gAnim_Leeper_Jumping_Left, gAnim_Leeper_Jumping_Up, gAnim_Leeper_Jumping_Right},
        {gAnim_Leeper_Sleeping_Down, gAnim_Leeper_Sleeping_Left, gAnim_Leeper_Sleeping_Up, gAnim_Leeper_Sleeping_Right},
    };
    
    if(pMst->nDir != e_Dir_Null){
        pMst->nAnimNoSlot=Animspr_AnimSetIfNew(pAnims[pMst->nState][pMst->nDir], pMst->nAnimNoSlot);
    }    
}
// ROCKY
void AnimSpr_RockyAnimInit(SMonster *pMst)
{
    if(bAnimSprIsCommentary) {info_context printf("pMst->nState %d, pMst->nDir %d", pMst->nState, pMst->nDir);lf}
    u64 *pAnims[][4]={
        {gAnim_Rocky_Idle_Down, gAnim_Rocky_Idle_Left, gAnim_Rocky_Idle_Up, gAnim_Rocky_Idle_Right},
        {gAnim_Rocky_Walk_Down, gAnim_Rocky_Walk_Left, gAnim_Rocky_Walk_Up, gAnim_Rocky_Walk_Right},
    };

    if(pMst->nDir != e_Dir_Null){
        pMst->nAnimNoSlot=Animspr_AnimSetIfNew(pAnims[pMst->nState][pMst->nDir], pMst->nAnimNoSlot);
    }    
}
// SKULL
void AnimSpr_SkullAnimInit(SMonster *pMst)
{
    u64 *pAnims[][4]={
        {gAnim_Skull_Idle_Down, gAnim_Skull_Idle_Left, gAnim_Skull_Idle_Up, gAnim_Skull_Idle_Right},
        {gAnim_Skull_Move_Down, gAnim_Skull_Move_Left, gAnim_Skull_Move_Up, gAnim_Skull_Move_Right},
    };

    if(pMst->nDir != e_Dir_Null){
        pMst->nAnimNoSlot=Animspr_AnimSetIfNew(pAnims[pMst->nState][pMst->nDir], pMst->nAnimNoSlot);
    }    
}
// DON MEDUSA
void AnimSpr_DonMedusaAnimInit(SMonster *pMst)
{
    u64 *pAnims[][4]={
        {gAnim_DonMedusa_Idle_Down, gAnim_DonMedusa_Idle_Down, gAnim_DonMedusa_Idle_Down, gAnim_DonMedusa_Idle_Down},
        {gAnim_DonMedusa_Move, gAnim_DonMedusa_Move, gAnim_DonMedusa_Move, gAnim_DonMedusa_Move},
    };

    if(pMst->nDir != e_Dir_Null){
        pMst->nAnimNoSlot=Animspr_AnimSetIfNew(pAnims[pMst->nState][pMst->nDir], pMst->nAnimNoSlot);
    }    
}

// MONSTRES STATIC
// MEDUSA
void AnimSpr_MedusaAnimInit(SMonster *pMst)
{
    u64 *pAnims[][4]={
        {gAnim_Medusa_Face, gAnim_Medusa_Face, gAnim_Medusa_Face, gAnim_Medusa_Face}, 
        {gAnim_Medusa_Attack, gAnim_Medusa_Attack, gAnim_Medusa_Attack, gAnim_Medusa_Attack},
    };
    
    if(pMst->nDir != e_Dir_Null){
        pMst->nAnimNoSlot=Animspr_AnimSetIfNew(pAnims[pMst->nState][pMst->nDir], pMst->nAnimNoSlot);
    }  
}

void AnimSpr_SnakeyAnimInit(SMonster *pMst)
{
    u64 *pAnims[][4]={
        {gAnim_Snakey_Stand_Left, gAnim_Snakey_Rotate_Left, gAnim_Snakey_Stand_Right, gAnim_Snakey_Rotate_Right},
        {gAnim_Snakey_WinPlyr, gAnim_Snakey_WinPlyr, gAnim_Snakey_WinPlyr, gAnim_Snakey_WinPlyr},
    };
    
    if(pMst->nDir != e_Dir_Null){
        pMst->nAnimNoSlot=Animspr_AnimSetIfNew(pAnims[pMst->nState][pMst->nDir], pMst->nAnimNoSlot);
    }  
}

void AnimSpr_GolAnimInit(SMonster *pMst)
{
    u64 *pAnims[][4]={
        {gAnim_Gol_Sleeping_Down, gAnim_Gol_Sleeping_Left, gAnim_Gol_Sleeping_Up, gAnim_Gol_Sleeping_Right},
        {gAnim_Gol_Awake_Down, gAnim_Gol_Awake_Left, gAnim_Gol_Awake_Up, gAnim_Gol_Awake_Right},
    };
    
    if(pMst->nDir != e_Dir_Null){
        pMst->nAnimNoSlot=Animspr_AnimSetIfNew(pAnims[pMst->nState][pMst->nDir], pMst->nAnimNoSlot);
    }  
}

void AnimSpr_WhaleAnimInit(SMonster *pMst)
{
    u64 *pAnims[][4]={
        {gAnim_Whale_Face_Down, gAnim_Whale_Face_Left, gAnim_Whale_Face_Up, gAnim_Whale_Face_Right},
        {gAnim_Whale_Attack_Down, gAnim_Whale_Attack_Left, gAnim_Whale_Attack_Up, gAnim_Whale_Attack_Right}
    };
    
    if(pMst->nDir != e_Dir_Null){
        pMst->nAnimNoSlot=Animspr_AnimSetIfNew(pAnims[pMst->nState][pMst->nDir], pMst->nAnimNoSlot);
    }  
}

// Tableau d'anim des monstres pour init un monstres.
typedef void (*pAnimInit)(SMonster *pMst);
pAnimInit gpMstAnimInitTb[]={
    // Dynamique
    AnimSpr_AlmaAnimInit,
    AnimSpr_LeeperAnimInit,
    AnimSpr_RockyAnimInit,
    AnimSpr_SkullAnimInit,
    AnimSpr_DonMedusaAnimInit,
    // Static
    AnimSpr_MedusaAnimInit,
    AnimSpr_SnakeyAnimInit,
    AnimSpr_GolAnimInit,
    AnimSpr_WhaleAnimInit
};


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
    if(bAnimSprIsCommentary) {info_context lf}
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

// Anim monstres // A REVOIR // MANQUE IDLE
void AnimSpr_MstAnimSetIfNew(SMonster *pMst){
    //u64 *pAnims[][4]={
    //    {gAnim_Alma_Walk_Down, gAnim_Alma_Walk_Left, gAnim_Alma_Walk_Up, gAnim_Alma_Walk_Right},
    //    {gAnim_Leeper_Jumping_Down, gAnim_Leeper_Jumping_Left, gAnim_Leeper_Jumping_Up, gAnim_Leeper_Jumping_Right},
    //    {gAnim_Rocky_Walk_Down, gAnim_Rocky_Walk_Left, gAnim_Rocky_Walk_Up, gAnim_Rocky_Walk_Right},
    //    {gAnim_Skull_Move_Down, gAnim_Skull_Move_Left, gAnim_Skull_Move_Up, gAnim_Skull_Move_Right},
    //    {gAnim_DonMedusa_Move, gAnim_DonMedusa_Move, gAnim_DonMedusa_Move, gAnim_DonMedusa_Move},
    //};
    //u64** pAnims[]={*pAnimsAlma, *pAnimsLeeper, *pAnimsRocky, *pAnimsSkull, *pAnimsDonMedusa};
    //{info_context printf("pMst->nName %d", pMst->nName);lf}
    //u64** pAnim=pAnims[pMst->nName];

    ////{info_context printf("pMst->nName %d, pMst->nState %d, pMst->nDir %d", pMst->nName, pMst->nState, pMst->nDir);lf}
    //if(pMst->nDir != e_Dir_Null){
    //    pMst->nAnimNoSlot=Animspr_AnimSetIfNew(&pAnim[pMst->nState][pMst->nDir], pMst->nAnimNoSlot);
    //}
}

//// Anim monstres // A REVOIR // MANQUE IDLE
//void AnimSpr_MstAnimSetIfNew(SMonster *pMst){
//    u64 *pAnims[][4]={
//        {gAnim_Alma_Walk_Down, gAnim_Alma_Walk_Left, gAnim_Alma_Walk_Up, gAnim_Alma_Walk_Right},
//        {gAnim_Leeper_Jumping_Down, gAnim_Leeper_Jumping_Left, gAnim_Leeper_Jumping_Up, gAnim_Leeper_Jumping_Right},
//        {gAnim_Rocky_Walk_Down, gAnim_Rocky_Walk_Left, gAnim_Rocky_Walk_Up, gAnim_Rocky_Walk_Right},
//        {gAnim_Skull_Move_Down, gAnim_Skull_Move_Left, gAnim_Skull_Move_Up, gAnim_Skull_Move_Right},
//        {gAnim_DonMedusa_Move, gAnim_DonMedusa_Move, gAnim_DonMedusa_Move, gAnim_DonMedusa_Move},
//    };

//    if(pMst->nDir != e_Dir_Null){
//        pMst->nAnimNoSlot=Animspr_AnimSetIfNew(pAnims[pMst->nState][pMst->nDir], pMst->nAnimNoSlot);
//    }
//}

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