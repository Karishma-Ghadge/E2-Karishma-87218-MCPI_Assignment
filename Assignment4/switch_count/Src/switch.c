/*
 * switch_intr.c
 *
 *  Created on: Sep 21, 2024
 *      Author: sunbeam
 */

#include "switch.h"

void SwitchInit(void) {
	//Enable clock
	RCC->AHB1ENR |= BV(SWITCH_GPIO_CLKEN);
	//set gpio mode as input
	GPIOA->MODER &= ~(BV(SWITCH_PIN*2+1) | BV(SWITCH_PIN*2));
	GPIOA->PUPDR &= ~(BV(SWITCH_PIN*2+1) | BV(SWITCH_PIN*2));
	EXTI->FTSR |= BV(SWITCH_EXTI);
	EXTI->IMR |= BV(SWITCH_EXTI); //enable unmask exti interrupt
	SYSCFG->EXTICR[0] &= ~(BV(3) | BV(2) | BV(1) | BV(0));
	NVIC_EnableIRQ(EXTI0_IRQn);
}

uint32_t SwitchExtiFlag = 0;

void EXTI0_IRQHnadler(void) {
	EXTI->PR |= BV(SWITCH_EXTI);

	SwitchExtiFlag = 1;
}
