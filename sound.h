
#define SOUND_MAX_CHANNEL 2
#define SOUND_CHANNEL_MUSIC 0 // Canal pour la musique (car SDL_Audio prend 2 cannaux).
#define SOUND_CHANNEL_EFFECT 1 // Canal pour les bruitages.

extern int gnCountTimeDownKey;

typedef struct SSound
{
	int nSoundSaveVolume; // Pour garder le même volume si on change de menu.
	int nModularitySound; // Pour changer le volume du son.
	bool bIsFinishSnd; // Si music fini true.
    // Sauvegarde les caractéristiques du son souhaité en sortie (sera identique pour tout les fichiers audios).
    SDL_AudioSpec sAudioSpec; 
    // Permettra de sauvegarder les caractéristiques des fichiers audios 
    // après conversion des données de ces fichiers avec les caractéristiques 
    // données au départ avec SDL_AudioSpec.
    SDL_AudioCVT pCVT[SOUND_MAX_FILE]; 
}SSound;

SSound gSound;

typedef struct SSample{
    u8 *pBuffer; // Buffer contenant l'audio à jouer.
    u32 nLen; // Taille total du buffer audio.
    u32 nPos; // Position du curseur dans le buffer.
    u32 nPrio; // Priorité des musiques.
}SSample;

SSample gpSample[SOUND_MAX_CHANNEL];



// Bruitage (Sound effects Sfx) + Musique :
enum ESfx{
	// Effet :
	e_Sfx_BallBounce,
	e_Sfx_BatMagnet,
	e_Sfx_BatPing,
	e_Sfx_BrickBounce,
	e_Sfx_BrickDissolve,
	e_Sfx_DoorThrough,
	e_Sfx_Explosion1,
	e_Sfx_Explosion2,
	e_Sfx_ExtraLife,
	e_Sfx_MenuClick,
 	e_Sfx_PillBonus,
	e_Sfx_PillMalus,
	e_Sfx_Shot,
	e_Sfx_LoloDead,
	
	// Music :
	e_Music_Menu,
    e_Music_Game,
	e_Sfx_Last,
};

void Sound_ReplayMusic(int music);
// Netoyage du tableau de struct gpSample.
void Sound_ClearChannels(void);
void Sound_ConvertAudio(u32 idx, SDL_AudioSpec *spec, u8 *buffer, u32 len);
// Permet d'augmenter le volume de façon rapide (lorsqu'on reste appuyer plus de 20 frames sur la touche + ou - ).
void Sound_VolumeSpeed(void);
// Arrêté un son. Quand on fait un choix au niveau du menu.
void Sound_Stop(void);
// Jouer un son. posChannel soit valeur 0 ou 1.
void Sound_Play(int noSound, int posChannel);
// Active l'audio.
void Sound_Pause(void);
// Libération de la mémoire pour chaque buffer alloué pour gSound.pCVT[idx].buf dans Sound_ConvertAudio ligne 601.
void Sound_Free(void);
// Récupération des fichiers audio, pour chaque fichier un buffer est alloué.
void Sound_LoadWAV(char *pFilename[]);
// Fonction de rappel appelé à chaque fois qu'un son doit-être joué. Envoi une partie du buffer audio dans le stream, et est appelé
// plusieurs fois jusqu'à arrivé à la fin du buffer. Ex. : le buffer à une taille de 6734 octets, à chaque appel on envoi les 2048 
// octets suivant donc 1er appel on envoi dans le stream les 2048 1er octets du buffer puis les 2048 octets suivant puis le reste.
/**
*  @param[out] stream	A pointer to the audio data buffer
*  @param[in]  len	The length of the audio buffer in bytes.
*/
void Sound_Callback(void *userdata, u8 *stream, int len);
// Initialisation de la structure gpSample.
void Sound_InitChannel(void);
bool Sound_Init(void);

