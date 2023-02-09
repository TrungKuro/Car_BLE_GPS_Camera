/* Code này test thử phần giao tiếp giữa Uno và module BLE
** Trong đó Uno khi có dữ liệu của GPS sẽ gửi qua BLE lên App mỗi giây
*/

#define BAUD_BLE 115200

unsigned long lastTime = 0;
char c;

void setup()
{
  Serial.begin(BAUD_BLE);
}

void loop()
{
  while (Serial.available()) // App gửi về Uno qua BLE
  {
    c = Serial.read(); // Uno làm gì đó với dữ liệu này
  }

  if (millis() - lastTime >= 1000UL)
  {
    lastTime = millis();

    Serial.print("ddmm.mmmmmm,dddmm.mmmmmm;"); // Uno gửi lên App qua BLE
  }
}
