/*
 * accel.h
 *
 *  Created on: Sep 25, 2024
 *      Author: sunbeam
 */

#include"uart.h"
#include "stm32f4xx.h"


void UartInit(uint32_t bps)
{
	RCC->AHB1ENR |= BV(GPIO_AHB1ENR_CCLK);
	GPIO_UART->MODER &= ~(BV(UART_TX*2) | BV(UART_RX*2));
	GPIO_UART->MODER |= (BV((UART_TX*2)+1) | BV((UART_RX*2)+1));

	GPIO_UART->AFR[1] |= (BV(10)| BV(9) | BV(8) | BV(12) | BV(13) | BV(14));
	GPIO_UART->AFR[1] &= ~(BV(11) | BV(15));

	RCC->APB1ENR |= BV(GPIO_APB1ENR_CCLK);

	UART->CR1 = (BV(USART_CR1_TE_Pos)|BV(USART_CR1_RE_Pos));
	UART->CR1 &= ~(BV(USART_CR1_M_Pos) |BV(USART_CR1_OVER8_Pos));

	UART->CR2 &= ~(USART_CR2_STOP_0 | USART_CR2_STOP_1);

	if(bps == 9600)
		UART->BRR = UBRR_9600;

	else if(bps == 38400)
			UART->BRR = UBRR_38400;

	else if (bps == 115200)
			UART->BRR = UBRR_115200;

	UART->CR1 |= BV(USART_CR1_UE_Pos);

}

void UartPutch(uint8_t ch)
{
   UART->DR = ch;
   while((UART->SR & BV(USART_SR_TXE_Pos)) == 0)
	   ;
}

void UartPuts(char str[])
{
	for(int i=0; str[i]!='\0'; i++)
		UartPutch((uint8_t)str[i]);
}

uint8_t UartGetch(void)
{
	while((UART->SR & BV(USART_SR_RXNE_Pos)) == 0);
	uint8_t ch = UART->DR;
	return ch;
}

void UartGets(char str[])
{
	char ch;
	int i=0;
	do{
		ch = UartGetch();
		str[i] = ch;
		i++;
	}while(ch != '\0');
	//str[i++] = '\n';
	//str[i] = '\0';
}










































