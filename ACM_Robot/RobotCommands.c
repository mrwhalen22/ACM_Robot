#include "RobotCommands.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "tm4c123gh6pm.h"
#include "interrupt.h"
#include "PLL.h"
#include "UART.h"
#include "ports.h"
#include "motor.h"
#include "ultrasonic.h"
#include "sw1.h"

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
	Delay(seconds * 10000000); // convert from microsecs to secs
}

void DriveForward(int amt, int speed) {
	int dutyCycle = speed % 11;
	Motor_Drive_ints(amt,amt, dutyCycle, dutyCycle, 0);  // Forward move
	
}

void TurnRight(int degrees) {
	//[0, 180] -> [0, 40]
	int amt = (degrees * 2) / 9;
	//printf("Degrees = %i\n", amt);
	Motor_Drive_ints(amt, -amt, 8, 8, 0);  // Stationary right turn
}

void TurnLeft(int degree)
{
	//
	int amt =(degree *2)/9;
	//printf("Degrees = %i\n", amt);
	Motor_Drive_ints(-amt, amt, 8, 8,0);
}

void DriveBackwards(int amt, int speed) {
	int dutyCycle = speed % 11;
	Motor_Drive_ints(-amt,-amt, dutyCycle, dutyCycle, 0);  // go backward
}

void ReadCommand(char* cmdBuf) {
	printf("Please Enter a command (F,B,L,R) with val > 0: ");
	scanf("%20s", cmdBuf); printf("\n"); 
	printf("%s\n", cmdBuf);
}

void Boogie() {
	for(int i = 0; i < 3; ++i) {
		DriveForward(10,8);
		DelayInSeconds(1);
		DriveBackwards(10,8);
		DelayInSeconds(1);
		TurnLeft(90);
		DelayInSeconds(1);
		DriveForward(10,8);
		DelayInSeconds(1);
		DriveBackwards(10,8);
		DelayInSeconds(1);
		TurnRight(90);
		DelayInSeconds(1);
	}
}

int ParseCommand(const char* cmd) {
	unsigned int length = strlen(cmd);
	
	if(length == 1) {
		if(toupper(cmd[0]) == 'Q') return 1;
	}
	else if(length < 2)
			return -1; 
	
	// extract everything after first letter and convert to int
	char substring[20];
	strncpy(substring, cmd+1, length-1);
	int val = atoi(substring);
	
	//printf("%s, %c, %d\n", cmd, cmd[0], val);
	
	// choose command based on first letter
	switch(toupper(cmd[0])) {
		case 'F':
			DriveForward(val, 8);
		break;
		case 'B':
			if(strcmp(cmd, "boogie") == 0)
				Boogie();
			DriveBackwards(val, 8);
		break;
		case 'L':
			TurnLeft(val);
		break;
		case 'R':
			TurnRight(val);
		break;
		case 'Q':
			return 1;
		default:
			return -1;
			
	}
	return 0;
	
	
}
