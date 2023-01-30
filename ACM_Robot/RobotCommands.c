#include "RobotCommands.h"
#include <stdint.h>
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
}

int ParseCommand(const char* cmd) {
	unsigned int length = strlen(cmd);
	
	if(length == 1) {
		if(toupper(cmd[0]) == 'Q') return 1;
	}
	else if(length < 2)
			return -1; 
	
	char substring[20];
	strncpy(substring, cmd+1, length-1);
	int val = atoi(substring);
	
	printf("%s, %c, %d\n", cmd, cmd[0], val);
	switch(toupper(cmd[0])) {
		case 'F':
			DriveForward(val, 8);
		break;
		case 'B':
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
