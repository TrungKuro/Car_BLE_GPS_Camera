#include "Control_Car_BLE_GPS.h"

/* ----------------- Hàm chuyển đổi công suất thành tốc độ ----------------- */

String convert_power_to_speed(byte power)
{
  /**
   *         100 * power
   * speed = -----------
   *             255
   */
  byte speed = 100 * power / 255;

  String reply = F("SPEED,");
  reply += String(speed);
  reply += F(";");

  return reply;
}

/* ------------------------ Hàm điều khiển LED trước ----------------------- */

void turn_on_LED_front()
{
  digitalWrite(LED_FRONT_LEFT, HIGH);
  digitalWrite(LED_FRONT_RIGHT, HIGH);
}

void turn_off_LED_front()
{
  digitalWrite(LED_FRONT_LEFT, LOW);
  digitalWrite(LED_FRONT_RIGHT, LOW);
}

/* ------------------------- Hàm điều khiển LED sau ------------------------ */

void turn_on_LED_back()
{
  digitalWrite(LED_BACK_LEFT, HIGH);
  digitalWrite(LED_BACK_RIGHT, HIGH);
}

void turn_off_LED_back()
{
  digitalWrite(LED_BACK_LEFT, LOW);
  digitalWrite(LED_BACK_RIGHT, LOW);
}

/* --------------------------- Hàm điều khiển còi -------------------------- */

void turn_on_buzzer()
{
  digitalWrite(BUZZER, HIGH);
}

void turn_off_buzzer()
{
  digitalWrite(BUZZER, LOW);
}

/* ----------------------------- Hàm dừng Motor ---------------------------- */

void motor_right_stop()
{
  digitalWrite(MOTOR_R_IN1, LOW);
  digitalWrite(MOTOR_R_IN2, LOW);
}

void motor_left_stop()
{
  digitalWrite(MOTOR_L_IN4, LOW);
  digitalWrite(MOTOR_L_IN3, LOW);
}

/* ---------------- Hàm quay Motor chiều kim đồng hồ (+ CW) ---------------- */

void motor_right_CW(byte power)
{
  analogWrite(MOTOR_RIGHT_ENA, power);
  digitalWrite(MOTOR_R_IN1, HIGH);
  digitalWrite(MOTOR_R_IN2, LOW);
}

void motor_left_CW(byte power)
{
  analogWrite(MOTOR_LEFT_ENB, power);
  digitalWrite(MOTOR_L_IN4, HIGH);
  digitalWrite(MOTOR_L_IN3, LOW);
}

/* ------------- Hàm quay Motor ngược chiều kim đồng hồ (- CCW) ------------ */

void motor_right_CCW(byte power)
{
  analogWrite(MOTOR_RIGHT_ENA, power);
  digitalWrite(MOTOR_R_IN1, LOW);
  digitalWrite(MOTOR_R_IN2, HIGH);
}

void motor_left_CCW(byte power)
{
  analogWrite(MOTOR_LEFT_ENB, power);
  digitalWrite(MOTOR_L_IN4, LOW);
  digitalWrite(MOTOR_L_IN3, HIGH);
}

/* ------------------------- Các hàm điều khiển xe ------------------------- */

// Dừng xe (ko làm gì cả)
void stop_car()
{
  motor_right_stop();
  motor_left_stop();
}

// Xe đi về phía trước (chiều dọc)
void go_forward(byte power)
{
  motor_right_CW(power);
  motor_left_CW(power);
}
// Xe đi lùi về phía sau (chiều dọc)
void back_forward(byte power)
{
  motor_right_CCW(power);
  motor_left_CCW(power);
}

// Xe quay chiều đồng hồ (CW)
void turn_CW(byte power)
{
  motor_right_CCW(power);
  motor_left_CW(power);
}
// Xe quay ngược chiều đồng hồ (CCW)
void turn_CCW(byte power)
{
  motor_right_CW(power);
  motor_left_CCW(power);
}

// Xe đi thẳng về phía trái
void go_left_forward(byte power)
{
  motor_right_CW(power);
  motor_left_stop();
}
// Xe đi thẳng về phía phải
void go_right_forward(byte power)
{
  motor_right_stop();
  motor_left_CW(power);
}

// Xe đi lùi về phía trái
void back_left_forward(byte power)
{
  motor_right_CCW(power);
  motor_left_stop();
}
// Xe đi lùi về phía phải
void back_right_forward(byte power)
{
  motor_right_stop();
  motor_left_CCW(power);
}
