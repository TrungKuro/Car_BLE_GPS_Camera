/* ------------------------------------------------------------------------- */
/*                                  LIBRARY                                  */
/* ------------------------------------------------------------------------- */

#include "Control_Car_BLE_GPS.h"
#include "Pin_Connect.h"

#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

/* ------------------------------------------------------------------------- */
/*                                  VARIABLE                                 */
/* ------------------------------------------------------------------------- */

TinyGPSPlus gps;                      // Tạo đối tượng "TinyGPSPlus"
SoftwareSerial myGPS(RX_GPS, TX_GPS); // Giao tiếp giữa Arduino với GPS

SoftwareSerial myBLE(RX_BLE, TX_BLE); // Giao tiếp giữa Arduino với Bluetooth
char blue = 0;                        // Biến nhận dữ liệu qua bluetooth
bool enable = false;                  // Cho phép hoặc ko xử lý dữ liệu nhận được
String data = "";                     // Để xử lý các thông tin dạng văn bản

/*
** "speed" là tốc độ quay Motor, đơn vị %, với độ phân giải 10%
** "power" là công suất cấp cho Motor, đơn vị ~pwm, từ 0 - 255
*/
// byte speed = 50; // Biến nhận giá trị tốc độ, mặc định mới khởi động là 50%
byte power = POWER_50_PER; // Biến cung cấp công suất cho Motor

bool ledFront = false;
bool ledBack = false;
bool buzzer = false;

/* Các biến thực hiện chức năng cảnh báo! */
bool warning = false;
bool half = true;
unsigned long now;    // Unit (ms)
#define ONE_CYCLE 500 // Unit (ms)

/* ------------------------------------------------------------------------- */
/*                                   CONFIG                                  */
/* ------------------------------------------------------------------------- */

void setup()
{
  DEBUG_BEGIN(115200);
  myGPS.begin(BAUD_GPS);
  myBLE.begin(BAUD_BLE);

  pinMode(MOTOR_R_IN1, OUTPUT);
  pinMode(MOTOR_R_IN2, OUTPUT);
  pinMode(MOTOR_L_IN3, OUTPUT);
  pinMode(MOTOR_L_IN4, OUTPUT);

  pinMode(LED_FRONT_LEFT, OUTPUT);
  pinMode(LED_FRONT_RIGHT, OUTPUT);
  pinMode(LED_BACK_LEFT, OUTPUT);
  pinMode(LED_BACK_RIGHT, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  // power = convert_speed_to_power(speed);

  turn_off_LED_front();
  turn_off_LED_back();
  turn_off_buzzer();
}

/* ------------------------------------------------------------------------- */
/*                                  FUNCTION                                 */
/* ------------------------------------------------------------------------- */

void processedGPS()
{
  if (gps.location.isValid())
  {
    DEBUG_PRINT(gps.location.lat(), 6);
    DEBUG_PRINT(F(","));
    DEBUG_PRINT(gps.location.lng(), 6);
    DEBUG_PRINT(F(";"));

    // Gửi data lên App
    myGPS.print(gps.location.lat(), 6);
    myGPS.print(",");
    myGPS.print(gps.location.lng(), 6);
    myGPS.print(";");
  }
  else
  {
    DEBUG_PRINT(F("INVALID;"));

    myGPS.print("INVALID;"); // Gửi data lên App
  }
}

/* ------------------------------------------------------------------------- */

void processedBLE()
{
  switch (blue)
  {
  case 'S':
    stop_car();
    break; // Dừng xe (ko làm gì cả)

  case 'F':
    go_forward(power);
    break; // Xe đi về phía trước (chiều dọc)
  case 'B':
    back_forward(power);
    break; // Xe đi lùi về phía sau (chiều dọc)

  case 'L':
    turn_CCW(power);
    break; // Xe quay ngược chiều đồng hồ (CCW)
  case 'R':
    turn_CW(power);
    break; // Xe quay chiều đồng hồ (CW)

  case 'G':
    go_left_forward(power);
    break; // Xe đi thẳng về phía trái
  case 'I':
    go_right_forward(power);
    break; // Xe đi thẳng về phía phải

  case 'H':
    back_left_forward(power);
    break; // Xe đi lùi về phía trái
  case 'J':
    back_right_forward(power);
    break; // Xe đi lùi về phía phải

    // speed = (?); power = convert_speed_to_power(speed);

  case '0':
    power = POWER_0_PER;
    break;
  case '1':
    power = POWER_10_PER;
    break;
  case '2':
    power = POWER_20_PER;
    break;
  case '3':
    power = POWER_30_PER;
    break;
  case '4':
    power = POWER_40_PER;
    break;
  case '5':
    power = POWER_50_PER;
    break;
  case '6':
    power = POWER_60_PER;
    break;
  case '7':
    power = POWER_70_PER;
    break;
  case '8':
    power = POWER_80_PER;
    break;
  case '9':
    power = POWER_90_PER;
    break;
  case 'q':
    power = POWER_100_PER;
    break;

  case 'W':
    ledFront = true;
    turn_on_LED_front();
    break; // Bật đèn trước
  case 'w':
    ledFront = false;
    turn_off_LED_front();
    break; // Tắt đèn trước

  case 'U':
    ledBack = true;
    turn_on_LED_back();
    break; // Bật đèn sau
  case 'u':
    ledBack = false;
    turn_off_LED_back();
    break; // Tắt đèn sau

  case 'V':
    buzzer = true;
    turn_on_buzzer();
    break; // Bật còi xe
  case 'v':
    buzzer = false;
    turn_off_buzzer();
    break; // Tắt còi xe

  case 'X':
    warning = true;
    now = millis();
    break; // Bật cảnh báo
  case 'x':
    warning = false;
    half = true;
    (ledFront) ? (turn_on_LED_front()) : (turn_off_LED_front());
    (ledBack) ? (turn_on_LED_back()) : (turn_off_LED_back());
    (buzzer) ? (turn_on_buzzer()) : (turn_off_buzzer());
    break; // Tắt cảnh báo

  /* Stop All */
  case 'D':
    stop_car();
    turn_off_LED_front();
    ledFront = false;
    turn_off_LED_back();
    ledBack = false;
    turn_off_buzzer();
    buzzer = false;
    warning = false;
    enable = false;
    DEBUG_PRINTLN(F("NOT"));
  }
}

/* ------------------------------------------------------------------------- */
/*                                    MAIN                                   */
/* ------------------------------------------------------------------------- */

void loop()
{
  /* XỬ LÝ DỮ LIỆU TỪ GPS */
  while (myGPS.available() > 0)
  {
    if (gps.encode(myGPS.read()))
    {
      processedGPS(); // Hàm xử lý data GPS
    }
  }

  /* XỬ LÝ DỮ LIỆU TỪ BLUETOOTH */
  if (myBLE.available() > 0) // Nếu có dữ liệu gửi về thì đọc
  {
    blue = myBLE.read();

    if (enable)
    {
      processedBLE(); // Hàm xử lý data BLE
    }
    else
    {
      data += blue;

      if (blue == '\n') // Chỉ xét 'data' mỗi khi gặp kí tự kết thúc này
      {
        DEBUG_PRINTLN(data);
        if (data == "CONNECTED\r\r\n")
        {
          DEBUG_PRINTLN(F("OK"));
          enable = true;
        }
        data = "";
      }
    }
  }

  /* XỬ LÝ CHẠY ĐỒNG BỘ ĐÈN, CÒI, MOTOR */
  if (warning && (millis() - now >= ONE_CYCLE))
  {
    if (half)
    {
      turn_on_LED_front();
      turn_on_buzzer();
      half = false;
    }
    else
    {
      turn_off_LED_front();
      turn_off_buzzer();
      half = true;
    }
    now = millis();
  }
}
