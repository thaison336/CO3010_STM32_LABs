/*
 * software_timer.h
 *
 *  Created on: Nov 4, 2025
 *      Author: DELL
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"

struct TimerStruct
{
	int counter;
	int flag;
};

extern struct TimerStruct timer[10];

void setTimer(int idx, int counter);
void timerRun();
int isFlag(int idx);

#endif /* INC_SOFTWARE_TIMER_H_ */
