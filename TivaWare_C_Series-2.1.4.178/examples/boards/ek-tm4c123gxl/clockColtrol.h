#ifndef __clockControl__
#define __clockControl__

void Timer_Init_2A(void);
void PortF_Init(void);
void ADC1_Init(void);
void ADC1_Handler(void);
void SYS_Init(void);
void LCD_Calibration(void);
void timer(void);
unsigned int tempTable(double temperature);
void LCD_DisplayTouchPos(void);
void LCD_DrawCube(unsigned short startX, unsigned short startY, unsigned short sildeLen, unsigned short Color);
void printData(void);
void isPressed(void);
void Lab5A(void *p);

#endif

