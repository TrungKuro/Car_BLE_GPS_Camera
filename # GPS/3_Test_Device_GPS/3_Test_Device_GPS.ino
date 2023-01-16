/* Code này cũng test với thư viện "TinyGPSPlus"
** Tuy nhiên lần này là kết nối với thiết bị GPS thực tế
**
** Trong đoạn code này, dữ liệu GPS mà mình quan tâm là [Kinh độ & Vĩ độ]
** Code nó có qua 2 lớp kiểm tra
**
** Thứ nhất, nếu sau 5s mà vẫn chưa nhận được bất kì kí tự nào từ GPS để xử lý
** Chương trình sẽ báo "NONE"
**
** Thứ hai, nếu đã nhận được data GPS truyền đến rồi
** Nó sẽ xử lý data. Tuy nhiên, nếu data ko hợp lệ, chương trình sẽ báo "INVALID"
*/
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

static const int RXPin = 11, TXPin = 12;
static const uint32_t GPSBaud = 115200;

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);

  Serial.println(F("Begin read data GPS: \"Latitude,Longitude;\""));
  Serial.println();
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.print(F("NONE;")); // No GPS detected: check wiring.
    while (true)
      ;
  }
}

void displayInfo()
{
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    Serial.print(F(";"));
  }
  else
  {
    Serial.print(F("INVALID;")); // Giá trị nhận được ko hợp lệ.
  }

  Serial.println();
}