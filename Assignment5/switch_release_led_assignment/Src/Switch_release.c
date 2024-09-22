/*
 * Switch_release.c
 *
 *  Created on: Sep 22, 2024
 *      Author: sunbeam
 */

#include "stm32f4xx.h"
#include "switch_release.h"

void SwitchInit(void) {
	RCC->AHB1ENR |= BV(SWITCH_GPIO_CLKEN);

	GPIOA->MODER &= ~(BV(SWITCH_PIN*2+1) | BV(SWITCH_PIN*2));

	GPIOA->PUPDR &= (BV(SWITCH_PIN*2) | BV(SWITCH_PIN*2));

	EXTI->FTSR |= BV(SWITCH_EXTI);

	EXTI->IMR |= BV(SWITCH_EXTI);

	SYSCFG->EXTICR[0] &= ~(BV(3) | BV(2) | BV(1) | BV(0));

	NVIC_EnableIRQ(EXTI0_IRQn);

}

volatile uint32_t SwitchFlagExti = 0;

void EXTI0_IRQHandler(void) {
	EXTI->PR |= BV(SWITCH_EXTI);

	SwitchFlagExti = 1;
}
