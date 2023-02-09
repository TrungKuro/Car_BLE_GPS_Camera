/* Đoạn code này, mình test giao tiếp giữa GPS và BLE
**
** Trong đó module GPS giao tiếp với UNO qua Software Serial
** Còn module BLE giao tiếp với UNO qua Hardware Serial
**
** Code này sẽ nhận dữ liệu từ GPS gửi xuống
** Sau đó giải mã lấy thông tin cần thiết và cho gửi lên BLE
*/

/* Dữ liệu GPS Raw mẫu:
**
** $GNRMC,125711.000,V,,,,,,,110123,,,N*52
** $GNRMC,125712.000,V,,,,,,,110123,,,N*51
** $GNRMC,125713.000,V,,,,,,,110123,,,N*50
**
** $GNRMC,085105.000,A,1046.39983,N,10639.40257,E,0.00,36.89,110123,,,A*4F
** $GNRMC,085106.000,A,1046.39984,N,10639.40257,E,0.00,36.89,110123,,,A*4B
** $GNRMC,085107.000,A,1046.39984,N,10639.40257,E,0.00,36.89,110123,,,A*4A
*/

#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

#define RX_GPS 2
#define TX_GPS 3

#define BAUD_GPS 9600

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RX_GPS, TX_GPS);

void setup()
{
  Serial.begin(115200);
  ss.begin(BAUD_GPS);
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available())
  {
    if (gps.encode(ss.read()))
    {
      displayInfo();
    }
  }

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
}
