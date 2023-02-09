# (Ver 2) Car BLE GPS

### Thông tin về App điều khiển

> ...

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
> Lưu ý, **Ver 2** chọn chế độ *"On change/touch"*.
>
> Ở chế độ này, khi [nhấn] các nút *"Điều khiển các hướng xe di chuyển"*, nó sẽ gửi kí tự của nút đó 1 lần.
>
> Luc này, nếu có thao tác với các nút khác vẫn được, nó chỉ đơn gửi các kí tự của những nút đó, thậm chí cả sự kết hợp của các nút điều khiển.
>
> Và khi [nhả] hoàn toàn các nút điều khiển, nó cũng sẽ gửi 1 kí tự `S` để cho dừng xe.

### Car (Uno) ↦ Phone (App)

> **Quy ước gói dữ liệu được gửi lên App:**
>
> Mỗi dữ liệu riêng lẻ được gửi ở định dạng `data;`.
>
> Các kí tự `;` đánh dấu sự kết thúc của luồng dữ liệu và giúp App *"phân biệt nội dung"* của mỗi luồng dữ liệu.
>
> Để gửi nhiều loại dữ liệu trong cùng 1 luồng, chúng ta phân tách từng dữ liệu bằng kí tự `,` *(không có khoảng trắng)* như sau `data_1,data_2,...,data_N;`.
>
> Hiện tại có tất cả **3 dạng** dữ liệu của GPS, mà Uno sẽ gửi lên App, tùy theo dữ liệu module GPS trả về Uno:
> - Gói dữ liệu (`NONE;`)
>   - Cho biết module GPS không có nhận được bất kì dữ liệu nào từ các vệ tinh cả.
>   - Lúc này ta sẽ cần kiểm tra tình trạng của module GPS hay dây kết nối của nó.
> - Gói dữ liệu (`INVALID;`)
>   - Cho biết các dữ liệu GPS gửi về ko hợp lệ, hay chưa xác định được vị trí.
>   - Lúc này có thể là do module GPS đang trong vùng cản sóng, nên ko bắt được tín hiệu với các vệ tinh, hoặc kết nối Anten có vấn đề, ...
> - Gói dữ liệu (`lat,lng;`)
>   - Cho biết giá trị **Vĩ độ (Latitude)** và **Kinh độ (Longitude)** hiện tại mà module GPS lấy được.

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

## Các vấn đề có thể xử lý nâng cấp thêm cho Version sau.