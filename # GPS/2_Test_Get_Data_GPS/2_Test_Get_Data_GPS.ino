// Phần code này mình sẽ mô phỏng quá trình hoạt động lấy data GPS, và cho gửi về phone qua BLE
#include <TinyGPSPlus.h>

/* Ban đầu chuỗi chưa có bất kì giá trị nào --- Phải trả về "#GPS\n"
 ** Sau đó chuỗi đã có giá trị rồi, nhưng thông tin sai --- Phải trả về "#SIG\n"
 ** Cuối cùng, khi đã ổn định, lúc này chuỗi sẽ có thông tin đúng --- Phải trả về cặp giá trị Kinh độ, Vĩ độ
 */
const char *gpsStream = " "
                        "$GNGGA,125711.000,,,,,0,00,25.5,,,,,,*7B\r\n"
                        "$GNGGA,085106.000,1046.39984,N,10639.40257,E,1,15,0.8,13.2,M,0.0,M,,*41\r\n";

TinyGPSPlus gps;

void setup()
{
  Serial.begin(115200);

  Serial.println(F("Test data raw of ATGM336H"));
  Serial.println();

  getInfoGPS();

  Serial.println();
  Serial.println(F("Done."));
}

void loop()
{
}

void getInfoGPS()
{
  while (*gpsStream)
  {
    /* Biến trỏ chuỗi "gpsStream", mình sẽ cho nhận chuỗi mới, cứ mỗi chu kì 1s
     ** Sau đó đưa vào hàm "encode()" để check có data GPS ko?
     **
     ** Nếu ko có thì trả về chuỗi với nội dung "#GPS\n"
     ** Điều này có nghĩa là ta cần kiểm tra phần cứng module GPS
     ** Nó có thể bị chết, bị mất nguồn, bị lỏng dây, bị cắm sai dây, ...
     **
     ** Ngược lại thì cho xử lý chuỗi để hiển thị thông tin GPS
     */
    if (gps.encode(*gpsStream++))
    {
      /* Xử lý nội dung trong trỏ chuỗi "gpsStream"
       ** Ở nhu cầu hiện tại, mình chỉ cần thông tin giá trị Kinh độ và Vĩ độ
       **
       ** Vậy nên, nếu giá trị trong chuỗi ko hợp lệ
       ** Thì sẽ trả về chuỗi với nội dung "#SIG\n"
       ** Điều này có nghĩa là module GPS vẫn chưa kết nối đến được các vệ tinh hoàn toàn
       ** Nguyên nhân có thể là đang ở trong khu vực cản sóng như trong nhà, hay dùng anten có độ lợi nhỏ
       ** Hay công suất khuếch đại yếu, hay lỏng kết nối anten, hay chưa đủ thời gian để khởi động, ...
       **
       ** Ngược lại thì cho ra chuỗi data đã xử lý thôi "#0.000000,0.000000"
       ** Chuỗi này là nội dung của cặp [Latitude (Vĩ độ) , Longitude (Kinh độ)]
       **
       ** @@@ Quy ước luôn, các thông tin mà do [Bo Arduino] gửi về [Phone] qua Bluetooth
       ** @@@ Nó là một chuỗi data
       ** @@@ Với kí tự bắt đầu chuỗi là '#'
       ** @@@ Và kí tự kết thúc chuỗi là '\n'
       ** @@@ Còn nội dung dữ liệu nằm giữa chuỗi này
       */
      if (gps.location.isValid())
      {
        Serial.print("#");
        Serial.print(gps.location.lat(), 6);
        Serial.print(",");
        Serial.print(gps.location.lng(), 6);
        Serial.print("\n");
      }
      else
      {
        Serial.print("#SIG\n");
      }
    }
    else
    {
      Serial.print("#GPS\n");
    }
  }
}