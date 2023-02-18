/* ------------------------------------------------------------------------- */
/*                                  LIBRARY                                  */
/* ------------------------------------------------------------------------- */

#include "Control_Car_BLE_GPS.h"

#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

/* ------------------------------------------------------------------------- */
/*                                  VARIABLE                                 */
/* ------------------------------------------------------------------------- */

TinyGPSPlus gps;                      // Tạo đối tượng "TinyGPSPlus"
SoftwareSerial myGPS(RX_GPS, TX_GPS); // Giao tiếp giữa Arduino với GPS

/* Serial - Giao tiếp giữa Arduino với Bluetooth */
char blue = 0;          // Biến nhận dữ liệu qua bluetooth
bool enableBLE = false; // Cho phép hoặc ko xử lý dữ liệu nhận được
String dataBLE = "";    // Để xử lý các thông tin dạng văn bản

/*
** "speed" là tốc độ quay Motor, đơn vị %, với độ phân giải 10%
** "power" là công suất cấp cho Motor, đơn vị ~pwm, từ 0 - 255
*/
byte power = POWER_50_PER; // Biến cung cấp công suất cho Motor, mặc định mới khởi động tốc độ là 50%

/*
** Các biến cho biết trạng thái làm việc của LED và Còi
** Mặc định khi khởi động tất cả thiết bị này đều tắt
*/
bool ledFront = false; // LED trước đang tắt
bool ledBack = false;  // LED sau đang tắt
bool buzzer = false;   // Còi đang tắt

/* Các biến thực hiện chức năng "cảnh báo" !!! */
bool modeWarn = false; // Đang tắt chức năng "cảnh báo" !!!
bool halfCycle = true;
unsigned long now;          // Unit (ms)
#define TIME_HALF_CYCLE 500 // Unit (ms)

/* Các biến thực hiện chức năng "Emulator GPS" */
bool emuGPS = false;          // Tắt chế độ giả lập GPS
float emuLatGPS = 10.773323;  // Giá trị ảo "vĩ độ" gốc
float emuLngGPS = 106.656741; // Giá trị ảo "kinh độ" gốc

/* ------------------------------------------------------------------------- */
/*                                   CONFIG                                  */
/* ------------------------------------------------------------------------- */

void setup()
{
  /* Bắt đầu kênh GPS */
  myGPS.begin(BAUD_GPS);

  /* Bắt đầu kênh Bluetooth */
  Serial.begin(BAUD_BLE);

  /* Tạo kết nối Motor, và dừng tất cả Motor */
  pinMode(MOTOR_R_IN1, OUTPUT);
  pinMode(MOTOR_R_IN2, OUTPUT);
  pinMode(MOTOR_L_IN3, OUTPUT);
  pinMode(MOTOR_L_IN4, OUTPUT);
  //
  stop_car();

  /* Tạo kết nối LED, và tắt tất cả LED */
  pinMode(LED_FRONT_LEFT, OUTPUT);
  pinMode(LED_FRONT_RIGHT, OUTPUT);
  pinMode(LED_BACK_LEFT, OUTPUT);
  pinMode(LED_BACK_RIGHT, OUTPUT);
  //
  turn_off_LED_front();
  turn_off_LED_back();

  /* Tạo kết nối Còi, và tắt Còi */
  pinMode(BUZZER, OUTPUT);
  turn_off_buzzer();
}

/* ------------------------------------------------------------------------- */
/*                                  FUNCTION                                 */
/* ------------------------------------------------------------------------- */

void processedGPS()
{
  if (gps.location.isValid())
  {
    // Giá trị GPS nhận được OK
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    Serial.print(F(";"));
  }
  else
  {
    Serial.print(F("INVALID;")); // Giá trị GPS nhận được ko hợp lệ
  }
}

void emulatorGPS()
{
  // Thay đổi giá trị GPS hiện tại (ngẫu nhiên)
  emuLatGPS += (random(0, 51) / 1000000.0);
  emuLngGPS += (random(0, 51) / 1000000.0);

  // Gửi giá trị GPS giả lập mới này đi
  Serial.print(emuLatGPS, 6);
  Serial.print(F(","));
  Serial.print(emuLngGPS, 6);
  Serial.print(F(";"));

  delay(1000);
}

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
    modeWarn = true;
    now = millis();
    break; // Bật cảnh báo
  case 'x':
    modeWarn = false;
    halfCycle = true;
    (ledFront) ? (turn_on_LED_front()) : (turn_off_LED_front());
    (ledBack) ? (turn_on_LED_back()) : (turn_off_LED_back());
    (buzzer) ? (turn_on_buzzer()) : (turn_off_buzzer());
    break; // Tắt cảnh báo

  case 'D':
    stop_car();
    turn_off_LED_front();
    ledFront = false;
    turn_off_LED_back();
    ledBack = false;
    turn_off_buzzer();
    buzzer = false;
    modeWarn = false;
    enableBLE = false;
    break; // Stop All

  /* Command ? */
  case '$':
    enableBLE = false; // Tạm thời tắt chức năng điều khiển xe, để nhận lệnh CMD
  }
}

/* ------------------------------------------------------------------------- */
/*                                    MAIN                                   */
/* ------------------------------------------------------------------------- */

void loop()
{
  /* XỬ LÝ DỮ LIỆU TỪ GPS */
  if (emuGPS)
  {
    emulatorGPS(); // Đang trong chế độ giả lập GPS
  }
  else
  {
    while (myGPS.available())
    {
      if (gps.encode(myGPS.read()))
      {
        processedGPS(); // Hàm xử lý data GPS
      }
    }
  }

  /* XỬ LÝ DỮ LIỆU TỪ BLUETOOTH */
  if (Serial.available()) // Nếu có dữ liệu gửi về thì đọc
  {
    blue = Serial.read();

    if (enableBLE)
    {
      processedBLE(); // Hàm xử lý data BLE
    }
    else
    {
      dataBLE += blue;

      if (blue == '\n') // Chỉ xét 'data' mỗi khi gặp kí tự kết thúc này
      {
        /* Quá trình kết nối BLE thành công */
        if (dataBLE == "CONNECTED\r\r\n")
        {
          enableBLE = true; // Bắt đầu có thể nhận lệnh điều khiển xe
        }

        /* Lệnh CMD - gửi giá trị tốc độ hiện tại của xe */
        if (dataBLE == "speed\n")
        {
          Serial.print(convert_power_to_speed(power));
          enableBLE = true; // Quay lại chế độ nhận lệnh điều khiển xe
        }

        /* Lệnh CMD - vào chế độ giả lập GPS */
        if (dataBLE == "enterGPS\n")
        {
          emuGPS = true;
        }

        /* Lệnh CMD - thoát chế độ giả lập GPS */
        if (dataBLE == "exitGPS\n")
        {
          emuGPS = false;
          enableBLE = true; // Quay lại chế độ nhận lệnh điều khiển xe
        }

        dataBLE = "";
      }
    }
  }

  /* XỬ LÝ CHẠY ĐỒNG BỘ ĐÈN, CÒI, MOTOR */
  if (modeWarn)
  {
    if (millis() - now >= TIME_HALF_CYCLE)
    {
      now = millis();

      if (halfCycle)
      {
        turn_on_LED_front();
        turn_on_buzzer();
        halfCycle = false;
      }
      else
      {
        turn_off_LED_front();
        turn_off_buzzer();
        halfCycle = true;
      }
    }
  }

  /* XỬ LÝ KHI CAR KO NHẬN ĐƯỢC DỮ LIỆU TỪ GPS */
  if (millis() > 7000UL && gps.charsProcessed() < 10)
  {
    // Cho dừng lại tất cả hoạt động của xe (nếu có)
    blue = 'D';
    processedBLE();

    Serial.print(F("NONE;")); // No GPS detected: check wiring.
    while (true)
      ;
  }
}
