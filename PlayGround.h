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
    NOTE_H,
    NOTE_K,
    NOTE_Q,
    GOLD_NOTE // Thêm loại nốt vàng
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
 int score;//them bien diem so
 int width, height; //Kich thuoc san choi
 GameStatus status; //Trang thai game
 std::vector<std::vector<CellType>> squares; //vector 2 chieu luu tru trang thai cua cac o
 std::vector<Note> notes; //Vecto luu tru vi tri cua cac not nhac
 bool gameRun; //Kiem tra game con chay ko
 Note targetNote;
 bool isGuiding = true;
 Uint32 guideStartTime;
 Uint32 guideDuration = 10000; // 3 giây
 Uint32 sequenceStartTime; // Thời điểm bắt đầu chuỗi nốt nhạc
 Uint32 sequenceTimeLimit = 10000; // 10 giây (có thể điều chỉnh)

 // Biến mới cho chế độ bản giao hưởng
 bool isSymphonyMode = false; // Kiểm tra có đang ở chế độ bản giao hưởng không
 Uint32 symphonyStartTime = 0; // Thời điểm bắt đầu bản giao hưởng
 const Uint32 SYMPHONY_TIME_LIMIT = 30000; // 50 giây (50000ms)
 int goldNotesEaten = 0; // Số nốt vàng đã ăn
 const int GOLD_NOTES_REQUIRED = 20; // Số nốt vàng cần ăn để chiến thắng
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
    //bool goldTime();
    Note getTargetNote () ;
    NoteValue getNoteSequence(int index);
     int currentNoteIndex = 0;// de theo doi chi so cua  not nhac trong 1 chuoi cac not nhac
     int NUM_NOTES = 25 ;
     NoteValue noteSequence[5] = {NOTE_C, NOTE_D, NOTE_E, NOTE_F, NOTE_G};
     bool isNoteGuiding() const { return isGuiding; }
    Uint32 getGuideStartTime() const { return guideStartTime; }
    Uint32 getGuideDuration() const { return guideDuration; }
    void setGuiding(bool guiding) { isGuiding = guiding; }
    void setGuideStartTime(Uint32 time) { guideStartTime = time; }
    void startNewSequence();
    Uint32 getSequenceStartTime() const { return sequenceStartTime; }
    Uint32 getSequenceTimeLimit() const { return sequenceTimeLimit; }
    int getScore() const{ return score;};
    void addScore(int points) { score += points;};
    void resetScore() { score = 0;}//Reset diem khi bat dau lai game

    //Hàm mới cho chế độ bản giao hưởng
    void startSymphonyMode();
    void endSymphonyMode();
    bool isInSymphonyMode() const { return isSymphonyMode; }
    bool setIsSymphonyMode(bool mode) { isSymphonyMode=mode;};
    Uint32 getSymphonyStartTime() const { return symphonyStartTime; }
    Uint32 getSymphonyTimeLimit() const { return SYMPHONY_TIME_LIMIT; }
    int getGoldNotesEaten() const { return goldNotesEaten; }
    void incrementGoldNotesEaten() { goldNotesEaten++; }
    void resetGoldNotesEaten() { goldNotesEaten = 0; }
    int getGoldNotesRequired() const { return GOLD_NOTES_REQUIRED; }
    void checkSymphonyStatus();
};
#endif // PLAYGROUND_H

