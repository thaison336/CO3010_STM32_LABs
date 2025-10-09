///*
// * software_timer.c
// *
// *  Created on: Oct 8, 2025
// *      Author: DELL
// */
//#include "software_timer.h"
//
//int timer_flag[101];
//int timer_counter[101];
//
//void init_timer() {
//    for (int i = 0; i <= 100; i++) {
//        timer_flag[i] = 0;
//        timer_counter[i] = 0;
//    }
//}
//void setTimer_i(int i, int duration){
//	timer_counter[i] = duration;
//	timer_flag[i] = 0;
//}
//void timerRun(){
//	if (timer_counter[1] > 0){
//		timer_counter[1] --;
//		if (timer_counter[1] <= 0) {
//			timer_flag[1] = 1;
//		}
//	}
//}
