#include "includes.h"

// Note (u64)-2 nous ramène 2 case en arrière, à la dernière valeur de la frame, i.e dans gAnim_Plyr_Down_Idle à 150. 
// On fait cela par ex, si on est en  condition de victoire, l'anim de la victoir s'exécute puis quand celle-ci est fini 
// on retourne au dernier sprite en attendant que le joueur appuis sur entrée pour revenir au menu. 
// PLAYER :
u64 gAnim_Plyr_Idle_Down[]={
    // Dans C_Bomber_v1_src3264 il met cela idem pour walk mais apparemment un animKey_Null serait suffisant. En fait non,
    // quand on veut s'arrêter pour savoir dans quel direction on s'arrête down, up, etc on a besoin de la clé d'anim.
    e_AnimKey_PlyrIdle, 
    // Le 150 ou dès fois 65000 évite dans getImg de faire des manipulation inutile sur pAnimSlot, 
    // test juste la conditon == 0.
    65000, e_Spr_Lolo_Down_Stand, 
    e_Anim_Jump, (u64)-2
};

u64 gAnim_Plyr_Idle_Left[]={
    e_AnimKey_PlyrIdle,
    65000, e_Spr_Lolo_Left_Stand,
    e_Anim_Jump, (u64)-2
};

u64 gAnim_Plyr_Idle_Up[]={
    e_AnimKey_PlyrIdle,
    65000, e_Spr_Lolo_Up_Stand,
    e_Anim_Jump, (u64)-2
};

u64 gAnim_Plyr_Idle_Right[]={
    e_AnimKey_PlyrIdle,
    65000, e_Spr_Lolo_Right_Stand,
    e_Anim_Jump, (u64)-2
};

u64 gAnim_Plyr_Walk_Down[]={
    e_AnimKey_PlyrWalk,
    6, e_Spr_Lolo_Walk_Down,
    6, e_Spr_Lolo_Walk_Down+1,
    6, e_Spr_Lolo_Walk_Down+2,
    6, e_Spr_Lolo_Walk_Down+3,
    e_Anim_Goto, (u64)gAnim_Plyr_Walk_Down
};
u64 gAnim_Plyr_Walk_Left[]={
    e_AnimKey_PlyrWalk,
    6, e_Spr_Lolo_Walk_Left,
    6, e_Spr_Lolo_Walk_Left+1,
    6, e_Spr_Lolo_Walk_Left+2,
    6, e_Spr_Lolo_Walk_Left+3,
    e_Anim_Goto, (u64)gAnim_Plyr_Walk_Left
};
u64 gAnim_Plyr_Walk_Up[]={
    e_AnimKey_PlyrWalk,
    6, e_Spr_Lolo_Walk_Up,
    6, e_Spr_Lolo_Walk_Up+1,
    6, e_Spr_Lolo_Walk_Up+2,
    6, e_Spr_Lolo_Walk_Up+3,
    e_Anim_Goto, (u64)gAnim_Plyr_Walk_Up
};
u64 gAnim_Plyr_Walk_Right[]={
    e_AnimKey_PlyrWalk,
    6, e_Spr_Lolo_Walk_Right,
    6, e_Spr_Lolo_Walk_Right+1,
    6, e_Spr_Lolo_Walk_Right+2,
    6, e_Spr_Lolo_Walk_Right+3,
    e_Anim_Goto, (u64)gAnim_Plyr_Walk_Right
};

u64 gAnim_Plyr_Sleeping_Down[]={
    e_AnimKey_Null,
    64, e_Spr_Lolo_Sleep_Down,
    64, e_Spr_Lolo_Sleep_Down+1,
    e_Anim_Goto, (u64)gAnim_Plyr_Sleeping_Down
};

u64 gAnim_Plyr_Sleeping_Left[]={
    e_AnimKey_Null,
    64, e_Spr_Lolo_Sleep_Left,
    64, e_Spr_Lolo_Sleep_Left+1,
    e_Anim_Goto, (u64)gAnim_Plyr_Sleeping_Left
};

u64 gAnim_Plyr_Sleeping_Up[]={
    e_AnimKey_Null,
    64, e_Spr_Lolo_Sleep_Up,
    64, e_Spr_Lolo_Sleep_Up+1,
    e_Anim_Goto, (u64)gAnim_Plyr_Sleeping_Up
};

u64 gAnim_Plyr_Sleeping_Right[]={
    e_AnimKey_Null,
    64, e_Spr_Lolo_Sleep_Right,
    64, e_Spr_Lolo_Sleep_Right+1,
    e_Anim_Goto, (u64)gAnim_Plyr_Sleeping_Right
};

// 2 anim différentes pour la victoire, au choix.
u64 gAnim_Plyr_Win[]={
    e_AnimKey_PlyrWin,
    6, e_Spr_Lolo_Win,
    6, e_Spr_Lolo_Win+1,
    10, e_Spr_Lolo_Win+2,
    6, e_Spr_Lolo_Win+3,
    e_Anim_Goto, (u64)gAnim_Plyr_Win
};

// Possibilité d'amélioration ? mettre dans gAnim_Plyr_Death.
u64 gAnim_Plyr_DeathArrow[]={
    e_AnimKey_PlyrDeath, e_Anim_Sfx, e_Sfx_LoloDead, 
    16, e_Spr_Lolo_DeadByArrow,
    36,e_Spr_Lolo_DeadFinal,
    4, e_Spr_Lolo_DeadFinal+1,
    6, e_Spr_Lolo_DeadFinal+2,
    4, e_Spr_Lolo_DeadFinal+1,
    8, e_Spr_Lolo_DeadFinal+2,
    6, e_Spr_Lolo_DeadFinal+1,
    4, e_Spr_Lolo_DeadFinal+2,
    4, e_Spr_Lolo_DeadFinal+1,
    6, e_Spr_Lolo_DeadFinal+2,
    4, e_Spr_Lolo_DeadFinal+1,
    6, e_Spr_Lolo_DeadFinal+2,
    4, e_Spr_Lolo_DeadFinal+1,
    4, e_Spr_Lolo_DeadFinal+2,
    4, e_Spr_Lolo_DeadFinal+1,
    36, e_Spr_Lolo_DeadFinal+3,
    1, SPR_NOSPRITE,
    e_Anim_End
};

u64 gAnim_Plyr_DeathBurnt[]={
    // Note : ce sera toujours des bruitages dans les anims donc pas besoin de rajouter opérateur binaire OU et SOUND_CHANNEL_EFFECT.
    e_AnimKey_PlyrDeath, e_Anim_Sfx, e_Sfx_LoloDead,  
    16, e_Spr_Lolo_DeadByBurnt,
    36, e_Spr_Lolo_DeadFinal,
     4, e_Spr_Lolo_DeadFinal+1,
     6, e_Spr_Lolo_DeadFinal+2,
     4, e_Spr_Lolo_DeadFinal+1,
     8, e_Spr_Lolo_DeadFinal+2,
     6, e_Spr_Lolo_DeadFinal+1,
     4, e_Spr_Lolo_DeadFinal+2,
     4, e_Spr_Lolo_DeadFinal+1,
     6, e_Spr_Lolo_DeadFinal+2,
     4, e_Spr_Lolo_DeadFinal+1,
     6, e_Spr_Lolo_DeadFinal+2,
     4, e_Spr_Lolo_DeadFinal+1,
     4, e_Spr_Lolo_DeadFinal+2,
     4, e_Spr_Lolo_DeadFinal+1,
    36, e_Spr_Lolo_DeadFinal+3,
    1, SPR_NOSPRITE,
    e_Anim_End
};


u64 gAnim_Plyr_Death[]={
    e_AnimKey_PlyrDeath, e_Anim_Sfx, e_Sfx_LoloDead, 
    36, e_Spr_Lolo_DeadFinal,
    4, e_Spr_Lolo_DeadFinal+1,
    6, e_Spr_Lolo_DeadFinal+2,
    4, e_Spr_Lolo_DeadFinal+1,
    8, e_Spr_Lolo_DeadFinal+2,
    6, e_Spr_Lolo_DeadFinal+1,
    4, e_Spr_Lolo_DeadFinal+2,
    4, e_Spr_Lolo_DeadFinal+1,
    6, e_Spr_Lolo_DeadFinal+2,
    4, e_Spr_Lolo_DeadFinal+1,
    6, e_Spr_Lolo_DeadFinal+2,
    4, e_Spr_Lolo_DeadFinal+1,
    4, e_Spr_Lolo_DeadFinal+2,
    4, e_Spr_Lolo_DeadFinal+1,
    36, e_Spr_Lolo_DeadFinal+3,
    1, SPR_NOSPRITE,
    e_Anim_End
};

/* *********************** MONSTERS : ***********************/

u64 gAnim_Snakey_WinPlyr[]={
    e_AnimKey_Null,
    6, e_Spr_Snakey_Rotate_Left,
    6, e_Spr_Snakey_Rotate_Right,
    e_Anim_Goto, (u64) gAnim_Snakey_WinPlyr
}; 

/*************** Alma : ***************/
// Idle :
u64 gAnim_Alma_Idle_Down[]={
    e_AnimKey_MstIdle,
    65000, e_Spr_Alma_Down_Stand,
    e_Anim_Jump, (u64)-2
};    

u64 gAnim_Alma_Idle_Left[]={
    e_AnimKey_MstIdle,
    65000, e_Spr_Alma_Left_Stand,
    e_Anim_Jump, (u64)-2
};    

u64 gAnim_Alma_Idle_Up[]={
    e_AnimKey_MstIdle,
    65000, e_Spr_Alma_Up_Stand,
    e_Anim_Jump, (u64)-2
};    

u64 gAnim_Alma_Idle_Right[]={
    e_AnimKey_MstIdle,
    65000, e_Spr_Alma_Right_Stand,
    e_Anim_Jump, (u64)-2
};  

// Walk
u64 gAnim_Alma_Walk_Down[]={
    e_AnimKey_Null,
    6, e_Spr_Alma_Walk_Down,
    6, e_Spr_Alma_Down_Stand,
    6, e_Spr_Alma_Walk_Down+1,
    6, e_Spr_Alma_Down_Stand,
    e_Anim_Goto, (u64)gAnim_Alma_Walk_Down
}; 

u64 gAnim_Alma_Walk_Left[]={
    e_AnimKey_Null,
    6, e_Spr_Alma_Walk_Left,
    6, e_Spr_Alma_Left_Stand,
    6, e_Spr_Alma_Walk_Left+1,
    6, e_Spr_Alma_Left_Stand,
    e_Anim_Goto, (u64)gAnim_Alma_Walk_Left
}; 

u64 gAnim_Alma_Walk_Up[]={
    e_AnimKey_Null,
    6, e_Spr_Alma_Walk_Up,
    6, e_Spr_Alma_Up_Stand,
    6, e_Spr_Alma_Walk_Up+1,
    6, e_Spr_Alma_Up_Stand,
    e_Anim_Goto, (u64)gAnim_Alma_Walk_Up
}; 

u64 gAnim_Alma_Walk_Right[]={
    e_AnimKey_Null,
    6, e_Spr_Alma_Walk_Right,
    6, e_Spr_Alma_Right_Stand,
    6, e_Spr_Alma_Walk_Right+1,
    6, e_Spr_Alma_Right_Stand,
    e_Anim_Goto, (u64)gAnim_Alma_Walk_Right
}; 

u64 gAnim_Alma_Roll_Left[]={
    e_AnimKey_Null,
    6, e_Spr_Alma_Roll_Left,    
    6, e_Spr_Alma_Roll_Left+1,
    e_Anim_Goto, (u64)gAnim_Alma_Roll_Left
}; 

u64 gAnim_Alma_Roll_Right[]={
    e_AnimKey_Null,
    6, e_Spr_Alma_Roll_Right,
    6, e_Spr_Alma_Roll_Right,
    e_Anim_Goto, (u64)gAnim_Alma_Roll_Right
};    

/*************** Leaper : ***************/
// Idle
u64 gAnim_Leeper_Idle_Down[]={
    e_AnimKey_MstIdle,
    65000, e_Spr_Leeper_Down_Stand,
    e_Anim_Jump, (u64)-2
};    

u64 gAnim_Leeper_Idle_Left[]={
    e_AnimKey_MstIdle,
    65000, e_Spr_Leeper_Left_Stand,
    e_Anim_Jump, (u64)-2
};    

u64 gAnim_Leeper_Idle_Up[]={
    e_AnimKey_MstIdle,
    65000, e_Spr_Leeper_Up_Stand,
    e_Anim_Jump, (u64)-2
};    

u64 gAnim_Leeper_Idle_Right[]={
    e_AnimKey_MstIdle,
    65000, e_Spr_Leeper_Right_Stand,
    e_Anim_Jump, (u64)-2
};  

// Jumping
u64 gAnim_Leeper_Jumping_Down[]={
    e_AnimKey_Null,
    3, e_Spr_Leeper_Down_Stand,
    1, e_Spr_Leeper_Jumping_Down,
    4, e_Spr_Leeper_Down_Stand,
    e_Anim_Goto, (u64)gAnim_Leeper_Jumping_Down    
};

u64 gAnim_Leeper_Jumping_Left[]={
    e_AnimKey_Null,
    6, e_Spr_Leeper_Left_Stand,
    6, e_Spr_Leeper_Jumping_Left,
    e_Anim_Goto, (u64)gAnim_Leeper_Jumping_Left
};

u64 gAnim_Leeper_Jumping_Up[]={
    e_AnimKey_Null,
    6, e_Spr_Leeper_Up_Stand,
    6, e_Spr_Leeper_Jumping_Up,
    e_Anim_Goto, (u64)gAnim_Leeper_Jumping_Up
};

u64 gAnim_Leeper_Jumping_Right[]={
    e_AnimKey_Null,
    6, e_Spr_Leeper_Right_Stand,
    6, e_Spr_Leeper_Jumping_Right,
    e_Anim_Goto, (u64)gAnim_Leeper_Jumping_Right
};

// Sleeping
u64 gAnim_Leeper_Sleeping_Down[]={
    e_AnimKey_Null,
    6, e_Spr_Leeper_Sleeping_Down,
    6, e_Spr_Leeper_Sleeping_Down+1,
    e_Anim_Goto, (u64)gAnim_Leeper_Sleeping_Down
};

u64 gAnim_Leeper_Sleeping_Left[]={
    e_AnimKey_Null,
    6, e_Spr_Leeper_Sleeping_Left,
    6, e_Spr_Leeper_Sleeping_Left+1,
    e_Anim_Goto, (u64)gAnim_Leeper_Sleeping_Left
};

u64 gAnim_Leeper_Sleeping_Up[]={
    e_AnimKey_Null,
    6, e_Spr_Leeper_Sleeping_Up,
    6, e_Spr_Leeper_Sleeping_Up+1,
    e_Anim_Goto, (u64)gAnim_Leeper_Sleeping_Up
};

u64 gAnim_Leeper_Sleeping_Right[]={
    e_AnimKey_Null,
    6, e_Spr_Leeper_Sleeping_Right,
    6, e_Spr_Leeper_Sleeping_Right+1,
    e_Anim_Goto, (u64)gAnim_Leeper_Sleeping_Right
};    

/*************** Rocky : ***************/
// Idle :
u64 gAnim_Rocky_Idle_Down[]={
    e_AnimKey_MstIdle,
    65000, e_Spr_Rocky_Stand_Down,
    e_Anim_Jump, (u64)-2
};    

u64 gAnim_Rocky_Idle_Left[]={
    e_AnimKey_MstIdle,
    65000, e_Spr_Rocky_Stand_Left,
    e_Anim_Jump, (u64)-2
};    

u64 gAnim_Rocky_Idle_Up[]={
    e_AnimKey_MstIdle,
    65000, e_Spr_Rocky_Stand_Up,
    e_Anim_Jump, (u64)-2
};    

u64 gAnim_Rocky_Idle_Right[]={
    e_AnimKey_MstIdle,
    65000, e_Spr_Rocky_Stand_Right,
    e_Anim_Jump, (u64)-2
};    

// Walk :
u64 gAnim_Rocky_Walk_Down[]={
    e_AnimKey_Null,
    6, e_Spr_Rocky_Walk_Down,
    6, e_Spr_Rocky_Stand_Down,
    6, e_Spr_Rocky_Walk_Down+1,
    6, e_Spr_Rocky_Stand_Down,
    e_Anim_Goto, (u64)gAnim_Rocky_Walk_Down
};    

u64 gAnim_Rocky_Walk_Left[]={
    e_AnimKey_Null,
    6, e_Spr_Rocky_Walk_Left,
    6, e_Spr_Rocky_Stand_Left,
    6, e_Spr_Rocky_Walk_Left+1,
    6, e_Spr_Rocky_Stand_Left,
    e_Anim_Goto, (u64)gAnim_Rocky_Walk_Left
};    

u64 gAnim_Rocky_Walk_Up[]={
    e_AnimKey_Null,
    6, e_Spr_Rocky_Walk_Up,
    6, e_Spr_Rocky_Stand_Up,
    6, e_Spr_Rocky_Walk_Up+1,
    6, e_Spr_Rocky_Stand_Up,
    e_Anim_Goto, (u64)gAnim_Rocky_Walk_Up
};    

u64 gAnim_Rocky_Walk_Right[]={
    e_AnimKey_Null,
    6, e_Spr_Rocky_Walk_Right,
    6, e_Spr_Rocky_Stand_Right,
    6, e_Spr_Rocky_Walk_Right+1,
    6, e_Spr_Rocky_Stand_Right,
    e_Anim_Goto, (u64)gAnim_Rocky_Walk_Right
};    

/*************** Skull : ***************/
// Idle :
u64 gAnim_Skull_Idle_Down[]={
    e_AnimKey_MstIdle,
    65000, e_Spr_Skull_Stand_Down,
    e_Anim_Jump, (u64)-2
};    

u64 gAnim_Skull_Idle_Left[]={
    e_AnimKey_MstIdle,
    65000, e_Spr_Skull_Stand_Left,
    e_Anim_Jump, (u64)-2
};    

u64 gAnim_Skull_Idle_Up[]={
    e_AnimKey_MstIdle,
    65000, e_Spr_Skull_Stand_Up,
    e_Anim_Jump, (u64)-2
};    

u64 gAnim_Skull_Idle_Right[]={
    e_AnimKey_MstIdle,
    65000, e_Spr_Skull_Stand_Right,
    e_Anim_Jump, (u64)-2
};   

// Move
u64 gAnim_Skull_Move_Down[]={
    e_AnimKey_Null,
    6, e_Spr_Skull_Move_Down,
    6, e_Spr_Skull_Stand_Down,
    6, e_Spr_Skull_Move_Down+1,
    6, e_Spr_Skull_Stand_Down,
    e_Anim_Goto, (u64)gAnim_Skull_Move_Down
};

u64 gAnim_Skull_Move_Left[]={
    e_AnimKey_Null,
    6, e_Spr_Skull_Move_Left,
    6, e_Spr_Skull_Stand_Left,
    6, e_Spr_Skull_Move_Left+1,
    6, e_Spr_Skull_Stand_Left,
    e_Anim_Goto, (u64)gAnim_Skull_Move_Left
};

u64 gAnim_Skull_Move_Up[]={
    e_AnimKey_Null,
    6, e_Spr_Skull_Move_Up,
    6, e_Spr_Skull_Stand_Up,
    6, e_Spr_Skull_Move_Up+1,
    6, e_Spr_Skull_Stand_Up,
    e_Anim_Goto, (u64)gAnim_Skull_Move_Up
};

u64 gAnim_Skull_Move_Right[]={
    e_AnimKey_Null,
    6, e_Spr_Skull_Move_Right,
    6, e_Spr_Skull_Stand_Right,
    6, e_Spr_Skull_Move_Right+1,
    6, e_Spr_Skull_Stand_Right,
    e_Anim_Goto, (u64)gAnim_Skull_Move_Right
};    


/*************** Gol : ***************/
// Shot
u64 gAnim_Gol_Shot_Down[]={
    e_AnimKey_Null,
    6, e_Spr_Gol_Shot_Down,    
    6, e_Spr_Gol_Shot_Down+1,    
    6, e_Spr_Gol_Shot_Down+2,    
    e_Anim_Goto, (u64)gAnim_Gol_Shot_Down
};

u64 gAnim_Gol_Shot_Right[]={
    e_AnimKey_Null,
    6, e_Spr_Gol_Shot_Right,
    6, e_Spr_Gol_Shot_Right+1,
    e_Anim_Goto, (u64)gAnim_Gol_Shot_Right
};

u64 gAnim_Gol_Shot_Up[]={
    e_AnimKey_Null,
    6, e_Spr_Gol_Shot_Up,
    6, e_Spr_Gol_Shot_Up+1,
    6, e_Spr_Gol_Shot_Up+2,
    e_Anim_Goto, (u64)gAnim_Gol_Shot_Up
};

u64 gAnim_Gol_Shot_Left[]={
    e_AnimKey_Null,
    6, e_Spr_Gol_Shot_Left,
    6, e_Spr_Gol_Shot_Left+1,
    e_Anim_Goto, (u64)gAnim_Gol_Shot_Left
};

// Shot collide :
u64 gAnim_Gol_ShotCollide_Down[]={
    e_AnimKey_Null,
    6, e_Spr_Gol_ShotCollide_Down,    
    6, e_Spr_Gol_ShotCollide_Down+1,    
    e_Anim_End    
};

u64 gAnim_Gol_ShotCollide_Right[]={
    e_AnimKey_Null,
    6, e_Spr_Gol_ShotCollide_Right,    
    6, e_Spr_Gol_ShotCollide_Right+1,    
    e_Anim_End    
};

u64 gAnim_Gol_ShotCollide_Up[]={
    e_AnimKey_Null,
    6, e_Spr_Gol_ShotCollide_Up,    
    6, e_Spr_Gol_ShotCollide_Up+1,    
    e_Anim_End    
};

u64 gAnim_Gol_ShotCollide_Left[]={
    e_AnimKey_Null,
    6, e_Spr_Gol_ShotCollide_Left,    
    6, e_Spr_Gol_ShotCollide_Left+1,    
    e_Anim_End    
};   

/*************** DonMedusa : ***************/
// Used for top, bottom, left and right.

// Idle :
u64 gAnim_DonMedusa_Idle_Down[]={
    e_AnimKey_MstIdle,
    65000, e_Spr_DonMedusa_Stand,
    e_Anim_Jump, (u64)-2
};    

u64 gAnim_DonMedusa_Move[]={
    e_AnimKey_Null,
    6, e_Spr_DonMedusa_Stand,
    6, e_Spr_DonMedusa_Move,
    e_Anim_Goto, (u64)gAnim_DonMedusa_Move
};

/*************** Divers : ***************/
// Egg
u64 gAnim_Egg_DisappearInWater[]={
    e_AnimKey_Null,
    6, e_Spr_Egg_Stand,
    6, e_Spr_Egg_Crack,
    6, e_Spr_Egg_Reduced,
    6, e_Spr_Egg_Reduced+1,
    e_Anim_End
};    

// Disappearance Monster in smoke
u64 gAnim_DisappearanceMonsterInSmoke[]={
    e_AnimKey_Null,
    6, e_Spr_DisappearanceMonsterInSmoke,
    6, e_Spr_DisappearanceMonsterInSmoke+1,
    6, e_Spr_DisappearanceMonsterInSmoke+2,
    6, e_Spr_DisappearanceMonsterInSmoke+3,
    e_Anim_End
};    

// DECORE :
u64 gAnim_Heart_Flashing[]={
    e_AnimKey_Null,
    6, e_Spr_Heart,
    6, e_Spr_Heart+1,
    e_Anim_Goto, (u64)gAnim_Heart_Flashing
};

u64 gAnim_Hammer_Flashing[]={
    e_AnimKey_Null,
    6, e_Spr_Hammer,
    6, e_Spr_Hammer+1,
    e_Anim_Goto, (u64)gAnim_Hammer_Flashing
};

u64 gAnim_Arrow_Flashing[]={
    e_AnimKey_Null,
    6, e_Spr_Arrow_Changer+4,
    6, e_Spr_Arrow_Changer+5,
    e_Anim_Goto, (u64)gAnim_Arrow_Flashing
};

u64 gAnim_Footbridge_Flashing[]={
    e_AnimKey_Null,
    6, e_Spr_Footbridge+2,
    6, e_Spr_Footbridge+3,
    e_Anim_Goto, (u64)gAnim_Footbridge_Flashing
};   

u64 gAnim_Water[]={
    e_AnimKey_Null,
    6, e_Spr_Water,
    6, e_Spr_Water+1,
    6, e_Spr_Water+2,
    6, e_Spr_Water+3,
    6, e_Spr_Water+4,
    6, e_Spr_Water+5,
    e_Anim_Goto, (u64)gAnim_Water
};

u64 gAnim_WaterShade[]={
    e_AnimKey_Null,
    6, e_Spr_Water_Shade,
    6, e_Spr_Water_Shade+1,
    6, e_Spr_Water_Shade+2,
    6, e_Spr_Water_Shade+3,
    6, e_Spr_Water_Shade+4,
    6, e_Spr_Water_Shade+5,
    e_Anim_Goto, (u64)gAnim_WaterShade
};   


u64 gAnim_LavaShade[]={
    e_AnimKey_Null,
    6, e_Spr_Lava_Shade,
    6, e_Spr_Lava_Shade+1,
    6, e_Spr_Lava_Shade+2,
    6, e_Spr_Lava_Shade+3,
    6, e_Spr_Lava_Shade+4,
    6, e_Spr_Lava_Shade+5,
    e_Anim_Goto, (u64)gAnim_LavaShade
};   

u64 gAnim_Lava[]={
    e_AnimKey_Null,
    6, e_Spr_Lava,
    6, e_Spr_Lava+1,
    6, e_Spr_Lava+2,
    6, e_Spr_Lava+3,
    6, e_Spr_Lava+4,
    6, e_Spr_Lava+5,
    e_Anim_Goto, (u64)gAnim_Lava
};
