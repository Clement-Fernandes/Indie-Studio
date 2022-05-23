/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Sound
*/

#include "Errors/ErrorsModules/ErrorsSettings.hpp"

#include "Sound.hpp"

MySound::MySound(std::string const &filename) : _sound(LoadSound(filename.c_str()))
{
    if (_sound.frameCount == 0)
        throw Error::ErrorsSettings(std::cerr, "MySound initialization failed");
}

MySound::~MySound()
{
    UnloadSound(_sound);
}

void MySound::play()
{
    PlaySound(_sound);
}

void MySound::stop()
{
    StopSound(_sound);
}

void MySound::pause()
{
    PauseSound(_sound);
}

void MySound::resume()
{
    ResumeSound(_sound);
}

bool MySound::isPlaying()
{
    return (IsSoundPlaying(_sound));
}

void MySound::setVolume(float volume)
{
    SetSoundVolume(_sound, volume);
}