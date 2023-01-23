#include "RobotCommands.h"
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
