#ifndef AUDIOMANAGER
#define AUDIOMANAGER

#include<SDL.h>
#include<SDL_mixer.h>
#include <string>
#include<vector>
 using namespace std;
class AudioManager {
public:
    AudioManager(); // Ham khoi tao dung de thiet lap SDL_mixer
    ~AudioManager(); // Ham huy dung de giai phong tai nguyen

    bool loadMusic(const string& file);
    void playMusic();
    void stopMusic();
    //int getBPM() const;
     bool loadNoteChunks(const vector<string>& files);
    void playRandomNoteChunk();
     void setMusicVolume(int volume); // Dieu chinh am luong cua nhac nen
private:
    Mix_Music* music; // Luu tru file nhac nen
    std::vector<Mix_Chunk*> noteChunks;// Luu am thanh tung not nhac
    //int bpm;  // Nhịp độ bài nhạc
};
#endif // AUDIOMANAGER
