/*
 * File:   main.c
 * Author: Phil
 *
 * Created on 07 June 2018, 21:41
 */


#include <xc.h>
#include <stdio.h>
#include "main.h"
#include "config.h"
#include "init_ports.h"
#include "init_TMR1.h"
#include "config_osc.h"
#include "set_usart.h"
#include "putch.h"
#include "resetRc5.h"
#include "initIOCir.h"
#include "stateMachine.h"
void main(void) 
{
    init_ports();
    config_osc();
    init_TMR1();
    initIOCir();
    set_usart();
    state = MID1;
    PORTAbits.RA5 = 1;              // Yellow LED
    PORTAbits.RA4 = 1;              // Blue LED
    PORTCbits.RC5 = 1;               // Green LED
    PORTCbits.RC4 = 1;                // Red LED
    PORTCbits.RC0 = 1;                // Orange LED
    __delay_ms(500);
    PORTAbits.RA5 = 0;              // Yellow LED
    PORTAbits.RA4 = 0;              // Blue LED
    PORTCbits.RC5 = 0;               // Green LED
    PORTCbits.RC4 = 0;                // Red LED
    PORTCbits.RC0 = 0;                // Orange LED
    RC2 = 0;
    printf("Friday 13/7/18\n");
    for(z = 0; z < 26; z++)
        {
             rc5[z] = 0;
        }
   

    while(1)
    {   
       
    start:  while(IR == LO && has_run !=1);    // wait for first button press on RC5 handset
            while(IR == HI && has_run !=1);
            if(IR == LO && has_run !=1)
            {
                b = 0;                      // allow single line printing of RC5_code to serial interface
                RC2 = 1;
                has_run = 1;                // this block only runs once until system is reset
                RC5_code = RC5_code | 1<<n; // generates initial RC5 code S1 of 0x2000
                n--;
                RC5_code = RC5_code | 1<<n; // generates initial RC5 code S2 of 0x1000
                n--;
                state = MID1;
               
                TMR1H = 0x00;
                TMR1L = 0x00;
                //T1CONbits.TMR1ON = 1;       // start TMR1
                IOCBPbits.IOCBP5 = 1;       // enable interrupt on rising edge
                IOCBNbits.IOCBN5 = 0;       // disable interrupt on falling edge
                INTCONbits.IOCIE = 1;       // master switch enable for interrupt on change     
            }
            else if(IOCIF !=1 && fsm_run >= 11 && b == 0)
            {
                printf("RC5 code = %x\n", RC5_code); 
                b = 1;    
                resetRc5();
                T1CONbits.TMR1ON = 0;
                goto start;
            }
                
    }
}
    
    
        
    

