#ifndef  PLAYGROUND_H
#define  PLAYGROUND_H
#include <vector>
#include "Position.h"
#include <SDL.h>

//Dinh nghia cac loai o co the co tren san choi
enum CellType{
 CELLEMPTY,  //O TRONG
 CELLSNAKE   //O RAN
};

//Dinh nghia cac trang thai GAME
enum GameStatus{
 GAMERUNNING, // GAME DANG CHAY
 GAMEWON,     // GAME CHIEN THANG
 GAMELOST,    // GAME THUA
 GAMESTOP     // GAME DUNG
};

//Dinh nghia cac loai not nhac
enum NoteValue {
    NOTE_C,
    NOTE_D,
    NOTE_E,
    NOTE_F,
    NOTE_G,
    NOTE_H,
    NOTE_K,
    NOTE_Q,
    GOLD_NOTE  // NOT VANG O SYMPHONY
};


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

 int score;             //diem so
 int width, height;     //Kich thuoc san choi
 GameStatus status;     //Trang thai game
 std::vector<std::vector<CellType>> squares;     //vector 2 chieu luu tru trang thai cua cac o
 std::vector<Note> notes;                        //Vecto luu tru cac not nhac
 bool gameRun;                                   //Kiem tra game con chay ko
 Note targetNote;
 bool isGuiding = true;                          //Co dang rung not nhac ko
 Uint32 guideStartTime;                          // Thoi gian bat dau huong dan rung
 Uint32 guideDuration =10000;                   // miligiay
 Uint32 sequenceStartTime;                       // Thời điểm bắt đầu chuỗi nốt nhạc
 Uint32 sequenceTimeLimit = 10000;               // 10 giây (có thể điều chỉnh)

 // Cho chế độ bản giao hưởng
 bool isSymphonyMode = false;                    // Kiểm tra có đang ở chế độ bản giao hưởng không
 Uint32 symphonyStartTime = 0;                   // Thời điểm bắt đầu bản giao hưởng
 const Uint32 SYMPHONY_TIME_LIMIT = 30000;       // 30 giây (30000ms)
 int goldNotesEaten = 0;                         // Số nốt vàng đã ăn
 const int GOLD_NOTES_REQUIRED = 20;             // Số nốt vàng cần ăn để chiến thắng
public:

    PlayGround(int width_, int height_);

    int getWidth() const;                    //Ham tra ve chieu rong san choi
    int getHeight() const;                   //Ham tra ve chieu dai san choi

    CellType getCellType(Position pos);                        // Ham tra ve trang thai cua 1 o tai vi tri xd
    CellType changeCellType(CellType type, Position pos );     // Ham thay doi trang thai o tren san choi

    bool isGameRun() const;                                    // Kiem tra game con chay ko
    void stopGame();                                           // Ham ket thuc game
    void setGameRun(bool run);                                 // Dat lai trang thai chay cua game

    const std::vector<Note>& getNotes() const;                  // Ham tra ve vi tri va gia tri cua cac not nhac
    void generateNotes(const std::vector<Position>& snakeBody); // Ham sinh ngau nhien cac not nhac
    void generateNewNote(const std::vector<Position>& snakeBody);  // Ham sinh ngau nhien not nhac moi
    void removeNote(Note note);                                    // Xoa not nhac
    Note getTargetNote () ;                                        // tra ve not nhac tang toc do
    NoteValue getNoteSequence(int index);                          //Tra ve gia tri note trong chuoi nhac
    int currentNoteIndex = 0;                                                // de theo doi chi so cua  not nhac trong 1 chuoi cac not nhac
    int NUM_NOTES = 25 ;                                                     //Tong cac note nhac
     NoteValue noteSequence[5] = {NOTE_C, NOTE_D, NOTE_E, NOTE_F, NOTE_G};   //Gia tri lan luot cua 1 chuoi note nhac khi o trang thai binh thuong
     bool isNoteGuiding() const { return isGuiding; }                        //Kiem tra xem co dang rung note nhac ko
    Uint32 getGuideStartTime() const { return guideStartTime; }              //Tra ve thoi gian bat dau rung note nhac
    Uint32 getGuideDuration() const { return guideDuration; }                //Tra ve gioi han thoi gian rung note nhac
    void setGuiding(bool guiding) { isGuiding = guiding; }                   //Dat lai thoi trang thai rung note nhac
    void setGuideStartTime(Uint32 time) { guideStartTime = time; }           //Dat lai thoi gian rung note nhac
    void startNewSequence();                                                 //Bat dau chuoi note nhac
    Uint32 getSequenceStartTime() const { return sequenceStartTime; }        //Tra ve thoi gian bat dau chuoi note nhac
    Uint32 getSequenceTimeLimit() const { return sequenceTimeLimit; }        //Tra ve gioi han an note nhac dung
    int getScore() const{ return score;};                                    //Tra ve diem so
    void addScore(int points) { score += points;};                           //Cong them diem
    void resetScore() { score = 0;}                                          //Reset diem khi bat dau lai game

    //Cho chế độ bản giao hưởng
    void startSymphonyMode();                                                //Ham bat dau ban giao huong
    void endSymphonyMode();                                                  //Ham ket thuc ban giao huong
    bool isInSymphonyMode() const { return isSymphonyMode; }                 //Ham tra kiem tra trang thai giao huong
    bool setIsSymphonyMode(bool mode) { isSymphonyMode=mode;};               //Dat lai trang thai ban giao huong
    Uint32 getSymphonyStartTime() const { return symphonyStartTime; }        //Tra ve thoi gian bat dau ban giao huong
    Uint32 getSymphonyTimeLimit() const { return SYMPHONY_TIME_LIMIT; }      //Tra ve gioi han thoi gian ban giao huong
    int getGoldNotesEaten() const { return goldNotesEaten; }                 //Tra ve so not nhac da an
    void incrementGoldNotesEaten() { goldNotesEaten++; }                     //Tang so not da an
    void resetGoldNotesEaten() { goldNotesEaten = 0; }                       //Dat lai so note da an
    int getGoldNotesRequired() const { return GOLD_NOTES_REQUIRED; }         //Tra ve so not can an
    void checkSymphonyStatus();                                              //Xu li ket thuc giao huong bat dau lai binh thuong hay chien thang hay thua



    void reset();                                                            //Dat lai trang thai game
};
#endif // PLAYGROUND_H
