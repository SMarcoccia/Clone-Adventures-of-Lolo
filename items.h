// Items (coeurs, blocks vert, coffre, ...) 
// Référence un item et ses propriétés
typedef struct SItem{
    u32 nNoSpr; // N° de sprite.
    bool nUsed; // Si slot utilisé (true), sinon false.
    u32 nColumns, nLines; // Position colonnes (x) et lignes (y).
    u32 nPosX, nPosY; // Position de l'item.
    u32 nNoSlot; // N° du slot de l'anim.
}SItem;

// Pour connaître le nombre d'items par type et par level
// Pour connaître le nombre de coeurs et ainsi savoir quand le coffre s'ouvre.
typedef struct SNbItemsByTypeByLvl{
    u8 nEmeraldBlocks;
    u8 nHearts;
    u8 nChests;
    u8 nArrowChangers;
}SNbItemsByTypeByLvl;

// Note : pItemsLvl peut-ê remplacé par pItemSlots !
// Référence tous les levels pour les items.
typedef struct SItemsLvls{
    struct SItem *pItemsLvl; // Le tableau des items d'un level.
    u32 nNbItems; // Nombre d'items dans le level.
    struct SNbItemsByTypeByLvl pItemsType;
}SItemsLvls;


extern SNbItemsByTypeByLvl pItemsTypeLvl;
extern SItemsLvls gItemsLvls[];

// Init des Items. Pour la réservation de l'anim je ne la met pas, je met en dure -1, on fera la réservation de l'anim en
// temps voulu.
// Affichage des items sur la map
void Items_InitItems(u32 nLvl);
// RAZ des slots.
void Items_InitSlots(void);
// Cherche un slot vide (renvoi le n° de slot ou -1).
u32 Items_GetSlot(void);
// Place un item dans un slot. Ajoute les valeurs manquante comme N° d'item, posX et Y, ...
void Items_SetItem(u32 nNoItem, u32 nNoSlot, u32 nPosX, u32 nPosY);
// Libère un slot.
void Items_ReleaseSlot(u32 nNoSlot);
