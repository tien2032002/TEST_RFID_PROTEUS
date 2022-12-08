/*
 * fsm.c
 *
 *  Created on: Nov 11, 2022
 *      Author: Acer
 */

#include "global.h"
#include "fsm.h"
#include "button.h"
#include "software_timer.h"
#include "main.h"
#include "memory_struct.h"
#include "blinking_led.h"


int state=INIT;
int admin_id;

void reset_buffer() {
	for (int i=0;i<5;i++) {
		CARD_BUF[i]=0;
	}
}

void fsm_run() {
	switch (state) {
	case INIT:
		//quet the admin va bam nut de luu vao bo nho
		//sau khi co the duoc quet , thay doi state
		if (equalZero(CARD_BUF)==0) { //kiem tra da quet the chua
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
			if (flagForButtonPress[REG_IDX]==1) {//nhan nut regist
				flagForButtonPress[REG_IDX]=0;//reset flag
				set_admin(CARD_BUF);//set admin
				reset_buffer();//reset buffer
				state=UNLOCK;//chuyen trang thai
				setTimer6(10);
			}
		}
		else {
			blink(10);
		}
		break;
	case UNLOCK:
		if (timer6_flag==1) {
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		}

		//dua ra tin hieu mo cua
		HAL_GPIO_WritePin(LOCK_SIGNAL_GPIO_Port, LOCK_SIGNAL_Pin, GPIO_PIN_RESET);

		//neu bam nut dong cua, qua trang thai dong cua
		if (flagForButtonPress[LOCK_IDX]==1) {
			reset_buffer();
			flagForButtonPress[LOCK_IDX]=0;
			state=LOCK;
		}
		else if (flagForButtonPress[UNLOCK_IDX]==1) {
			flagForButtonPress[UNLOCK_IDX]=0;
		}
		//bam nut dang ki the de qua trang thai dang ki the
		else if (flagForButtonPress[REG_IDX]==1)  {
			flagForButtonPress[REG_IDX]=0;
			reset_buffer();
			setTimer2(500);
			state=REG_PROCESS;
		}
		//bam nut reset de qua trang thai xoa bo nho
		else if (flagForButtonPress[RESET_IDX]==1) {
			flagForButtonPress[RESET_IDX]=0;
			reset_buffer();
			setTimer3(500);
			state=MEM_DELETE;
		}

		//quet the
		/*if (the duoc quet da duoc dang ki) {
			state=LOCK;
		}*/
		else if (equalZero(CARD_BUF)==0) {
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
			setTimer6(10);
			if (search(CARD_BUF)==1) {
				state=LOCK;
			}
			reset_buffer();
		}

		break;
	case LOCK:
		if (timer6_flag==1) {
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		}
		//dua ra tin hieu dong cua
		HAL_GPIO_WritePin(LOCK_SIGNAL_GPIO_Port, LOCK_SIGNAL_Pin, GPIO_PIN_SET);

		//neu bam nut mo cua, qua trang thai mo cua
		if (flagForButtonPress[UNLOCK_IDX]==1) {
			flagForButtonPress[UNLOCK_IDX]=0;
			state=UNLOCK;
		}
		else if (flagForButtonPress[LOCK_IDX]==1) {
			flagForButtonPress[LOCK_IDX]=0;
		}
		else if (flagForButtonPress[REG_IDX]==1) {
			flagForButtonPress[REG_IDX]=0;
		}
		else if (flagForButtonPress[RESET_IDX]==1) {
			flagForButtonPress[RESET_IDX]=0;
		}
		//quet the
		/*if (the duoc quet da duoc dang ki) {
			state=UNLOCK;
		}
		else {
			state=WRONG1;
		}*/
		else if (equalZero(CARD_BUF)==0) {
			if (search(CARD_BUF)==1) {
				reset_buffer();
				state=UNLOCK;
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
				setTimer6(10);
			}
			else {
				state=WRONG1;
				reset_buffer();
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
				setTimer6(10);
			}
		}

		break;
	case WRONG1:
		//quet the
		/*if (the duoc quet da duoc dang ki) {
			state=UNLOCK;
		}
		else {
			state=WRONG2;
		}*/
		if (timer6_flag==1) {
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		}
		if (equalZero(CARD_BUF)==0) {
			if (search(CARD_BUF)==1) {
				reset_buffer();
				state=UNLOCK;
			}
			else {
				reset_buffer();
				state=WRONG2;
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
				setTimer6(10);
			}
		}
		break;
	case WRONG2:
		if (timer6_flag==1) {
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		}
		//quet the
		/*if (the duoc quet da duoc dang ki) {
			state=UNLOCK;
		}
		else {
			state=ALARM;
			setTimer1(500);
		}*/
		if (equalZero(CARD_BUF)==0) {
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
			setTimer6(10);
			if (search(CARD_BUF)==1) {
				reset_buffer();
				state=UNLOCK;

			}
			else {
				reset_buffer();
				state=ALARM;
				setTimer7(500);
			}
		}
		break;
	case ALARM:
		if (timer6_flag==1) {
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		}
		HAL_GPIO_WritePin(GPIOA, BUZZER_Pin, GPIO_PIN_SET);
		//quet the
		/*if (the duoc quet da duoc dang ki) {
			state=UNLOCK;
		}
		else {
			state=ALARM;
		}*/
		if (equalZero(CARD_BUF)==0) {
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
			setTimer6(10);
			if (search(CARD_BUF)==1) {
				reset_buffer();
				state=UNLOCK;
				HAL_GPIO_WritePin(GPIOA, BUZZER_Pin, GPIO_PIN_RESET);
				setTimer7(0);
			}
			else {
				state=ALARM;
				reset_buffer();
				setTimer7(500);
			}
		}
		if (timer7_flag==1) {
			timer7_flag=0;
			state=WRONG2;
			reset_buffer();
			HAL_GPIO_WritePin(GPIOA, BUZZER_Pin, GPIO_PIN_RESET);
		}
		break;
	case MEM_DELETE:
		//Trong 5s k lam gi se tro ve trang thai UNLOCK
		//Neu the duoc quet vao la the admin se xoa bo nho
		//Neu the duoc quet khong phai the admin, tro ve trang thai UNLOCK
		if (timer3_flag==1) {
			state=UNLOCK;
			setTimer3(0);
		}
		else {
			if (equalZero(CARD_BUF)==0) {
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
				if (check_admin(CARD_BUF)==1) {
					delete_card();
					state=UNLOCK;
					reset_buffer();
				}
				else {
					setTimer3(0);
					reset_buffer();
					state=UNLOCK;
				}
			}
			else {
				blink(10);
			}
		}
		break;
	case REG_PROCESS:
		//Trong 5s k lam gi se tro ve trang thai UNLOCK
		//Neu the duoc quet khong phai the admin, tro ve trang thai UNLOCK
		//Neu the duoc quet vao la the admin, sau do quet the can dang ki vao se luu the vua quet vao bo nho
		if (timer2_flag==1) {
			state=UNLOCK;
		}
		else {
			if (equalZero(CARD_BUF)==0) {
				if (check_admin(CARD_BUF)==1) {
					state=REGIST;
					setTimer4(5000);
					reset_buffer();
					HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
				}
				else {
					setTimer2(0);
					reset_buffer();
					state=UNLOCK;
				}
			}
			else {
				blink(10);
			}
		}
		break;
	case REGIST:
		if (timer4_flag==1) {
			state=UNLOCK;
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		}
		else {
			if (equalZero(CARD_BUF)==0) {
					add_new_card(CARD_BUF);
					state=UNLOCK;
					reset_buffer();
					HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
			}
		}
	default:
		break;
	}
}
