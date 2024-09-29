/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "stm32f4xx.h"
#include "i2c.h"
#include "i2c_lcd.h"
#include "accel.h"

int main(void) {

	int ret, count;
	LIS_Data val;
	char str[32];
	SystemInit();
	ret = Lcd_Init();
	if (ret) {
		Lcd_Puts(LCD_LINE1,"Accel read");
		for (count = 1; count < 100; count++) {
			sprintf(str, "X=%d, Y=%d, Z=%d\r\n", val.x, val.y, val.z);
			Lcd_Puts(LCD_LINE2, str);
			DelayMs(1000);
		}
	}
	return 0;
}
