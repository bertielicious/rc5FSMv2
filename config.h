/* 
 * File:   config.h
 * Author: Phil
 *
 * Created on 07 June 2018, 21:48
 */

#ifndef CONFIG_H
#define	CONFIG_H

#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover Mode (Internal/External Switchover Mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config CPUDIV = CLKDIV6 // CPU System Clock Selection Bit (CPU system clock divided by 6)
#pragma config USBLSCLK = 48MHz // USB Low SPeed Clock Selection bit (System clock expects 48 MHz, FS/LS USB CLKENs divide-by is set to 8.)
#pragma config PLLMULT = 3x     // PLL Multipler Selection Bit (3x Output Frequency Selected)
#pragma config PLLEN = DISABLED // PLL Enable Bit (3x or 4x PLL Disabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)
#define _XTAL_FREQ 4000000
#include <xc.h>
#include <stdbool.h>

/********States**********/
#define START 0
#define MID1 1
#define START1 2
#define MID0 3
#define START0 4

/****OUTPUTS of state machine******/
#define HI 1
#define LO 0
/******pulse_types****/
#define SP 0
#define LP 1
#define SS 2
#define LS 3
#define ERR 4



#define IR  PORTBbits.RB5
/************global variables********/
volatile unsigned char has_run = 0;
volatile unsigned int  period, temp, space_width, a, b = 0;
volatile unsigned int pulse_width, temp1, temp2,temp3, pulse, space, width, count, nois = 0;
volatile unsigned int pulse_type = SP;
unsigned int state = MID1;
volatile unsigned int RC5_code = 0x0000;
volatile unsigned int i,z, w = 0;
volatile unsigned int n = 13;        // number of bits to be shifted left to form the RC5_code (14 bits)
volatile unsigned int magic_num = 1;
volatile unsigned int rc5[24];
volatile unsigned int fsm_run = 0;
#endif	/* CONFIG_H */

