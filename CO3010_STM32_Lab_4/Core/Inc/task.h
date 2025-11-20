/*
 * task.h
 *
 *  Created on: Nov 19, 2025
 *      Author: DELL
 */

#ifndef INC_TASK_H_
#define INC_TASK_H_

#include "global.h"

void statusLED();
void get3ButtonInput();
void decreaseCounter();
void oneSecondTick();

void turn_on_red_grn();
void turn_on_red_yel();
void turn_on_grn_red();
void turn_on_yel_red();
void update_led_7seg_buffer();
void display_4digits();

#endif /* INC_TASK_H_ */
