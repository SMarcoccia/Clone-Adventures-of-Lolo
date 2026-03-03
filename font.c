#include "includes.h"

int Font_PhraseStockedForBlitting(char *pStr, int x, int y, int flag)
{
    int posXOrg=x;
    int noSpr = 0;
    SSprite *pSpr = NULL;

    while (*pStr != '\0')
    {
        noSpr = e_Spr_Font+*pStr-' '-1;
        //printf("noSpr font %d", noSpr);lf
        if (*pStr != ' ')
        {
            pSpr = Sprites_GetDesc(noSpr);
            if (flag == FONT_DISPO) 
            {
                Sprites_Stock(noSpr, x, y, 0);
            }
        }
        else
        {
            pSpr = Sprites_GetDesc(e_Spr_Font + 'I'-' ' -1); // Espace vaut la taille d'un 'I'.
        }
        x += pSpr->w +1; // +1 pour l'espace entre les lettres.
        pStr++;
    }

    return x-posXOrg;
}