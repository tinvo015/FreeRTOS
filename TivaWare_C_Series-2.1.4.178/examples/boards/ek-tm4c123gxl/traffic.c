
#include "lab2a.h"
#include <stdint.h>
#include <stdbool.h>
#include "C:\Users\taojin\Desktop\EE 474\Lab\EE474-Lab4\TaskB\lab4_starter\LCD\SSD2119.h"
#include "C:\Users\taojin\Desktop\EE 474\Lab\EE474-Lab4\TaskB\lab4_starter\LCD\myHeader.h"

#define RED_1 		0xF800
#define GREEN_1		0x07E0
#define BLUE_1		0x001F

extern void LEDR_On(void);
extern void LEDY_On(void);
extern void LEDG_On(void);
extern void timer0A_init(void);
bool SwitchPedest_Input(void);
bool SwitchStart_Input(void);
void LCD_Calibration(void);
void DrawButton(void);
void isPressed(void);
void LCD_DisplayTouchPos(void);
void LED_Init(void);
void readEvent(int state);

volatile int offset_X = 0;
volatile int offset_Y = 0;
volatile int pressed = 0;
volatile int xPos = 0;
volatile int yPos = 0;


bool SwitchPedest_Input(void) {
	// return xPos < 190 && xPos > 130 && yPos > 100 && yPos < 150;
  return xPos < 190 && xPos > 130;
}

bool SwitchStart_Input(void) {
  // return xPos > 230 && xPos < 290 && yPos > 100 && yPos < 150;
	return xPos > 230 && xPos < 290;
}

void isPressed(void)
{
	int z = (int)Touch_ReadZ1();
	if (z > 1000)
		pressed = 1;
	else
		pressed = 0;
}

void LCD_Calibration(void)
{
  LCD_DrawFilledCircle(160, 120, 10, 0x1234);
  LCD_SetCursor(60, 230);
  LCD_PrintString("Please Hit the Center Circle to Calibrate");

  int z = (int)Touch_ReadZ1();

  int x = (int)Touch_ReadX() / 10;
  int y = (int)Touch_ReadY() / 10;
  offset_X = abs(x - 160);
  offset_Y = abs(y - 120);
}

void LCD_DisplayTouchPos(void)
{
	int z = (int)Touch_ReadZ1();
	xPos = (int)Touch_ReadX() / 10 + offset_X;
	yPos = (int)Touch_ReadY() / 10 - offset_Y;

	LCD_SetCursor(60, 230);
	printf("X Coor is: %d and Y Coor is: %d", xPos, yPos);
	LCD_SetCursor(60, 200);
	printf("Z1 Coor is: %d ", z);
}

void DrawButton(void) {
  LCD_DrawFilledCircle(80, 120, 50, RED_1);
  LCD_DrawFilledCircle(240, 120, 50, GREEN_1);
}

void LED_Init(void) {
  volatile unsigned long delay;
  RCGCGPIO |= 0x10; //activate clock for port E
  delay = RCGCGPIO;
  
  GPIOPCTL_PORTE &= ~0x00000FFF; //enable clock for PE0-2
  GPIOAMSEL_PORTE &= ~(PIN2+PIN1+PIN0); //disable analog
  GPIODIR_PORTE |= (PIN2+PIN1+PIN0); 
  GPIOAFSEL_PORTE &= ~(PIN2+PIN1+PIN0); 
  GPIODEN_PORTE |= (PIN2+PIN1+PIN0); 
	
	GPIODATA_PORTE |= (PIN0+PIN1+PIN2);
}
