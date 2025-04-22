# RedmiGame

Chào mừng bạn đến với **RedmiGame**, một trò chơi rắn săn mồi kết hợp âm nhạc! 🐍🎵 Game được phát triển bằng C++ sử dụng thư viện SDL2, mang đến trải nghiệm thú vị với chế độ Giao hưởng (Symphony Mode) độc đáo.

## Giới thiệu game

Trong **RedmiGame**, bạn sẽ điều khiển một con rắn di chuyển trên màn hình để ăn các nốt nhạc. Mỗi nốt nhạc bạn ăn đúng sẽ tăng điểm số, và nếu bạn ăn đủ một chuỗi nốt nhạc theo đúng thứ tự, bạn sẽ kích hoạt **Chế độ Giao hưởng**. Trong chế độ này, bạn cần thu thập 20 nốt vàng trong vòng 50 giây để chiến thắng. Hãy cẩn thận để không đâm vào tường hoặc thân rắn, nếu không game sẽ kết thúc!

### Tính năng nổi bật

- **Chơi rắn cổ điển**: Điều khiển rắn bằng phím mũi tên để ăn các nốt nhạc.
- **Nốt nhạc**: Ăn các nốt nhạc theo đúng thứ tự để tiến bộ.
- **Chế độ Giao hưởng**: Thu thập 20 nốt vàng trong 50 giây để giành chiến thắng.
- **Hiệu ứng âm thanh**: Tận hưởng âm thanh khi ăn nốt, thất bại, hoặc hoàn thành chuỗi nốt.
- **Hiệu ứng hình ảnh**: Hiệu ứng lấp lánh và ăn nốt làm game thêm sinh động.
- **Hệ thống điểm số**: Nhận điểm khi ăn nốt và hoàn thành chuỗi nốt.

## Cài đặt

Để chơi **RedmiGame**, bạn cần biên dịch mã nguồn trên máy tính của mình. Hãy làm theo các bước sau:

### Yêu cầu

- **Trình biên dịch C++**: g++ hoặc bất kỳ trình biên dịch C++ nào (ví dụ: MinGW cho Windows, GCC cho Linux/Mac).
- **Thư viện SDL2**:
  - SDL2
  - SDL2_image
  - SDL2_ttf
  - SDL2_mixer
- Cài đặt SDL2 trên hệ điều hành của bạn:
  - **Ubuntu/Linux**: Chạy lệnh `sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev`.
  - **Windows**: Tải thư viện SDL2 từ [libsdl.org](https://www.libsdl.org/) và liên kết chúng trong trình biên dịch.
  - **macOS**: Sử dụng Homebrew: `brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer`.

### Các bước cài đặt và chạy game

1. Tải mã nguồn từ repository:
git clone https://github.com/DovietHoang24021483/SNAKEGAMEEEE.git
cd SNAKEGAMEEEE

text

Sao chép
2. Biên dịch mã nguồn:
g++ -o RedmiGame main.cpp PlayGround.cpp Snake.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

text

Sao chép
- Nếu bạn dùng Windows, có thể cần chỉ định đường dẫn thư viện, ví dụ:
g++ -o RedmiGame main.cpp PlayGround.cpp Snake.cpp -I"đường/dẫn/đến/SDL2/include" -L"đường/dẫn/đến/SDL2/lib" -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

text

Sao chép
3. Chạy game:
./RedmiGame

text

Sao chép

## Cách chơi

- **Điều khiển**:
- Sử dụng **phím mũi tên** để điều khiển hướng rắn (Lên, Xuống, Trái, Phải).
- Nhấn **Enter** để chơi lại sau khi thắng hoặc thua.
- Nhấn **Escape** để thoát game.
- **Mục tiêu**:
- Ăn các nốt nhạc theo đúng thứ tự để tăng điểm.
- Hoàn thành chuỗi 5 nốt nhạc để kích hoạt **Chế độ Giao hưởng**.
- Trong Chế độ Giao hưởng, thu thập 20 nốt vàng trong 50 giây để chiến thắng.
- **Kết thúc game**:
- Game kết thúc nếu rắn đâm vào tường hoặc thân của chính nó.
- Trong Chế độ Giao hưởng, nếu không thu thập đủ 20 nốt vàng trong thời gian quy định, game sẽ quay lại chế độ thường.

## Cấu trúc dự án

- `main.cpp`: Vòng lặp game chính và khởi tạo game.
- `PlayGround.cpp`/`PlayGround.h`: Quản lý bàn chơi, nốt nhạc, và trạng thái game.
- `Snake.cpp`/`Snake.h`: Xử lý di chuyển, va chạm, và logic ăn nốt của rắn.
- `Renderer.h`: (Giả định) Vẽ game bằng SDL2.
- `AudioManager.h`: (Giả định) Quản lý âm thanh.
- `EffectManager.h`: (Giả định) Quản lý hiệu ứng hình ảnh.

## Hình ảnh minh họa

(TODO: Thêm hình ảnh minh họa gameplay tại đây.)

## Đóng góp

Nếu bạn muốn đóng góp vào dự án, hãy fork repository này, thực hiện cải tiến, và gửi pull request! Nếu bạn tìm thấy lỗi hoặc có gợi ý, vui lòng mở một issue.

## Giấy phép

Dự án này sử dụng **MIT License** - xem file LICENSE để biết thêm chi tiết.

## Lời cảm ơn

- Cảm hứng từ các game rắn cổ điển.
- Cảm ơn cộng đồng SDL2 đã cung cấp các thư viện tuyệt vời để phát triển game.
