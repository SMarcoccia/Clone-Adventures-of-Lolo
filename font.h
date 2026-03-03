
#define FONT_NO_DISPO 0
#define FONT_DISPO 1
#define FONT_HEIGHT 7

// Stockage des lettres gfx à blitter.
// Renvoi la longueur (en pixels) de la phrase gfx si le flag e_Font_NoDispo est utilisé.
int Font_PhraseStockedForBlitting(char *pStr, int x, int y, int flag);
