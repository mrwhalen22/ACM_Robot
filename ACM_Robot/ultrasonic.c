

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "interrupt.h"

void Delay(uint32_t);

#define PF1 (*((unsigned long volatile *)(0x40025008))) //0010 00
#define RED_LED PF1
#define PB3 (*((unsigned long volatile *)(0x40005020))) //10 00 00
#define PB4 (*((unsigned long volatile *)(0x40005040))) //01 00 00 00
	
#define PA5 (*((unsigned long volatile *)(0x40004080)))   //00 10 00 00 00
//#define PA6 (*((unsigned long volatile *)(0x40004100))) //01 00 00 00 00
//#define PA7 (*((unsigned long volatile *)(0x40004200))) //10 00 00 00 00


#define ULTRASONIC_ECHO PB3
#define ULTRASONIC_TRIG PB4

#define SERVO_PIN PA5  //jeljel // Select come GPIO pin for the servo PX#

volatile uint32_t SERVO_DUTY = 50;  // set to neutral servo position to start (valid values are 0-100)
volatile uint32_t ULTRA_START_CONVERSION = 0;  // global used to request an ultrasonic sample

void PortB_Init(void){

	SYSCTL_RCGC2_R |=0x02;								//Init clock for PortB
	while((SYSCTL_PRGPIO_R & 0x02)==0)
       {};	//Loop while waiting for clock to init
	GPIO_PORTB_DIR_R |= 0x10;							//Set PB4 to Output
	GPIO_PORTB_DIR_R &= ~0x08;						//Set PB3 to Input
	GPIO_PORTB_AFSEL_R &= ~0x18;					//Clear AFSEL
	GPIO_PORTB_AMSEL_R &= ~0x18;					//Clear AMSEL
	GPIO_PORTB_PCTL_R &= ~0x000FF000;			//Clear PCTL
	GPIO_PORTB_DEN_R |= 0x18;    					//Enable PB3 & PB4
	
}


// ***************** Timer0A_Init ****************
// Activate TIMER0 interrupts one-shot used for ultrasonic trigger
// Inputs:  delay time (1/clockfreq), 32 bits
// Outputs: none
void Timer0A_Init(uint32_t period){
	uint32_t sr;
  sr = StartCritical(); 
  SYSCTL_RCGCTIMER_R |= 0x01;   // 0) activate TIMER0
  sr = sr;          
  TIMER0_CTL_R = 0x00000000;    // 1) disable TIMER0A during setup
  TIMER0_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER0_TAMR_R = 0x00000002;   // 3) configure for periodic mode (1 for one-shot) or (2 for periodic) and default down-count settings 
  TIMER0_TAILR_R = period-1;    // 4) reload value
  TIMER0_TAPR_R = 0;            // 5) bus clock resolution
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;    // 6) clear TIMER0A timeout flag
  TIMER0_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI4_R = (NVIC_PRI4_R&0x0FFFFFFF)|0x80000000; // 8) priority 4
          // interrupts enabled in the main program after all devices initialized
          // vector number 35, interrupt number 19
  NVIC_EN0_R = 1<<19;           // 9) enable IRQ 19 in NVIC
  TIMER0_CTL_R = 0x00000001;    // 10) enable TIMER0A
  EndCritical(sr);
}


void Timer0A_Handler(void){
static uint32_t triggering = 0;  // used to tell if we are triggering the ultrasonic
static uint32_t servo_count = 0;  // counter for servo signal timming

	TIMER0_ICR_R = TIMER_ICR_TATOCINT;// acknowledge timer0A timeout
	
					/*********** Manage the Ultrasonic Sensor *************/
	if (triggering){
		ULTRASONIC_TRIG = 0;  // after one timeout set Trigger back to zero
		triggering = 0;
	}

	if (ULTRA_START_CONVERSION){  // request for ultrasonic conversion received
		ULTRASONIC_TRIG = 0xFF;        // set triger to 1
		triggering = 1;
	}
						/*********** Manage the RC Servo  *************/
		//    Drive servo with a 1,000 to 2,000 microsecond     pulse every 10,000 microseconds
		// OR Drive servo with a 100   to 200   interrupt delay pulse every 1000   interrupts (at 10 microsec rate)
		// 10 microsecond timeout => 0 to 100 steps for the range of servo control values
	if((++servo_count) >= 1000)
		servo_count = 0;
	
	if (SERVO_DUTY > 190)       // keep servo drive between 500 and 2400 microseconds (0 <= SERVO_DUTY <= 190) (limits for our servo)
			SERVO_DUTY = 190;
	
	if (servo_count < (SERVO_DUTY + 50)){
		SERVO_PIN = 0xFF;   // drive a one
	} else {
		SERVO_PIN = 0x00;   // dirve a zero
	}
}


