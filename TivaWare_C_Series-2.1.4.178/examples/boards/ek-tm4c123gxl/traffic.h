#ifndef __traffic__
#define __traffic__

void LCD_Init(void);
void Touch_Init(void);
void LED_Init(void);
void DrawButton(void);
bool SwitchStart_Input(void);
bool SwitchPedest_Input(void);
void LED_Init(void);
void readEvent(int state);
void FSM(void);
bool isPressed(void);
void LCD_DisplayTouchPos(void);
void LCD_Calibration(void);

#endif