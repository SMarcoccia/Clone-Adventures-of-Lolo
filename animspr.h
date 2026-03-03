
enum{
    e_AnimFlag_End=1, // Pour vérifier si l'anim est terminé.
};

typedef struct SAnim
{
    bool nUsed;
    // Adresse de la 1er valeur du tableau d'anim. Ex. : pOrg=gAnim_Plyr_Down_Walk (l'adresse de gAnim_Plyr_Down_Walk est  l'adresse de la 1er case du tableau
    // car on déclare un tableau statique).
    u64 *pOrg;
    u64 *pAnim; // Adresse de la case de l'anim courante.
    //u64 *pAnimNext; // Adresse de la prochaine anim. ATTENTION : n'existe pas dans code Clément Corde.
    u32 nFramesCnt; // Compteur de frames.
    u32 nCurSpr; // Image courrante (Numéro du sprite).
    u32 nKey; // Clé d'anim.
    s32 nFlags; // Pour indiquer un état (victoire, mort, etc) pour le joueur par ex..
    u32 nChannel; // Prend comme valeur soit : SOUND_CHANNEL_MUSIC, SOUND_CHANNEL_EFFECT (dans sound.h) ou -1 si pas d'audio.
}SAnim;

#define ANIM_MAX_SLOT 64 // Nb maximum d'anim soit 64 slot utilisable donc 64 sprites qui peuvent être animé en même temps.
extern SAnim pAnimSlots[ANIM_MAX_SLOT];

// Place une nouvelle anim d'un monstre.
void AnimSpr_MstAnimSetIfNew(SMonster *pMst);
// Place une nouvelle anim du player.
void AnimSpr_PlyrAnimSetIfNew(SPlayer *pPlyr);
// Renvoi la clé d'anim.
void Animspr_GetKey(void);
// Initialise le tableau de slots d'anim à 0.
void Animspr_InitSlots(void);
// Test si l'anim est terminé (e_Anim_End).
bool Animspr_CheckEnd(s32 nSlotNo);
// Vérifie si c'est la même anim. Si oui renvoi le même n° de slot. Sinon renvoi un n° de slot différent. Fonction clé ! 
// Evite de rappeler GetImage à chaque fois.
s32 Animspr_AnimSetIfNew(u64 *pAnim, u32 nNoSlot);
// Place une anim, mettre n° du slot à -1. Ex : s32 nMySlotForPlayerIdle = Animspr_AnimSet(gAnim_Plyr_Down_Idle, -1);
// Retourne le n° du slot.
s32 Animspr_AnimSet(u64 *pAnim, u32 nNoSlot); 
// Recherche un slot vide. Retourne n° du slot.
s32 Animspr_GetSlot(void);
// Renvoi le dernier sprite (le n° du sprite).
u32 Animspr_GetImgLast(u32 nNoSlot);
// Contient la machine à état, renvoi l'image courrante (le numéro de sprite) à afficher.
// Permet de passer à l'anim suivante voir dans Bomberman C_Bomber_v1_src3264 - bomber.c n° ligne 1177.
u32 Animspr_GetImg(u32 nNoSlot);
// RAZ (Remise à zéro) du tableau de slots.
void Animspr_ClearSlots(void);