// CPE287 Lab9 sw1.c
// James Lumpp
// 11/1/2018

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "interrupt.h"

uint32_t SW1_Presses=0;


// ********* SW1_Ints_On *********
// Enable interruprs on SW1 (ASSUMING PORTF IS ALREADY CONFIGURED AND RUNNING)
// input: none
// output: none

void SW1_Ints_On(void){       
              // This function assumes that port F has already been intialized and it just enables interrupts for SW1 (PF4)
//jeljel
	uint32_t sr;
  sr = StartCritical(); 
  GPIO_PORTF_IS_R &= ~0x10;     // (d) PF4 is edge-sensitive
  GPIO_PORTF_IBE_R &= ~0x10;    //     PF4 is not both edges
  GPIO_PORTF_IEV_R &= ~0x10;    //     PF4 falling edge event
  GPIO_PORTF_ICR_R |= 0x10;      // (e) clear flag4
  GPIO_PORTF_IM_R |= 0x10;      // (f) arm interrupt on PF4
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF1FFFFF)|0x00200000; // (g) bits 23-21 priority 1
  NVIC_EN0_R |= 0x40000000;      // (h) enable interrupt 30 (Portf) in NVIC
	EndCritical(sr);
}

//******************GPIOPortF_Handler*************
// increments a global counter and clears the flag for PortF pin 4
//
void GPIOPortF_Handler(void){
//jeljel
  GPIO_PORTF_ICR_R |= 0x10;      // acknowledge flag4

  SW1_Presses = SW1_Presses + 1;
}
