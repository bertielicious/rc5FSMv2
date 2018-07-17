/*
 * File:   interrupt isr.c
 * Author: philip
 *
 * Created on 30 March 2018, 20:08
 */
#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include "stateMachine.h"
#include "interrupt isr.h"   

void interrupt isr(void) 
{
    if(PIR1bits.TMR1IF == 1)
    {  
        RC0 = ~RC0;
        TMR1L = 0x00;
        TMR1H = 0x00;  
        PIR1bits.TMR1IF = 0;
    }
      
     
     if(IOCBFbits.IOCBF5 == 1)
     {
         if(magic_num%2 != 0)   // first rising edge of pulse detected
         {
             if(count == 0)                 // path A
             {
                 T1CONbits.TMR1ON = 1;       // start TMR1
                //temp1 = TMR1H<<8 | TMR1L;    // store TMR1 at start of pulse
                magic_num++;               // make an even number so %evennum = 0
                count = 1;
                IOCBNbits.IOCBN5 = 1;      // enable interrupt on falling edge
                IOCBFbits.IOCBF5 = 0;      // clear relevant interrupt flags
                INTCONbits.IOCIF = 0;
                
             }
             else if(count !=0)             // path C
             {
                 
                 temp3 = TMR1H<<8 | TMR1L;    // store TMR1 at start of next pulse 
                 space_width = temp3 - pulse_width;
                 
                 if(space_width >= 444 && space_width <= 1333)
                 {
                     pulse_type = SS;
                 }
                 else if(space_width >= 1334 && space_width <= 2222)
                 {
                     pulse_type = LS;
                 }
                 stateMachine();
                 fsm_run++;
                
                 
                 TMR1H = 0x00;
                 TMR1L = 0x00;
                 temp1 = 0;
                 magic_num++;
                 
                IOCBFbits.IOCBF5 = 0;      // clear relevant interrupt flags
                INTCONbits.IOCIF = 0;
                   
             }
         }
         else           // path B
         {
            
             temp2 = TMR1H<<8 | TMR1L;    // store TMR1 at start of pulse
             pulse_width = temp2; //- temp1;
             magic_num = 1;
             
             if(pulse_width >= 444 && pulse_width <= 1333)
                 {
                     pulse_type = SP;
                 }
             else if(pulse_width >= 1334 && pulse_width <= 2222)
                 {
                     pulse_type = LP;
                 }
             stateMachine();
             
             
             IOCBFbits.IOCBF5 = 0;      // clear relevant interrupt flags
             INTCONbits.IOCIF = 0;
         } 
         
     }  
}
     