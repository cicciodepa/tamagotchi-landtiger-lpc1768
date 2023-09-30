#ifndef __TAMAGOTCHI_H 
#define __TAMAGOTCHI_H

#include "LPC17xx.h"

extern int contatore1;
extern int contatore2;
extern int contatore3; 
extern volatile int ismeal;
extern volatile int issnack; 
extern volatile int hasEnd;
extern int x,y,xi,yi,point;
extern int era;
extern int sounds;
extern int tempo1;
extern int tempo2;
extern const int b5;
extern const int eating[];
extern const int away[];
extern const int cuddle[];
extern uint8_t counternotes;
extern const uint16_t Speaker3[576];
extern const uint16_t Speaker2[576];
extern const uint16_t Speaker1[576];
extern const uint16_t Speaker0[576];

void EeveeEat(int xi, int yi, int point);
void LCD_DrawScreen(void);
void HAPPYNESS(void);
void SATIETY(void);
void Eevee0(void);
void Eevee1(void);
void Eevee2L(int xpos);
void Eevee2R(int xpos);
void EeveeToMeal(int xpos);
void EeveeToSnack(int xpos);
void AgeCounter(void);
void SNACK(void);
void MEAL(void);
void ClearZone(int posx, int posy, int width, int height);
void LCD_DrawButton(int posx, int posy, int width, int height, uint16_t color);
void resetGame(void);
void endGame(void);
void ECuddling1(void);
void ECuddling2(void);
void ECuddling3(void);
void ECuddling4(void);
void ECuddling5(void);
void ECuddling6(void);
void drawSpeaker0(void);
void drawSpeaker1(void);
void drawSpeaker2(void);
void drawSpeaker3(void);

#endif 
