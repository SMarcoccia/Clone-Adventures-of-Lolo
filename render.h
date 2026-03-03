
enum{
    e_ModeVideoNormal, // 320*240.
    e_ModeVideo2x, // 640*480.
    e_ModeVideoResize, // Redimenssionnement de l'écran.
    e_ModeVideo_MAX
};

typedef struct SRender{
    SDL_Surface *pScreen2x; // Pour l'affichage sur l'écran réel (l'écran vue par l'utilisateur).
    SDL_Surface *pScreenBuf; // Surface 320x240 qui sera blitté sur pScreen2x et pScreenResize.
    SDL_Surface *pScreenResize; // Surface pour le redimenssionnement manuelle de l'écran.
    int nFullScreenMode; // Variable recevant 1 pour le pleine écran sinon 0.
    int nOldModeVideo; // 
}SRender;

SRender gRender;

void Render_ModeVideoResize(void);
// Initialisation de tous ce qui concerne le rendu vidéo.
void Render_InitVideo(void);
// Met le mode vidéo qui va bien.
void Render_SetModeVideo(void);
// Pour le 640x480. On transpose le buf2 dans pScreen2x.
void Render_ModeVideo2x(void); 
// Affiche le jeu à l'écran.
// Paramètre formel x et y pour récupérer la taille de l'écran lors d'un resize.
void Render_Flip();
// Libération de la surface uniqu' pour SDL_CreateRGBSurface.
void Render_FreeSurface(void);


