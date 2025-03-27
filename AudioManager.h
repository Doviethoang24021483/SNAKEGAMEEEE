#ifndef AUDIOMANAGER
#define AUDIOMANAGER

#include<SDL.h>
#include<SDL_mixer.h>
#include <string>
#include<vector>
#include "PlayGround.h"
 using namespace std;
class AudioManager {
public:
    AudioManager(); // Ham khoi tao dung de thiet lap SDL_mixer
    ~AudioManager(); // Ham huy dung de giai phong tai nguyen

    bool loadMusic(const string& file);
    void playMusic();
    void stopMusic();
    //int getBPM() const;
     //bool loadNoteChunks(const vector<string>& files);
    //void playRandomNoteChunk();
     void setMusicVolume(int volume); // Dieu chinh am luong cua nhac nen
     bool loadFailChunk( const string& file);
     void playFailChunk();
     bool loadNoteChunk(NoteValue note, const std::string& filePath);
    void playNoteChunk(NoteValue note);
    bool loadCompleteSong(const std::string& filePath);
    void playCompleteSong();
private:
    Mix_Music* music; // Luu tru file nhac nen
    std::vector<Mix_Chunk*> noteChunks;// Luu am thanh tung not nhac
     Mix_Chunk* failChunk;
     Mix_Chunk* noteSounds[5];
    Mix_Music* completeSong;
};
#endif // AUDIOMANAGER
