/*
 * global.h
 *
 *  Created on: Nov 4, 2025
 *      Author: DELL
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "button.h"
#include "led_7_segment.h"
#include "scheduler.h"
#include "software_timer.h"
#include "traffic_light.h"
#include "task.h"

// TRAFFIC LIGHT
#define MIN_COUNTER 1
#define MAX_COUNTER 99

// TIMER
#define INDEX_READ_BTN 0
#define INDEX_TRAFFIC_LIGHT 1
#define INDEX_7SEG 2
#define INDEX_7SEG_STATUS 3
#define INDEX_1SEC 4
#define INDEX_500MS 5
#define INDEX_250MS 6
#define INDEX_STATUS 7

#define TIME_READ_BTN 9 // ms

#define TIME_7SEG 5
#define TIME_7SEG_STATUS 250
#define TIME_1SEC 1000
#define TIME_500MS 500
#define TIME_250MS 250
#define TIME_STATUS 1000

// BUTTON
#define NORMAL_STATE              SET
#define PRESSED_STATE             RESET
#define TIME_OUT_FOR_LONG_PRESSED 500 // ms

// LED CONTROL
#define LED_ON                    RESET
#define LED_OFF                   SET
#define ENABLE                    SET
#define DISABLE                   RESET

extern int led_7seg_index;
extern int led_7seg_buffer[4];
extern int status_4digits[4];

extern int counter_horizontal;
extern int counter_vertical;

extern int red_time;
extern int yel_time;
extern int grn_time;

extern int red_temp_time;
extern int yel_temp_time;
extern int grn_temp_time;

#endif /* INC_GLOBAL_H_ */
