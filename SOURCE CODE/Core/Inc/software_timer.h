/*
 * software_timer.h
 *
 *  Created on: Nov 4, 2022
 *      Author: Administrator
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer1_flag;
extern int timer1_counter;
extern int timer2_flag;
extern int timer2_counter;
extern int timer3_flag;
extern int timer3_counter;
extern int timer4_flag;
extern int timer4_counter;
extern int timer5_flag;
extern int timer5_counter;
extern int timer6_flag;
extern int timer6_counter;
extern int timer7_flag;
extern int timer7_counter;
extern int timer8_flag;
extern int timer8_counter;

void setTimer1(int duration);//button
void setTimer2(int duration);//reg
void setTimer3(int duration);//reset
void setTimer4(int duration);//timeout reg
void setTimer5(int duration);//main
void setTimer6(int duration);
void setTimer7(int duration);//alarm
void setTimer8(int duration);//blink led
void timeRun();


#endif /* INC_SOFTWARE_TIMER_H_ */
