// ACM Robot main
// Modified from CPE287 Lab main by James Lumpp
// 1/23/2023
// By: Matthew Whalen

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
#include "RobotCommands.h"

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

void DelayInSeconds(uint32_t seconds)
{
	Delay(seconds * 10000000);
}
	
void Init() {
	PLL_Init();                   // 80 MHz
	PortA_Init();
	PortB_Init();
	PortE_Init();
	PortF_Init();
	UART_Init();     // 115,200 baud
  Timer0A_Init(80000000/100000); 	// start 10 usec timer timeout
	SysTick_Init(80000000/1000);    // one millisecond 
	SW1_Ints_On();
	EnableInterrupts();
}

int main(void){ 
	uint64_t start, end;          // local variables for timestamps
  Init();
	
	printf("\n\nWelcome to ACM Robot\n\n");
	
	SW1_Presses = 0;
	
	start = SysTick_Uptime();
	
	unsigned int speed = 8;
	//DriveForward(10, speed);
	//printf("Moved forward\n");
	//DelayInSeconds(3);
	//Motor_Drive_ints(20,-20, 8, 8, 0);
	DriveBackwards(20, speed);
	DelayInSeconds(3);
	
	//printf("Turned right\n");
	
	end = SysTick_Uptime();
  printf("Elapsed Time = %llu\n",end-start);



} // main
