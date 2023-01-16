#ifndef _CONTROL_CAR_BLUETOOTH_H_
#define _CONTROL_CAR_BLUETOOTH_H_

/* ------------------------------------------------------------------------- */

#include "Arduino.h"
#include "Pin_Connect.h"

/* -------------- DEBUG (uncomment to open the Debug function) ------------- */

#define ENABLE_DEBUG

#if defined(ENABLE_DEBUG)
#define Debug Serial
#define DEBUG_BEGIN(...) Debug.begin(__VA_ARGS__)
#define DEBUG_WRITE(...) Debug.write(__VA_ARGS__)
#define DEBUG_PRINT(...) Debug.print(__VA_ARGS__)
#define DEBUG_PRINTLN(...) Debug.println(__VA_ARGS__)
#else
#define DEBUG_BEGIN(...)
#define DEBUG_WRITE(...)
#define DEBUG_PRINT(...)
#define DEBUG_PRINTLN(...)
#endif

/* ------------------------------------------------------------------------- */

// "speed" là tốc độ quay Motor, đơn vị %, với độ phân giải 10%
// "power" là công suất cấp cho Motor, đơn vị ~pwm, từ 0 - 255

/* Hàm chuyển đổi Tốc độ sang Công suất */
// byte convert_speed_to_power(byte speed);

/* ------------------------------------------------------------------------- */

/* Hàm điều khiển LED trước */
void turn_on_LED_front();
void turn_off_LED_front();

/* Hàm điều khiển LED sau */
void turn_on_LED_back();
void turn_off_LED_back();

/* Hàm điều khiển còi */
void turn_on_buzzer();
void turn_off_buzzer();

/* ------------------------------------------------------------------------- */

/* Hàm dừng Motor */
void motor_right_stop();
void motor_left_stop();

/* Hàm quay Motor chiều kim đồng hồ (+ CW) */
void motor_right_CW(byte power);
void motor_left_CW(byte power);

/* Hàm quay Motor ngược chiều kim đồng hồ (- CCW) */
void motor_right_CCW(byte power);
void motor_left_CCW(byte power);

/* ------------------------------------------------------------------------- */

void stop_car(); // Dừng xe (ko làm gì cả)

void go_forward(byte power);   // Xe đi về phía trước (chiều dọc)
void back_forward(byte power); // Xe đi lùi về phía sau (chiều dọc)

void turn_CW(byte power);  // Xe quay chiều đồng hồ (CW)
void turn_CCW(byte power); // Xe quay ngược chiều đồng hồ (CCW)

void go_left_forward(byte power);  // Xe đi thẳng về phía trái
void go_right_forward(byte power); // Xe đi thẳng về phía phải

void back_left_forward(byte power);  // Xe đi lùi về phía trái
void back_right_forward(byte power); // Xe đi lùi về phía phải

/* ------------------------------------------------------------------------- */

#endif