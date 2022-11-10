



;****************** LED.s ***************
; CPE287, Fall 2018, Lab 6
; James Lumpp
; 09/29/2018
; Credit: Based on software by Valvano
;*****************************************

;//
;//
;// GPIO registers EQU PORTA
;//
;//
GPIO_PORTA_DATA_BITS_R  EQU  0x40004000
GPIO_PORTA_DATA_R       EQU  0x400043FC
GPIO_PORTA_DIR_R        EQU  0x40004400
GPIO_PORTA_IS_R         EQU  0x40004404
GPIO_PORTA_IBE_R        EQU  0x40004408
GPIO_PORTA_IEV_R        EQU  0x4000440C
GPIO_PORTA_IM_R         EQU  0x40004410
GPIO_PORTA_RIS_R        EQU  0x40004414
GPIO_PORTA_MIS_R        EQU  0x40004418
GPIO_PORTA_ICR_R        EQU  0x4000441C
GPIO_PORTA_AFSEL_R      EQU  0x40004420
GPIO_PORTA_DR2R_R       EQU  0x40004500
GPIO_PORTA_DR4R_R       EQU  0x40004504
GPIO_PORTA_DR8R_R       EQU  0x40004508
GPIO_PORTA_ODR_R        EQU  0x4000450C
GPIO_PORTA_PUR_R        EQU  0x40004510
GPIO_PORTA_PDR_R        EQU  0x40004514
GPIO_PORTA_SLR_R        EQU  0x40004518
GPIO_PORTA_DEN_R        EQU  0x4000451C
GPIO_PORTA_LOCK_R       EQU  0x40004520
GPIO_PORTA_CR_R         EQU  0x40004524
GPIO_PORTA_AMSEL_R      EQU  0x40004528
GPIO_PORTA_PCTL_R       EQU  0x4000452C
GPIO_PORTA_ADCCTL_R     EQU  0x40004530
GPIO_PORTA_DMACTL_R     EQU  0x40004534

;//
;//
;// GPIO registers EQU PORTB
;//
;//
GPIO_PORTB_DATA_BITS_R  EQU  0x40005000
GPIO_PORTB_DATA_R       EQU  0x400053FC
GPIO_PORTB_DIR_R        EQU  0x40005400
GPIO_PORTB_IS_R         EQU  0x40005404
GPIO_PORTB_IBE_R        EQU  0x40005408
GPIO_PORTB_IEV_R        EQU  0x4000540C
GPIO_PORTB_IM_R         EQU  0x40005410
GPIO_PORTB_RIS_R        EQU  0x40005414
GPIO_PORTB_MIS_R        EQU  0x40005418
GPIO_PORTB_ICR_R        EQU  0x4000541C
GPIO_PORTB_AFSEL_R      EQU  0x40005420
GPIO_PORTB_DR2R_R       EQU  0x40005500
GPIO_PORTB_DR4R_R       EQU  0x40005504
GPIO_PORTB_DR8R_R       EQU  0x40005508
GPIO_PORTB_ODR_R        EQU  0x4000550C
GPIO_PORTB_PUR_R        EQU  0x40005510
GPIO_PORTB_PDR_R        EQU  0x40005514
GPIO_PORTB_SLR_R        EQU  0x40005518
GPIO_PORTB_DEN_R        EQU  0x4000551C
GPIO_PORTB_LOCK_R       EQU  0x40005520
GPIO_PORTB_CR_R         EQU  0x40005524
GPIO_PORTB_AMSEL_R      EQU  0x40005528
GPIO_PORTB_PCTL_R       EQU  0x4000552C
GPIO_PORTB_ADCCTL_R     EQU  0x40005530
GPIO_PORTB_DMACTL_R     EQU  0x40005534

;//
;//
;// GPIO registers EQU PORTC
;//
;//
GPIO_PORTC_DATA_BITS_R  EQU  0x40006000
GPIO_PORTC_DATA_R       EQU  0x400063FC
GPIO_PORTC_DIR_R        EQU  0x40006400
GPIO_PORTC_IS_R         EQU  0x40006404
GPIO_PORTC_IBE_R        EQU  0x40006408
GPIO_PORTC_IEV_R        EQU  0x4000640C
GPIO_PORTC_IM_R         EQU  0x40006410
GPIO_PORTC_RIS_R        EQU  0x40006414
GPIO_PORTC_MIS_R        EQU  0x40006418
GPIO_PORTC_ICR_R        EQU  0x4000641C
GPIO_PORTC_AFSEL_R      EQU  0x40006420
GPIO_PORTC_DR2R_R       EQU  0x40006500
GPIO_PORTC_DR4R_R       EQU  0x40006504
GPIO_PORTC_DR8R_R       EQU  0x40006508
GPIO_PORTC_ODR_R        EQU  0x4000650C
GPIO_PORTC_PUR_R        EQU  0x40006510
GPIO_PORTC_PDR_R        EQU  0x40006514
GPIO_PORTC_SLR_R        EQU  0x40006518
GPIO_PORTC_DEN_R        EQU  0x4000651C
GPIO_PORTC_LOCK_R       EQU  0x40006520
GPIO_PORTC_CR_R         EQU  0x40006524
GPIO_PORTC_AMSEL_R      EQU  0x40006528
GPIO_PORTC_PCTL_R       EQU  0x4000652C
GPIO_PORTC_ADCCTL_R     EQU  0x40006530
GPIO_PORTC_DMACTL_R     EQU  0x40006534

;//
;//
;// GPIO registers EQU PORTD
;//
;//
GPIO_PORTD_DATA_BITS_R  EQU  0x40007000
GPIO_PORTD_DATA_R       EQU  0x400073FC
GPIO_PORTD_DIR_R        EQU  0x40007400
GPIO_PORTD_IS_R         EQU  0x40007404
GPIO_PORTD_IBE_R        EQU  0x40007408
GPIO_PORTD_IEV_R        EQU  0x4000740C
GPIO_PORTD_IM_R         EQU  0x40007410
GPIO_PORTD_RIS_R        EQU  0x40007414
GPIO_PORTD_MIS_R        EQU  0x40007418
GPIO_PORTD_ICR_R        EQU  0x4000741C
GPIO_PORTD_AFSEL_R      EQU  0x40007420
GPIO_PORTD_DR2R_R       EQU  0x40007500
GPIO_PORTD_DR4R_R       EQU  0x40007504
GPIO_PORTD_DR8R_R       EQU  0x40007508
GPIO_PORTD_ODR_R        EQU  0x4000750C
GPIO_PORTD_PUR_R        EQU  0x40007510
GPIO_PORTD_PDR_R        EQU  0x40007514
GPIO_PORTD_SLR_R        EQU  0x40007518
GPIO_PORTD_DEN_R        EQU  0x4000751C
GPIO_PORTD_LOCK_R       EQU  0x40007520
GPIO_PORTD_CR_R         EQU  0x40007524
GPIO_PORTD_AMSEL_R      EQU  0x40007528
GPIO_PORTD_PCTL_R       EQU  0x4000752C
GPIO_PORTD_ADCCTL_R     EQU  0x40007530
GPIO_PORTD_DMACTL_R     EQU  0x40007534

;//
;//
;// GPIO registers EQU PORTE
;//
;//
GPIO_PORTE_DATA_BITS_R  EQU  0x40024000
GPIO_PORTE_DATA_R       EQU  0x400243FC
GPIO_PORTE_DIR_R        EQU  0x40024400
GPIO_PORTE_IS_R         EQU  0x40024404
GPIO_PORTE_IBE_R        EQU  0x40024408
GPIO_PORTE_IEV_R        EQU  0x4002440C
GPIO_PORTE_IM_R         EQU  0x40024410
GPIO_PORTE_RIS_R        EQU  0x40024414
GPIO_PORTE_MIS_R        EQU  0x40024418
GPIO_PORTE_ICR_R        EQU  0x4002441C
GPIO_PORTE_AFSEL_R      EQU  0x40024420
GPIO_PORTE_DR2R_R       EQU  0x40024500
GPIO_PORTE_DR4R_R       EQU  0x40024504
GPIO_PORTE_DR8R_R       EQU  0x40024508
GPIO_PORTE_ODR_R        EQU  0x4002450C
GPIO_PORTE_PUR_R        EQU  0x40024510
GPIO_PORTE_PDR_R        EQU  0x40024514
GPIO_PORTE_SLR_R        EQU  0x40024518
GPIO_PORTE_DEN_R        EQU  0x4002451C
GPIO_PORTE_LOCK_R       EQU  0x40024520
GPIO_PORTE_CR_R         EQU  0x40024524
GPIO_PORTE_AMSEL_R      EQU  0x40024528
GPIO_PORTE_PCTL_R       EQU  0x4002452C
GPIO_PORTE_ADCCTL_R     EQU  0x40024530
GPIO_PORTE_DMACTL_R     EQU  0x40024534

;//
;//
;// GPIO registers EQU PORTF
;//
;//
GPIO_PORTF_DATA_BITS_R  EQU  0x40025000
GPIO_PORTF_DATA_R       EQU  0x400253FC
GPIO_PORTF_DIR_R        EQU  0x40025400
GPIO_PORTF_IS_R         EQU  0x40025404
GPIO_PORTF_IBE_R        EQU  0x40025408
GPIO_PORTF_IEV_R        EQU  0x4002540C
GPIO_PORTF_IM_R         EQU  0x40025410
GPIO_PORTF_RIS_R        EQU  0x40025414
GPIO_PORTF_MIS_R        EQU  0x40025418
GPIO_PORTF_ICR_R        EQU  0x4002541C
GPIO_PORTF_AFSEL_R      EQU  0x40025420
GPIO_PORTF_DR2R_R       EQU  0x40025500
GPIO_PORTF_DR4R_R       EQU  0x40025504
GPIO_PORTF_DR8R_R       EQU  0x40025508
GPIO_PORTF_ODR_R        EQU  0x4002550C
GPIO_PORTF_PUR_R        EQU  0x40025510
GPIO_PORTF_PDR_R        EQU  0x40025514
GPIO_PORTF_SLR_R        EQU  0x40025518
GPIO_PORTF_DEN_R        EQU  0x4002551C
GPIO_PORTF_LOCK_R       EQU  0x40025520
GPIO_PORTF_CR_R         EQU  0x40025524
GPIO_PORTF_AMSEL_R      EQU  0x40025528
GPIO_PORTF_PCTL_R       EQU  0x4002552C
GPIO_PORTF_ADCCTL_R     EQU  0x40025530
GPIO_PORTF_DMACTL_R     EQU  0x40025534


; If you wish to use the bit specific addressing 
; here are some examples for PortF
PF0 EQU  0x40025004;0 00.0000.0100 EQU 0x40025004
PF1 EQU  0x40025008;1 00.0000.1000 EQU 0x40025008
PF2 EQU  0x40025010;2 00.0001.0000 EQU 0x40025010
PF3 EQU  0x40025020;3 00.0010.0000 EQU 0x40025020
PF4 EQU  0x40025040;4 00.0100.0000 EQU 0x40025040
PF5 EQU  0x40025080;5 00.1000.0000 EQU 0x40025080
PF6 EQU  0x40025100;6 01.0000.0000 EQU 0x40025100
PF7 EQU  0x40025200;7 10.0000.0000 EQU 0x40025200
	
PA7  EQU  0x40004200
PE4  EQU  0x40024040

PF1and3 EQU 0x40025028;1 and 3 00.0010.1000 EQU 0x40025028 
;etc.

;GPIO_PORTF_DATA_R  EQU 0x400253FC
;GPIO_PORTF_DIR_R   EQU 0x40025400
;GPIO_PORTF_AFSEL_R EQU 0x40025420
;GPIO_PORTF_PUR_R   EQU 0x40025510
;GPIO_PORTF_DEN_R   EQU 0x4002551C
;GPIO_PORTF_LOCK_R  EQU 0x40025520
;GPIO_PORTF_CR_R    EQU 0x40025524
;GPIO_PORTF_AMSEL_R EQU 0x40025528
;GPIO_PORTF_PCTL_R  EQU 0x4002552C
GPIO_LOCK_KEY      EQU 0x4C4F434B  ; Unlocks the GPIO_CR register
SYSCTL_RCGC2_R     EQU 0x400FE108
SYSCTL_RCGC2_GPIOF EQU 0x00000020  ; port F Clock Gating Control
RED       		   EQU 0x02
BLUE      		   EQU 0x04
GREEN     		   EQU 0x08
;PF1				   EQU 0x40025008   ; uses special bit specific GPIO port addressing
;PF2				   EQU 0x40025010   ; uses special bit specific GPIO port addressing
;PF3				   EQU 0x40025020   ; uses special bit specific GPIO port addressing
;0 00.0000.0100 EQU 0x40025004
;1 00.0000.1000 EQU 0x40025008
;2 00.0001.0000 EQU 0x40025010
;3 00.0010.0000 EQU 0x40025020
;4 00.0100.0000 EQU 0x40025040
;5 00.1000.0000 EQU 0x40025080
;6 01.0000.0000 EQU 0x40025100
;7 10.0000.0000 EQU 0x40025200

        AREA    |.text|, CODE, READONLY, ALIGN=2
		PRESERVE8
		REQUIRE8
        THUMB
        EXPORT   PortA_Init
        EXPORT   PortF_Init
        EXPORT   blue_led_on
		EXPORT   blue_led_off
        EXPORT   red_led_on
		EXPORT   red_led_off
		EXPORT   green_led_on
		EXPORT   green_led_off
			
	
;------------PortA_Init------------
; Initialize GPIO Port A bit 7 (PA7) as a digital output 
; for a brushed DC motor output.
; NOTE: This function only configures PA7 and thus 
; must preserve the contents of any of the other control registers.
; Input: none
; Output: none
; Modifies: R0, R1, R2
PortA_Init
    LDR R1, =SYSCTL_RCGC2_R         ; 1) activate clock for Port A
    LDR R0, [R1]                 
    ORR R0, R0, #0x01              ; set bit _0__ to turn on clock for PortA
    STR R0, [R1]                  
    NOP
    NOP                             ; allow time for clock to finish
    LDR R1, =GPIO_PORTA_AMSEL_R     ; 3) disable analog functionality
    LDR R0, [R1]                  ; 1100 0000 = C0
    BIC R0,R0, #0xE0             ; AMSEL off for bit 7,6,5 (0 for analog off)
    STR R0, [R1]                    
    LDR R1, =GPIO_PORTA_PCTL_R      ; 4) configure as GPIO
    LDR R0, [R1]
    BIC R0, R0, #0xff000000            ; PA7,6,5 GPIO: 0 means config Port F as GPIO
    BIC R0, R0, #0x00f00000            ; PA7,6,5 GPIO: 0 means config Port F as GPIO
    STR R0, [R1]                  
    LDR R1, =GPIO_PORTA_DIR_R       ; 5) set direction register
    LDR R0, [R1]
    ORR R0, R0, #0xE0           ; PA7,6,5 set as output
    STR R0, [R1]                    
    LDR R1, =GPIO_PORTA_AFSEL_R     ; 6) regular port function
    LDR R0, [R1]
    BIC R0, R0, #0xE0             ; No AF PA7,6,5, 0 means disable alt. func.
    STR R0, [R1]                    
    LDR R1, =GPIO_PORTA_DEN_R       ; 7) enable Port F digital port
    LDR R0, [R1]
    ORR R0, R0, #0xE0             ; Enable PA7,6,5: 1 means enable digital I/O
    STR R0, [R1]                   
    BX  LR



			;------------PortF_Init------------
; Initialize GPIO Port F for negative logic switches on PF0 and
; PF4 as the Launchpad is wired.  Weak internal pull-up
; resistors are enabled, and the NMI functionality on PF0 is
; disabled.  Make the RGB LED's pins outputs.
; Input: none
; Output: none
; Modifies: R0, R1, R2
PortF_Init
    LDR R1, =SYSCTL_RCGC2_R         ; 1) activate clock for Port F
    LDR R0, [R1]                 
    ORR R0, R0, #0x20               ; set bit 5 to turn on clock
    STR R0, [R1]                  
    NOP
    NOP                             ; allow time for clock to finish
    LDR R1, =GPIO_PORTF_LOCK_R      ; 2) unlock the lock register
    LDR R0, =0x4C4F434B             ; unlock GPIO Port F Commit Register
    STR R0, [R1]                    
    LDR R1, =GPIO_PORTF_CR_R        ; enable commit for Port F
    MOV R0, #0xFF                   ; 1 means allow access
    STR R0, [R1]                    
    LDR R1, =GPIO_PORTF_AMSEL_R     ; 3) disable analog functionality
    MOV R0, #0x00                   ; 0 means analog is off
    STR R0, [R1]                    
    LDR R1, =GPIO_PORTF_PCTL_R      ; 4) configure as GPIO
    MOV R0, #0x00000000                   ; 0 means configure Port F as GPIO
    STR R0, [R1]                  
    LDR R1, =GPIO_PORTF_DIR_R       ; 5) set direction register
    MOV R0, #0x0E                   ; PF0 and PF7-4 input, PF3-1 output
    STR R0, [R1]                    
    LDR R1, =GPIO_PORTF_AFSEL_R     ; 6) regular port function
    MOV R0, #0x00                   ; 0 means disable alternate function 
    STR R0, [R1]                    
    LDR R1, =GPIO_PORTF_PUR_R       ; pull-up resistors for PF4,PF0
    MOV R0, #0x11                   ; enable weak pull-up on PF0 and PF4
    STR R0, [R1]              
    LDR R1, =GPIO_PORTF_DEN_R       ; 7) enable Port F digital port
    MOV R0, #0xFF                   ; 1 means enable digital I/O
    STR R0, [R1]                   
    BX  LR 


;------------PortF_Output------
; Set the output state of PF3-1.
; Input: R0  new state of PF
; Output: none
; Modifies: R1
PortF_Output
    LDR R1, =GPIO_PORTF_DATA_R 		; pointer to Port F data
    STR R0, [R1]               		; write to PF3-1
    BX  LR                    

;------------blue_led_on------
; Turn the blue LED on (Uses the port specific addressing)
; Input: none
; Output: none
blue_led_on
	LDR R1, =PF2
	MOV R0, #BLUE                   ; R0 = BLUE (blue LED on)
    STR R0, [R1]                    ; turn the blue LED on
    BX  LR
	
;------------blue_led_off-----
; Turn the blue LED off (Uses the port specific addressing)
; Input: none
; Output: none
blue_led_off
	LDR R1, =PF2
	MOV R0, #0                      ; R0 = 0
    STR R0, [R1]                    ; turn the blue LED OFF
    BX  LR
	
;------------red_led_on-------
; Turn the red LED on  (Uses the port specific addressing)
; Input: none
; Output: none
red_led_on
	LDR R1, =PF1
	MOV R0, #RED                    ; R0 = RED (red LED on)
    STR R0, [R1]                    ; turn the red LED on
    BX  LR
	
;------------red_led_off------
; Turn the red LED off (Uses the port specific addressing)
; Input: none
; Output: none
red_led_off
	LDR R1, =PF1
	MOV R0, #0                      ; R0 = 0
    STR R0, [R1]                    ; turn the red LED OFF
    BX  LR
	
;------------green_led_on------
; Turn the green LED on (Uses the port specific addressing)
; Input: none
; Output: none
green_led_on
	LDR R1, =PF3
	MOV R0, #GREEN                  ; R0 = GREEN (green LED on)
    STR R0, [R1]                    ; turn the green LED on
    BX  LR
	
;------------green_led_off-----
; Turn the green LED off (Uses the port specific addressing)
; Input: none
; Output: none
green_led_off
	LDR R1, =PF3
	MOV R0, #0                      ; R0 = 0
    STR R0, [R1]                    ; turn the green LED OFF
    BX  LR
	
    ALIGN                           ; make sure the end of this section is aligned
    END                             ; end of file
