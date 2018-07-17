#include <xc.h>
#include "config.h"
void init_ports(void) 
{
    //********TURN OFF ANALOGUE INPUTS**********************
    ANSELA = 0x00;                  // turn off all ADC inputs on PORTA
    ANSELB = 0x00;                  // turn off all ADC inputs on PORTB
    ANSELC = 0x00;                  // turn off all ADC inputs on PORTC
    
   
   // TRISBbits.TRISB4 = 1;           // IR NEG IOC input pin 13
    TRISBbits.TRISB5 = 1;           // IR POS IOC input pin 12
    /*SET DATA DIRECTION FOR SPI PINS***********************/
   
    
    TRISAbits.TRISA5 = 0;
    TRISAbits.TRISA4 = 0;
    TRISCbits.TRISC5 = 0; 
    TRISCbits.TRISC4 = 0; 
    PORTAbits.RA5 = 0;              // Yellow LED
    PORTAbits.RA4 = 0;              // Blue LED
    PORTCbits.RC5 =0;               // Green LED
    PORTCbits.RC4 =0;                // Red LED
    TRISCbits.TRISC2 = 0;           // diagnostic RED led
    PORTCbits.RC2 =0;                // Red LED
    PORTCbits.RC1 = 1;              // set so that there is no conflict with CS OLED
    TRISCbits.TRISC0 = 0;           // diagnostic RED led pin 16
    PORTCbits.RC0 =0;
    /*SET DATA DIRECTION FOR ROTARY ENCODER AND SWITCH*******/
    /*RA0, RA1 no TRIS needed as these pins only function as inputs*/
    /* RA0 = SWIP pin 19*/
    /* RA1 = CLK pin 18*/
    
    
    /*SET DATA DIRECTION FOR UART*******************/
    PORTBbits.RB7 = 0;              // TX pin 10
}
