
#define BIT31 1 << 31 // BIT32 permet de savoir dans getImg si on est sur le nb de frames ou bien si on est à la fin de l'anim, évite d'avoir à testé le switch 
// à chaque passage dans getImg et aussi évite les conflits entre la valeur des frames et les e_Anim_). Autre façon de faire, mettre une valeur pour e_Anim_ qui
// est différente de toutes les valeurs qui existe dans tout les tableaux d'anim.

// Fin de l'anim (ce que l'on doit faire).
enum{
    e_Anim_Jump= BIT31  | 1, // Saute au sprite précédent. En général c'est tjrs le dernier sprites sur lequel on jump.
    // Repart à la 1er case du tableau d'anim ou à une autre anim.
    e_Anim_Goto= BIT31  | 2, 
    // Pour tout les sprites important (mort du joueur, un monstre qui est tué mais qui devra réaparaître par la suite, etc) on n'enlève pas du tableau de slots 
    // d'anim (moteur du jeu). 
    e_Anim_End=  BIT31  | 3, 
    e_Anim_Kill= BIT31  | 4, // Tous ce qui n'est pas important et qui est donc sucesptible de revenir (tire, explosion, ...).
    e_Anim_Sfx=  BIT31  | 5, // Pour jouer un son avec l'anim.
};


// Clé d'anim. Début de l'anim (que fait l'anim, marche, immobile, meurt, vainqueur).
enum{
    e_AnimKey_Null,
    e_AnimKey_PlyrIdle, // Joueur inactif (idle).
    e_AnimKey_PlyrWalk,
    e_AnimKey_PlyrDeath,
    e_AnimKey_PlyrWin,
    
    e_AnimKey_MstIdle,
    e_AnimKey_MstWalk,
    e_AnimKey_MstDeath,
    e_AnimKey_MstWin,
};

// PLAYER :

/*************** Player : ***************/
// Idle
extern u64 gAnim_Plyr_Idle_Down[]; // Joueur inactif regarde en bas.
extern u64 gAnim_Plyr_Idle_Left[]; 
extern u64 gAnim_Plyr_Idle_Up[]; 
extern u64 gAnim_Plyr_Idle_Right[]; 
// Walk
extern u64 gAnim_Plyr_Walk_Down[]; // Joueur marche vers le bas.
extern u64 gAnim_Plyr_Walk_Left[]; 
extern u64 gAnim_Plyr_Walk_Up[]; 
extern u64 gAnim_Plyr_Walk_Right[];
// Sleeping
extern u64 gAnim_Plyr_Sleeping_Down[];
extern u64 gAnim_Plyr_Sleeping_Left[];
extern u64 gAnim_Plyr_Sleeping_Up[]; // Utiliser sprite stand up en 1er.
extern u64 gAnim_Plyr_Sleeping_Right[];
// Win
extern u64 gAnim_Plyr_Win[]; // Utiliser sprite stand down en 1er.
// Death
// Note : fusionner les 3 en mettant peut-ê un || binaire pour les 2 sprite arrow et burnt.
extern u64 gAnim_Plyr_DeathArrow[]; // Le 1er sprite est celui quand le joueur est touché, le 2e sprite est l'anim de la mort.
extern u64 gAnim_Plyr_DeathBurnt[]; // Idem.
extern u64 gAnim_Plyr_Death[]; // Animation player quand il meurt.

// MONSTERS :

/*************** Snakey : ***************/
extern u64 gAnim_Snakey_WinPlyr[];

/*************** Alma : ***************/
extern u64 gAnim_Alma_Idle_Down[];
extern u64 gAnim_Alma_Idle_Left[];
extern u64 gAnim_Alma_Idle_Up[];
extern u64 gAnim_Alma_Idle_Right[];
// Walk
extern u64 gAnim_Alma_Walk_Down[];
extern u64 gAnim_Alma_Walk_Left[];
extern u64 gAnim_Alma_Walk_Up[];
extern u64 gAnim_Alma_Walk_Right[];
// Roll
extern u64 gAnim_Alma_Roll_Left[];
extern u64 gAnim_Alma_Roll_Right[];

/*************** Leaper : ***************/
// Idle
extern u64 gAnim_Leeper_Idle_Down[];
extern u64 gAnim_Leeper_Idle_Left[];
extern u64 gAnim_Leeper_Idle_Up[];
extern u64 gAnim_Leeper_Idle_Right[];
// Jumping
extern u64 gAnim_Leeper_Jumping_Down[];
extern u64 gAnim_Leeper_Jumping_Left[];
extern u64 gAnim_Leeper_Jumping_Up[];
extern u64 gAnim_Leeper_Jumping_Right[];
// Sleeping
extern u64 gAnim_Leeper_Sleeping_Down[];
extern u64 gAnim_Leeper_Sleeping_Left[];
extern u64 gAnim_Leeper_Sleeping_Up[];
extern u64 gAnim_Leeper_Sleeping_Right[];

/*************** Rocky : ***************/
// Idle :
extern u64 gAnim_Rocky_Idle_Down[];
extern u64 gAnim_Rocky_Idle_Left[];
extern u64 gAnim_Rocky_Idle_Up[];
extern u64 gAnim_Rocky_Idle_Right[];
// Walk :
extern u64 gAnim_Rocky_Walk_Down[];
extern u64 gAnim_Rocky_Walk_Left[];
extern u64 gAnim_Rocky_Walk_Up[];
extern u64 gAnim_Rocky_Walk_Right[];

/*************** Skull : ***************/
//Idle
extern u64 gAnim_Skull_Idle_Down[];
extern u64 gAnim_Skull_Idle_Left[];
extern u64 gAnim_Skull_Idle_Up[];
extern u64 gAnim_Skull_Idle_Right[];
// Move 
extern u64 gAnim_Skull_Move_Down[];
extern u64 gAnim_Skull_Move_Left[];
extern u64 gAnim_Skull_Move_Up[];
extern u64 gAnim_Skull_Move_Right[];

/*************** Gol : ***************/
// Shot
extern u64 gAnim_Gol_Shot_Down[];
extern u64 gAnim_Gol_Shot_Right[];
extern u64 gAnim_Gol_Shot_Up[];
extern u64 gAnim_Gol_Shot_Left[];
// Shot collide
extern u64 gAnim_Gol_ShotCollide_Down[];
extern u64 gAnim_Gol_ShotCollide_Right[];
extern u64 gAnim_Gol_ShotCollide_Up[];
extern u64 gAnim_Gol_ShotCollide_Left[];

/*************** DonMedusa : ***************/
extern u64 gAnim_DonMedusa_Idle_Down[];
extern u64 gAnim_DonMedusa_Move[]; // For top to bottom and left of right.

/*************** Egg : ***************/
extern u64 gAnim_Egg_DisappearInWater[];

/*************** Disapearance Monster : ***************/
extern u64 gAnim_DisappearanceMonsterInSmoke[];

/*************** ITEMS : ***************/
extern u64 gAnim_Heart_Flashing[];
extern u64 gAnim_Hammer_Flashing[];
extern u64 gAnim_Arrow_Flashing[];
extern u64 gAnim_Footbridge_Flashing[];

/*************** DECORES : ***************/
extern u64 gAnim_Water[];
extern u64 gAnim_WaterShade[];
extern u64 gAnim_LavaShade[];
extern u64 gAnim_Lava[];



