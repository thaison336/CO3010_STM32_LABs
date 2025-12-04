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
	INIT,
	AUTO_RED_GRN,
	AUTO_RED_YEL,
	AUTO_GRN_RED,
	AUTO_YEL_RED,
	RED_TIME_CONFIG,
	YEL_TIME_CONFIG,
	GRN_TIME_CONFIG,
};

void fsm_traffic_light();

void turn_red_on();
void turn_yel_on();
void turn_grn_on();
void turn_on_red_grn();
void turn_on_red_yel();
void turn_on_grn_red();
void turn_on_yel_red();

void init_auto_red_grn();
void auto_red_grn();

void init_auto_red_yel();
void auto_red_yel();

void init_auto_grn_red();
void auto_grn_red();

void init_auto_yel_red();
void auto_yel_red();

void init_red_time_config();
void red_time_config();

void init_red_time_config_change();
void red_time_config_change();

void init_yel_time_config();
void yel_time_config();

void init_yel_time_config_change();
void yel_time_config_change();

void init_grn_time_config();
void grn_time_config();

void init_grn_time_config_change();
void grn_time_config_change();

void init_yel_blinky();
void yel_blinky();

#endif /* INC_TRAFFIC_LIGHT_H_ */