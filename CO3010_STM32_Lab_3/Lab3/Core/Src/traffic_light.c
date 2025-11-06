/*
 * light_traffic.c
 *
 *  Created on: Nov 4, 2025
 *      Author: DELL
 */

#include "traffic_light.h"
#define temp_time_offset 10
enum TrafficLightState TRAFFIC_LIGHT_STATE = INIT;

void fsm_traffic_light()
{
	switch (TRAFFIC_LIGHT_STATE) {
		case INIT:
			if (1)
			{
				init_auto_red_grn();
				TRAFFIC_LIGHT_STATE = AUTO_RED_GRN;
			}
			break;

		case AUTO_RED_GRN:
			auto_red_grn();
			if (isFlag(INDEX_TRAFFIC_LIGHT))
			{
				init_auto_red_yel();
				TRAFFIC_LIGHT_STATE = AUTO_RED_YEL;
			}
			else if (isButtonPressed(&button1))
			{
				init_red_time_config();
				TRAFFIC_LIGHT_STATE = RED_TIME_CONFIG;
			}
			break;

		case AUTO_RED_YEL:
			auto_red_yel();

			if (isFlag(INDEX_TRAFFIC_LIGHT))
			{
				init_auto_grn_red();
				TRAFFIC_LIGHT_STATE = AUTO_GRN_RED;
			}
			else if (isButtonPressed(&button1))
			{
				init_red_time_config();
				TRAFFIC_LIGHT_STATE = RED_TIME_CONFIG;
			}
			break;

		case AUTO_GRN_RED:
			auto_grn_red();

			if (isFlag(INDEX_TRAFFIC_LIGHT))
			{
				init_auto_yel_red();
				TRAFFIC_LIGHT_STATE = AUTO_YEL_RED;
			}
			else if (isButtonPressed(&button1))
			{
				init_red_time_config();
				TRAFFIC_LIGHT_STATE = RED_TIME_CONFIG;
			}
			break;

		case AUTO_YEL_RED:
			auto_yel_red();
			if (isFlag(INDEX_TRAFFIC_LIGHT))
			{
				init_auto_red_grn();
				TRAFFIC_LIGHT_STATE = AUTO_RED_GRN;
			}
			else if (isButtonPressed(&button1))
			{
				init_red_time_config();
				TRAFFIC_LIGHT_STATE = RED_TIME_CONFIG;
			}

			break;

		case RED_TIME_CONFIG:
			red_time_config();

			if (isButtonPressed(&button1))
			{
				init_yel_time_config();
				TRAFFIC_LIGHT_STATE = YEL_TIME_CONFIG;
			}
			else if (isButtonPressed(&button3))
			{
				if (red_temp_time > yel_time)
				{
					red_time = red_temp_time;
					grn_time = red_time - yel_time;
				}
				init_red_time_config(); 
			}
			break;

		case YEL_TIME_CONFIG:
			yel_time_config();

			if (isButtonPressed(&button1))
			{
				init_grn_time_config();
				TRAFFIC_LIGHT_STATE = GRN_TIME_CONFIG;
			}
			else if (isButtonPressed(&button3))
			{
				if (yel_temp_time >= red_time)
				{
					red_time = yel_temp_time + grn_time;
					yel_time = yel_temp_time;
				} else {
					yel_time = yel_temp_time;
					grn_time = red_time - yel_time; 
				}
				init_yel_time_config(); 
			}
			break;

		case GRN_TIME_CONFIG:
			grn_time_config();

			if (isButtonPressed(&button1))
			{
				init_auto_red_grn();
				TRAFFIC_LIGHT_STATE = AUTO_RED_GRN;
			}
			else if (isButtonPressed(&button3))
			{
				grn_time = grn_temp_time;
				red_time = grn_time + yel_time;
			}
			break;

		default:
			TRAFFIC_LIGHT_STATE = INIT;
			break;
	}
}

void turn_red_on()
{
	HAL_GPIO_WritePin(LED_RED_0_GPIO_Port, LED_RED_0_Pin, LED_ON);
	HAL_GPIO_WritePin(LED_YEL_0_GPIO_Port, LED_YEL_0_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_GRN_0_GPIO_Port, LED_GRN_0_Pin, LED_OFF);

	HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, LED_ON);
	HAL_GPIO_WritePin(LED_YEL_1_GPIO_Port, LED_YEL_1_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_GRN_1_GPIO_Port, LED_GRN_1_Pin, LED_OFF);
}

void turn_yel_on()
{
	HAL_GPIO_WritePin(LED_RED_0_GPIO_Port, LED_RED_0_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_YEL_0_GPIO_Port, LED_YEL_0_Pin, LED_ON);
	HAL_GPIO_WritePin(LED_GRN_0_GPIO_Port, LED_GRN_0_Pin, LED_OFF);

	HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_YEL_1_GPIO_Port, LED_YEL_1_Pin, LED_ON);
	HAL_GPIO_WritePin(LED_GRN_1_GPIO_Port, LED_GRN_1_Pin, LED_OFF);
}

void turn_grn_on()
{
	HAL_GPIO_WritePin(LED_RED_0_GPIO_Port, LED_RED_0_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_YEL_0_GPIO_Port, LED_YEL_0_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_GRN_0_GPIO_Port, LED_GRN_0_Pin, LED_ON);

	HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_YEL_1_GPIO_Port, LED_YEL_1_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_GRN_1_GPIO_Port, LED_GRN_1_Pin, LED_ON);
}

void turn_on_red_grn()
{
	HAL_GPIO_WritePin(LED_RED_0_GPIO_Port, LED_RED_0_Pin, LED_ON);
	HAL_GPIO_WritePin(LED_YEL_0_GPIO_Port, LED_YEL_0_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_GRN_0_GPIO_Port, LED_GRN_0_Pin, LED_OFF);

	HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_YEL_1_GPIO_Port, LED_YEL_1_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_GRN_1_GPIO_Port, LED_GRN_1_Pin, LED_ON);
}

void turn_on_red_yel()
{
	HAL_GPIO_WritePin(LED_RED_0_GPIO_Port, LED_RED_0_Pin, LED_ON);
	HAL_GPIO_WritePin(LED_YEL_0_GPIO_Port, LED_YEL_0_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_GRN_0_GPIO_Port, LED_GRN_0_Pin, LED_OFF);

	HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_YEL_1_GPIO_Port, LED_YEL_1_Pin, LED_ON);
	HAL_GPIO_WritePin(LED_GRN_1_GPIO_Port, LED_GRN_1_Pin, LED_OFF);
}

void turn_on_grn_red()
{
	HAL_GPIO_WritePin(LED_RED_0_GPIO_Port, LED_RED_0_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_YEL_0_GPIO_Port, LED_YEL_0_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_GRN_0_GPIO_Port, LED_GRN_0_Pin, LED_ON);

	HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, LED_ON);
	HAL_GPIO_WritePin(LED_YEL_1_GPIO_Port, LED_YEL_1_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_GRN_1_GPIO_Port, LED_GRN_1_Pin, LED_OFF);
}

void turn_on_yel_red()
{
	HAL_GPIO_WritePin(LED_RED_0_GPIO_Port, LED_RED_0_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_YEL_0_GPIO_Port, LED_YEL_0_Pin, LED_ON);
	HAL_GPIO_WritePin(LED_GRN_0_GPIO_Port, LED_GRN_0_Pin, LED_OFF);

	HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, LED_ON);
	HAL_GPIO_WritePin(LED_YEL_1_GPIO_Port, LED_YEL_1_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_GRN_1_GPIO_Port, LED_GRN_1_Pin, LED_OFF);
}


// ----------------------------------------------------------------------
// --- MODE 1 ---
// ----------------------------------------------------------------------

void init_auto_red_grn()
{
	setTimer(INDEX_TRAFFIC_LIGHT, grn_time * 1000);
	resetButton(&button1);
	resetButton(&button2);
	resetButton(&button3);

	set_on_4digits();
	setTimer(INDEX_7SEG, TIME_7SEG);
	setTimer(INDEX_1SEC, TIME_1SEC);
	counter_horizontal = red_time;
	counter_vertical = grn_time;
	update_led_7seg_buffer();
}
void auto_red_grn()
{
	turn_on_red_grn();

	if (isFlag(INDEX_7SEG))
	{
		display_4digits();
		setTimer(INDEX_7SEG, TIME_7SEG);
	}

	if (isFlag(INDEX_1SEC))
	{
		--counter_horizontal;
		--counter_vertical;
		update_led_7seg_buffer();
		setTimer(INDEX_1SEC, TIME_1SEC);
	}
}

void init_auto_red_yel()
{
	setTimer(INDEX_TRAFFIC_LIGHT, yel_time * 1000);
	resetButton(&button1);
	resetButton(&button2);

	set_on_4digits();
	setTimer(INDEX_7SEG, TIME_7SEG);
	setTimer(INDEX_1SEC, TIME_1SEC);
	counter_horizontal = red_time;
	counter_vertical = yel_time;
	update_led_7seg_buffer();
}
void auto_red_yel()
{
	turn_on_red_yel();

	if (isFlag(INDEX_7SEG))
	{
		display_4digits();
		setTimer(INDEX_7SEG, TIME_7SEG);
	}

	if (isFlag(INDEX_1SEC))
	{
		--counter_horizontal;
		--counter_vertical;
		update_led_7seg_buffer();
		setTimer(INDEX_1SEC, TIME_1SEC);
	}
}

void init_auto_grn_red()
{
	setTimer(INDEX_TRAFFIC_LIGHT, grn_time * 1000);
	resetButton(&button1);
	resetButton(&button2);
	resetButton(&button3);

	set_on_4digits();
	setTimer(INDEX_7SEG, TIME_7SEG);
	setTimer(INDEX_1SEC, TIME_1SEC);
	counter_horizontal = grn_time;
	counter_vertical = red_time;
	update_led_7seg_buffer();
}
void auto_grn_red()
{
	turn_on_grn_red();

	if (isFlag(INDEX_7SEG))
	{
		display_4digits();
		setTimer(INDEX_7SEG, TIME_7SEG);
	}

	if (isFlag(INDEX_1SEC))
	{
		--counter_horizontal;
		--counter_vertical;
		update_led_7seg_buffer();
		setTimer(INDEX_1SEC, TIME_1SEC);
	}
}

void init_auto_yel_red()
{
	setTimer(INDEX_TRAFFIC_LIGHT, yel_time * 1000);
	resetButton(&button1);
	resetButton(&button2);


	set_on_4digits();
	setTimer(INDEX_7SEG, TIME_7SEG);
	setTimer(INDEX_1SEC, TIME_1SEC);
	counter_horizontal = yel_time;
	counter_vertical = red_time;
	update_led_7seg_buffer();
}
void auto_yel_red()
{
	turn_on_yel_red();

	if (isFlag(INDEX_7SEG))
	{
		display_4digits();
		setTimer(INDEX_7SEG, TIME_7SEG);
	}

	if (isFlag(INDEX_1SEC))
	{
		--counter_horizontal;
		--counter_vertical;
		update_led_7seg_buffer();
		setTimer(INDEX_1SEC, TIME_1SEC);
	}
}

// ----------------------------------------------------------------------
// --- MODE 2 ---
// ----------------------------------------------------------------------

void init_red_time_config()
{
	// Reset nút bấm (button1: chuyển mode, button2: tăng, button3: lưu)
	resetButton(&button1);
	resetButton(&button2);
	resetButton(&button3);

	red_temp_time = red_time;

	// Bật đèn Đỏ và setup Blinking (2Hz = 250ms ON/OFF)
	turn_red_on();
	setTimer(INDEX_250MS, TIME_250MS);

	set_on_4digits();
	counter_horizontal = red_temp_time;
	counter_vertical = 0; 
	update_led_7seg_buffer();
	setTimer(INDEX_7SEG, TIME_7SEG);
}
void red_time_config()
{
	if (1)
	{
		if (isButtonPressed(&button2))
		{
			++red_temp_time;
		}
		if (isButtonLongPressed(&button2))
		{
			red_temp_time += temp_time_offset;
		}
		if (red_temp_time > MAX_COUNTER)
		{
			red_temp_time = MIN_COUNTER;
		}

		counter_horizontal = red_temp_time;
		update_led_7seg_buffer(); 
	}

	if (isFlag(INDEX_250MS))
	{
		HAL_GPIO_TogglePin(LED_RED_0_GPIO_Port, LED_RED_0_Pin);
		HAL_GPIO_TogglePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin);

		setTimer(INDEX_250MS, TIME_250MS);
	}

	if (isFlag(INDEX_7SEG))
	{
		display_4digits();
		setTimer(INDEX_7SEG, TIME_7SEG);
	}
}

// ----------------------------------------------------------------------
// --- MODE 3 ---
// ----------------------------------------------------------------------

void init_yel_time_config()
{
	resetButton(&button1);
	resetButton(&button2);
	resetButton(&button3);

	yel_temp_time = yel_time;

	turn_yel_on();
	setTimer(INDEX_250MS, TIME_250MS);

	set_on_4digits();
	counter_horizontal = yel_temp_time;
	counter_vertical = 0;
	update_led_7seg_buffer();
	setTimer(INDEX_7SEG, TIME_7SEG);
}
void yel_time_config()
{
	if (1)
	{
		if (isButtonPressed(&button2))
		{
			++yel_temp_time;
		}
		if (isButtonLongPressed(&button2))
		{
			yel_temp_time += temp_time_offset;
		}
		if (yel_temp_time > MAX_COUNTER)
		{
			yel_temp_time = MIN_COUNTER;
		}

		counter_horizontal = yel_temp_time;
		update_led_7seg_buffer();
	}

	if (isFlag(INDEX_250MS))
	{
		HAL_GPIO_TogglePin(LED_YEL_0_GPIO_Port, LED_YEL_0_Pin);
		HAL_GPIO_TogglePin(LED_YEL_1_GPIO_Port, LED_YEL_1_Pin);

		setTimer(INDEX_250MS, TIME_250MS);
	}

	if (isFlag(INDEX_7SEG))
	{
		display_4digits();
		setTimer(INDEX_7SEG, TIME_7SEG);
	}
}

// ----------------------------------------------------------------------
// --- MODE 4---
// ----------------------------------------------------------------------

void init_grn_time_config()
{
	resetButton(&button1);
	resetButton(&button2);
	resetButton(&button3);

	grn_temp_time = grn_time;

	turn_grn_on();
	setTimer(INDEX_250MS, TIME_250MS);

	set_on_4digits();
	counter_horizontal = grn_temp_time;
	counter_vertical = 0; 
	update_led_7seg_buffer();
	setTimer(INDEX_7SEG, TIME_7SEG);
}
void grn_time_config()
{
	if (1)
	{
		if (isButtonPressed(&button2))
		{
			++grn_temp_time;
		}
		if (isButtonLongPressed(&button2))
		{
			grn_temp_time += temp_time_offset;
		}
		if (grn_temp_time > MAX_COUNTER)
		{
			grn_temp_time = MIN_COUNTER;
		}

		counter_horizontal = grn_temp_time;
		update_led_7seg_buffer();
	}

	if (isFlag(INDEX_250MS))
	{
		HAL_GPIO_TogglePin(LED_GRN_0_GPIO_Port, LED_GRN_0_Pin);
		HAL_GPIO_TogglePin(LED_GRN_1_GPIO_Port, LED_GRN_1_Pin);

		setTimer(INDEX_250MS, TIME_250MS);
	}

	if (isFlag(INDEX_7SEG))
	{
		display_4digits();
		setTimer(INDEX_7SEG, TIME_7SEG);
	}
}
