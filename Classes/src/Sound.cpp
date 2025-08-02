//
// Created by judelhuu on 7/7/25.
//

#include "../include/Sound.h"
#include <iostream>

Sound::Sound(std::string filepath): m_device(0) {
    if (!SDL_LoadWAV(filepath.c_str(), &m_audioSpec, &m_waveStart, &m_waveLength)) {
        std::cerr << "sound loading error: " << Mix_GetError() << std::endl;
    }

    int status = SDL_QueueAudio(m_device, m_waveStart, m_waveLength);
    SDL_PauseAudioDevice(m_device, 0);
}

Sound::~Sound() {
    SDL_FreeWAV(m_waveStart);
    SDL_CloseAudioDevice(m_device);
}

void Sound::SetupDevice() {
    m_device = SDL_OpenAudioDevice(nullptr, 0, &m_audioSpec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE);
    if (m_device == 0) {
        std::cerr << "sound device error: " << SDL_GetError() << std::endl;
    }
}

void Sound::StopSound() {
    SDL_PauseAudioDevice(m_device,1);
}

void Sound::PlaySound() {
    int status = SDL_QueueAudio(m_device, m_waveStart, m_waveLength);
    SDL_PauseAudioDevice(m_device,0);
}
