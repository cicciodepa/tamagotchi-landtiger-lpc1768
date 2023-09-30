/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../tamagotchi.h"
#include "../RIT.h"
#include "../TouchPanel/TouchPanel.h"

static int tick = 0;
static int cuddling = 0;
int volume = 1;
/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER0_IRQHandler (void)
{
	if(cuddling==6){
		cuddling=0;
		contatore2++;
		ECuddling6();
		HAPPYNESS();
		enable_timer(1);
	}
	if(cuddling==5){
		ECuddling5();
		cuddling++;
	}
	if(cuddling==4){
		ECuddling4();
		cuddling++;
	}
	if(cuddling==3){
		ECuddling3();
		cuddling++;
	}
	if(cuddling==2){
		ECuddling2();
		cuddling++;
	}
	if(cuddling==1){
		ECuddling1();
		cuddling++;
	}
	if(cuddling==0){
		disable_RIT();
		
		if(volume>9){
			drawSpeaker3();}
		if(volume>5 & volume <9){
				drawSpeaker2();}
		if(volume>1 & volume<6){
			drawSpeaker1();}
		
		if(volume==0){
			drawSpeaker0();}
			
		if ((ismeal == 0) & (issnack==0) & (hasEnd==0) & (era==0)){
			contatore1++; //conta tick, ogni 2 tick 1 secondo, poi resetto
			if(contatore1==2){
				Eevee0();
				AgeCounter();
			};
			if(contatore1==1)
				Eevee1();
		}
		
		if(hasEnd){
			if(tick==0){
//				disable_timer(2);
//				reset_timer(2);
//				init_timer(2,away[tick+1]);
//				tempo1=away[tick+1];
//				enable_timer(2);
				era=1;
				LCD_DrawRectangle(88,128,59,50,White);
				Eevee2R(140);
				tick++;
				LPC_TIM0->IR = 1;			/* clear interrupt flag */
				return;
			}
			if(tick==1){
//				disable_timer(2);
//				reset_timer(2);
//				init_timer(2,away[tick+1]);
//				tempo1=away[tick+1];
//				enable_timer(2);
				LCD_DrawRectangle(140,128,59,50,White);
				Eevee2R(180);
				tick++;
				LPC_TIM0->IR = 1;			/* clear interrupt flag */
				return;
			}
			if(tick==2){
//				disable_timer(2);
//				reset_timer(2);
//				init_timer(2,away[tick+1]);
//				tempo1=away[tick+1];
//				enable_timer(2);
				LCD_DrawRectangle(180,128,59,50,White);
				Eevee2R(220);
				tick++;
				LPC_TIM0->IR = 1;			/* clear interrupt flag */
				return;
			}
			if(tick==3){

				LCD_DrawRectangle(0,48,240,272,Red);
				LCD_DrawRectangle(16,64,208,240,White);
				GUI_Text(40, 90, (uint8_t *) "eevee ha abbandonato", Red, White);
				LCD_DrawButton(20,254,200,48,Black);
				GUI_Text(75,270, (uint8_t *) "ricomincia", Red, White);
				tick=0;
				LPC_TIM0->IR = 1;			/* clear interrupt flag */
				hasEnd=0;
				enable_RIT();
				return;
			}
		}
		
	//	if (ismeal || issnack)
	//		EeveeToMeal(140);
	//		
		if(issnack){
			if(tick==0){
				//disable_RIT();
				ClearZone(88,128,59,50);
				disable_timer(2);
				reset_timer(2);
				counternotes=0;
				init_timer(2,eating[counternotes]);
				tempo1=eating[counternotes]/4;
				tempo2=tempo1;
				counternotes++;
				sounds=1;
				enable_timer(2);
				Eevee2L(36);
				tick++;
				LPC_TIM0->IR = 1;			/* clear interrupt flag */
				return;
			};
			if(tick==1){
//				disable_timer(2);
//				reset_timer(2);
//				init_timer(2,eating[2]);
//				tempo1=eating[2]/12;
//				enable_timer(2);
				xi=36;
				yi=128;
				for(y=0;y<50; y++){
					for(x=0; x<59; x++){
						point = (y*59)+x;
						EeveeEat(xi,yi,point);
						xi++;
					}
					yi++;
					xi=36;
				};
				tick++;
				LPC_TIM0->IR = 1;			/* clear interrupt flag */
				return;
			};
			if(tick==2){
//				disable_timer(2);
//				reset_timer(2);
//				init_timer(2,eating[4]);
//				tempo1=eating[4]/12;
//				enable_timer(2);
				ClearZone(8,180,24,24);
				if(contatore2<10){
					contatore2++;
				};
				HAPPYNESS();
				Eevee2R(36);
				tick++;
				LPC_TIM0->IR = 1;			/* clear interrupt flag */
				return;
			};
			if(tick==3){
				ClearZone(36,128,59,50);
				issnack = 0;
//				disable_timer(2);
//				reset_timer(2);
//				init_timer(2,eating[6]);
//				tempo1=eating[6];
//				enable_timer(2);
				Eevee0();
				AgeCounter();
				tick=0;
				LPC_TIM0->IR = 1;			/* clear interrupt flag */
				enable_RIT();
				return;
			};
		};
		
		if(ismeal){
			int n=59;
			if(tick==0){
				//disable_RIT();
				ClearZone(88,128,59,50);
				disable_timer(2);
				reset_timer(2);
				counternotes=0;
				init_timer(2,eating[counternotes]);
				tempo1=eating[counternotes]/4;
				tempo2=tempo1;
				counternotes++;
				sounds=1;
				enable_timer(2);
				Eevee2R(140);
				tick++;
				LPC_TIM0->IR = 1;			/* clear interrupt flag */
				return;
			};
			if(tick==1){
				xi=140;
				yi=128;
				for(y=0;y<50; y++){
					for(x=0; x<59; x++){
						point = (y*59)+n;
						n--;
						EeveeEat(xi,yi,point);
						xi++;
					}
					yi++;
					xi=140;
					n=59;
				};
				tick++;
				AgeCounter();
				LPC_TIM0->IR = 1;			/* clear interrupt flag */
				return;
			};
			if(tick==2){
				ClearZone(208,180,24,24);
				if(contatore3<10){
					contatore3++;
				};
				SATIETY();
				Eevee2L(140);
				tick++;
				LPC_TIM0->IR = 1;			/* clear interrupt flag */
				return;
			};
			if(tick==3){
				ClearZone(140,128,59,50);
				ismeal = 0;
				Eevee0();
				AgeCounter();
				tick=0;
				LPC_TIM0->IR = 1;			/* clear interrupt flag */
				enable_RIT();
				return;
			};
		};
	};
	enable_RIT();
	LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	if(getDisplayPoint(&display, Read_Ads7846(), &matrix )){
		if(display.x > 87 & display.x<148 & display.y>127 & display.y <178){
			cuddling=1;
			counternotes=0;
			disable_timer(2);
			reset_timer(2);
			sounds=3;
			init_timer(2,cuddle[counternotes]);
			tempo1=cuddle[counternotes];
			tempo2=cuddle[counternotes];
			counternotes++;
			enable_timer(2);
			disable_timer(1);
		}
	}
	LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
	
}

void TIMER2_IRQHandler (void)
{
	uint16_t SinTable[8] = {0,20,40,60,80,60,40,20};
	
	static int ticks=0;

	if(tempo1>0 & tempo2>0){
		tempo1--;
		if(volume>0){
			LPC_DAC->DACR = (SinTable[ticks]*volume<<6);
			ticks++;
			if(ticks==8) ticks=0;
		}
	}
	
	if(tempo1==0 & tempo2>0){
		tempo2--;
	}
	
	if(tempo1==0 & tempo2==0){
		disable_timer(2);
		reset_timer(2);
		if(sounds==3){
			if(counternotes<16){
				init_timer(2,cuddle[counternotes]);
				tempo1=cuddle[counternotes]/4;
				tempo2=tempo1;
				counternotes++;
				enable_timer(2);
				}
			else{
				disable_timer(2);
			counternotes=0;}
		};
		if(sounds==2){
			if(counternotes<5){
				init_timer(2,away[counternotes]);
				tempo1=eating[counternotes]/4;
				tempo2=tempo1;
				counternotes++;
				enable_timer(2);
				}
			else{counternotes=0;
			disable_timer(2);}
		};
		if(sounds==1){
			if(counternotes<4){
				init_timer(2,eating[counternotes]);
				tempo1=eating[counternotes]/4;
				tempo2=tempo1;
				counternotes++;
				enable_timer(2);
			}
			else{counternotes=0;
			disable_timer(2);}
		};
	}


  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
};


/******************************************************************************
**                            End Of File
******************************************************************************/
