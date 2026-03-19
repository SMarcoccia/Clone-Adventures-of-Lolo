#include "includes.h"

// -1 Pas de sprite.
//  0 Ground With Shadow.
//  1 Ground Without Shadow.
//  2 Stone With Shadow. 
//  3 Stone Without Shadow.
//  4 Tree With Shadow.
//  5 Tree Without Shadow.
//  7 Heart (Color Pink)
//  9 chest
//  30 Porte
//  34 Mur
//  35 Mur
//  36 Mur
//  37 Mur 
//  38 Mur
//  39 Mur
//  40 Mur
//  41 Mur
//  42 Mur
//  248 lolo.

s16 gLvl1[AREA_WIDTH*AREA_HEIGHT]={
     //  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16   17  18  19
/* 0*/  -1, -1, -1, -1, 34, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 35,  -1, -1, -1, /*19*/
/* 1*/  -1, -1, -1, -1, 38, 41, 42, 42, 42, 42, 42, 30, 42, 42, 42, 42, 39,  -1, -1, -1, /*39*/
/* 2*/  -1, -1, -1, -1, 38,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 39, 248, -1, -1, /*59*/
/* 3*/  -1, -1, -1, -1, 38,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 39,  -1, -1, -1, /*79*/
/* 4*/  -1, -1, -1, -1, 38,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 39, 240, -1, -1, /*99*/
/* 5*/  -1, -1, -1, -1, 38,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 39,  -1, -1, -1, /*119*/
/* 6*/  -1, -1, -1, -1, 38,  1,  1,  1,  1,  1,  1,  5,  1,  1,  1,  1, 39,  -1, -1, -1, /*139*/
/* 7*/  -1, -1, -1, -1, 38,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 39,  -1, -1, -1, /*159*/
/* 8*/  -1, -1, -1, -1, 38,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 39,  -1, -1, -1, /*179*/
/* 9*/  -1, -1, -1, -1, 38,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 39, 238, -1, -1, /*199*/
/*10*/  -1, -1, -1, -1, 38,  1,  1,  5,  1,  1,  1,  1,  1,  1,  1,  1, 39, 238, -1, -1, /*219*/
/*11*/  -1, -1, -1, -1, 38,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 39, 238, -1, -1, /*239*/
/*12*/  -1, -1, -1, -1, 38,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 39,  -1, -1, -1, /*259*/
/*13*/  -1, -1, -1, -1, 36, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 37,  -1, -1, -1, /*279*/
/*14*/  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, /*299*/
};


s16 gLvl2[AREA_WIDTH*AREA_HEIGHT]={
     //  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16   17  18  19
/* 0*/  -1, -1, -1, -1, 34, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 35,  -1, -1, -1, /*19*/
/* 1*/  -1, -1, -1, -1, 38, 41, 42, 42, 42, 42, 42, 30, 42, 42, 42, 42, 39,  -1, -1, -1, /*39*/
/* 2*/  -1, -1, -1, -1, 38,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 39, 248, -1, -1, /*59*/
/* 3*/  -1, -1, -1, -1, 38,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 39,  -1, -1, -1, /*79*/
/* 4*/  -1, -1, -1, -1, 38,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 39, 240, -1, -1, /*99*/
/* 5*/  -1, -1, -1, -1, 38,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 39,  -1, -1, -1, /*119*/
/* 6*/  -1, -1, -1, -1, 38,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 39,  -1, -1, -1, /*139*/
/* 7*/  -1, -1, -1, -1, 38,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 39,  -1, -1, -1, /*159*/
/* 8*/  -1, -1, -1, -1, 38,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 39,  -1, -1, -1, /*179*/
/* 9*/  -1, -1, -1, -1, 38,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 39, 238, -1, -1, /*199*/
/*10*/  -1, -1, -1, -1, 38,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 39, 238, -1, -1, /*219*/
/*11*/  -1, -1, -1, -1, 38,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 39, 238, -1, -1, /*239*/
/*12*/  -1, -1, -1, -1, 38,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 39,  -1, -1, -1, /*259*/
/*13*/  -1, -1, -1, -1, 36, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 37,  -1, -1, -1, /*279*/
/*14*/  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, /*299*/
};

// Player :
// Le sprite de départ + la position du plyr sur la carte.
SPlyrLvl gPlyrLvl1[]={
    {e_Spr_Lolo_Down_Stand, 13, 12},
};

SPlyrLvl gPlyrLvl2[]={
    {e_Spr_Lolo_Down_Stand, 10, 12},
};

/*ENSEMBLE DES LEVELS POUR PLAYER*/
// Pour les items voir items.c et .h

s16 *gpLevels[]={
    gLvl1, 
    gLvl2
};

SPlyrsLvls gPlyrsLvls[]={
    {gPlyrLvl1, 1},
    {gPlyrLvl2, 2},
};

// Note sur les monstres :
// Leeper va sur le sable, pas sur l'herbe mais si on le met sur l'herbe ne bouge plus, passe sur les flèches au sol.
// Skull :
//  - Va sur passerel, va sur le sable, ne va pas sur le coffre, ne va pas sur l'herbe sauf si on le met sur au milieu de 9 cases, si est sur l'herbe pars de 
//    l'herbe. Passe sur les flèches au sol. Ne traverse pas les coffres ouvert.
// Rock : 
//  - Pousse Don Médusa, va sur passerel, va sur le sable, va sur flèche par terre peu importe le sens, va pas sur l'herbe si sur l'herbe ne bouge plus, ne va pas 
//    sur le coffre.
// Médusa : 
//  - les flèches passent les flêches au sol, flèche passe au travers du egg dans l'eau mais pas sur terre et flèche passe au travers du coeur si on prend le
//    coeur mais les flèches ne passe pas si on est derrière le coeur, les flèches ne passe pas si on est sur 1/2 de coeur et que médusa nous tourne le dos.
//    Si on est sur la moitié d'un coeur pas de danger ni avec don médusa. Flèche passe au travers si on est derrière un coffre.
// Block passe pas au travers des coeurs, passe aux travers des coffres, arbres.
// Don médusa : 
//  - l'épée passe aux travers des flèches au sols et des arbres et du coffre. Si on le pousse avec un block dans le sens contraire il va dans le sens du 
//    block qu'on pousse. Ne travers pas l'herbe. Si on est sur le 1/4 ou le 1/2 coeur mais pas en face de lui alors pas de danger. 
// Alma : 
//  - ne passe pas au travers des coffres, ne passe pas sur l'herbe, si est sur l'herbe quitte l'herbe sauf si est au milieu de 9 cases, passe sur le sable. Si on est sur la moitié d'un coeur
//    on meurt. Block le pousse.       
// perso protégé des alma si est sur le coffre
// Conversion de toutes les Case : non solide (0), items et décore (1), les murs (2), -1 pas de sprite.

void Level_DisplayCollide(s16 *pLvl){
    for (u32 i = 0, k=0; i < AREA_WIDTH*AREA_HEIGHT; i++, k++){
        if(k < AREA_WIDTH){
            if (pLvl[i] != e_Area_Solid ){
                printf("%4d", pLvl[i]); 
            }else{
                printf("\x1b[1;45m%4d\x1b[0m", pLvl[i]); 
            }
        }else{
            k=-1;
            i-=1;
            lf
        } 
    }
}

void Level_Display(s16 *pLvl, bool isLvlCollide)
{
    if( ! isLvlCollide){
        for (u32 i = 0, k=0; i < AREA_WIDTH*AREA_HEIGHT; i++, k++)
        {
            if(k < AREA_WIDTH){
                if (pLvl[i] != -1){
                    if(pLvl[i] != e_Spr_Lolo_Down_Stand && pLvl[i] != e_Spr_Player_Shoot_Left && pLvl[i] != e_Spr_Square){
                        if((pLvl[i] == e_Spr_Ground || pLvl[i] == e_Spr_Ground+1) || (pLvl[i] >= e_Spr_Footbridge && pLvl[i] < e_Spr_Door) || (pLvl[i] >=e_Spr_Sand_End && pLvl[i] < e_Spr_Snakey_Stand_Left)){
                            printf("%4d", pLvl[i]); 
                        } 
                        // e_Case_Solid
                        else if(
                            (pLvl[i] >= e_Spr_Stone && pLvl[i] < e_Spr_Hammer) || 
                            (pLvl[i] >= e_Spr_Arrow_Changer && pLvl[i] < e_Spr_Footbridge) || 
                            (pLvl[i] >= e_Spr_Snakey_Stand_Left && pLvl[i] < e_Spr_Alma_Down_Stand) ||
                            (pLvl[i] >= e_Spr_Leeper_Sleeping_Down && pLvl[i] < e_Spr_Rocky_Stand_Down) ||
                            (pLvl[i] >= e_Spr_Skull_Stand_Down && pLvl[i] < e_Spr_DonMedusa_Stand) ||
                            (pLvl[i] >= e_Spr_Medusa_Stand && pLvl[i] < e_Spr_Medusa_Arrows) ||
                            (pLvl[i] >= e_Spr_Whale_Stand_Down && pLvl[i] < e_Spr_Square)
                        ){
                            printf("\x1b[1;45m%4d\x1b[0m", pLvl[i]); 
                        }
                        // Monstre en mouvement
                        else if (
                            (pLvl[i] >= e_Spr_Alma_Down_Stand && pLvl[i] < e_Spr_Gol_Sleeping_Down) ||
                            (pLvl[i] >= e_Spr_Rocky_Stand_Down && pLvl[i] < e_Spr_Skull_Stand_Down)
                        )
                        {
                            printf("\x1b[1;41m%4d\x1b[0m", pLvl[i]); 

                        }
                        else{
                            printf("%4d", pLvl[i]); 
                        }
                    }else if(pLvl[i]==238 || pLvl[i]==240 || pLvl[i]==248){
                        if(pLvl[i]==248){
                            printf("\x1b[1;44m%4d\x1b[0m", pLvl[i]); 
                        }else{
                            printf("%4d", pLvl[i]); 
                        }
                    }
                }else{
                    printf("%4d", pLvl[i]); 
                }
            
                //printf("%4d", pLvl[i]); 
                //printf("%4d, k=%d, i=%d", pLvl[i], k, i); 
                // printf("\033[33mThis is yellow\033[0m");
                
            }else{
                k=-1;
                i-=1;
                lf
            } 
        }
    }else
    {
        Level_DisplayCollide(pLvl); lf
    }
}