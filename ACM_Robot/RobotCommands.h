#include <stdint.h>

// Commands used for Robot Initialization and Movement
void DelayInSeconds(uint32_t seconds); 

void DriveForward(int amt, int speed);
void DriveBackwards(int amt, int speed);

void TurnRight(int degrees);
void TurnLeft(int degrees);

void ReadCommand(char* cmdBuf); // limit to 20 characters in buffer
int ParseCommand(const char* cmd);
