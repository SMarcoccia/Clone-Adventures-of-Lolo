
// Convertit le nombre de cases en pixels.
u32 Tools_LineToY(u32 nLine);
u32 Tools_ColumnToX(u32 nColumn);
// Convertit le nombre de pixels en cases. 
u32 Tools_XToColumn(u32 x);
u32 Tools_YToLine(u32 y);
// Convertit le nombre de pixels en case à la case supérieur, ex. 223 pixel donne une case de 14 au lieu de 13.
u32 Tools_XToColumnCeilf(u32 x);
u32 Tools_YToLineCeilf(u32 y);

float Tools_XToColumnFloat(u32 x);
float Tools_YToLineFloat(u32 y);
// Renvoi le n° du sprite du décor en fonction des coordonnées du joueur ou du monstre ou du décor.
// nIdx : l'index pour le tableau de monstre (gMst). nLvl : le level en cours.
//u32 Tools_GetSprDecor(u32 nIdx, u32 nLvl);
char *Tools_ReplaceOccurence(char *dst);
char *Tools_IntToASCII(int nb, char *dst);

void info_dir_plyr(SPlayer gPlyr);
void info_dir_Mst(SMonster gMst);
