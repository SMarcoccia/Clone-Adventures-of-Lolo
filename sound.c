
#include "includes.h"

// Compteur permettant de savoir si l'utilisateur est resté appuyé suffisament longtemps sur la touche + ou - pour activer la 
// répétition des touches + et -.
int gnCountTimeDownKey=0; 

bool gnIsInitAudio = false; // Initialisation de l'audio, false : l'initialisation à échoué.
int gnNoSound = -1; // Numéro du son à jouer.
const int SOUND_VOLUME=0;
//const int SOUND_VOLUME=SOUND_MIX_VOLUME;

void Sound_ReplayMusic(int music)
{
    if(gSound.bIsFinishSnd){
        Sound_Play(music, SOUND_CHANNEL_MUSIC);
    }
}

void Sound_VolumeSpeed(void)
{
    if (gnCountTimeDownKey > 20 ? true:false)
    {
        // gnCountTimeDownKey % 5 == 0 permet de moduler la vitesse de décrémentation ou d'incrémentation du son.
        if(gSound.nModularitySound > 0 && gSound.nModularitySound < SDL_MIX_MAXVOLUME && gnCountTimeDownKey % 5 == 0)
        {
            if(gGen.pKeys[SDLK_KP_PLUS]) gSound.nModularitySound++;
            if(gGen.pKeys[SDLK_KP_MINUS]) gSound.nModularitySound--;
        }
    }

    if(gGen.pKeys[SDLK_KP_PLUS]) gnCountTimeDownKey++;
    if(gGen.pKeys[SDLK_KP_MINUS]) gnCountTimeDownKey++;
}
void Sound_Stop(void)
{
    Sound_ClearChannels();
}

void Sound_Play(int noSound, int posChannel)
{
#ifdef DEBUG
    if(posChannel < 0 || posChannel > 1)
    {
        printf("The posChannel value must be between 0 and 1. %s %d", __FILE__, __LINE__);
        return;
    }
#endif
    if(gSound.nModularitySound < 1)
    {
        gSound.nModularitySound=0;
    }
    
    SDL_LockAudio();
    gpSample[posChannel].pBuffer = gSound.pCVT[noSound].buf;
    gpSample[posChannel].nLen = gSound.pCVT[noSound].len_cvt;
    gpSample[posChannel].nPos = 0;
    gpSample[posChannel].nPrio = 0;
    SDL_UnlockAudio();
}

void Sound_Pause(void)
{
    SDL_PauseAudio(1);
}
void Sound_Free(void)
{
    for (int i = 0; i < SOUND_MAX_FILE; i++)
    {
        free(gSound.pCVT[i].buf);
    }
}

void Sound_ConvertAudio(u32 idx, SDL_AudioSpec *spec, u8 *buffer, u32 len)
{
    SDL_BuildAudioCVT(
        &gSound.pCVT[idx], 
        spec->format, spec->channels, spec->freq,
        gSound.sAudioSpec.format, gSound.sAudioSpec.channels, gSound.sAudioSpec.freq
    );
    gSound.pCVT[idx].buf=malloc(len * gSound.pCVT[idx].len_mult);
    memcpy(gSound.pCVT[idx].buf, buffer, len);
    gSound.pCVT[idx].len = len;
    SDL_ConvertAudio(&gSound.pCVT[idx]);
}
void Sound_LoadWAV(char *pFilename[])
{ 
    SDL_AudioSpec spec;
    u8 *buffer;
    u32 len;

    for (int i = 0; i < SOUND_MAX_FILE; i++)
    {
        if(SDL_LoadWAV(pFilename[i], &spec, &buffer, &len) == NULL)
        {
            fprintf(stdout, "File sound %s not loading: %s, %s %d", pFilename[i], SDL_GetError(), __FILE__, __LINE__);
        }
        Sound_ConvertAudio(i, &spec, buffer, len);
        SDL_FreeWAV(buffer);
    }
    
}
void Sound_Callback(void *userdata, u8 *stream, int len)
{
    int amount=0;
    for (int i = 0; i < SOUND_MAX_CHANNEL; i++)
    {
        amount = gpSample[i].nLen - gpSample[i].nPos; // On soustrait la taille de la mémoire audio avec la taille du buffer audio.
        if(amount > len) amount=len;

        SDL_MixAudio(stream, &gpSample[i].pBuffer[gpSample[i].nPos] , amount, gSound.nModularitySound);
        gpSample[i].nPos+=amount;
    }
    gSound.bIsFinishSnd=gpSample[SOUND_CHANNEL_MUSIC].nLen==gpSample[SOUND_CHANNEL_MUSIC].nPos?true:false;
}
void Sound_ClearChannels(void)
{
    for (int i = 0; i < SOUND_MAX_CHANNEL; i++)
    {
        SDL_LockAudio();
        gpSample[i].pBuffer=NULL;
        gpSample[i].nLen=0;
        gpSample[i].nPos=0;
        gpSample[i].nPrio=0;
        SDL_UnlockAudio();
    }
}
bool Sound_Init(void)
{
    // Variable permettant de controler le volume.
    gSound.nSoundSaveVolume=gSound.nModularitySound=SOUND_VOLUME;
    gSound.sAudioSpec.freq=22050;
    gSound.sAudioSpec.format=AUDIO_S16;
    gSound.sAudioSpec.channels=2;
    gSound.sAudioSpec.samples=512;
    gSound.sAudioSpec.callback=Sound_Callback;

    if(SDL_OpenAudio(&gSound.sAudioSpec, NULL) < 0)
    {
        fprintf(stdout, "Coulnd't opened audio device: %s, %s %d", SDL_GetError(), __FILE__, __LINE__);
        printf("The sound hasn't game");
        return false;
    }
    Sound_ClearChannels();

    return true;
}

