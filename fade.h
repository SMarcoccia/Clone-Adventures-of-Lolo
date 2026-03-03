
#define FADE_STEP 4

enum{
    e_Menu_FadeIn,
    e_Menu_FadeOut,
    e_Menu_FadeInput,
};

typedef struct SFade{
    int nState; // Pour savoir si on est en fadeOut, fadeIn, ou fadeInput.
    int nFadeVal; // Pour modifier la palette, si on est en FadeIn on va de 0 à 255 frame et FadeOut 255 à 0.
    SDL_Color pColor[256]; 
}SFade;

SFade gFade;

void Fade(void);
void Fade_Gfx(void);
void Fade_Sfx(void);