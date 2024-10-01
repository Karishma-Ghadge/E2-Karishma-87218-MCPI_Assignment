/*
 * switch_intr.h
 *
 *  Created on: Sep 21, 2024
 *      Author: sunbeam
 */

#ifndef SWITCH_INTR_H_
#define SWITCH_INTR_H_

#include "stm32f4xx.h"

#define GPIO_SWTICH        GPIOA
#define SWITCH_PIN          0
#define SWITCH_GPIO_CLKEN   0
#define SWITCH_EXTI         0

void SwitchInit(void);
void EXTI0_IRQHandler(void);


extern uint32_t SwitchExtiFlag;
#endif /* SWITCH_INTR_H_ */
