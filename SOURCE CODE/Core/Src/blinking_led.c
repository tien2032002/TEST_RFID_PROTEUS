/*
 * blinking_led.c
 *
 *  Created on: Nov 30, 2022
 *      Author: Administrator
 */


#include "blinking_led.h"
#include "software_timer.h"
#include "main.h"

int led_status=0;

void blink(int duration) {
	switch (led_status) {
		case 0: //init
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
			setTimer8(duration);
			led_status=1;
			break;
		case 1: //led off
			if (timer8_flag==1) {
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
				setTimer8(duration);
				led_status=2;
			}
			break;
		case 2: //led on
			if (timer8_flag==1) {
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
				setTimer8(duration);
				led_status=1;
			}
			break;
		default:
			break;
	}
}
