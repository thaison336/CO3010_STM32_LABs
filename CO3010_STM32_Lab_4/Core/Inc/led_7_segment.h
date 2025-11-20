/*
 * led_7_segment.h
 *
 *  Created on: Nov 5, 2025
 *      Author: DELL
 */

#ifndef INC_LED_7_SEGMENT_H_
#define INC_LED_7_SEGMENT_H_

#include "main.h"
#include "global.h"

void set_on_4digits();
void unable_4digit();
void display_4digits();
void update_led_7seg_buffer();
void display_a_digit(int digit, int num);
void display_number(int num);
void enable_digit(int digit);


#endif /* INC_LED_7_SEGMENT_H_ */
