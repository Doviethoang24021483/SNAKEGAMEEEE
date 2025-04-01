// AudioManager.h
#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H
#include <SDL_mixer.h>
#include <map>
#include"PlayGround.h"

class AudioManager {
private:
    Mix_Music* music;
    Mix_Chunk* failChunk;
    Mix_Chunk* completeSong;
    std::map<NoteValue, Mix_Chunk*> noteChunks;
    Mix_Chunk* goldNoteSound; // Âm thanh cho nốt vàng
public:
    AudioManager();
    ~AudioManager();
    bool loadMusic(const std::string& path);
    bool loadFailChunk(const std::string& path);
    bool loadNoteChunk(NoteValue note, const std::string& path);
    bool loadCompleteSong(const std::string& path);
    bool loadGoldNoteSound(const std::string& path); // Thêm hàm mới
    void playMusic();
    void stopMusic();
    void setMusicVolume(int volume);
    void playFailChunk();
    void playNoteChunk(NoteValue note);
    void playCompleteSong();
    void playGoldNoteSound(); // Thêm hàm mới
};
#endif
