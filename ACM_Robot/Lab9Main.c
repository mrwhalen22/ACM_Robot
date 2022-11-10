// CPE287 Lab9 main
// James Lumpp
// 10/28/2018

#include <stdint.h>
#include <stdio.h>
#include "tm4c123gh6pm.h"
#include "interrupt.h"
#include "PLL.h"
#include "UART.h"
#include "ports.h"
#include "motor.h"
#include "ultrasonic.h"
#include "sw1.h"

// Define some useful port pins using bit-specific addressing

#define PF0 (*((unsigned long volatile *)(0x40025004))) //0001 00
#define SW2 PF0
#define PF1 (*((unsigned long volatile *)(0x40025008))) //0010 00
#define RED_LED PF1
#define PF4 (*((unsigned long volatile *)(0x40025040))) //1 0000 00
#define SW1 PF4

//********************Delay****************
// delay function which delays 3*ulCount cycles
// input: loop count
//output: none
void Delay(uint32_t);
	//Keil uVision Code
	__asm void
	Delay(uint32_t ulCount)
	{
    subs    r0, #1
    bne     Delay
    bx      lr
	}
	
int main(void){ 
  uint32_t i;	
	uint64_t start, end;          // local variables for timestamps
  PLL_Init();                   // 80 MHz
	PortA_Init();
	PortB_Init();
	PortE_Init();
	PortF_Init();
	UART_Init();     // 115,200 baud
  Timer0A_Init(80000000/100000); 	// start 10 usec timer timeout
	SysTick_Init(80000000/1000);    // one millisecond 
	
	SW1_Ints_On();
	
	printf("\n\nWelcome to 287 Robot\n\n");
	
	SW1_Presses = 0;
	
//	printf("LTC, RTC, SW1_Presses are:"); 

  EnableInterrupts();
	
	start = SysTick_Uptime();
  Delay(100);
	end = SysTick_Uptime();
	printf("elapsed time %llu - %llu = %llu\n",end, start, end-start);
	
	Motor_Drive_ints(10,10, 5, 5, 0);  // move forward a little
	
	end = SysTick_Uptime();
	printf("after motor %llu - %llu = %llu\n",end, start, end-start);

	while(1)
	{
	for (i=0;i<=190;i+=10){
	  SERVO_DUTY = i;
		Delay(0x400000);
	}

		

	}


} // main
