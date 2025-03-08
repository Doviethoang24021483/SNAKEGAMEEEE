 //#include<iostream>
 //#include<chrono>
 //#include<SDL.h>
 //#include "SDL_utils.h"
 //#define CLOCK_NOW chrono::system_clock::now
 //typedef chrono::duration<double> ElapsedTime;
 //const double STEP_DELAY = 0.5;// pham vi toan cuc, truy cap dc moi noi trong ma cua ban
 //const int BOARD_WIDTH = 30;
 //const int BOARD_HEIGHT = 20;
 //void renderSplashScreen();
 //void renderGamePlay(Painter&, const PlayGround& playGround);
 //void renderGameOver(Painter&, const PlayGround& playGround);
 //UserInput interpretEvent(SDL_Event e);
 //void updateRankingTable(const PlayGround& playGround);
 //Game //Lop dieu khien logic cua game
 //Userinput//cachanhdongcuanguoichoi
// enum UserInput{
   // NO_INPUT = 0,
   // KEY_UP,KEY_DOWN,KEY_LEFT,_KEY_RIGHT
// };
 //int main(int argc, char* argv[])
 //{
 //   SDL_Window* window;
 //   SDL_Renderer* renderer;
//    initSDL(window, renderer);
 // Your drawing code here
 // use SDL_RenderPresent(renderer) to show it
    //*/ Khoi tao
    //1. Hien thi man hinh chao khi bat dau tro choi
    //2. Tao man hinh tro choi voi kich thuoc (chieu rong,chieucao)xac dinh.
     //Khoi tao cac bien quan trong nhu vi tri ban dau cua ran,thuc an,diemso
   // */ Vong lap chinh
    // vong lap vo tan lap di lap lai cho den khi tro choi ket thuc
    // nhan dau vao tu nguoi choi(vi du: phim mui ten, nut dieu khien)
    // Thay doi huong di chuyen cua ran dua tren dau vao cua nguoi choi
    // Kiem tra xem da den thoi diem de ran di chuyen 1 buoc chua
      // Thuc hien cac hanh dong can thiet de di chuyen tro choi sang trang thai tiep
         // Di chuyen ran theo huong hien tai .Than ran theo sau dau
         // Tao thuc an(cherry) ngau nhien tren man hinh
    // Xoa man hinh cu va ve lai cac thanh phan cua tro choi ( bao gom ca ran) o vi tri
    // trong moi khung hinh de tao cam giac chuyen dong
    // Luu thoi diem hien tai
   //  renderSplashScreen();
// Game game(BOARD_WIDTH, BOARD_HEIGHT);//Tao mot doi tuong game thuoc lop Game .lop nay co
 //kha nang chua tat ca cac logic va du lieu cua tro choi(vi tri ran, thuc an, kich thuoc bang)
 //SDL_Event e;// Luu tru cac su kien tu SDl
 //renderGamePlay(renderer, game);// Ve trang thai ban dau cua tro choi len man hinh
 //auto start = CLOCK_NOW();
 //while (game.isRunning()) {
 //   while (SDL_PollEvent(&e) != 0) {//Kiem tra xem co su kien nao tu nguoi dung hay khong.Neu co no luu tru sk vao e va tra ve khac 0
    //    interpretEvent(e); // Ham nay dien giai su kien va thuc hien cac hanh dong tuong ung (vi du doi hg di chuyen cua ran)
   // } // non-blocking event detection
    // game logic here
 //   auto end = CLOCK_NOW();// Luu thoi diem hien tai, phai dc lay truoc khi cap nhat trang thai.
// ElapsedTime elapsed = end-start;// thoi gian troi qua
 //if (elapsed.count() > STEP_DELAY) {//so voi 1 gt hang so de xem co can di chuyen buoc nua chx
 //   game.nextStep();//Goij ham next step cua doi tuong game.Ham thuc hien viec di chuyen tro sang trang thai tiep
 //   renderGamePlay(renderer, game);//ve lai trang thai tro choi len man hinh
 //   start = end;//cap nhat start bang end
 //   SDL_Delay(1);// Tam dung chuong trinh trong 1miligiay giam tai CPU vi SDL_POLLEvent tieu thu nhieu tai nguyen
    // to prevent high CPU usage because of SDL_PollEvent()
 //}
 //renderGameOver(renderer, game);//Hien thi man hinh ket thuc tro choi
 //updateRankingTable(playGround);//Cap nhat bang xep hang

  //  waitUntilKeyPressed();
  //  quitSDL(window, renderer);
// return 0;
// }#include <iostream>
#include <SDL.h>
#include "SDL_utils.h"
#include "PlayGround.h"
using namespace std;

int main(int argc, char* argv[]) {
    SDL_Window* window ;
    SDL_Renderer* renderer ;
    initSDL(window, renderer);
    int WIDTH=20;
    int HEIGHT =20;
    PlayGround playGround(WIDTH, HEIGHT);

    // In thử trạng thái sân chơi
    for (int y = 0; y < playGround.getHeight(); ++y) {
        for (int x = 0; x < playGround.getWidth(); ++x) {
            Position pos(x, y);
              cout << playGround.getCellState(pos) << " ";
        }
        cout << endl;
    }

    quitSDL(window, renderer);
    return 0;
}
