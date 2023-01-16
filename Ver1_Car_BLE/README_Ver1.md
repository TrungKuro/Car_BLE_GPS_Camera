# Car BLE GPS Camera

## (Ver 1) Car BLE

### Thông tin App "Bluetooth RC Controller" - by Andi.Co

> **Điều khiển các hướng xe di chuyển.**
> - Button UP : **(F)** - Forward
>   - UP + LEFT : **(G)** - Forward Left
>   - UP + RIGHT : **(I)** - Forward Right
> - Button DOWN : **(B)** - Back
>   - DOWN + LEFT : **(H)** - Back Left
>   - DOWN + RIGHT : **(J)** - Back Right
> - Button LEFT : **(L)** - Left
> - Button RIGHT : **(R)** - Right
>
> **Khi người dùng ko thực hiện bất kì thao tác điều khiển xe nào trên App, xe sẽ đứng yên.**
> - Stop - **(S)**
>
> **Trước khi bị ngắt kết nối, đây là kí tự cuối cùng xe nhận được.**
> - Stop All - **(D)**

> **Điều khiển phần tốc độ của xe.**
> - Speed 0% : **(0)**
> - Speed 10% : **(1)**
> - Speed 20% : **(2)**
> - Speed 30% : **(3)**
> - Speed 40% : **(4)**
> - Speed 50% : **(5)**
> - Speed 60% : **(6)**
> - Speed 70% : **(7)**
> - Speed 80% : **(8)**
> - Speed 90% : **(9)**
> - Speed 100% : **(q)**

> **Điều khiển đèn xe phía trước.**
> - Front Lights On : **(W)**
> - Front Lights Off : **(w)**

> **Điều khiển đèn xe phía sau.**
> - Back Lights On : **(U)**
> - Back Lights Off : **(u)**

> **Điều khiển còi xe.**
> - Horn On : **(V)**
> - Horn Off : **(v)**

> **Điều khiển phần cảnh báo trên xe.**
> - Extra On : **(X)**
> - Extra Off : **(x)**

> **Cài đặt tần suất truyền của dữ liệu.**
> - Continuous Stream (every 50 ms)
> - On change/touch
>
> **Ver 1** chọn chế độ *"Continuous Stream"*.
>
> Chế độ này có điểm lợi giúp xe biết khi vượt quá phạm vi BLE, sau *50ms* ko nhận được tín hiệu sẽ tự động dừng xe lại.

### Thiết bị Bluetooth sử dụng: [JDY-33](https://hshop.vn/products/mach-thu-phat-bluetooth-dual-mode-3-0-spp-ble-4-2-jdy-33-hc-05-hc-06-compatible).

> **Quy chuẩn một số cấu hình trên thiết bị Bluetooth.**
> - AT+NAME (Name Setting) : JDY_Car
> - AT+NAMB (BLE Name Setting) : JDY_Car_BLE
> - AT+PIN (Pin Setting - password) : 1234
> - AT+BAUD (UART Baudrate Setting) : 9600 bps
>
> **Bộ tập lệnh AT**, lưu ý *Baudrate Default: (9600, N, 8, 1)* và sau các lệnh AT cần thêm *\r\n*.

> **Lưu ý:** khi kết nối BLE với App, chọn thiết bị có tên đặt theo lệnh *AT+NAME*.
>
> Các Version sau có thể tăng độ lớn tốc độ Baudrate như *115200* hoặc cao hơn thế. Tuy nhiên, cần đảm bảo phần cứng giữa 2 bên đáp ứng nhau được. Bên cạnh mình sẽ ko dùng *SoftwareSerial* mà dùng cổng UART trực tiếp của bo Arduino.
>
> Tất nhiên để dùng được với phần cứng UART của bo Arduino. Mình cần thiết kế một shiled kết nối cho BLE với Arduino, kèm *1 jumper* để ngắt kết nối, cho phép thực hiện chức năng nạp code vào bo mạch.
>
> Thậm chí để phần điều khiển tín hiệu đến Driver nhanh hơn nữa. Mình có thể bỏ các lệnh *DigitalWrite* thay bằng việc can thiệp vào *Thanh ghi* trực tiếp của Vi điều khiển.

> **Sơ đồ chân kết nối JDY với bo Arduino Uno.**
> - VCC <---> 5V
> - GND <---> GND
> - TXD <---> D2 (RX)
> - RXD <---> D3 (TX)

### Driver sử dụng cho Motor: [L298](https://hshop.vn/products/mach-dieu-khien-dong-co-dc-l298).

> **Sơ đồ chân kết nối L298 với bo Arduino Uno.**
> - ENA <---> D10 (~PWM)
> - IN1 <---> D9
> - IN2 <---> D8
> - IN3 <---> D7
> - IN4 <---> D6
> - ENB <---> D5 (~PWM)
>
> Nhớ rút jumper cắm mặc định trên các chân *ENA* và *ENB* để sử dụng tính năng (~PWM).

> **Sơ đồ chân kết nối L298 với các Motor.**
> - OUT1 & OUT2 <---> **(FR)** & **(BR)**
> - OUT3 & OUT4 <---> **(FL)** & **(BL)**
>
> **Quy chuẩn vị trí các Motor.**
> - Front Left : **(FL)** - Bánh trước bên trái xe
> - Front Right : **(FR)** - Bánh trước bên phải xe
> - Back Left : **(BL)** - Bánh sau bên trái xe
> - Back Right : **(BR)** - Bánh sau bên phải xe
>
> **Sơ đồ chân kết nối L298 với nguồn pin.**
> - +12V : (+) 8,4V - Dùng 2 pin 18650
> - GND  : (-) 0V

### Đèn LED trước của xe: [LED](https://hshop.vn/products/mach-led-don-mkl-m01-10mm-single-led-module).

> **Sơ đồ chân kết nối LED Trước với bo Arduino Uno.**
> - SIG : A0 - LED trước bên phải
> - SIG : A1 - LED trước bên trái
> - 5V : 5V
> - GND : GND
>
> Kích HIGH để On và LOW để Off.

### Đèn LED sau của xe: [LED](https://hshop.vn/products/mach-led-don-mkl-m01-10mm-single-led-module).

> **Sơ đồ chân kết nối LED Sau với bo Arduino Uno.**
> - SIG : A2 - LED sau bên phải
> - SIG : A3 - LED sau bên trái
> - 5V : 5V
> - GND : GND
>
> Kích HIGH để On và LOW để Off.

### Còi trên xe: [Buzzer](https://hshop.vn/products/mach-buzzer-5v).

> **Sơ đồ chân kết nối Buzzer với bo Arduino Uno.**
> - VCC : 5V
> - I/O : A4
> - GND : GND
>
> Kích HIGH để On và LOW để Off.

### Các vấn đề có thể xử lý nâng cấp thêm cho Version sau.

Khi bị mất kết nối (ra ngoài phạm vi, sóng yếu nhiễu, ...) hoặc ngắt kết nối (người dùng tự Disconnect, lỏng dây nguồn, ...) Bluetooth, xe phải dừng hết tất cả mọi hoạt động lại.

Khi mới bắt đầu kết nối giữa App và Bluetooth. Đây là nội dung đầu tiên JDY nhận được. Cũng như trước khi bị ngắt kết nối hoàn toàn:
>+CONNECTING<<xx:xx:xx:xx:xx:xx\r\n
>
>CONNECTED\r\r\n
>
>SSS...SSSD+DISC:SUCCESS\r\r\n

Có thể thấy, trước khi ngắt kết nối hoàn toàn, App sẽ gửi kí tự 'D' và loạt thông tin phía sau. Mình cần xử lý các chuỗi thông tin này, để khi App bắt đầu đi vào hoạt động sẽ nhận đúng các dữ liệu cần thiết mà thôi!
