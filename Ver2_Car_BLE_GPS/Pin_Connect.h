#ifndef _PIN_CONNECT_H_
#define _PIN_CONNECT_H_

/* GPS */
#define BAUD_GPS 115200 // bps
#define RX_GPS 11
#define TX_GPS 12

/* BLE */
#define BAUD_BLE 115200 // bps
#define RX_BLE 2
#define TX_BLE 3

/* Driver L298 */
#define MOTOR_RIGHT_ENA 10 // ~pwm
#define MOTOR_R_IN1 9
#define MOTOR_R_IN2 8
#define MOTOR_L_IN3 7
#define MOTOR_L_IN4 6
#define MOTOR_LEFT_ENB 5 // ~pwm

/* Power */
#define POWER_0_PER 0     // 0%
#define POWER_10_PER 26   // 10%
#define POWER_20_PER 51   // 20%
#define POWER_30_PER 77   // 30%
#define POWER_40_PER 102  // 40%
#define POWER_50_PER 128  // 50%
#define POWER_60_PER 153  // 60%
#define POWER_70_PER 179  // 70%
#define POWER_80_PER 204  // 80%
#define POWER_90_PER 230  // 90%
#define POWER_100_PER 255 // 100%

/* LED Front */
#define LED_FRONT_RIGHT A0
#define LED_FRONT_LEFT A1

/* LED Back */
#define LED_BACK_RIGHT A2
#define LED_BACK_LEFT A3

/* Buzzer */
#define BUZZER A4

#endif
