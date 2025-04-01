#ifndef EFFECTMANAGER_H // Ngăn chặn việc include file nhiều lần
#define EFFECTMANAGER_H

#include <SDL.h> // Include thư viện SDL
#include <vector> // Include thư viện vector để lưu trữ các hạt
#include <cstdlib> // Cấp phát số ngẫu nhiên
#include <cmath>   //Tính toán hình học
// Định nghĩa cấu trúc dữ liệu cho một hạt
struct Particle {
    float x, y;       // Vị trí của hạt (tọa độ x và y)
    float vx, vy;     // Vận tốc của hạt (thành phần x và y)
    int lifetime;   // Thời gian tồn tại của hạt (số frame)
    SDL_Color color;  // Màu sắc của hạt (đỏ, xanh lá, xanh dương, độ trong suốt)
};

class EffectManager {
public:
    // Hàm khởi tạo
    EffectManager(SDL_Renderer* renderer); // Truyền vào một SDL_Renderer để vẽ các hiệu ứng
    // Hàm hủy
    ~EffectManager(); // Giải phóng bộ nhớ khi đối tượng bị hủy

    // Hàm tạo hiệu ứng ăn nốt nhạc
    void createEatEffect(int x, int y); // Truyền vào vị trí (x, y) của nốt nhạc bị ăn
    void createSparkleEffect(int x, int y); // Hiệu ứng lấp lánh cho nốt vàng (mới)
    // Hàm cập nhật trạng thái của tất cả các hiệu ứng
    void updateEffects();

    // Hàm vẽ tất cả các hiệu ứng lên màn hình
    void drawEffects();

private:
    SDL_Renderer* renderer; // Con trỏ đến SDL_Renderer để vẽ
    std::vector<Particle> particles; // Vector để lưu trữ danh sách các hạt trong hiệu ứng
};

#endif // EFFECTMANAGER_H
