/*
 * File:   Ejercicio4.c
 * Author: Josea
 *
 * Created on 30 de marzo de 2022, 07:41 PM
 */


// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory codeprotection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <xc.h>
#include <stdio.h>
#include <stdint.h>

#define _XTAL_FREQ 4000000    //definicion de frecuencia macro delay 4mhz

#define b0 PORTBbits.RB0
#define b1 PORTBbits.RB1
//definicion del array valores entre 0 y 20
    
int valores[10] = {2, 8, 12, 19, 4, 11, 7, 3, 13, 9};

uint8_t contador = 0, posi = 0;         //definimos las variables que vamos a usar como enteros de 8 bits

void __interrupt() isr (void){
    
    if(INTCONbits.RBIF){                // Fue interrupci n del PORTB?
        
        if (contador > 20)
            contador = 0;
            INTCONbits.RBIF = 0;         
        if (!b0)             
            contador += 1;              // Incremento del contador
            INTCONbits.RBIF = 0;        // Limpiamos bandera de interrupci n?
        if (!b1)
            contador -= 1;
            INTCONbits.RBIF = 0;            
        
        //Verificar si el contador es igual a algun numero del array
        if (contador == valores[0]) 
            posi = 0;
            INTCONbits.RBIF = 0;
        if (contador == valores[1]) 
            posi = 1;
            INTCONbits.RBIF = 0;
        if (contador == valores[2]) 
            posi = 2;
            INTCONbits.RBIF = 0;
        if (contador == valores[3]) 
            posi = 3;
            INTCONbits.RBIF = 0;
        if (contador == valores[4]) 
            posi = 4;
            INTCONbits.RBIF = 0;
        if (contador == valores[5]) 
            posi = 5;
            INTCONbits.RBIF = 0;
        if (contador == valores[6]) 
            posi = 6;
            INTCONbits.RBIF = 0;
        if (contador == valores[7]) 
            posi = 7;
            INTCONbits.RBIF = 0;
        if (contador == valores[8]) 
            posi = 8;
            INTCONbits.RBIF = 0;
        if (contador == valores[9]) 
            posi = 9;
            INTCONbits.RBIF = 0;
           
            
    }
    return;
}


void setup(void);

void main(void) {
    setup();
  

    while(1){
        PORTA = contador;
        PORTC = posi;
    }
    return;
   
    
}

void setup(void){
    ANSEL = 0;
    ANSELH = 0;        // Usamos solo I/O digitales
    
    TRISC = 0x00;               // PORTC como salida
    PORTC = 0;                  // Limpiamos PORTC
    
    TRISA = 0x00;               // PORTA como salida
    PORTA = 0;                  // Limpiamos PORTA
  
    
    TRISBbits.TRISB0 = 1;       // RB0 como entrada (configurada con bits de control)
    TRISBbits.TRISB1 = 1;       // RB1 como entrada (configurada con bits de control)
    OPTION_REGbits.nRBPU = 0;   // Habilitamos resistencias de pull-up del PORTB
    WPUBbits.WPUB0 = 1;         // Habilitamos resistencia de pull-up de RB0
    WPUBbits.WPUB1 = 1;         // Habilitamos resistencia de pull-up de RB1
    
    INTCONbits.GIE = 1;         // Habilitamos interrupciones globales
    INTCONbits.RBIE = 1;        // Habilitamos interrupciones del PORTB
    IOCBbits.IOCB0 = 1;         // Habilitamos interrupcion por cambio de estado ?para RB0
    IOCBbits.IOCB1 = 1;         // Habilitamos interrupcion por cambio de estado ?para RB1
    INTCONbits.RBIF = 0;        // Limpiamos bandera de interrupcion

    
    OSCCONbits.IRCF = 0b0110;   // Oscilador a 4mhz
    OSCCONbits.SCS = 1;        // Habilitado el oscilador interno
}