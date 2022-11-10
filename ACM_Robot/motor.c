

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "interrupt.h"

void Delay(uint32_t);


#define PE4 (*((unsigned long volatile *)(0x40024040))) //100 00 00
#define LEFT_TACH_BIT PE4
#define PE5 (*((unsigned long volatile *)(0x40024080))) //1000 00 00
#define RIGHT_TACH_BIT PE5
	
#define PF0 (*((unsigned long volatile *)(0x40025004))) //0001 00
#define PF1 (*((unsigned long volatile *)(0x40025008))) //0010 00
#define PF2 (*((unsigned long volatile *)(0x40025010))) //0100 00
#define PF3 (*((unsigned long volatile *)(0x40025020))) //1000 00
#define PF4 (*((unsigned long volatile *)(0x40025040))) //1 0000 00
#define LEFT_REV PF3
#define LEFT_FWD PF2
#define SW1 PF4
#define SW2 PF0
#define RED_LED PF1

#define PA6 (*((unsigned long volatile *)(0x40004100))) //01 00 00 00 00
#define PA7 (*((unsigned long volatile *)(0x40004200))) //10 00 00 00 00

#define RIGHT_FWD PA6
#define RIGHT_REV PA7



volatile int32_t LTC, RTC;
volatile uint32_t DUTY_LEFT, DUTY_RIGHT, LEFT_RUNNING, RIGHT_RUNNING, START_CYCLES;

//************SysTick_Init***************
// Initialize the SysTick subsystem
// input: period (for the reload value)
// output: none
	
void SysTick_Init(uint32_t period){

  NVIC_ST_CTRL_R = 0;         // disable SysTick during setup
  NVIC_ST_RELOAD_R = period-1;// reload value
  NVIC_ST_CURRENT_R = 0;      // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x8FFFFFFF)|0x40000000; // SysTick is bits 31-29, priority 2          
	
  NVIC_ST_CTRL_R = 0x07; // enable SysTick with core clock AND WITH interrupts  //jeljel

}

volatile uint64_t MSEC_COUNT = 0;
// SysTick_Uptime  returns the number of ticks since reboot as a 64 bit integer
uint64_t SysTick_Uptime(){
 uint32_t sr;
 uint64_t intcount1, intcount2;
 uint32_t freerun1, freerun2;

	sr = StartCritical();
		freerun1 = NVIC_ST_CURRENT_R;
		intcount1 = MSEC_COUNT;
	EnableInterrupts();
												 // deal with the possibility that the free running clock has rolled over
												 // and the interrupt to update teh MSEC_COUNT was blocked.
	DisableInterrupts();
		freerun2 = NVIC_ST_CURRENT_R;
		intcount2 = MSEC_COUNT;
	EndCritical(sr);

	if(intcount2 > intcount1){                  // use second sample because it just rolled over
		return(intcount2*80000 + 79999 - (uint64_t) freerun2);
	} else {                                                   // first sample must be safe so use that
		return(intcount1*80000 + 79999 - (uint64_t) freerun1);
	}
}



void  PortE_Init(void){
//	;------------PortE_Init------------
//; Initialize GPIO Port E pin 4 and pin 5 (PE4 and PE5) as digital input 
//; for a slotted switch tachometer.
	// Enable endge-sensitive interrupts for both rising and falling edges
//; NOTE: This function only configures PE4 and PE5 and thus 
//; must preserve the contents of any of the other control registers.
//; Input: none
//; Output: none
//; Modifies: R0, R1, R2

//PortE_Init
   
	SYSCTL_RCGC2_R |= 0x10;
	while((SYSCTL_PRGPIO_R & 0x10)==0)
       {};	//Loop while waiting for clock to init
	GPIO_PORTE_AMSEL_R &= ~ 0x30;       //; 3) disable analog functionality
	GPIO_PORTE_PCTL_R &= ~ 0x00FF0000;   //; 4) configure as GPIO
	GPIO_PORTE_DIR_R &= ~ 0x30;       //; 5) set direction register
	GPIO_PORTE_AFSEL_R &= ~ 0x30;    //; 6) regular port function
	GPIO_PORTE_DEN_R |= 0x30;       //; 7) enable Port F digital port
	
	//; Your code here //jeljel

  GPIO_PORTE_IS_R &= ~0x30;     //     PF4,5 edge-sensitive
  GPIO_PORTE_IBE_R |= 0x30;     //     PF4,5 both edges
//  GPIO_PORTE_IEV_R &= ~0x30;  //     PF4,5 falling edge event
  GPIO_PORTE_ICR_R |= 0x30;      //     clear flags4,5
  GPIO_PORTE_IM_R |= 0x30;      //     arm interrupt on PF4 and PF5
	NVIC_PRI1_R = (NVIC_PRI1_R&0xFFFFFF1F)|0x00000020;  // bits 7-5 priotirty 1
  NVIC_EN0_R |= 0x00000010;      //     enable interrupt bit4 (portE) in NVIC
}

//*************GPIOPortE_Handler*******************
//handles interrupts for the two tachometers.  
//When an interrupt occurs on PE4 the left tachemter has transitioned
//When an interrupt occurs on PE5 the right tachemter has transitioned
// SInce the motors may be driving forward or backward we need to know the direction.
// directions is determined by the sign of the LTC or RTC.

void GPIOPortE_Handler(void)
{
		  /****** check if the left tachometers has transitioned (RIS bit 4) *****/
			if (GPIO_PORTE_RIS_R & 0x10)
			{
				    GPIO_PORTE_ICR_R |= 0x10;      // acknowledge flag4
				
						if (LTC > 0)    // transition occured, update the tack count based on the direction
							LTC--;
						else if (LTC < 0) 
							LTC++;
						else
							LEFT_RUNNING = 0;
			}

			/****** check if the right tachometers has transitioned (RIS bit 5) ******/
						
			if (GPIO_PORTE_RIS_R & 0x20)
			{
					  GPIO_PORTE_ICR_R |= 0x20;      // acknowledge flag5

						if (RTC > 0)    // transition occured, update the tack count based on the direction
							RTC--;
						else if (RTC < 0) 
							RTC++;
						else
							RIGHT_RUNNING = 0;
			}
}  //tach_isr


void Motor_Drive_ints(int32_t LTCrequest, int32_t RTCrequest, uint32_t duty_left, uint32_t duty_right, int32_t start_cycles)
{
	DUTY_LEFT = duty_left;
	DUTY_RIGHT = duty_right;
	START_CYCLES = start_cycles;

	LTC = LTCrequest;   // set counter to the requested number of tach transitions
  if(LTCrequest == 0) 
			LEFT_RUNNING =0;
	else
			LEFT_RUNNING =1;
		
	RTC = RTCrequest;
	if(RTCrequest == 0) 
			RIGHT_RUNNING =0;
	else
			RIGHT_RUNNING =1;
	
}  //Motor_Drive


//************************SysTick_Handler************************
// this functions is called every millisecond.
// each 20 msec block is used to drive a duty cycle (0-20) 
void SysTick_Handler(void){
static	uint32_t msec_count=0;
	                    // No need to clear the a flag
	RED_LED ^= 0xff;  //toggle Red LED
	MSEC_COUNT++;

			if (++msec_count > 20) 
					msec_count = 1; 

			/*********  Drive the Left motor *********/
			
			if (LEFT_RUNNING && (msec_count > DUTY_LEFT)){
						LEFT_FWD = 0;  // zero for this part of period to form duty cycle
						LEFT_REV = 0;
			}  else {
					if (LTC > 0)
							LEFT_FWD = 0xFF;  // dirve wheel fwd (or backward) based on goal
					else if (LTC < 0)
							LEFT_REV = 0xFF;			
			}
			
			/*********  Drive the Right motor *********/
			
			if (RIGHT_RUNNING &&(msec_count > DUTY_RIGHT)){
						RIGHT_FWD = 0;  // zero for this part of period to form duty cycle
						RIGHT_REV = 0;
			}  else {
					if (RTC > 0)
							RIGHT_FWD = 0xFF;  // dirve wheel fwd (or backward) based on goal
					else if (RTC < 0)
							RIGHT_REV = 0xFF;
			}
	
}  //motor_systick_isr

