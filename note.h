#ifndef NOTE_H
#define NOTE_H
#include<string>
using namespace std;

class Note{
 private:
     int x,y;
     string name;
 public:
    Note(int x_, int y_, string name_);
    int getX() const;
    int getY() const;
    string getName() const;
};

#endif
