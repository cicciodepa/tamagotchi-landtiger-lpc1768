/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "tamagotchi.h"
#include "RIT.h"
#include "joystick.h"
#include "adc.h"

#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	
  LCD_Initialization();
	joystick_init();											/* Joystick Initialization            */
	init_RIT(0x1312D0);									/* RIT Initialization 50 msec       	*/
	init_timer(0, 0xBEBC20 ); 								/* 0.5 s=> 25MHz * 0.5 = 1.25*10^6 = 1312D0*/
	TP_Init();
	//init_timer(0, 0x2625a8 ); 
	init_timer(1, 0x004C4B40); 
	ADC_init();
	TouchPanel_Calibrate();
	LCD_Clear(White);
	LCD_DrawScreen();
	
	enable_timer(0);
	enable_timer(1);
	enable_RIT();													/* RIT enabled	*/
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);		
  LPC_SC->PCONP |= (1 << 22);		//timer2 power on
	//LPC_SC->PCONP |= (1 << 23);		//timer3
	
	LPC_PINCON->PINSEL1 |= (1<<21);
	LPC_PINCON->PINSEL1 &= ~(1<<20);
	LPC_GPIO0->FIODIR |= (1<<26);
	
  while (1)	
  {
		__ASM("wfi");		
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
