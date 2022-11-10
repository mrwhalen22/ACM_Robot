
// ***************** Timer0A_Init ****************
// Activate Timer0A interrupts for one-time interrupt
// Inputs:  
//          period in units (1/clockfreq), 32 bits
// Outputs: none
void Timer0A_Init(uint32_t period);

extern volatile uint32_t SERVO_DUTY;  //  (valid values are 0-190)

