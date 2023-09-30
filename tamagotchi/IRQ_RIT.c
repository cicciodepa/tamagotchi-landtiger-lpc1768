/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "tamagotchi.h"
#include "GLCD/GLCD.h" 
#include "timer/timer.h"
#include "adc.h"
/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile int down=0;

void RIT_IRQHandler (void)
{					
	static int selectLeft=0, selectRight=0, L, R;
	ADC_start_conversion();		
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0 & era==0){	
		/* Joytick SELECT pressed */
		disable_timer(0);
		disable_timer(2);
		reset_timer(2);
		if(L>0){
			issnack=1;
			SNACK();
			LCD_DrawButton(8,264,114,48,Black);
			L=0;
		}
		if(R>0){
			ismeal=1;
			MEAL();
			LCD_DrawButton(118,264,116,48,Black);
			R=0;
		};
		counternotes=0;
		sounds=0;
		tempo1=b5/4;
		tempo2=tempo1;
		init_timer(2,b5);
		enable_timer(0);
		enable_timer(2);
		LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
		return;
	};
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0 & era==0){	
		/* Joytick LEFT pressed */
		selectLeft++;
		selectRight=0;
	};
	
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0 & era==0){	
		/* Joytick RIGHT pressed */
		selectRight++;
		selectLeft=0;
	};
	if(selectLeft>0){
		disable_timer(0);
		LCD_DrawButton(118,264,116,48,Black);
		LCD_DrawButton(8,264,114,48,Red);
		selectLeft=0;
		L=1;
		R=0;
		LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
		enable_timer(0);
		return;
	};
	if(selectRight>0){
		disable_timer(0);
		LCD_DrawButton(8,264,114,48,Black);
		LCD_DrawButton(118,264,116,48,Red);
		selectRight=0;
		R=1;
		L=0;
		LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
		enable_timer(0);
		return;
	};
	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0 & era==1){	
		/* Joytick SELECT pressed when dead */
		LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
		resetGame();
		return;
	};
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
