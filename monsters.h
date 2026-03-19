


#define MST_MAX_SLOTS 64 // 64 monstres max à l'écran.

#define MST_SPEED_INIT 0x080 // Vitesse testé avec le jeu d'origine (lolo 1) donc ok 0x80
#define MST_SPEED_MAX 0x200  // 0x100

// Monsters :

/**** MONSTRE ****/
// Référence le nombre de monstre et leurs propriétés, positions pour un level.
typedef struct SMstLvl{
    s32 nNoSpr; // N° du sprite.
    u64 *pAnm; // Adresse du tableau d'anim (représenté par le nom du tableau d'anim (voir anim.h)). NULL si pas d'anim.
    u32 nDir; // Direction du monstre au départ du level.
    u32 nColumns, nLines; // Position du monstre en nombre de lignes et de colonnes.
    u32 nProperty; // Propriété du monstre : inoffensif, dangereux.
    s32 nSpeed; // Vitesse des monstre.
    u32 nName; // Nom du monstre.
}SMstLvl;

// (n° de sprite, nom de l'anim (si pas d'anim NULL) on cast car la paramètre formel est en u64, direction, position en case, si inoffensif ou dangereux) : 
extern SMstLvl gMstLvl1[];

// Référence tous les levels pour les monstres.
typedef struct SMstsLvls{
    SMstLvl *pMstsLvl;
    u32 nNbMsts;
}SMstsLvls;

extern SMstsLvls gMstsLvls[];

// Noms des monstres.
enum EMstName{
    // En mouvement :
    e_Mst_Alma,
    e_Mst_Leeper, // Si collision devient static.
    e_Mst_Rocky,
    e_Mst_Skull, // Static tant que le joueur n'a pas récupéré tout les coffres.
    e_Mst_DonMedusa,    
    // Static :
    e_Mst_Medusa,
    e_Mst_Snakey,
    e_Mst_Gol,
    e_Mst_Whale,
};

// Propriété des monstres.
enum EMstProperties{
    e_Mst_Harmless, // Inoffensif.
    e_Mst_Dangerous,
};

enum EMstState{
    e_MstAnim_Idle,
    e_MstAnim_Walk, // ou Jumping
    e_MstAnim_Sleeping,
    e_MstAnim_Win,
    e_MstAnim_Death,
    e_MstAnim_Max,
};

// Je crée un tableau fixe de struct de monstres, qui sera rempli plus ou moins en fonction du nombre de monstres à l'écran.
typedef struct SMonster{

u32 nUsed; // Slot utilisé ou pas.
u32 nNoSpr; // N° du sprite.
u32 nAnimNoSlot; // N° du slot de l'anim.
u32 nDir; // Direction.
s32 nSpeed; // Vitesse du monstre.
s32 nPosX, nPosY; // Position en pixels.
s32 nLastPosX, nLastPosY;
u32 nState; // Etat du monstre (move, idle, ...).
u64 *pAnim; // Pointeur pour le tableau d'anim.
u32 nFlag; // Averti d'un événement qui à lieu sur le monstre (mort, ...).
u32 nProperty; // Propriété du monstre, est-il dangereux, inoffensif ?
u32 nName; // Nom du monstre.
bool bCollidePlyr; // Collision avec le player. Pour éviter le recallage si collision, on le fait dans Monsters_MonstersMove.

}SMonster;

// Note : gMst peut-ê remplacé par gpMstSlots
extern SMonster gMst[MST_MAX_SLOTS];
// Recalage du plyer après collision avec le Monster
void Monster_CollideAdjusting(u32 nPX, u32 nMX, SMonster *pMst);
// Test si le monstre peut se déplacer dans la direction demandée. Utilisé pour les murs, décore (arbres, pierre, ...), items (coeurs, blocs, eggs, ...)
// Out : true = déplacement ok, false = ne doit pas gouger.
bool Monster_CheckDepl(SMonster *pMst, u32 nDir, bool bIsCollide);
// Recalage Mst
void Game_MstRecalage(SMonster* pMst);
// Test si le monstre à une anim. Retourne dans tous les cas un n° de sprites.
// Utilisation de Animspr_GetImgLast dans la fonction.
u32 Monsters_IfHasAnAnim(u32 nIdx);
// Si le perso est tué => on fait une init de fin, les monstres sont mit en idle.
void Monsters_InitOfEnd(void);
// Collision Monstre avec le Joueur (contient Monsters_CollideDecor).
void Monster_CollidePlyr(void);
// Collision avec les items lorsque M et P même colonne.
bool Monster_CollidePlyrItem(SMonster *pMst);
// Collision avec le décore lorsque M et P son sur la même colonne et que M à côté de S à côté de P (M S P).
// Out : true = bloc est un solide, false = n'est pas un solide.
bool Monster_CollideDecorPlyr(SMonster *pMst, u32 nNbBlk);
// Collision avec le décore lorsque monster et player son sur la même colonne et que M à côté de P à côté de S (M P S).
// nNbBlk est le nombre de blocs qui séparent le M et le S inclue.
bool Monster_CollidePlyrDecor(SMonster *pMst, u32 nNbBlk);
// Collision avec le décore y compris les items (coffre, coeurs, block déplaçable ou oeuf (tire du plyr sur un mst)) et monstre statique.
bool Monsters_CollideDecor(SMonster *pMst, u32 nLvl);
// Collision mur :
void Monsters_CollideWalls(u32 nIdxMst);
// RAZ des slots.
void Monsters_ClearSlot(void);
// Mouvement des monstres.
void Monsters_MonstersMove(u32 nLvl);
// Initialisation de tout les slot du tableau de structure SMonster (uniquement nUsed mis à 0).
void Monsters_InitSlots(void);
// Cherche un slot vide. -1 si pas de slot vide.
u32 Monsters_GetSlot(void);
void Monsters_InitMonsters(u32 nLvl);
// Retourne un numéro de slot du moteur de monstre et qui attribut un slot d'anim s'il y en à une. 
// nNoMst : n° du sprite.
s32 Monsters_InitMonsters_Aux(u32 nNoSlotMst, u32 nNoMst, u64 *pAnim, u64 nAnimNoSlot, u32 nDir, u32 nBlkX, u32 nBlkY, u8 nProperty, s16 nSpeed, u32 nName);
// Gestion des mnostres (collision, etc). A faire
void Monsters_Manage(void);
void Monster_Recalage(struct SMonster *pMst, u32 nLastPosX, u32 nLastPosY);
// Collision Snake avec joueur.
bool Monster_CollideSnake(SMonster *pMst);


