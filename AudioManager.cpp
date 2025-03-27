#include<iostream>
#include "AudioManager.h"
#include <time.h>
#include <SDL.h>
using namespace std;

AudioManager::AudioManager() : music(nullptr), failChunk(nullptr),completeSong(nullptr) {
    // Initialize SDL_mixer
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
        srand(time(0));
        for (int i = 0; i < 5; i++) {
        noteSounds[i] = nullptr;
    }
}

AudioManager::~AudioManager() {
    if (music) {
        Mix_FreeMusic(music);
        music = nullptr;//Dam bao ko tro vao vung nho da giai phong
    }
    for ( int i = 0 ; i < 5 ; i ++){
        if(noteSounds[i]){
            Mix_FreeChunk(noteSounds[i]);
        }
    }
    if (failChunk){
       Mix_FreeChunk(failChunk);
        failChunk = nullptr;//Dam bao ko tro vao vung nho da giai phong
    }
    if (completeSong){
       Mix_FreeMusic(completeSong);
        completeSong= nullptr;//Dam bao ko tro vao vung nho da giai phong
    }
   // .clear();// clear boi vi noteChunks van giu cac con tro xoa de tranh tro vao cac vung nho loi
    Mix_CloseAudio(); // Dong toan bo he thong am thanh tranh ro ri
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
     noteSounds[note] = Mix_LoadWAV(filePath.c_str());
    if (noteSounds[note] == nullptr) {
        std::cerr << "Failed to load note sound effect: " << filePath << " SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}
 void AudioManager::playNoteChunk(NoteValue note){
    if (noteSounds[note] != nullptr) {
        Mix_PlayChannel(-1, noteSounds[note], 0);
    }
}
 bool AudioManager::loadCompleteSong(const std::string& filePath){
    completeSong = Mix_LoadMUS(filePath.c_str());
     if (completeSong == nullptr) {
        std::cerr << "Failed to load complete song: " << filePath << " SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
 }
void AudioManager::playCompleteSong(){
    if (completeSong != nullptr) {
          Mix_PlayMusic(completeSong,1);
    }
}



