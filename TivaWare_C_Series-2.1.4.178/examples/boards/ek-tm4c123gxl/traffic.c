
#include "lab2a.h"
#include <stdint.h>
#include <stdbool.h>
#include "C:\Users\taojin\Desktop\EE 474\Lab\EE474-Lab4\TaskB\lab4_starter\LCD\SSD2119.h"
#include "C:\Users\taojin\Desktop\EE 474\Lab\EE474-Lab4\TaskB\lab4_starter\LCD\myHeader.h"

#define RED_1 		0xF800
#define GREEN_1		0x07E0
#define BLUE_1		0x001F

bool SwitchPedest_Input(void);
bool SwitchStart_Input(void);
void LCD_Calibration(void);
void DrawButton(void);
bool isPressed(void);
void LCD_DisplayTouchPos(void);
void LED_Init(void);
void readEvent(int state);
void FSM(void);

// FSM state definition
const int OFF = 0;
const int GO = 1;
const int STOP = 2;
const int WARN = 3;

volatile int state = 0;
volatile int next_state = 0;

volatile int offset_X = 0;
volatile int offset_Y = 0;
volatile int xPos = 0;
volatile int yPos = 0;

volatile int start_stop_count = 0;
volatile int passenger_count = 0;
volatile int FSM_count = 0;
volatile int start_stop_status = 0;
volatile int passenger_status = 0;


bool SwitchPedest_Input(void) {
	// return xPos < 190 && xPos > 130 && yPos > 100 && yPos < 150;
  return xPos < 280 && xPos > 240;
}

bool SwitchStart_Input(void) {
  // return xPos > 230 && xPos < 290 && yPos > 100 && yPos < 150;
	return xPos > 310 && xPos < 350;
}

bool isPressed(void)
{
	int z = (int)Touch_ReadZ1();
  return z > 1000;
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

// executes the output of the parameter state
void readEvent(int state) {
  GPIODATA_PORTE &= ~0x7;
	if (state == OFF) {
    GPIODATA_PORTE &= ~0x7;
	} else if (state == GO) {
    GPIODATA_PORTE |= PIN2;
  } else if (state == STOP) {
    GPIODATA_PORTE |= PIN0;
  } else if (state == WARN) {
    GPIODATA_PORTE |= PIN1;
  }
}

void FSM(void)
{
  if (state == GO)
  {
    if (start_stop_status) 
    {
      start_stop_status = 0;
      next_state = OFF;
    }
    else if (passenger_status)
		{
			passenger_status = 0;
			next_state = WARN;
		}
    else
      next_state = STOP;
  }
  else if (state == STOP)
  {
    if (start_stop_status) 
    {
      start_stop_status = 0;
      next_state = OFF;
    }
    else
      next_state = GO;
  }
  else if (state == WARN)
  {
    if (start_stop_status)
    {
      start_stop_status = 0;
      next_state = OFF;
    }
    else
      next_state = STOP;
  }
  else
  {
    if (start_stop_status)
      next_state = STOP;
  }
  
  state = next_state;         // assign the current state to the next state
	readEvent(state);
}