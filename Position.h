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

      //Ham tra ve doi tuong Position moi voi x da thay doi
      Position setx(int newx) const;

      //Ham tra ve doi tuong Position moi voi y da thay doi
      Position sety(int newy) const;

      //Kiem tra xem vi tri co nam trong hcn
      bool isInsideBox(int left,int top,int width,int height );

      //In ra vi tri
      void disPlay() const;
};
#endif // POSITION
