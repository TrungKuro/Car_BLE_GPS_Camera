# (Ver 3) Car BLE GPS

- Module Bluetooth.
- Module GPS.
- Module Driver.
- Module LED.
- Module Buzzer.

## Thông tin về App điều khiển

> ...

### Phone (App) == Bluetooth ==> Car (Uno)

> **Quy ước gói dữ liệu từ App gửi xuống:**
>
> Mỗi **lệnh CMD** riêng lẻ được gửi ở định dạng `$cmd\n`, trong đó:
> - `$` là kí tự bắt đầu lệnh.
> - *"cmd"* là nội dung lệnh CMD.
> - `\n` là kí tự kết thúc lệnh, mã HEX (0x0A).
>
> Đây là danh sách các **lệnh CMD** hiện có ở phiên bản hiện tại:
> - `$speed\n`.
> - `$enterGPS\n`.
> - `$exitGPS\n`.

> **Điều khiển các hướng xe di chuyển.**
> - Button UP : `F` - Forward
>   - UP + LEFT : `G` - Forward Left
>   - UP + RIGHT : `I` - Forward Right
> - Button DOWN : `B` - Back
>   - DOWN + LEFT : `H` - Back Left
>   - DOWN + RIGHT : `J` - Back Right
> - Button LEFT : `L` - Left
> - Button RIGHT : `R` - Right
>
> **Khi người dùng ko thực hiện bất kì thao tác điều khiển xe nào trên App, xe sẽ đứng yên.**
> - Stop - `S`
>
> **Trước khi bị ngắt kết nối, đây là kí tự cuối cùng xe nhận được.**
> - Stop All - `D`

> **Điều khiển phần tốc độ của xe.**
> - Speed 0% : `0`
> - Speed 10% : `1`
> - Speed 20% : `2`
> - Speed 30% : `3`
> - Speed 40% : `4`
> - Speed 50% : `5`
> - Speed 60% : `6`
> - Speed 70% : `7`
> - Speed 80% : `8`
> - Speed 90% : `9`
> - Speed 100% : `q`
>
> Ở lần kết nối Bluetooth đầu tiên, hoặc những lần kết nối lại. App nên gửi lệnh `$speed\n` để nhận được thông số **Speed** *"tốc độ"* mà đang thiết lập trên xe.

> **Điều khiển đèn xe phía trước.**
> - Front Lights On : `W`
> - Front Lights Off : `w`

> **Điều khiển đèn xe phía sau.**
> - Back Lights On : `U`
> - Back Lights Off : `u`

> **Điều khiển còi xe.**
> - Horn On : `V`
> - Horn Off : `v`

> **Điều khiển phần cảnh báo trên xe.**
> - Extra On : `X`
> - Extra Off : `x`

> **Cài đặt tần suất truyền của dữ liệu.**
> - Continuous Stream *(every 50 ms)*
> - On change/touch
>
> Lưu ý, **Ver 3** chọn chế độ *"On change/touch"*.
>
> Ở chế độ này, khi [nhấn] các nút *"Điều khiển các hướng xe di chuyển"*, nó sẽ gửi kí tự của nút đó 1 lần.
>
> Lúc này, nếu có thao tác với các nút khác vẫn được, nó chỉ đơn giản gửi các kí tự của những nút đó, thậm chí cả sự kết hợp của các nút điều khiển.
>
> Và khi [nhả] hoàn toàn các nút *"Điều khiển các hướng xe di chuyển"*, nó sẽ gửi 1 kí tự `S` để cho dừng xe.

> ---

> **Chế độ test GPS.**
>
> Lệnh này dành cho nhà phát triển App. Khi App gửi lệnh `$enterGPS\n`, bo Arduino Uno sẽ vào chế độ giả lập GPS.
>
> Trong chế độ này, xe sẽ hoàn toàn đứng yên, không nhận bất cứ tín hiệu điều khiển nào. Lúc này, xe chỉ đơn thuần gửi các *"dữ liệu giả"* của GPS về cho App qua Bluetooth.
>
> Để thoát khỏi chế độ này, App cần gửi lệnh `$exitGPS\n`.

### Car (Uno) == Bluetooth ==> Phone (App)

> **Quy ước gói dữ liệu được gửi lên App:**
>
> Mỗi dữ liệu riêng lẻ được gửi ở định dạng `data;`.
>
> Các kí tự `;` đánh dấu sự kết thúc của luồng dữ liệu và giúp App *"phân biệt nội dung"* của mỗi luồng dữ liệu.
>
> Để gửi nhiều loại dữ liệu trong cùng 1 luồng, chúng ta phân tách từng dữ liệu bằng kí tự `,` *(không có khoảng trắng)* như sau `data_1,data_2,...,data_N;`.

> Hiện tại có tất cả **3 dạng** dữ liệu của GPS, mà Uno sẽ gửi lên App, tùy theo dữ liệu module GPS trả về Uno:
> - Gói dữ liệu (`NONE;`)
>   - Cho biết module GPS không có nhận được bất kì dữ liệu nào từ các vệ tinh cả.
>   - Lúc này ta sẽ cần kiểm tra tình trạng của module GPS hay dây kết nối của nó.
> - Gói dữ liệu (`INVALID;`)
>   - Cho biết các dữ liệu GPS gửi về ko hợp lệ, hay chưa xác định được vị trí.
>   - Lúc này có thể là do module GPS đang trong vùng cản sóng, nên ko bắt được tín hiệu với các vệ tinh, hoặc kết nối Anten có vấn đề, ...
> - Gói dữ liệu (`lat,lng;`)
>   - Trong đó `lat` cho biết giá trị **Vĩ độ (Latitude)** và `lng` cho biết giá trị **Kinh độ (Longitude)** hiện tại mà module GPS lấy được.
>   - Vd: **10.773323,106.656741;**
>   - |
>   - Ngoài ra, gói dữ liệu này cũng có thể dùng trong *"chế độ test GPS"*. Khi xe bắt đầu gửi những *"dữ liệu GPS giả"* đến App.
>   - Xe sẽ gửi trước gói (`ENTER_GPS;`) cho App biết nó đã vào chế độ này, và cho đến khi nào nó gửi gói (`EXIT_GPS;`) cho App biết đã thoát khỏi chế độ này.

> ---

> - Gói dữ liệu (`SPEED,num;`)
>   - Trong đó `SPEED` cho App biết giá trị tiếp theo là *"tốc độ"* mà đang thiết lập trên xe, để hiển thị thanh trượt tốc độ tương ứng trên giao diện của App.
>   - Với đơn vị **%**, `num` có thể là một trong số các giá trị sau: `0`, `10`, `20`, `30`, `40`, `50`, `60`, `70`, `80`, `90`, `100`.

## Thiết bị Bluetooth sử dụng: [JDY-33](https://hshop.vn/products/mach-thu-phat-bluetooth-dual-mode-3-0-spp-ble-4-2-jdy-33-hc-05-hc-06-compatible).

### Bộ tập lệnh AT

> **Baudrate Default** - *"Tốc độ truyền mặc định"* của **JDY-33** ban đầu là `(9600, N, 8, 1)` và sau mỗi lệnh AT có thêm các kí tự kết thúc là `\r\n`.

### Cấu hình module Bluetooth

> **Lưu ý,** cần cấu hình cho module Bluetooth trước khi sử dụng theo cấu hình sau:
> - AT+NAME (Name Setting) : JDY-Car-SPP = `AT+NAMEJDY-Car-SPP`.
> - AT+NAMB (BLE Name Setting) : JDY-Car-BLE = `AT+NAMBJDY-Car-BLE`.
> - AT+PIN (Pin Setting - password) : 3333 = `AT+PIN3333`.
> - AT+BAUD (UART Baudrate Setting) : 115200 bps = `AT+BAUD8`.
>
> Và khi cho kết nối Bluetooth với App, chọn thiết bị trong danh sách có tên đặt theo lệnh *AT+NAME*.

### Sơ đồ chân kết nối JDY-33 với bo Arduino Uno

> - VCC <---> 5V
> - GND <---> GND
> - TXD <---> `D0 (RX)`
> - RXD <---> `D1 (TX)`
>
> **Lưu ý,** module Bluetooth đang sử dụng các chân *"Hardware Serial"* của bo Arduino Uno. Cho nên mỗi khi nạp code cho bo Arduino, cần ngắt kết nối với module Bluetooth.

### Nội dung truyền

> Khi mới bắt đầu thực hiện kết nối Bluetooth giữa App và **JDY-33**. Đây là nội dung đầu tiên bo **Uno** nhận được (nhờ qua **JDY-33**), cũng như trước khi bị ngắt kết nối hoàn toàn.
>
>     +CONNECTING<<xx:xx:xx:xx:xx:xx\r\n
>     CONNECTED\r\r\n
>     ...D
>     +DISC:SUCCESS\r\r\n

## Thiết bị GPS sử dụng: [ATGM336H](https://hshop.vn/products/mach-gps-bds-atgm336h).

> **Sử dụng thư viện Arduino:** `TinyGPSPlus` by [mikalhart](https://github.com/mikalhart/TinyGPSPlus).

### Cấu hình module GPS

> **Lưu ý,** cần cấu hình cho module GPS trước khi sử dụng theo cấu hình sau...
>
> Và sau mỗi câu lệnh cấu hình dưới đây đều có thêm các kí tự kết thúc là `\r\n`.
>
> **CAS01** - Cài đặt tốc độ Baudrate.
> - `$PCAS01,1*1D` : 9600bps
>
> **CAS03** - Cài đặt yêu cầu thêm hoặc dừng dữ liệu đầu ra các *"câu NMEA"*.
> - `$PCAS03,0,0,0,0,1,0,0,0,0,0,,,0,0*03` : Chỉ lấy dữ liệu RMC.

### Sơ đồ chân kết nối ATGM336H với bo Arduino Uno

> - VCC <---> 3.3V
> - GND <---> GND
> - TX <---> `D2 (RX)`
> - RX <---> `D3 (TX)`
> - PPS <---> *none*
>
> **Lưu ý,** module GPS đang sử dụng các chân bình thường của bo Arduino Uno. Vậy nên mình cần cấu hình các chân này để biến nó thành chuẩn UART cho việc giao tiếp giữa bo Uno và module GPS.

### Sử dụng thư viện [SoftwareSerial](https://docs.arduino.cc/learn/built-in-libraries/software-serial).

> **Ưu điểm:**
> - Có thể có tạo nhiều cổng *"Software Serial"* với tốc độ lên tới **115.200 bps**.
>
> **Nhược điểm:**
> - Nó không thể truyền và nhận dữ liệu cùng một lúc.
> - Nếu sử dụng nhiều cổng *"Software Serial"*, mỗi lần chỉ có một cổng có thể nhận dữ liệu.
> - Không phải tất cả các chân trên bo Mega, Genuino, Leonardo, Micro đều hỗ trợ các ngắt thay đổi!

## Thiết bị Driver sử dụng: [L298](https://hshop.vn/products/mach-dieu-khien-dong-co-dc-l298).

### Sơ đồ chân kết nối L298 với bo Arduino Uno

> - ENA <---> `D10` *(~PWM)*
> - IN1 <---> `D9`
> - IN2 <---> `D8`
> - IN3 <---> `D7`
> - IN4 <---> `D6`
> - ENB <---> `D5` *(~PWM)*
>
> Nhớ rút jumper cắm mặc định trên các chân **ENA** và **ENB** để sử dụng tính năng *(~PWM)*.

### Sơ đồ chân kết nối L298 với Nguồn pin

> - +12V <---> (+) 8,4V - Dùng 2 pin 18650
> - GND  <---> (-) 0V

### Quy chuẩn tên gọi các Motor lắp trên khung xe

> - Front Left : **(FL)** - Bánh trước bên trái xe.
> - Front Right : **(FR)** - Bánh trước bên phải xe.
> - Back Left : **(BL)** - Bánh sau bên trái xe.
> - Back Right : **(BR)** - Bánh sau bên phải xe.

### Sơ đồ chân kết nối L298 với các Motor

> - OUT1 & OUT2 <---> **(FR)** & **(BR)**
> - OUT3 & OUT4 <---> **(FL)** & **(BL)**

## Thiết bị LED sử dụng: [LED](https://hshop.vn/products/mach-led-don-mkl-m01-10mm-single-led-module).

### Sơ đồ chân kết nối "LED trước" với bo Arduino Uno

> - SIG <---> `A0` - LED trước bên phải
> - SIG <---> `A1` - LED trước bên trái
> - 5V <---> 5V
> - GND <---> GND
>
> Kích HIGH để On và LOW để Off.

### Sơ đồ chân kết nối "LED sau" với bo Arduino Uno

> - SIG <---> `A2` - LED sau bên phải
> - SIG <---> `A3` - LED sau bên trái
> - 5V <---> 5V
> - GND <---> GND
>
> Kích HIGH để On và LOW để Off.

## Thiết bị Buzzer sử dụng: [Buzzer](https://hshop.vn/products/mach-buzzer-5v).

### Sơ đồ chân kết nối Buzzer với bo Arduino Uno

> - VCC <---> 5V
> - I/O <---> `A4`
> - GND <---> GND
>
> Kích HIGH để On và LOW để Off.