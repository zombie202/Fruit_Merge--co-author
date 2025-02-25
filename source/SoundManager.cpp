#include "SoundManager.h"


SoundManager::SoundManager()
{
    music.openFromFile(musicPath1);
    music.setLoop(true);
    music.setVolume(musicVolume);

    soundBuffer1.loadFromFile(popSoundPath);
    sound1.setBuffer(soundBuffer1);
    sound1.setVolume(soundVolume);
    
    soundBuffer2.loadFromFile(mergeSoundPath);
    sound2.setBuffer(soundBuffer2);
    sound2.setVolume(soundVolume);
}

void SoundManager::playMusic()
{
    music.play();
}

void SoundManager::playPopSound()
{
    sound1.play();
}

void SoundManager::playMergeSound()
{
    sound2.play();
}