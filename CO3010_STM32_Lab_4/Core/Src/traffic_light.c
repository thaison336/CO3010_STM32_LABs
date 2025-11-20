/*
 * light_traffic.c
 *
 *  Created on: Nov 4, 2025
 *      Author: DELL
 */

#include "traffic_light.h"
#define temp_time_offset 10
enum TrafficLightState TRAFFIC_LIGHT_STATE = INIT_TRAFFIC_LIGHT;

// ------------------------------------------------------
// Helper Functions
// ------------------------------------------------------
void load_timer_auto(int time_hor, int time_ver) {
    counter_horizontal = time_hor;
    counter_vertical = time_ver;
    update_led_7seg_buffer();
}

// ------------------------------------------------------
// SCHEDULER TASKS
// ------------------------------------------------------

// Task 1: Cập nhật LED giao thông (250ms)
void task_update_traffic_light() {
    switch (TRAFFIC_LIGHT_STATE) {
        case AUTO_RED_GRN:
            turn_on_red_grn();
            break;
        case AUTO_RED_YEL:
            turn_on_red_yel();
            break;
        case AUTO_GRN_RED:
            turn_on_grn_red();
            break;
        case AUTO_YEL_RED:
            turn_on_yel_red();
            break;
        case RED_TIME_CONFIG:
            HAL_GPIO_TogglePin(LED_RED_0_GPIO_Port, LED_RED_0_Pin);
            HAL_GPIO_TogglePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin);
            break;
        case YEL_TIME_CONFIG:
            HAL_GPIO_TogglePin(LED_YEL_0_GPIO_Port, LED_YEL_0_Pin);
            HAL_GPIO_TogglePin(LED_YEL_1_GPIO_Port, LED_YEL_1_Pin);
            break;
        case GRN_TIME_CONFIG:
            HAL_GPIO_TogglePin(LED_GRN_0_GPIO_Port, LED_GRN_0_Pin);
            HAL_GPIO_TogglePin(LED_GRN_1_GPIO_Port, LED_GRN_1_Pin);
            break;
        default:
            break;
    }
}

// Task 2: Cập nhật 7-segment (5ms)
void task_update_7segment() {
	update_led_7seg_buffer();
    display_4digits();
}

// Task 3: Đếm ngược (1000ms)
void task_countdown() {
    switch (TRAFFIC_LIGHT_STATE) {
        case AUTO_RED_GRN:
        case AUTO_RED_YEL:
        case AUTO_GRN_RED:
        case AUTO_YEL_RED:
            if (counter_horizontal > 0) counter_horizontal--;
            if (counter_vertical > 0) counter_vertical--;
//            update_led_7seg_buffer();
            break;
        default:
            break;
    }
}

// ------------------------------------------------------
// MAIN FSM (Chạy 10ms - 50ms)
// ------------------------------------------------------
void fsm_traffic_light()
{
    switch (TRAFFIC_LIGHT_STATE) {
        case INIT_TRAFFIC_LIGHT:
            turn_on_red_grn();
            load_timer_auto(red_time, grn_time);
            set_on_4digits();
            TRAFFIC_LIGHT_STATE = AUTO_RED_GRN;
            break;

        // --- AUTO MODES ---
        case AUTO_RED_GRN:
            if (counter_vertical <= 0) {
                turn_on_red_yel();
                load_timer_auto(red_time - grn_time, yel_time);
                TRAFFIC_LIGHT_STATE = AUTO_RED_YEL;
            }
            else if (isButtonPressed(&button1)) {
                init_red_time_config();
                TRAFFIC_LIGHT_STATE = RED_TIME_CONFIG;
            }
            break;

        case AUTO_RED_YEL:
            if (counter_horizontal <= 0 && counter_vertical <= 0) {
                turn_on_grn_red();
                load_timer_auto(grn_time, red_time);
                TRAFFIC_LIGHT_STATE = AUTO_GRN_RED;
            }
            else if (isButtonPressed(&button1)) {
                init_red_time_config();
                TRAFFIC_LIGHT_STATE = RED_TIME_CONFIG;
            }
            break;

        case AUTO_GRN_RED:
            if (counter_horizontal <= 0) {
                turn_on_yel_red();
                load_timer_auto(yel_time, red_time - grn_time);
                TRAFFIC_LIGHT_STATE = AUTO_YEL_RED;
            }
            else if (isButtonPressed(&button1)) {
                init_red_time_config();
                TRAFFIC_LIGHT_STATE = RED_TIME_CONFIG;
            }
            break;

        case AUTO_YEL_RED:
            if (counter_horizontal <= 0 && counter_vertical <= 0) {
                turn_on_red_grn();
                load_timer_auto(red_time, grn_time);
                TRAFFIC_LIGHT_STATE = AUTO_RED_GRN;
            }
            else if (isButtonPressed(&button1)) {
                init_red_time_config();
                TRAFFIC_LIGHT_STATE = RED_TIME_CONFIG;
            }
            break;

        // --- CONFIG MODES ---
        case RED_TIME_CONFIG:
            if (isButtonPressed(&button2)) {
                red_temp_time++;
                if (red_temp_time > MAX_COUNTER) {
                    red_temp_time = MIN_COUNTER;
                }
                counter_horizontal = red_temp_time;
                update_led_7seg_buffer();
            }
            if (isButtonLongPressed(&button2)) {
                red_temp_time += temp_time_offset;
                if (red_temp_time > MAX_COUNTER) {
                    red_temp_time = MIN_COUNTER;
                }
                counter_horizontal = red_temp_time;
                update_led_7seg_buffer();
            }
            
            if (isButtonPressed(&button1)) {
                init_yel_time_config();
                TRAFFIC_LIGHT_STATE = YEL_TIME_CONFIG;
            }
            else if (isButtonPressed(&button3)) {
                if (red_temp_time > yel_time) {
                    red_time = red_temp_time;
                    grn_time = red_time - yel_time;
                }
                init_red_time_config();
            }
            break;

        case YEL_TIME_CONFIG:
            if (isButtonPressed(&button2)) {
                yel_temp_time++;
                if (yel_temp_time > MAX_COUNTER) {
                    yel_temp_time = MIN_COUNTER;
                }
                counter_horizontal = yel_temp_time;
                update_led_7seg_buffer();
            }
            if (isButtonLongPressed(&button2)) {
                yel_temp_time += temp_time_offset;
                if (yel_temp_time > MAX_COUNTER) {
                    yel_temp_time = MIN_COUNTER;
                }
                counter_horizontal = yel_temp_time;
                update_led_7seg_buffer();
            }
            
            if (isButtonPressed(&button1)) {
                init_grn_time_config();
                TRAFFIC_LIGHT_STATE = GRN_TIME_CONFIG;
            }
            else if (isButtonPressed(&button3)) {
                if (yel_temp_time >= red_time) {
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
            if (isButtonPressed(&button2)) {
                grn_temp_time++;
                if (grn_temp_time > MAX_COUNTER) {
                    grn_temp_time = MIN_COUNTER;
                }
                counter_horizontal = grn_temp_time;
                update_led_7seg_buffer();
            }
            if (isButtonLongPressed(&button2)) {
                grn_temp_time += temp_time_offset;
                if (grn_temp_time > MAX_COUNTER) {
                    grn_temp_time = MIN_COUNTER;
                }
                counter_horizontal = grn_temp_time;
                update_led_7seg_buffer();
            }
            
            if (isButtonPressed(&button1)) {
                turn_on_red_grn();
                load_timer_auto(red_time, grn_time);
                TRAFFIC_LIGHT_STATE = AUTO_RED_GRN;
            }
            else if (isButtonPressed(&button3)) {
                grn_time = grn_temp_time;
                red_time = grn_time + yel_time;
                init_grn_time_config();
            }
            break;

        default:
            TRAFFIC_LIGHT_STATE = INIT_TRAFFIC_LIGHT;
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
	resetButton(&button1);
	resetButton(&button2);
	resetButton(&button3);

	set_on_4digits();
	counter_horizontal = red_time;
	counter_vertical = grn_time;
	update_led_7seg_buffer();
}
// Không dùng - đã tách thành task
//void auto_red_grn()
//{
//    turn_on_red_grn();
//
//    if (isFlag(INDEX_7SEG))
//    {
//        display_4digits();
//        setTimer(INDEX_7SEG, TIME_7SEG);
//    }
//
//    if (isFlag(INDEX_1SEC))
//    {
//        --counter_horizontal;
//        --counter_vertical;
//        update_led_7seg_buffer();
//        setTimer(INDEX_1SEC, TIME_1SEC);
//    }
//}

void init_auto_red_yel()
{
	resetButton(&button1);
	resetButton(&button2);

	set_on_4digits();
	counter_horizontal = red_time;
	counter_vertical = yel_time;
	update_led_7seg_buffer();
}
// Không dùng - đã tách thành task
//void auto_red_yel()
//{
//    turn_on_red_yel();
//
//    if (isFlag(INDEX_7SEG))
//    {
//        display_4digits();
//        setTimer(INDEX_7SEG, TIME_7SEG);
//    }
//
//    if (isFlag(INDEX_1SEC))
//    {
//        --counter_horizontal;
//        --counter_vertical;
//        update_led_7seg_buffer();
//        setTimer(INDEX_1SEC, TIME_1SEC);
//    }
//}

void init_auto_grn_red()
{
	resetButton(&button1);
	resetButton(&button2);
	resetButton(&button3);

	set_on_4digits();
	counter_horizontal = grn_time;
	counter_vertical = red_time;
	update_led_7seg_buffer();
}

// Không dùng - đã tách thành task
//void auto_grn_red()
//{
//    turn_on_grn_red();
//
//    if (isFlag(INDEX_7SEG))
//    {
//        display_4digits();
//        setTimer(INDEX_7SEG, TIME_7SEG);
//    }
//
//    if (isFlag(INDEX_1SEC))
//    {
//        --counter_horizontal;
//        --counter_vertical;
//        update_led_7seg_buffer();
//        setTimer(INDEX_1SEC, TIME_1SEC);
//    }
//}

void init_auto_yel_red()
{
	resetButton(&button1);
	resetButton(&button2);

	set_on_4digits();
	counter_horizontal = yel_time;
	counter_vertical = red_time;
	update_led_7seg_buffer();
}
// Không dùng - đã tách thành task
//void auto_yel_red()
//{
//    turn_on_yel_red();
//
//    if (isFlag(INDEX_7SEG))
//    {
//        display_4digits();
//        setTimer(INDEX_7SEG, TIME_7SEG);
//    }
//
//    if (isFlag(INDEX_1SEC))
//    {
//        --counter_horizontal;
//        --counter_vertical;
//        update_led_7seg_buffer();
//        setTimer(INDEX_1SEC, TIME_1SEC);
//    }
//}

// ----------------------------------------------------------------------
// --- MODE 2 ---
// ----------------------------------------------------------------------

void init_red_time_config()
{
	resetButton(&button1);
	resetButton(&button2);
	resetButton(&button3);

	red_temp_time = red_time;
	turn_red_on();

	set_on_4digits();
	counter_horizontal = red_temp_time;
	counter_vertical = 0;
	update_led_7seg_buffer();
}
// Không dùng - logic đã chuyển vào FSM
//void red_time_config()
//{
//    if (1)
//    {
//        if (isButtonPressed(&button2))
//        {
//            ++red_temp_time;
//        }
//        if (isButtonLongPressed(&button2))
//        {
//            red_temp_time += temp_time_offset;
//        }
//        if (red_temp_time > MAX_COUNTER)
//        {
//            red_temp_time = MIN_COUNTER;
//        }
//
//        counter_horizontal = red_temp_time;
//        update_led_7seg_buffer();
//    }
//
//    if (isFlag(INDEX_250MS))
//    {
//        HAL_GPIO_TogglePin(LED_RED_0_GPIO_Port, LED_RED_0_Pin);
//        HAL_GPIO_TogglePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin);
//
//        setTimer(INDEX_250MS, TIME_250MS);
//    }
//
//    if (isFlag(INDEX_7SEG))
//    {
//        display_4digits();
//        setTimer(INDEX_7SEG, TIME_7SEG);
//    }
//}// ----------------------------------------------------------------------
// --- MODE 3 ---
// ----------------------------------------------------------------------

void init_yel_time_config()
{
	resetButton(&button1);
	resetButton(&button2);
	resetButton(&button3);

	yel_temp_time = yel_time;
	turn_yel_on();

	set_on_4digits();
	counter_horizontal = yel_temp_time;
	counter_vertical = 0;
	update_led_7seg_buffer();
}
// Không dùng - logic đã chuyển vào FSM
//void yel_time_config()
//{
//    if (1)
//    {
//        if (isButtonPressed(&button2))
//        {
//            ++yel_temp_time;
//        }
//        if (isButtonLongPressed(&button2))
//        {
//            yel_temp_time += temp_time_offset;
//        }
//        if (yel_temp_time > MAX_COUNTER)
//        {
//            yel_temp_time = MIN_COUNTER;
//        }
//
//        counter_horizontal = yel_temp_time;
//        update_led_7seg_buffer();
//    }
//
//    if (isFlag(INDEX_250MS))
//    {
//        HAL_GPIO_TogglePin(LED_YEL_0_GPIO_Port, LED_YEL_0_Pin);
//        HAL_GPIO_TogglePin(LED_YEL_1_GPIO_Port, LED_YEL_1_Pin);
//
//        setTimer(INDEX_250MS, TIME_250MS);
//    }
//
//    if (isFlag(INDEX_7SEG))
//    {
//        display_4digits();
//        setTimer(INDEX_7SEG, TIME_7SEG);
//    }
//}

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

	set_on_4digits();
	counter_horizontal = grn_temp_time;
	counter_vertical = 0;
	update_led_7seg_buffer();
}
// Không dùng - logic đã chuyển vào FSM
//void grn_time_config()
//{
//	if (1)
//	{
//		if (isButtonPressed(&button2))
//		{
//			++grn_temp_time;
//		}
//		if (isButtonLongPressed(&button2))
//		{
//			grn_temp_time += temp_time_offset;
//		}
//		if (grn_temp_time > MAX_COUNTER)
//		{
//			grn_temp_time = MIN_COUNTER;
//		}
//
//		counter_horizontal = grn_temp_time;
//		update_led_7seg_buffer();
//	}
//
//	if (isFlag(INDEX_250MS))
//	{
//		HAL_GPIO_TogglePin(LED_GRN_0_GPIO_Port, LED_GRN_0_Pin);
//		HAL_GPIO_TogglePin(LED_GRN_1_GPIO_Port, LED_GRN_1_Pin);
//
//		setTimer(INDEX_250MS, TIME_250MS);
//	}
//
//	if (isFlag(INDEX_7SEG))
//	{
//		display_4digits();
//		setTimer(INDEX_7SEG, TIME_7SEG);
//	}
//}
