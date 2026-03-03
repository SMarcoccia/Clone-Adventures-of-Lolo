
#define NO_EXIT false // On ne quitte pas la partie du jeu (menu, game, option) dans laquelle on est.
#define EXIT true
#define EVENTFILTER_NO_DISPO false
#define EVENTFILTER_DISPO true


// Fc qui sera appelé par SDL_SetEventFilter en premier.
int EventHandler_EventFilter(const SDL_Event *pEvent);
int EventHandler_EventHandler(u32 nInGame );