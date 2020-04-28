#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = OFF
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = ON
#pragma config FCMEN = ON
#pragma config LVP = OFF
#pragma config BOR4V = BOR40V
#pragma config WRT = OFF 

#include <xc.h>
#include "DISPLAY7SEG.h"

#define P1 PORTCbits.RC0
#define P2 PORTCbits.RC1
#define DATA PORTBbits.RB7
#define CLOCK PORTBbits.RB6
#define STROBE PORTBbits.RB5

void main(void) {
    int valor=0, PP=0;
    TRISA=0x03;
    TRISB=0x00;
    TRISC=0x03;
    ANSEL=0b00000000; //Configura entradas en digital.
    OPTION_REG=0x02;
    while(1)
    {
        //Timer Setup.
        if(T0IF==1)
        {
            TMR0=TMR0+131;
            T0IF=0;
            ConmutarDigito();
        }
        //Pulsadores
        if(P1==1&&PP==0)
        {
            PP=1; //Anti rebote
            if(valor!=999)valor=valor+1;
            else valor=0;
            MostrarDisplay(valor); //Actualiza el valor a mostrar por los digitos.
        }
        else if(P2==1&&PP==0)
        {
            PP=1;
            if(valor!=0)valor=valor-1;
            else valor=999;
            MostrarDisplay(valor); //Actualiza el valor a mostrar por los digitos.
        }
        else if(P1==0&&P2==0)
        {
            PP=0;
        }
    }
}
