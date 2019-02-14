#include "lab2a.h"
#include "C:\Users\taojin\Desktop\EE 474\Lab\EE474-Lab4\TaskB\lab4_starter\LCD\myHeader.h"

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
  
// Turns all LED off and specified LED on
void LEDR_On(void) {
  GPIODATA_PORTE &= ~(PIN2+PIN1+PIN0);
  GPIODATA_PORTE |= PIN0;
}
void LEDY_On(void) {
  GPIODATA_PORTE &= ~(PIN2 + PIN1 + PIN0);
  GPIODATA_PORTE |= PIN1;
}
void LEDG_On(void) {
  GPIODATA_PORTE &= ~(PIN2 + PIN1 + PIN0);
  GPIODATA_PORTE |= PIN2;
}