
// ATTENTION : 
//    - Le .h se trouve dans includes.c
//    - On ne définie (u32 nMaVariable=0;) pas les variables dans les entêtes mais dans les .c. Dans le .h uniquement la déclaration (u32 nMaVariable;).
//    - Mais on ne peut pas mettre dans plusieurs .c une définition même en mettant extern.
//    - Si on supprime le .h du includes.h et que l'on met le .h dans plusieurs .c sa ne marchera pas (erreur multiple définition).

// Note : j'utilise un .c car j'utilise les variables dans plusieurs fichiers.
// Note 2 : avec extern on déclare un tableau sans le définir et sans mettre sa taille.
/*** STRUCTURES : ***/

// Tableau des levels 
extern s16* gpLevels[];

// Placement sur la map d'origine contenu dans gpLevels des Items, Monstres, Player.
void Levels_PlacementElements(u32 nLvl);
// Affiche le level d'origine ou de collision (false pour origine)
void Level_Display(s16 *pLvl, bool isLvlCollide);
// Affiche le level pour les collision
void Level_DisplayCollide(s16 *pLvl);