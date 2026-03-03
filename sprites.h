
// Index des couleurs de la palette.
#define COLOR_BLACK_IDX 128
#define COLOR_WHITE_IDX 254
#define COLOR_BLUE_IDX 255
#define COLOR_PINK_IDX 0
// Index ou commence les couleurs pour les sprites et les background dans la palette.
// Note : normalement pour chaque sprite sheet (sauf bkg) on devrait avoir dans la palette uniquement les couleurs lié à celle-ci, mais pour une question de 
// facilité, j'ai mis toutes les couleurs des sprites sheet ensemble dans toutes les palettes. I.e que la palette de la sprites sheet décor à aussi les couleurs
// de la sprite sheet lolo, font, monster idem pour celle susmentionné, au lieu d'avoir uniquement ses couleurs qui ensuite sont misent ensembles lors de la
// récupération de la sprite sheet.
#define PALETTE_IDX_SPR 128 
#define PALETTE_IDX_BKG 0
#define SPR_MAX 2048 // Nombre de sprites pouvant être récupérés dans les sprites sheets.
#define SPR_STOCK_MAX 512 // Nombre de sprites stockés pour l'affichage.

// Taille d'un sprite x et y identique.
#define SPR_SIZE 16

enum EPrio{
    e_Prio_Decor=10,
    e_Prio_Items=20,
    e_Prio_Monsters=30,
    e_Prio_Plyr=40,
};

// Struct caractérisant un sprites.
typedef struct SSprite{
    int w,h;
    int PtRefX, PtRefY;
    u8 *pGfx;
    u8 *pMask;
    
}SSprite;

// Struct stockant les sprites à afficher.
typedef struct SStockSpr{
    int nNoSpr;
    int nPosX, nPosY;
    int nPrio;
}SStockSpr;


#define SPR_NOSPRITE ((u64)-2)

// Fonction de callback pour le tri des sprites pour la prio.
int Sprites_ComparQSort(const void *pElem1, const void *pElem2);
// Collision entre sprites, bord de l'écran.
bool Sprites_CollideSprs(u32 noSpr1, u32 noSpr2);
// Affiche les index de la palette.
void Sprites_DisplayIdxPalette(SDL_Color *color);
void Sprites_BlitBkgGrid(void);
// On blit tout les sprites dans le buffer écran.
// Attention si on démarre avec le mode 2x, pScreenBuf2 sera mis dans pScreen.
void Sprites_BlitAll(void);
// On stock tous les sprites à blitter dans le tableau de struct SStockSpr.
// Cette fc permet de stocker 1 seul sprite. Pas de recherche de slots libre mis les uns à la suite des autres puis
// utilisation des prio et utilisation du qsort. Correspond à SprDisplay chez Clément Corde.
void Sprites_Stock(s32 noSpr, s32 x, s32 y, s32 prio);
// Extraction des backgrounds.
void Sprites_ExtractBkgs(char *pFilenames[]);
// Descripteur de sprite.
SSprite *Sprites_GetDesc(int noSpr);
// Libération de la mémoire alloué pour les sprites.
void Sprites_Release(void);
// Affichage du masque du sprite avec les index  de la palette.
void Sprites_DisplayMaskSpr(void);
// Affichage des données du sprite récupéré.
void Sprites_DisplayData(void);
// Affichage du sprite avec les index de la palette.
void Sprites_DisplaySpr(void);
void Sprites_FreeAllBMPs(SDL_Surface *pBMP, int size);
// Sauvegarde de la palette (sprites et backgrounds) et place la palette avec SDL_SetPalette.
// Note : quand on place la palette, on doit dabord la placer dans la palette logique puis dans la palette physque, c'est la SDL 
// qui fera la correspondance entre la palette logique et physique. Il semble que ceci soit obligatoire.
void Sprites_SetPalette(SDL_Surface *pPlanche, int paletteIdx);
void Sprites_Init(void);
// Extraction des sprites de la sprites sheet.
void Sprites_ExtractSprSheet(char *pFilename);
SDL_Surface *Sprites_LoadBMP(char *pFilename); 

// Nom des sprites et numérotation des sprites.
// Numéro des index des sprites pour le tableau de sprites.
enum{
    // Note manque le scintillement pour la bloque emeraude
    // DECOR :
    e_Spr_Ground=0, // Spr N° 0 Ground with shadow, 1 without shadow.
    e_Spr_Stone=e_Spr_Ground+2, // Spr N° 2 Stone with shadow, 3 without shadow.
    e_Spr_Tree=e_Spr_Stone+2, // Spr N° 4 Tree with shadow, 5 without shadow.

    // OBJETS (Jewel Chest, Heart, Emerald, egg) :
    e_Spr_Emerald_Block=e_Spr_Tree+2, 
    e_Spr_Heart=e_Spr_Emerald_Block+1, // Spr N° 7 Heart color pink.
    e_Spr_Chest_Lock=e_Spr_Heart+2, // Spr N° 9 Chest lock.
    e_Spr_Chest_OpenWithGem=e_Spr_Chest_Lock+1,
    e_Spr_Chest_OpenNoGem=e_Spr_Chest_OpenWithGem+1,

    // ITEMS (Bridge, Hammer, Arrow Changer) :
    e_Spr_Hammer=e_Spr_Chest_OpenNoGem+1,
    e_Spr_Plaques=e_Spr_Hammer+2,
    e_Spr_Arrow_Changer=e_Spr_Plaques+2,
 
    e_Spr_Footbridge=e_Spr_Arrow_Changer+6,
    e_Spr_Footbridge_Stone=e_Spr_Footbridge+4,
    
    e_Spr_Door=e_Spr_Footbridge_Stone+4, // Spr N° 30 Door close, 31 Door open, 32 Door open Stairs Go Up, 33 Door open Stairs Go Down.

    // WALL
    e_Spr_Wall_Corner_TopView=e_Spr_Door+4, // Spr N° 34 Top-Left, 35 Top-Right, 36 Bottom-Left, 37 Bottom-Right.
    e_Spr_Wall_TopView=e_Spr_Wall_Corner_TopView+4, // Spr N° 38 Left, 39 Right, 40 Top and Bottom.
    e_Spr_Wall=e_Spr_Wall_TopView+3, // Spr N° 41 Angle Left, 42 Wall whithout Angle
    
    // Ground miscellanous
    // Sand
    e_Spr_Sand_End=e_Spr_Wall+2, 
    e_Spr_Sand_Tubes=e_Spr_Sand_End+4,  
    e_Spr_Sand_Square=e_Spr_Sand_Tubes+2, 
    e_Spr_Sand0_Shade_End=e_Spr_Sand_Square+1,         
    e_Spr_Sand0_Shade_Tubes=e_Spr_Sand0_Shade_End+2,   
    e_Spr_Sand1_Shade_End=e_Spr_Sand0_Shade_Tubes+1,   
    e_Spr_Sand1_Shade_Tube=e_Spr_Sand1_Shade_End+2,    
    e_Spr_Sand2_Shade_End=e_Spr_Sand1_Shade_Tube+1,    
    e_Spr_Sand_Diamond=e_Spr_Sand2_Shade_End+2,
    e_Spr_Sand_Diamond_Shade=e_Spr_Sand_Diamond+4,
    e_Spr_Sand_BigSquare=e_Spr_Sand_Diamond_Shade+4,
    
    // Grass
    e_Spr_Grass_End=e_Spr_Sand_BigSquare+9,       
    e_Spr_Grass_Tubes=e_Spr_Grass_End+4,      
    e_Spr_Grass_Square=e_Spr_Grass_Tubes+2,      
    
    e_Spr_Grass0_Shade_End=e_Spr_Grass_Square+1,      
    e_Spr_Grass0_Shade_Tubes=e_Spr_Grass0_Shade_End+2,      
    e_Spr_Grass1_Shade_End=e_Spr_Grass0_Shade_Tubes+1, 
    e_Spr_Grass1_Shade_Tube=e_Spr_Grass1_Shade_End+2,
    e_Spr_Grass2_Shade_End=e_Spr_Grass1_Shade_Tube+1,
    e_Spr_Grass_BigSquare=e_Spr_Grass2_Shade_End+2,

    // Water
    e_Spr_Water_Shade=e_Spr_Grass_BigSquare+9,
    e_Spr_Water=e_Spr_Water_Shade+6,
    
    e_Spr_Lava_Shade=e_Spr_Water+6,
    e_Spr_Lava=e_Spr_Lava_Shade+9,

    // MONSTERS :
// Snakey :
    e_Spr_Snakey_Stand_Left=e_Spr_Lava+9,
    e_Spr_Snakey_Rotate_Left=e_Spr_Snakey_Stand_Left+1,
    e_Spr_Snakey_Stand_Right=e_Spr_Snakey_Rotate_Left+1,
    e_Spr_Snakey_Rotate_Right=e_Spr_Snakey_Stand_Right+1,

// Alma :
    e_Spr_Alma_Down_Stand=e_Spr_Snakey_Rotate_Right+1,
    e_Spr_Alma_Walk_Down=e_Spr_Alma_Down_Stand+1,
    e_Spr_Alma_Left_Stand=e_Spr_Alma_Walk_Down+2,
    e_Spr_Alma_Walk_Left=e_Spr_Alma_Left_Stand+1,
    e_Spr_Alma_Up_Stand=e_Spr_Alma_Walk_Left+2,
    e_Spr_Alma_Walk_Up=e_Spr_Alma_Up_Stand+1,
    e_Spr_Alma_Right_Stand=e_Spr_Alma_Walk_Up+2,
    e_Spr_Alma_Walk_Right=e_Spr_Alma_Right_Stand+1,
    
    e_Spr_Alma_Roll_Left_Stand=e_Spr_Alma_Walk_Right+2,
    e_Spr_Alma_Roll_Left=e_Spr_Alma_Roll_Left_Stand+1,
    e_Spr_Alma_Roll_Right_Stand=e_Spr_Alma_Roll_Left+2,
    e_Spr_Alma_Roll_Right=e_Spr_Alma_Roll_Right_Stand+1,

// Leeper (sur word référence c'est leaper):    
    e_Spr_Leeper_Down_Stand=e_Spr_Alma_Roll_Right+2,
    e_Spr_Leeper_Jumping_Down=e_Spr_Leeper_Down_Stand+1,
    e_Spr_Leeper_Left_Stand=e_Spr_Leeper_Jumping_Down+1,
    e_Spr_Leeper_Jumping_Left=e_Spr_Leeper_Left_Stand+1,
    e_Spr_Leeper_Up_Stand=e_Spr_Leeper_Jumping_Left+1,
    e_Spr_Leeper_Jumping_Up=e_Spr_Leeper_Up_Stand+1,
    e_Spr_Leeper_Right_Stand=e_Spr_Leeper_Jumping_Up+1,
    e_Spr_Leeper_Jumping_Right=e_Spr_Leeper_Right_Stand+1,
    e_Spr_Leeper_Sleeping_Down=e_Spr_Leeper_Jumping_Right+1,
    e_Spr_Leeper_Sleeping_Left=e_Spr_Leeper_Sleeping_Down+2,
    e_Spr_Leeper_Sleeping_Up=e_Spr_Leeper_Sleeping_Left+2,
    e_Spr_Leeper_Sleeping_Right=e_Spr_Leeper_Sleeping_Up+2,
    
// Rocky :
    e_Spr_Rocky_Stand_Down=e_Spr_Leeper_Sleeping_Right+2,
    e_Spr_Rocky_Walk_Down=e_Spr_Rocky_Stand_Down+1,
    e_Spr_Rocky_Stand_Left=e_Spr_Rocky_Walk_Down+2,
    e_Spr_Rocky_Walk_Left=e_Spr_Rocky_Stand_Left+1,
    e_Spr_Rocky_Stand_Up=e_Spr_Rocky_Walk_Left+2,
    e_Spr_Rocky_Walk_Up=e_Spr_Rocky_Stand_Up+1,
    e_Spr_Rocky_Stand_Right=e_Spr_Rocky_Walk_Up+2,
    e_Spr_Rocky_Walk_Right=e_Spr_Rocky_Stand_Right+1,

// Skull :
    e_Spr_Skull_Stand_Down=e_Spr_Rocky_Walk_Right+2,
    e_Spr_Skull_Move_Down=e_Spr_Skull_Stand_Down+1,
    e_Spr_Skull_Stand_Left=e_Spr_Skull_Move_Down+2,
    e_Spr_Skull_Move_Left=e_Spr_Skull_Stand_Left+1,
    e_Spr_Skull_Stand_Up=e_Spr_Skull_Move_Left+1,
    e_Spr_Skull_Move_Up=e_Spr_Skull_Stand_Up+1,
    e_Spr_Skull_Stand_Right=e_Spr_Skull_Move_Up+1,
    e_Spr_Skull_Move_Right=e_Spr_Skull_Stand_Right+1,

// Gol :
    e_Spr_Gol_Sleeping_Down=e_Spr_Skull_Move_Right+1,
    e_Spr_Gol_Sleeping_Left=e_Spr_Gol_Sleeping_Down+1,
    e_Spr_Gol_Sleeping_Up=e_Spr_Gol_Sleeping_Left+1,
    e_Spr_Gol_Sleeping_Right=e_Spr_Gol_Sleeping_Up+1,
    e_Spr_Gol_Wake_Down=e_Spr_Gol_Sleeping_Right+1,
    e_Spr_Gol_Wake_Left=e_Spr_Gol_Wake_Down+1,
    e_Spr_Gol_Wake_Up=e_Spr_Gol_Wake_Left+1,
    e_Spr_Gol_Wake_Right=e_Spr_Gol_Wake_Up+1,
    
    e_Spr_Gol_Shot_Down=e_Spr_Gol_Wake_Right+1,
    e_Spr_Gol_ShotCollide_Down=e_Spr_Gol_Shot_Down+3,
    e_Spr_Gol_Shot_Right=e_Spr_Gol_ShotCollide_Down+2,
    e_Spr_Gol_ShotCollide_Right=e_Spr_Gol_Shot_Right+2,
    e_Spr_Gol_Shot_Up=e_Spr_Gol_ShotCollide_Right+2,
    e_Spr_Gol_ShotCollide_Up=e_Spr_Gol_Shot_Up+3,
    e_Spr_Gol_Shot_Left=e_Spr_Gol_ShotCollide_Up+2,
    e_Spr_Gol_ShotCollide_Left=e_Spr_Gol_Shot_Left+2,

// DonMedusa :    
    e_Spr_DonMedusa_Stand=e_Spr_Gol_ShotCollide_Left+2,
    e_Spr_DonMedusa_Move=e_Spr_DonMedusa_Stand+1,
    e_Spr_DonMedusa_Sword=e_Spr_DonMedusa_Move+1,
   
    e_Spr_Medusa_Stand=e_Spr_DonMedusa_Sword+4,
    e_Spr_Medusa_Attack=e_Spr_Medusa_Stand+1,
    e_Spr_Medusa_Arrows=e_Spr_Medusa_Attack+1,

// Whale :
    e_Spr_Whale_Stand_Down=e_Spr_Medusa_Arrows+4,
    e_Spr_Whale_Stand_Left=e_Spr_Whale_Stand_Down+1,
    e_Spr_Whale_Stand_Up=e_Spr_Whale_Stand_Left+1,
    e_Spr_Whale_Stand_Right=e_Spr_Whale_Stand_Up+1,

    e_Spr_Whale_Suck_Down=e_Spr_Whale_Stand_Right+1,
    e_Spr_Whale_Suck_Left=e_Spr_Whale_Suck_Down+1,
    e_Spr_Whale_Suck_Up=e_Spr_Whale_Suck_Left+1,
    e_Spr_Whale_Suck_Right=e_Spr_Whale_Suck_Up+1,

// Miscellaneous :    
    e_Spr_Egg_Stand=e_Spr_Whale_Suck_Right+1,
    e_Spr_Egg_Crack=e_Spr_Egg_Stand+1,
    e_Spr_Egg_Reduced=e_Spr_Egg_Crack+1,
    e_Spr_Square=e_Spr_Egg_Reduced+2,
    e_Spr_Player_Shoot_Up=e_Spr_Square+1,
    e_Spr_Player_Shoot_Left=e_Spr_Player_Shoot_Up+1,
    e_Spr_Player_Shoot_Down=e_Spr_Player_Shoot_Left+1,
    e_Spr_Player_Shoot_Right=e_Spr_Player_Shoot_Down+1,

    e_Spr_DisappearanceMonsterInSmoke=e_Spr_Player_Shoot_Right+1,
    e_Spr_Circle_Reappearance=e_Spr_DisappearanceMonsterInSmoke+4,

    // PLAYER :
    e_Spr_Lolo_Down_Stand=e_Spr_Circle_Reappearance+1,
    e_Spr_Lolo_Walk_Down=e_Spr_Lolo_Down_Stand+1,
    e_Spr_Lolo_Left_Stand=e_Spr_Lolo_Walk_Down+4,
    e_Spr_Lolo_Walk_Left=e_Spr_Lolo_Left_Stand+1,
    e_Spr_Lolo_Up_Stand=e_Spr_Lolo_Walk_Left+4,
    e_Spr_Lolo_Walk_Up=e_Spr_Lolo_Up_Stand+1,
    e_Spr_Lolo_Right_Stand=e_Spr_Lolo_Walk_Up+4,
    e_Spr_Lolo_Walk_Right=e_Spr_Lolo_Right_Stand+1,

    e_Spr_Lolo_Sleep_Down=e_Spr_Lolo_Walk_Right+4,
    e_Spr_Lolo_Sleep_Left=e_Spr_Lolo_Sleep_Down+2,
    e_Spr_Lolo_Sleep_Up=e_Spr_Lolo_Sleep_Left+2,
    e_Spr_Lolo_Sleep_Right=e_Spr_Lolo_Sleep_Up+2,

    e_Spr_Lolo_Win=e_Spr_Lolo_Sleep_Right+2,
    e_Spr_Lolo_DeadByArrow=e_Spr_Lolo_Win+4,
    e_Spr_Lolo_DeadByBurnt=e_Spr_Lolo_DeadByArrow+1,
    e_Spr_Lolo_DeadFinal=e_Spr_Lolo_DeadByBurnt+1,
    
    // FONT :
    e_Spr_Font=e_Spr_Lolo_DeadFinal+4,
    e_Spr_Next = e_Spr_Font + 64,
};







