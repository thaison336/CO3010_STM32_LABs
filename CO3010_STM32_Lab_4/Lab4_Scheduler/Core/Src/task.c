/*
 * task.c
 *
 *  Created on: Nov 20, 2025
 *      Author: DELL
 */
#include "global.h"

void get3ButtonInput()
{
	getKeyInput(&button1);
	getKeyInput(&button2);
	getKeyInput(&button3);
}

void statusLED()
{
  HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
}

void decreaseCounter() {
    if(counter_horizontal > 0) counter_horizontal--;
    if(counter_vertical > 0) counter_vertical--;
    update_led_7seg_buffer();
}
