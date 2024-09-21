/*
 * led.c
 *
 *  Created on: Sep 20, 2024
 *      Author: sunbeam
 */

#include "led.h"

void LedInit(uint32_t pin)
{
	//enable GPIOD clock ->RCC->AHB1ENR
	RCC->AHB1ENR |= BV(GPIOD_LED_CLKEN);

	//configure GPIOD.13 as output ->MODER ->01
	GPIOD_LED->MODER &= ~BV(pin*2+1);
	GPIOD_LED->MODER |= BV(pin*2);

	//configure GPIOD.13 as open drain output ->OTYPER->1
	GPIOD_LED->OTYPER |= BV(pin);

	//configure GPIOD.13 as low speed ->OSPEEDR ->00
	GPIOD_LED->OSPEEDR &= ~(BV(pin*2+1) | BV(pin*2));

	//configure GPIOD.13 with pull up resistor PUPDR->01
	GPIOD_LED->PUPDR &= ~BV(pin*2+1);
	GPIOD_LED->PUPDR |= BV(pin*2);
}

void LedOn(uint32_t pin)
{
	//GPIOD->ODR ->1
	GPIOD_LED->ODR |= BV(pin);
}

void LedOff(uint32_t pin)
{
	//GPIOD->ODR ->0
	GPIOD_LED->ODR &=~BV(pin);
}
void LedBlink(uint32_t pin,uint32_t delayMs)
{
	LedOn(pin);
	DelayMs(1000);
	LedOff(pin);
}
