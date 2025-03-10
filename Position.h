#ifndef POSITION_H
#define POSITION_H
class Position{
  private:
      int x, y;
  public:
     //Ham khoi tao voi gia tri mac dinh
      Position(int x_=0, int y_=0);
      //Kiem tra xem vi tri co nam trong san ko
      int getx() const;
      int gety() const;
      int setx(int newx) ;
      int sety(int newy) ;
      bool isInsideBox(int left,int right,int width,int height );
      //In ra vi tri
      void disPlay() const;
};
#endif // POSITION
