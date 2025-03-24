#ifndef POSITION_H
#define POSITION_H
class Position{
  private:
      int x, y;
  public:
     //Ham khoi tao voi gia tri mac dinh
      Position(int x_=0, int y_=0);

      // Ham lay toa do x
      int getx() const;

      //ham lay toa do y
      int gety() const;

      //Kiem tra vi tri
      bool isInsideBox(int left,int top,int width,int height );

};
#endif // POSITION
