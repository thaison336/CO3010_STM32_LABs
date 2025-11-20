/*
 * button.h
 *
 *  Created on: Nov 4, 2025
 *      Author: DELL
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "global.h"

struct ButtonStruct
{
	int keyBuffer[4]; // New data in [0], old data in [2]
	int timeOutForPressed; // ms
	int isPressed;
	int isLongPress;
	GPIO_TypeDef *PORT;
	uint16_t PIN;
};

extern struct ButtonStruct button1;
extern struct ButtonStruct button2;
extern struct ButtonStruct button3;

void getKeyInput(struct ButtonStruct* button);
int isButtonPressed(struct ButtonStruct* button);
int isButtonLongPressed(struct ButtonStruct* button);
void resetButton(struct ButtonStruct* button);
void subKeyProcess(struct ButtonStruct* button);


#endif /* INC_BUTTON_H_ */
