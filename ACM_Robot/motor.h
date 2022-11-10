#include <stdint.h>
#include "tm4c123gh6pm.h"

extern volatile int32_t LTC, RTC;
extern volatile uint32_t DUTY_LEFT, DUTY_RIGHT, LEFT_RUNNING, RIGHT_RUNNING, START_CYCLES;
void  PortB_Init(void);
void  PortE_Init(void);
void SysTick_Init(uint32_t period);

void Motor_Drive_ints(int32_t LTCrequest, int32_t RTCrequest, uint32_t duty_left, uint32_t duty_right, int32_t start_cycles);

uint64_t SysTick_Uptime(void);


