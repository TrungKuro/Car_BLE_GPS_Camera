/* Thử nghiệm giao tiếp Serial UART
** Hardware Serial (GỬI) - dùng cổng USB của bo Arduino
** Software Serial (NHẬN) - dùng mạch chuyển UART TTL
**
** Hard-Serial Gửi ; Soft-Serial Nhận
**
** https://www.arduino.cc/reference/en/language/functions/communication/serial/
*/

// #include <SoftwareSerial.h>

// #define rxPin 2
// #define txPin 3

// // Set up a new SoftwareSerial object
// SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);

// char c;

// void setup()
// {
//   Serial.begin(115200); // Hardware Serial

//   // Define pin modes for TX and RX
//   pinMode(rxPin, INPUT);
//   pinMode(txPin, OUTPUT);

//   mySerial.begin(115200); // Software Serial
// }

// void loop()
// {
//   if (Serial.available() > 0)
//   {
//     c = Serial.read();

//     mySerial.print(c);
//   }
// }

/* ------------------------------------------------------------------------- */

/* Khi Hard-Serial khi nhận được dữ liệu
** Nó có thể gửi cùng lúc cho cả 2 Soft-Serial
**
** @ Nói đúng hơn, Soft-Serial có thể gửi tuần tự từng cổng riêng
*/

#include <SoftwareSerial.h>

#define rx_1 2
#define tx_1 3

#define rx_2 4
#define tx_2 5

// Set up a new SoftwareSerial object
SoftwareSerial mySerial_1 = SoftwareSerial(rx_1, tx_1);
SoftwareSerial mySerial_2 = SoftwareSerial(rx_2, tx_2);

char c;

void setup()
{
  Serial.begin(115200); // Hardware Serial

  // Define pin modes for TX and RX
  pinMode(rx_1, INPUT);
  pinMode(tx_1, OUTPUT);
  pinMode(rx_2, INPUT);
  pinMode(tx_2, OUTPUT);

  mySerial_1.begin(115200); // Software Serial 1
  mySerial_2.begin(115200); // Software Serial 2
}

void loop()
{
  if (Serial.available() > 0)
  {
    c = Serial.read();

    mySerial_1.println(c);
    mySerial_2.println(c);
  }
}