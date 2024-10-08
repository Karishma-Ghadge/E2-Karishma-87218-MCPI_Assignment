/*
 * uart.c
 *
 *  Created on: Sep 23, 2024
 *      Author: sunbeam
 */

#include "uart.h"

void UartInit(uint32_t baud) {

	RCC->AHB1ENR |= BV(GPIO_UART_CLKEN);
	GPIO_UART->AFR[0] |= BV(14) | BV(13) | BV(12) | BV(10) | BV(9) | BV(8);
	GPIO_UART->AFR[0] &= ~(BV(15) | BV(11));

	GPIO_UART->MODER &= ~(BV(UART_TX_PIN*2) | BV(UART_RX_PIN*2));
	GPIO_UART->MODER |= (BV(UART_TX_PIN*2+1) | BV(UART_RX_PIN*2+1));

	RCC->APB1ENR |= BV(UART_CLKEN); //enable uart clock AHB1ENR=>17
	UART->CR1 = BV(USART_CR1_TE_Pos) | BV(USART_CR1_RE_Pos); //enable transmission and reception on uart
	UART->CR1 &= ~(BV(USART_CR1_M_Pos) | BV(USART_CR1_OVER8_Pos)); //set word length in CR1 ->M bit = 8 bit daat length,Over8=0
	UART->CR2 &= ~(USART_CR2_STOP_0 | USART_CR2_STOP_1); //set stop bits in CR2=>1 stop bit

	//set baud rate
	if (baud == 9600) {
		UART->BRR = UBRR_9600;
	} else if (baud == 38400) {
		UART->BRR = UBRR_38400;
	} else if (baud == 115200) {
		UART->BRR = UBRR_115200;
	}
	UART->CR1 |= BV(USART_CR1_UE_Pos);
}

void UartPutch(uint8_t ch) {
	UART->DR = ch;
	while ((UART->SR & BV(USART_CR1_UE_Pos)) == 0)
		;
}

void UartPuts(char str[]) {
	for(int i=0; str[i]!='\0'; i++)
			UartPutch((uint8_t)str[i]);

}
uint8_t UartGetch(void) {
	while ((UART->SR & BV(USART_SR_RXNE_Pos)) == 0)
		;
	uint8_t ch = UART->DR;
	return ch;
}
void UartGets(char str[]) {
	char ch;
	int i = 0;
	do {
		ch = UartGetch();
		str[i]=ch;
		i++;
	} while (ch != '\r');
	str[i++] = '\n';
	str[i] = '\0';
}
