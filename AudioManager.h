#ifndef AUDIOMANAGER
#define AUDIOMANAGER

#include<SDL.h>
#include<SDL_mixer.h>
#include <string>
#include<vector>
 using namespace std;
class AudioManager {
public:
    AudioManager();
    ~AudioManager();

    bool loadMusic(const string& file);
    void playMusic();
    void stopMusic();
    int getBPM() const;
     bool loadNoteChunks(const vector<string>& files);
    void playRandomNoteChunk();
     void setMusicVolume(int volume);
private:
    Mix_Music* music;
    std::vector<Mix_Chunk*> noteChunks; // Thay đổi biến này
    int bpm;  // Nhịp độ bài nhạc
};
#endif // AUDIOMANAGER
