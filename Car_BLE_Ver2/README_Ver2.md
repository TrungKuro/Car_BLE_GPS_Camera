# (Ver 2) Car BLE GPS

## Thông tin về App điều khiển (đang phát triển...)

### Phone (App) ↦ Car (Uno)

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
> **Ver 2** chọn chế độ *"On change/touch"*.

### Car (Uno) ↦ Phone (App)

> **Quy ước gói dữ liệu được gửi lên App:**
>
> Mỗi dữ liệu riêng lẻ được gửi ở định dạng `data;`.
>
> Các kí tự `;` đánh dấu sự kết thúc của luồng dữ liệu và giúp App phân biệt giữa các *"phiên bản khác nhau"* của cùng một dữ liệu.
>
> Để gửi nhiều loại dữ liệu, chúng ta phân tách từng dữ liệu bằng kí tự `,` *(không có khoảng trắng)* như sau `data_1,data_2,...,data_N;`.

> **Ứng dụng gửi cặp dữ liệu Vĩ độ (Latitude) và Kinh độ (Longitude)**:
> - Cặp dữ liệu mỗi lần gửi (`lat,lng;`)

## Thiết bị Bluetooth sử dụng: [JDY-33](https://hshop.vn/products/mach-thu-phat-bluetooth-dual-mode-3-0-spp-ble-4-2-jdy-33-hc-05-hc-06-compatible).

> **Bộ tập lệnh AT**, *Baudrate Default: (9600, N, 8, 1)* và sau các lệnh AT cần thêm *\r\n*.

> **Lưu ý:** Cần cấu hình cho thiết bị BLE trước khi sử dụng. Và khi kết nối BLE với App, chọn thiết bị có tên đặt theo lệnh *AT+NAME*.
> - AT+NAME (Name Setting) : JDY-Car-SPP = `AT+NAMEJDY-Car-SPP`.
> - AT+NAMB (BLE Name Setting) : JDY-Car-BLE = `AT+NAMBJDY-Car-BLE`.
> - AT+PIN (Pin Setting - password) : 3333 = `AT+PIN3333`.
> - AT+BAUD (UART Baudrate Setting) : 115200 bps = `AT+BAUD8`.

> **Sơ đồ chân kết nối JDY-33 với bo Arduino Uno.**
> - VCC <---> 5V
> - GND <---> GND
> - TXD <---> `D2 (RX)`
> - RXD <---> `D3 (TX)`

> **Nội dung truyền:** Khi mới bắt đầu kết nối giữa App và Bluetooth. Đây là nội dung đầu tiên JDY nhận được. Cũng như trước khi bị ngắt kết nối hoàn toàn.
>
> ---
>
> +CONNECTING<<xx:xx:xx:xx:xx:xx\r\n
>
> CONNECTED\r\r\n
>
> SSS...SSSD+DISC:SUCCESS\r\r\n
>
> ---

## Thiết bị GPS sử dụng: [ATGM336H](https://hshop.vn/products/mach-gps-bds-atgm336h).

> **Sử dụng thư viện Arduino:** `TinyGPSPlus` by [mikalhart](https://github.com/mikalhart/TinyGPSPlus).
>
> **Lưu ý:** Cần cấu hình cho thiết bị GPS trước khi sử dụng. Và các lệnh cấu hình dưới đây đều có kí tự kết thúc `\r\n`.
>
> **CAS01:** Cài đặt tốc độ Baudrate.
> - `$PCAS01,5*19` : 115200bps
>
> **CAS03:** Cài đặt yêu cầu thêm hoặc dừng dữ liệu đầu ra các *"câu NMEA"*.
> - `$PCAS03,0,1,0,0,0,0,0,0,0,0,,,0,0*03` : Chỉ lấy dữ liệu GLL.
>
> **Sơ đồ chân kết nối ATGM336H với bo Arduino Uno.**
> - VCC <---> 3.3V
> - GND <---> GND
> - TX <---> `D11 (RX)`
> - RX <---> `D12 (TX)`
> - PPS <---> *none*

## Giao tiếp qua UART, sử dụng thư viện [SoftwareSerial](https://docs.arduino.cc/learn/built-in-libraries/software-serial).

> **Ưu điểm:**
> - Có thể có tạo nhiều cổng *"Software Serial"* với tốc độ lên tới 115200 bps.
>
> **Nhược điểm:**
> - Nó không thể truyền và nhận dữ liệu cùng một lúc.
> - Nếu sử dụng nhiều cổng *"Software Serial"*, mỗi lần chỉ có một cổng có thể nhận dữ liệu.
> - Không phải tất cả các chân trên bo Mega, Genuino, Leonardo, Micro đều hỗ trợ các ngắt thay đổi!