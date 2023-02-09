#include <SoftwareSerial.h>

#define rxPin 2
#define txPin 3

// Set up a new SoftwareSerial object
SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);

char c;

void setup()
{
  Serial.begin(115200); // Hardware Serial

  // Define pin modes for TX and RX
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  mySerial.begin(115200); // Software Serial
}

void loop()
{
  /* --> Hard --> Uno --> Soft */
  // if (Serial.available() > 0)
  // {
  //   c = Serial.read();

  //   mySerial.print(c);
  // }

  /* --> Soft --> Uno --> Hard */
  // if (mySerial.available() > 0)
  // {
  //   c = mySerial.read();

  //   Serial.print(c);
  // }

  /* ----------------------------------------------------------------------- */

  // if (Serial.availableForWrite() > 0)
  // {
  //   c = Serial.read();
  //   mySerial.print(c);
  // }
  // if (mySerial.availableForWrite() > 0)
  // {
  //   c = mySerial.read();
  //   Serial.print(c);
  // }

  /* ----------------------------------------------------------------------- */

  while (Serial.available())
  {
    c = Serial.read();
    mySerial.print(c);
  }
  while (mySerial.available())
  {
    c = mySerial.read();
    Serial.print(c);
  }
}