//
// Created by judelhuu on 7/7/25.
//

#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <string>



class Sound {
public:
    Sound(std::string filepath);
    ~Sound();
    void SetupDevice();
    void StopSound();
    void PlaySound();


private:
    SDL_AudioDeviceID   m_device;
    SDL_AudioSpec       m_audioSpec;
    Uint8*              m_waveStart;
    Uint32              m_waveLength;
};



#endif //SOUND_H
