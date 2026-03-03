// ERREUR rencontré :
// Bug de collision avec Rock alors que l'on est pas en collision. Problème venait du sprite qui avait une erreur de son point de référence. Résolution j'ai
// modifier (avec photoshop) mon sprite en décalent le point de référence de un pixel.
/*  Note : pour les décalage 
    *16 (<<4) pour le bloc, *256 (<<8) pour la virgule fixe.
    gPlyr.nPosX 49152 = 12*16*256
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL.h>
#include <windows.h> // Mettre en dernier sinon SDL fonctionne pas pour le redimenssionnement.

#include "types.h"
#include "levels.h"
#include "initSDL.h"
#include "render.h"
#include "sprites.h"
#include "font.h"
#include "frame.h"
#include "menu.h"
#include "game.h"
#include "fade.h"
#include "anims.h"
#include "monsters.h"
#include "animspr.h"
#include "ia.h"
#include "tools.h"

// Audio :
#define SOUND_MIX_VOLUME SDL_MIX_MAXVOLUME/16
#define SOUND_MAX_FILE 16
#define SOUND_FILENAMES {\
    "_sfx/_ball_bounce.wav",\
    "_sfx/_bat_magnet.wav",\
    "_sfx/_bat_ping.wav",\
    "_sfx/_brick_bounce.wav",\
    "_sfx/_brick_dissolve.wav",\
    "_sfx/_door_through.wav",\
    "_sfx/_explosion1.wav",\
    "_sfx/_explosion2.wav",\
    "_sfx/_extra_life.wav",\
    "_sfx/_menu_click.wav",\
    "_sfx/_pill_bonus.wav",\
    "_sfx/_pill_malus.wav",\
    "_sfx/_shot.wav",\
    "_sfx/_lolo_dead.wav",\
    "_sfx/_music_menu.wav",\
    "_sfx/_arkanoid_theme.wav",\
}

#include "sound.h"
#include "eventHandler.h"
#include "items.h"



#define lf printf("\n");
#define info_context printf("%s %s : line %d --- ", __FILE__, __FUNCTION__, __LINE__);
#define	SGN(x)	((x) >= 0 ? 1 : -1)

// Taille d'une case 16 pixels par 16 pixels
#define CASE_SIZE 16 

// Bord de l'air de jeu inclue les murs en nombre de case.
// On compte le nombre de case en partant de 1.
#define WALL_COLMin (4+1)*SPR_SIZE // 4+1 : 4 cases de la marge et +1 pour que le perso soit en dehors du mur.
#define WALL_COLMax (17-1)*SPR_SIZE // 17-1 : 17 cases, la limite du bord du jeu -1 pour que le perso soit en dehors du mur.
#define WALL_LINEMin (0+2)*SPR_SIZE // 0+2 : 0 pas de marge et +2, pour que le perso soit en dehors du mur.
#define WALL_LINEMax (14-1)*SPR_SIZE // 14-1 : 14 cases c'est la limite du bord du jeu -1 évite que le perso soit dans le mur.

// Ou :
//#define WALL_XMin 80 // 5 cases * 16 taille du sprite.
//#define WALL_XMax 256 // 16 * 16.
//#define WALL_YMin 32 // 2 * 16.
//#define WALL_YMax 208 // 16 * 16.

// Rendu vidéo :
#define VIDEO_MODE_DEFAULT e_ModeVideo2x;
//#define VIDEO_MODE_DEFAULT e_ModeVideoNormal;
#define SCR_WIDTH 320
#define SCR_HEIGHT 240
#define SCR_BPP 8
#define SCR_FLAGS (SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE)

// Tableau calcul la taille :
#define NBELEM(array) (sizeof(array)/sizeof(array[0]))

// Sourie :
#define MOUSE_BTN_LEFT 1
#define MOUSE_BTN_RIGHT 2

// Background (bkg)):
#define BKGs_MAX 3 // Nombre maximum de backgrounds.
#define BKGs_FILENAMES {"_gfx/bkg1.bmp", "_gfx/bkg2.bmp", "_gfx/grid.bmp"}

// Palette color :
#define COLOR_MAX 256

typedef struct SGen{
    SDL_Surface *pScreen; // Surface afficher à l'écran.
    SDL_Surface *pBkg[BKGs_MAX]; // Tableau des Backgrounds.
    SDL_Surface *pBackground; // Background courant.
    SDL_Surface *pBackground_Grid; // Background grid pour test plyr si bien dans colonnes et lignes.
    SDL_Color pColor[256]; // Palette général, contiendra la palette Bkg et sprite.
    
    u32 nModeVideo; // Permet de savoir quel est le mode vidéo utilisé.
    //u32 nModeMenu; // Permet de savoir dans quel partie du jeu on se trouve (game, option, etc).
    u8 *pKeys; // Pointeur sur le tableau des events clavier.

    POINT cursor;

    s32 nMouseX, nMouseY; // Position de la souris.
    s32 nMouseBtnLeft, nMouseBtnRight; // Récupère l'évenement clique de la souris. Remettre manuellement à zéro.
    s32 nResizeW, nResizeH;
    s32 nMenuChoice;
    s32 isTransition; // Pour savoir si la transition (fade) est terminé.
    u32 nPhase; // On indique si le joueur est mort, par ex.
    bool nIsStartPlyr; // Indique si le joueur à commencé à se déplacer pour la première fois.
    u32 nLevel; // Level actuel.
}SGen;

extern SGen gGen;

// Structure d'échange entre les différents modules
typedef struct SExg{
    u32 nExitCode; // Pour sortie du jeu. Tjs à 0, sauf pour sortie
    u32 nLevel; // Level atteint au game over
}SExg;

extern SExg gExg;