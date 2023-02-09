/* Thử nghiệm giao tiếp Serial UART
** Hardware Serial (NHẬN) - dùng cổng USB của bo Arduino
** Software Serial (GỬI) - dùng mạch chuyển UART TTL
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
//   if (mySerial.available() > 0)
//   {
//     c = mySerial.read();

//     Serial.print(c);
//   }
// }

/* ------------------------------------------------------------------------- */

/* Không thể dùng 2 Software Serial cùng lúc
** Nó chỉ lấy cái khởi tạo gần nhất sử dụng thôi
**
** Chỉ Soft-Serial (2) mới gửi được lên Hard-Serial
** Còn Soft-Serial (1) thì ko được
**
** @ Nói đúng hơn, Soft-Serial ko thể xử lý nhận kí tự cùng lúc
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
  // if (mySerial_1.available() > 0)
  // {
  //   c = mySerial_1.read();

  //   Serial.print("1: ");
  //   Serial.println(c);
  // }

  // if (mySerial_2.available() > 0)
  // {
  //   c = mySerial_2.read();

  //   Serial.print("2: ");
  //   Serial.println(c);
  // }

  /* ----------------------------------------------------------------------- */

  while (mySerial_1.available())
  {
    c = mySerial_1.read();

    Serial.print("1: ");
    Serial.println(c);
  }

  while (mySerial_2.available())
  {
    c = mySerial_2.read();

    Serial.print("2: ");
    Serial.println(c);
  }
}
