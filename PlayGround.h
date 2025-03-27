#ifndef PLAYGROUND_H
#define PLAYGROUND_H
#include  <vector>
#include "Position.h"
#include<SDL.h>

//Dinh nghia cac loai o co the co tren san choi
enum CellType{
 CELLEMPTY,
 CELLSNAKE,
 CELLCHERRY
};

//Dinh nghia cac trang thai co the co
enum GameStatus{
 GAMERUNNING,
 GAMEWON,
 GAMELOST,
 GAMESTOP
};
enum NoteValue {
    NOTE_C,
    NOTE_D,
    NOTE_E,
    NOTE_F,
    NOTE_G,
    NUM_NOTE_VALUES // Important: Keep this at the end
};

//Kich thuoc o( co the se thay doi)
struct CellSize {
    int width;
    int height;
};

struct Note {
    Position position;
    NoteValue value;
};
class PlayGround {
private:
 int diemso;
 int width, height; //Kich thuoc san choi
 GameStatus status; //Trang thai game
 std::vector<std::vector<CellType>> squares; //vector 2 chieu luu tru trang thai cua cac o
 std::vector<Note> notes; //Vecto luu tru vi tri cua cac not nhac
 bool gameRun; //Kiem tra game con chay ko
 Uint32 lastGoldTime; //Luu thoi diem bat dau thoi gian vang
 bool isGoldTime;   // Trang thai dang trong thoi gian vang
 Note targetNote;
 bool isGuiding = true;
    Uint32 guideStartTime;
    Uint32 guideDuration = 3000; // 3 giây
public:
    PlayGround(int width_=0, int height_=0); // Khoi tao san choi voi kich thuoc mac dinh la 0 0

    int getWidth() const; //Ham tra ve chieu rong san choi
    int getHeight() const; //Ham tra ve chieu dai san choi

    CellType getCellType(Position pos); // Ham tra ve trang thai cua 1 o tai vi tri xd
    CellType changeCellType(CellType type, Position pos ); // Ham thay doi trang thai o tren san choi

    bool isGameRun() const; // Kiem tra game con chay ko
    void stopGame(); // Ham ket thuc game
    void setGameRun(bool run); // Dat lai trang thai chay cua game

    const std::vector<Note>& getNotes() const; // Ham tra ve vi tri cua cac not nhac
    void generateNotes(const std::vector<Position>& snakeBody); // Ham sinh ngau nhien 10 not nhac
    void generateNewNote(const std::vector<Position>& snakeBody);  // Ham sinh ngau nhien not nhac moi
    void removeNote(Note note); // Xoa not nhac
    bool goldTime();
    Note getTargetNote () ;
    NoteValue getNoteSequence(int index);
     int currentNoteIndex = 0;// de theo doi chi so cua  not nhac trong 1 chuoi cac not nhac
     int NUM_NOTES = 40 ;
     NoteValue noteSequence[NUM_NOTE_VALUES] = {NOTE_C, NOTE_D, NOTE_E, NOTE_F, NOTE_G};
     bool isNoteGuiding() const { return isGuiding; }
    Uint32 getGuideStartTime() const { return guideStartTime; }
    Uint32 getGuideDuration() const { return guideDuration; }
    void setGuiding(bool guiding) { isGuiding = guiding; }
    void setGuideStartTime(Uint32 time) { guideStartTime = time; }
};
#endif // PLAYGROUND_H

