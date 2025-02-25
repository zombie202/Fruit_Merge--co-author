#pragma once

#include <string>
#include "SFML/Audio/Music.hpp"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"


class SoundManager
{
    private:
        sf::Music music;
        sf::SoundBuffer soundBuffer1;
        sf::SoundBuffer soundBuffer2;
        sf::Sound sound1;
        sf::Sound sound2;

        const std::string musicPath0 = "assets/rung-xanh-hoang-da-61985.wav";
        const std::string musicPath1 = "assets/1_symphony1.wav";
        const std::string musicPath2 = "assets/2_symphony_automatycy.wav";
        const std::string popSoundPath = "assets/happy-pop-2-185287.wav";
        const std::string mergeSoundPath = "assets/pop-39222-_AudioTrimmer.com_.wav";
        float musicVolume = 50.f;
        float soundVolume = 100.f;

    public:
        SoundManager();
        void playMusic();
        void playPopSound();
        void playMergeSound();
};