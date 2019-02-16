
// EE 474, Lab - 4, Section B

// Section B

#include <tm4c123gh6pm.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "C:\Users\taojin\Desktop\EE 474\Lab\EE474-Lab4\TaskB\lab4_starter\LCD\myHeader.h"
#include "C:\Users\taojin\Desktop\EE 474\Lab\EE474-Lab4\TaskB\lab4_starter\LCD\SSD2119.h"

#define RED_1 		0xF800
#define GREEN_1		0x07E0
#define BLUE_1		0x001F

void Timer_Init_2A(void);
void PortF_Init(void);
//void ADC1_Init(void);
//void ADC1_Handler(void);
void SYS_Init(void);
void LCD_Calibration(void);
void timer(void);
unsigned int tempTable(double temperature);
void LCD_DisplayTouchPos(void);
void LCD_DrawCube(unsigned short startX, unsigned short startY, unsigned short sildeLen, unsigned short Color);
void printData(void);
bool isPressed(void);

volatile bool blink = 0;
volatile int offset_X = 0;
volatile int offset_Y = 0;
volatile int temperature = 0;
volatile int pressed = 0;
volatile int previousPress = 0;
volatile int currentColor = RED_1;

void Lab5A(void *p)
{


	while (1)
	{
		printData();
		isPressed();
		sleep(10);
	}
}

bool isPressed(void)
{
	int z = (int)Touch_ReadZ1();
	return z >= 1000;
}

void printData(void)
{
	LCD_SetCursor(50, 50);
	LCD_PrintInteger(temperature);

	LCD_DisplayTouchPos();
	if (!previousPress && pressed)
	{
		if (pressed && currentColor == RED_1)
			LCD_DrawCube(160, 120, 60, GREEN_1);
		else if (pressed && currentColor == GREEN_1)
			LCD_DrawCube(160, 120, 60, BLUE_1);
		else if (pressed && currentColor == BLUE_1)
			LCD_DrawCube(160, 120, 60, RED_1);		
	}
	previousPress = pressed;
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

void SYS_Init(void)
{
	PortF_Init();
	Timer_Init_2A();
	// ADC1_Init();
	LCD_Init();
	Touch_Init();
}

/** Max countdown value can be adjusted
 *	based on the current clock frequency
 */
void Timer_Init_2A(void)
{
  RCGCTIMER |= 0x04;               // enable clock for Timer 2
  GPTMCFG_2A = 0x00000000;         // select 32-bit timer config
  GPTMCTL_2A = 0x00;               // disable Timer 2
  GPTMCTL_2A |= 0x00000020;				 // enable ADC trigger
  GPTMTAMR_2A |= 0x00000002;       // enable periodic timer mode
  GPTMTAMR_2A &= ~0x000000010000;  // enable countdown mode
  
  // set appropriate second based on clock frequency
  GPTMTAILR_2A = 0xF42400;

  GPTMICR_2A = 0x01;               // clear flag
  GPTMCTL_2A |= 0x01;							 // enable the Timer_2A
}

/** Initialize GPIO Port F Pins to
 *	enable onboard switches and LEDs
 */
void PortF_Init(void)
{
  volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x20;         		// activate clock for Port F
  delay = SYSCTL_RCGC2_R;             // allow time for clock to start
  GPIODIR_PORTF |= 0x0E;          		// direction PF [1:3] to input
  GPIODEN_PORTF |= 0x1F;           		// enable PF [0:4] digital port
}

/** Configures the ADC module, triggered by
 *  timer and interrupts
 */
//void ADC1_Init(void)
//{
//	RCGCADC |= 0x2;							// enable ADC Module 1
//	timer();										// add delay for allowing time to configure RCGCADC
//	ADCACTSS_1 &= ~0xF;					// disable the sample sequencer
//	ADCISC_1 |= 0xF;						// clear the trigger event
//	ADCEMUX_1 |= 0x5000;				// select software trigger for SS3- Timer
//	ADCSSCTL3_1 |= 0xE;					// sample the temperature sensor
//
//	// interrupt service config
//	ADCIM_1 |= 0x8;							// mask interrupt for SS3
//	EN1 |= (1 << 19);						// enable ADC1 SS3 interrupt (interrupt # 51)
//	PRI12 |= (3 << 29);         // set interrupt priority to 3
//
//	ADCISC_1 |= 0x8;						// clear trigger status
//	ADCACTSS_1 |= 0x8;					// enable SS3
//}

/**	ISR for the ADC1 module
 *
 *	Calculate the temperature
 *	Display the color code with LEDs
 */
//void ADC1_Handler(void)
//{
//	ADCPSSI_1 |= 0x3;						// start a conversion sequence 3
//	
//	while (!(ADCRIS_1 & 0x8))
//	{
//		// wait for conversion to complete
//	}
//	float result = (float) ADCSSFIFO3_1;
//	temperature = (int) (147.5 - ((247.5 * result) / 4096));	// temp conversion
//	int color = tempTable(temperature);
//	
//	if ((GPIODATA_PORTF & 0x0E))
//		GPIODATA_PORTF = 0;
//	else
//		GPIODATA_PORTF = color;
//
//	GPTMCTL_2A &= ~0x01;				// disable the Timer_2A
//	ADCISC_1 |= 0x8;								// clear the ADC flag
//	GPTMICR_2A = 0x01;  						// clear timer flag
//	GPTMCTL_2A |= 0x01;							// enable the Timer_2A
//}

void timer(void)
{
	int count = 0;
	for (int i = 0; i < 500000; i++)
		count++;
}

unsigned int tempTable(double temp)
{
	unsigned int LED = 0;
	if (temp > 0 && temp <= 17)
		LED = RED;
	else if (temp > 17 && temp <= 19)
		LED = BLUE;
	else if (temp > 19 && temp <= 21)
		LED = VIOLET;
	else if (temp > 21 && temp <= 23)
		LED = GREEN;
	else if (temp > 23 && temp <= 25)
		LED = YELLOW;
	else if (temp > 25 && temp <= 27)
		LED = LIGHT_BLUE;
	else if (temp > 27 && temp <= 40)
		LED = WHITE;
	
	return LED;
}

void LCD_DisplayTouchPos(void)
{
	int z = (int)Touch_ReadZ1();

	int x = (int)Touch_ReadX() / 10 + offset_X;
	int y = (int)Touch_ReadY() / 10 - offset_Y;

	LCD_SetCursor(60, 230);
	printf("X Coor is: %d and Y Coor is: %d", x, y);
	LCD_SetCursor(60, 200);
	printf("Z1 Coor is: %d ", z);
}

void LCD_DrawCube(unsigned short startX, unsigned short startY, unsigned short sideLen, unsigned short Color)
{
	currentColor = Color;
	
	LCD_DrawFilledRect(startX, startY, sideLen, sideLen, Color);

	for (int i = startX + 1; i < startX + sideLen; i++)
	{
		LCD_DrawLine((unsigned short)i, (unsigned short)startY, (unsigned short)(i + (sideLen / sqrt(2))),
								 (unsigned short)(startY - (sideLen / sqrt(2))), Color);
	}

	for (int i = startY + 1; i < startY + sideLen; i++)
	{
		LCD_DrawLine((unsigned short)(startX + sideLen), (unsigned short)i,
								 (unsigned short)(startX + (sideLen / sqrt(2)) + sideLen),
								 (unsigned short)(i - (sideLen / sqrt(2))), Color);
	}
	
	LCD_DrawRect(startX, startY, sideLen, sideLen, 0xFFFF);

	LCD_DrawLine(startX, startY, (unsigned short)(startX + (sideLen / sqrt(2))), (unsigned short)(startY - (sideLen / sqrt(2))), 0xFFFF);

	LCD_DrawLine((unsigned short)(startX + (sideLen / sqrt(2))), (unsigned short)(startY - (sideLen / sqrt(2))),
							 (unsigned short)((startX + (sideLen / sqrt(2))) + sideLen), (unsigned short)(startY - (sideLen / sqrt(2))), 0xFFFF);

	LCD_DrawLine((unsigned short)((startX + (sideLen / sqrt(2))) + sideLen), (unsigned short)(startY - (sideLen / sqrt(2))),
							 (unsigned short)(startX + sideLen), startY, 0xFFFF);

	LCD_DrawLine((unsigned short)((startX + (sideLen / sqrt(2))) + sideLen), (unsigned short)(startY - (sideLen / sqrt(2))),
							 (unsigned short)((startX + (sideLen / sqrt(2))) + sideLen), (unsigned short)(startY - (sideLen / sqrt(2)) + sideLen), 0xFFFF);

	LCD_DrawLine((unsigned short)((startX + (sideLen / sqrt(2))) + sideLen), (unsigned short)(startY - (sideLen / sqrt(2)) + sideLen),
							 (unsigned short)(startX + sideLen), (unsigned short)(startY + sideLen), 0xFFFF);

}
