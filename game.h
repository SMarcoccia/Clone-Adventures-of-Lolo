
#define LEVEL_MAX 2

// Nombre de cases de l'aire de l'écran :
#define AREA_WIDTH 20
#define AREA_HEIGHT 15

#define TIMER_FRAMES_SLEEPING 18000 // Nb de frames avant que le perso s'endorme. Vaut 5 mins.
#define TIMER_DISPLAY_LEVEL (60*3) // Nombre de secondes avant d'afficher le level

#define PLYR_SPEED_INIT 0x100
#define PLYR_SPEED_SAND 0x080

#define PLYR_LIVES 5 // Nb de vie max du joueur.

// Enum clavier
enum EKeyboard{
    e_Kb_Null=0,
    e_Kb_Up=1,
    e_Kb_Right=2,
    e_Kb_Down=4,
    e_Kb_Left=8,
};

// Direction pour Plyr, Monster. 
// Note : ici on se base sur les flèches du clavier, ex : e_Dir_Down on va en direction opposé de l'origine du screen (coin supérieur gauche (0x/0y en px)).
enum EDir{
    e_Dir_Null=-1,
    e_Dir_Down,
    e_Dir_Left,
    e_Dir_Up, 
    e_Dir_Right,
};

// Direction des items flèches
enum EDirArrow{
    e_Dir_Arrow_Down = ~e_Dir_Up,
    e_Dir_Arrow_Left = ~e_Dir_Right,
    e_Dir_Arrow_Up = ~e_Dir_Down,
    e_Dir_Arrow_Right = ~e_Dir_Left,
};

// Indique si le jeu doit lancer une anim joueur inactif, marche, victoire, meurt.
enum EStatePlyr{
    e_PlyrAnim_Idle,
    e_PlyrAnim_Sleeping,
    e_PlyrAnim_Walk,
    e_PlyrAnim_Win,
    e_PlyrAnim_DeathArrow,
    e_PlyrAnim_DeathBurnt,
    e_PlyrAnim_Death,
    e_PlyrAnim_Max,
};

// Phase du jeu
enum EStateGame{
    e_Game_Null,
    e_Game_Normal,
    e_Game_LevelCompleted,
    e_Game_GameOver,
    e_Game_AllClear,
    e_Game_Pause,

};

/**** AREA GAME ****/

// Liste des différentes type de cases.
enum ETypeBox{
    e_Area_Ground, // (e_Area_Empty) Sol ou le Plyr peut marcher (sauf pont en bois et pont en pierre, sable).
    e_Area_Sand,   // (e_Area_Empty) Car il ralentit le plyr
    e_Area_Bridge, // (e_Area_Empty) Car disparait dans la lave ou reste dans l'eau.
    e_Area_Stone,  // (e_Area_Solid M et P) Car utilisation avec le marteau donc disparait.
    e_Area_Tree,   // (e_Area_Solid M et P)
    e_Area_Block,  // (e_Area_Solid M et P) Bloc d'émeraude, car se déplace.
    e_Area_Heart,  // (e_Area_Solid pour M) Car plyr passe au travers et se supprime à son passage.
    e_Area_Chest,  // (e_Area_Solid pour M) Car plyr passe au travers.
    e_Area_Arrow,  // (e_Area_Solid pour M et éventuell' P en fonction de la direction) Car change de direction.
    e_Area_Door,   // (e_Area_Solid)
    e_Area_Border, // (e_Area_Solid) Mur externe.
    e_Area_Water,  // (e_Area_Solid) car bloqué par le bord
    e_Area_Lava,   // (e_Area_Solid) idem
    e_Area_Mst,    // (e_Area_Solid) car Monstres statiques (l'oeuf est pris en compte, Mst se transforme en oeuf mais ensuite revient on laisse sur le même slot)
};

// Blocs solide ?
enum EIsSolid{
    e_Area_Empty,
    e_Area_Solid,
};

// Structure d'une case. Servira pour les test de collision décor, items, avec les monstres player.
typedef struct SAreaBox{
    u32 nSprNo; // Numéro de sprite (i.e la valeur du sprite qui est dans enum dans sprites.h)
    s8 nType; // Type du bloc (coffre, coeur, arbre, pierre, lave, herbe, ...)
    bool isSolid; // Bloc solide ou vide
    u8 nDir; // Direction si tuile fléché
    u32 nBlkX; // Position du bloc en X.
    u32 nBlkY; // Position du bloc en Y.
}SAreaBox;

extern struct SAreaBox gArea[AREA_WIDTH * AREA_HEIGHT];

/**** PLAYER : ****/
// Référence le joueur avec sa position dans le jeu.
// Question : est-ce au départ ou bien à n'importe quel moment du jeu ?
typedef struct SPlyrLvl{
    s32 nNoSpr;
    u32 nColumns, nLines;
}SPlyrLvl;

// Player :
extern SPlyrLvl gPlyrLvl1[];

// Référence tous les levels pour le joueur.
typedef struct SPlyrsLvls{
    SPlyrLvl *pPlyrLvl;
    u32 nNbPlyrs;
}SPlyrsLvls;

extern SPlyrsLvls gPlyrsLvls[];

typedef struct SGame{
    u32 nRemainingHearts; // Nb de coeurs restant
    u32 nPhase; // Phase du jeu (init, jeu, game over, ...)
    u32 nLevel; // Level en cours et sert aussi pour le level atteint au game over
    u32 nTimerLevelDisplay; // Compteur pour affichage du n° du level
}SGame;

extern SGame gGame;

//==================================================================

// Structure du joueur
typedef struct SPlayer
{
    u32 nAnimNoSlot;    // N° de slot d'anim (pour toute les anim du plyr). Note : on peut aussi réservé un slot pour chaque anim.
    s32 nDir;           // Direction du player.
    s32 nSpeed;         // Vitesse de déplacement du player.
    s32 nPosX, nPosY;   // Position du player.
    s32 nLastPosX, nLastPosY; // Dernière position du joueur
    u32 nLockedDir;     // Pour empécher le player d'aller dans une direction si collision avec Mst.
    bool bCollideMst;
    u32 nKb;            // Touche de direction appuyer par le player.
    u32 nState;         // Indique si le joueur est inactif, marche, meurt lier avec enum EStatePlyr.
    u64 *pAnim;         // Récupère l'adresse du tableau d'anim qui se trouve dans anims.c.
    s32 nCountFrames;   // Servira pour activation de l'anim du sleeping.
    u32 isCollide;
    u32 nFlags;         // Averti d'un événement lié au player, ex la mort.
	u32	nNbLives;	        // Nb de vie
}SPlayer;

extern SPlayer gPlyr;

// Recalage Plyr
void Game_PlyrRecalage(SPlayer* pPlyr, u32 nLastPosX, u32 nLastPosY);
// Renvoi booleen s'il y a collision entre Plyr et Mst.
bool Game_IsCollidePlyrMonster(void);
// Converti la position en X et Y en position de la case.
void Game_PosToCase(void);
// Converti la position de la case en X et Y.
void Game_CaseToPos(void);
// Init le level doit se trouver dans Game_Init(). Doit ê mit à chaque changement de level.
// Init des monstres, items, player et éventuellement du décor.
void Game_InitLevel(u32 nLvl);
// Dessine le bkg + décor.
void LoloAdventureDraw(void); 
// Test collision joueur et un item (coeur, bloc, egg).
void Game_CollidePlyrItem(u32 nLvl);
// Test collision entre le joueur et le décore.
bool Game_CollidePlyrDecor(u32 nLvl);
// Collision entre 2 sprites. nNoSpr1 et nNoSpr1 sont les numéros de sprites.
// Gestion collision joueur-murs. Obsolette remplacé par Game_PlyrCheckDepl.
bool Game_CollidePlyrWalls(void);
bool Game_Collide(u32 nNoSpr1, u32 nPosX1, u32 nPosY1, u32 nNoSpr2, u32 nPosX2, u32 nPosY2);
void Game_InitPlyr(u32 nLvl);
void LoloAdventureDraw(void); // Dessine le décore, joueur(s), etc.
// On envoi en paramètre l'anim qui doit-ê Initialisation.
void Game_PlayerAnimInit(SPlayer *pPlyr, int nAnim);
// Mouvement du joueur, chg' de direct°, ... Méthode compteur de frames.
// Déplacement du joueur automatiquement (si on à relaché la touche) jusqu'à arrivé soit à la moitié de la case soit à la case suivante ou précédente.
void Game_PlayerMoveCounterFrame(void);
// Mouvement du joueur, chg' de direct°, ... Méthode modulo 8.
void Game_PlyrMove(void);
void Game_InitPlayer(SPlayer *pPlyr); // On cherche un slot vide + init des caractéristique du player.
// Le jeu.
void LoloAdventureGame(void);
void LoloAdventure(void); // Fc° principale du jeu test clavier, joueur(s), monstres, collisions.
// Peut ê utilisé à chaque nouveau level.
// Correspond dans Breaker à BreakerInit(), ou il y a l'init des engines pour les monstres, fires, dust. init level aussi.
void Game_Init(void);
// Prepare la structure gExg pour la sortie de la partie.
void Game_ExgExit(u32 nExitCode);
// Gère tous les init
void Game_ExgBrkInit();
void Game(void);
// Test si le joueur peut se déplacer dans la direction demandée. Utilisé pour les murs et le décore pas pour les items (coeurs, blocs, eggs, ...)
// Out : true = déplacement ok, false = ne doit pas gouger.
bool Game_PlyrCheckDepl(SPlayer *pPlyr, u32 nDir);
// Collision entre le Joueur et le Monstre en cours de remplacement par Monster_CollidePlyr et Game_CollideMst
void Game_CollidePlyrMsts(s32 nPlyrLastPosX, s32 nPlyrLastPosY);

