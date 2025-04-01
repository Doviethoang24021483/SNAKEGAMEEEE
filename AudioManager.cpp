#include<iostream>
#include "AudioManager.h"
#include <time.h>
#include <SDL.h>
#include "PlayGround.h"
using namespace std;

AudioManager::AudioManager() : music(nullptr), failChunk(nullptr), completeSong(nullptr), goldNoteSound(nullptr) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Mix_OpenAudio failed: " << Mix_GetError() << std::endl;
    }
}
AudioManager::~AudioManager() {
    Mix_FreeMusic(music);
    Mix_FreeChunk(failChunk);
    Mix_FreeChunk(completeSong);
    Mix_FreeChunk(goldNoteSound); // Giải phóng âm thanh nốt vàng
    for (auto& pair : noteChunks) {
        Mix_FreeChunk(pair.second);
    }
    Mix_CloseAudio();
}

bool AudioManager::loadGoldNoteSound(const std::string& path) {
    goldNoteSound = Mix_LoadWAV(path.c_str());
    if (goldNoteSound == nullptr) {
        std::cerr << "Failed to load gold note sound: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void AudioManager::playGoldNoteSound() {
    if (goldNoteSound != nullptr) {
        Mix_PlayChannel(-1, goldNoteSound, 0);
    }
}

bool AudioManager::loadMusic(const std::string& file) {
    music = Mix_LoadMUS(file.c_str());//tai nhac tu duong dan, chuyen string thanh chuoi c_style (const char*)
    if (!music) {
        std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

//phat nhac
 void AudioManager::playMusic(){
  if(music) Mix_PlayMusic(music, -1);//lap vo han
 }

void AudioManager::stopMusic() {
    Mix_HaltMusic();
}

 bool AudioManager::loadFailChunk(const std::string& filePath) {
    failChunk = Mix_LoadWAV(filePath.c_str());
    if (failChunk == nullptr) {
        std::cerr << "Failed to load 'fail' sound effect: " << filePath << " SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void AudioManager::playFailChunk() {
    if (failChunk != nullptr) {
        Mix_PlayChannel(-1, failChunk, 0);
    }
}
void AudioManager::setMusicVolume(int volume) {
    if (volume < 0) volume = 0;
    if (volume > MIX_MAX_VOLUME) volume = MIX_MAX_VOLUME;
    Mix_VolumeMusic(volume);//thay doi am thanh nhac nen
}
bool AudioManager::loadNoteChunk(NoteValue note, const std::string& filePath){
     noteChunks[note] = Mix_LoadWAV(filePath.c_str());
    if (noteChunks[note] == nullptr) {
        std::cerr << "Failed to load note sound effect: " << filePath << " SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}
 void AudioManager::playNoteChunk(NoteValue note){
    if (noteChunks[note] != nullptr) {
        Mix_PlayChannel(-1, noteChunks[note], 0);
    }
}
 bool AudioManager::loadCompleteSong(const std::string& filePath){
    completeSong = Mix_LoadWAV(filePath.c_str());
     if (completeSong == nullptr) {
        std::cerr << "Failed to load complete song: " << filePath << " SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
 }
void AudioManager::playCompleteSong(){
    if (completeSong != nullptr) {
       Mix_PlayChannel(-1, completeSong, 0);
    }
}



