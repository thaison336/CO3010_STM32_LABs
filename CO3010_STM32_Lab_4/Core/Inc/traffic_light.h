/*
 * light_traffic.h
 *
 *  Created on: Nov 4, 2025
 *      Author: DELL
 */

#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_

#include "main.h"
#include "software_timer.h"
#include "button.h"
#include "global.h"
#include "led_7_segment.h"

enum TrafficLightState
{
	INIT_TRAFFIC_LIGHT,
	AUTO_RED_GRN,
	AUTO_RED_YEL,
	AUTO_GRN_RED,
	AUTO_YEL_RED,
	RED_TIME_CONFIG,
	YEL_TIME_CONFIG,
	GRN_TIME_CONFIG,
};

// ------------------------------------------------------
// Helper Functions
// ------------------------------------------------------
void load_timer_auto(int time_hor, int time_ver);

// ------------------------------------------------------
// FSM chính và các task cho scheduler
// ------------------------------------------------------
void fsm_traffic_light();

// Task 1: Cập nhật LED giao thông (250ms)
void task_update_traffic_light();

// Task 2: Cập nhật 7-segment (5ms)
void task_update_7segment();

// Task 3: Đếm ngược (1000ms)
void task_countdown();

// ------------------------------------------------------
// Các hàm điều khiển LED
// ------------------------------------------------------
void turn_red_on();
void turn_yel_on();
void turn_grn_on();
void turn_on_red_grn();
void turn_on_red_yel();
void turn_on_grn_red();
void turn_on_yel_red();

// ------------------------------------------------------
// Các hàm khởi tạo trạng thái AUTO
// ------------------------------------------------------
void init_auto_red_grn();
//void auto_red_grn();  // Không dùng - đã tách thành task

void init_auto_red_yel();
//void auto_red_yel();  // Không dùng - đã tách thành task

void init_auto_grn_red();
//void auto_grn_red();  // Không dùng - đã tách thành task

void init_auto_yel_red();
//void auto_yel_red();  // Không dùng - đã tách thành task

// ------------------------------------------------------
// Các hàm khởi tạo trạng thái CONFIG
// ------------------------------------------------------
void init_red_time_config();
//void red_time_config();  // Không dùng - đã tách thành task

//void init_red_time_config_change();
//void red_time_config_change();

void init_yel_time_config();
//void yel_time_config();  // Không dùng - đã tách thành task

//void init_yel_time_config_change();
//void yel_time_config_change();

void init_grn_time_config();
//void grn_time_config();  // Không dùng - đã tách thành task

//void init_grn_time_config_change();
//void grn_time_config_change();

//void init_yel_blinky();
//void yel_blinky();

#endif /* INC_TRAFFIC_LIGHT_H_ */
