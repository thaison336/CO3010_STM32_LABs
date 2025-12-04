/*
 * global.c
 *
 *  Created on: Nov 5, 2025
 *      Author: DELL
 */

#include "global.h"

int led_7seg_index = 0;
int led_7seg_buffer[4] = {0, 5, 0, 3};
int status_4digits[4] = {LED_ON, LED_ON, LED_ON, LED_ON};

int counter_horizontal = 0;
int counter_vertical = 0;

int red_time = 4;
int yel_time = 1;
int grn_time = 3;

int red_temp_time = 0;
int yel_temp_time = 0;
int grn_temp_time = 0;
