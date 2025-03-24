#include<iostream>
#include "AudioManager.h"
using namespace std;

AudioManager::AudioManager() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) { //khoi tao he thong am thanh
        std::cerr << "SDL_mixer init failed: " << Mix_GetError() << std::endl;
    }
    music = nullptr;//tranh tro vao vung nho da giai phong
    //bpm = 120;
}

AudioManager::~AudioManager() {
    if (music) {
        Mix_FreeMusic(music);
        music = nullptr;//Dam bao ko tro vao vung nho da giai phong
    }
    // Giải phóng tất cả các chunk
    for (Mix_Chunk* chunk : noteChunks) {
        Mix_FreeChunk(chunk);
    }
    noteChunks.clear();// clear boi vi noteChunks van giu cac con tro xoa de tranh tro vao cac vung nho loi
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

bool AudioManager::loadNoteChunks(const std::vector<std::string>& files) {
    noteChunks.clear(); // Xóa các chunk cũ trước khi tải mới

    for (const std::string& file : files) {
        Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
        if (!chunk) {
            std::cerr << "Failed to load chunk: " << file << " Error: " << Mix_GetError() << std::endl;
            // Giải phóng các chunk đã tải trước đó
            for (Mix_Chunk* loadedChunk : noteChunks) {
                Mix_FreeChunk(loadedChunk);
            }
            noteChunks.clear();
            return false;
        }
        noteChunks.push_back(chunk);
    }
    return true;
}

void AudioManager::playRandomNoteChunk() {
    if (!noteChunks.empty()) {
        int randomIndex = rand() % noteChunks.size(); // Chọn ngẫu nhiên một chunk
        Mix_PlayChannel(-1, noteChunks[randomIndex], 0);
    }
}

void AudioManager::setMusicVolume(int volume) {
    if (volume < 0) volume = 0;
    if (volume > MIX_MAX_VOLUME) volume = MIX_MAX_VOLUME;
    Mix_VolumeMusic(volume);//thay doi am thanh nhac nen
}




