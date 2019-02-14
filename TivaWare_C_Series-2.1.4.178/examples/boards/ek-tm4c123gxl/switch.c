#include "lab2a.h"

extern unsigned long Touch_ReadX(void);

void Switch_Init(void) {
  volatile unsigned long delay;

  *rcgcgpio |= 0x01; //activate clock for port A
  delay = *rcgcgpio; // allow time for clock to start
  
  *gpio_amsel_a &= ~(PIN2+PIN3); //disable analog on PA2 and 3
  
  *gpio_pctl_a &= ~0x0000FF00; // PCTL GPIO on PA2 and PA3 
  
  *gpio_dir_a &= ~(PIN2+PIN3); // direct PA2 and PA3 as input 
  *gpio_afsel_a &= ~(PIN2+PIN3); // set PA2 and PA3 as regular port function 
  *gpio_den_a |= (PIN2+PIN3);

  *gpio_icr_a = (PIN2 + PIN3);
  *gpio_im_a = (PIN2+PIN3); 
  
  *interrupt_en0 |= 0x1; //enable interrupt at interrupt 19
}

//unsigned long SwitchPedest_Input(void) {
//  int x = (int)Touch_ReadX();
//  return x < 1800; // return 0x8 (pressed) or 0x0 (not pressed)
//}
//
//unsigned long SwitchStart_Input(void) {
//  int x = (int)Touch_ReadX();
//  return x > 2600; // return 0x4 (pressed) or 0x0 (not pressed)
//}