

enum{
    e_Menu_Null,
    e_Menu_Main,
    e_Menu_Game,
    e_Menu_Options,
    e_Menu_HallOfFame,
    e_Menu_Quit,
};

typedef struct SMenu{
    u32 nIdx; // Récupère l'index du choix.
    u32 nOldIdx;
}SMenu;

SMenu gMenu;

typedef struct SMenuChoice{
    char *pStr; // Le nom du choix.
    int nLg; // La longueur gfx du choix.
    int flag; // Le flag du choix ie e_Menu_Game...
}SMenuChoice;

extern SMenuChoice gpMenuChoice[];

int Menu_Main(bool eventFilter);
bool Menu_CollideSprMouseMenu(int x, int y,  int w, int h);
void Menu_Init(void);
int Menu(void);