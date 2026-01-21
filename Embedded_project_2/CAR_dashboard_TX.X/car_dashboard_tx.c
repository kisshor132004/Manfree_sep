/*
 * File:   car_tx.c
 * Author: Naveen
 *
 * Created on 19 January, 2026, 4:34 PM
 */

#include <xc.h>
#define _XTAL_FREQ 4000000
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, PWRTE = ON
#pragma config MCLRE = ON, CP = OFF, CPD = OFF, BOREN = ON
#pragma config IESO = OFF, FCMEN = OFF, LVP = OFF

void UART_Init(void)
{
    TXSTA = 0x24;    // BRGH=1, TX enable
    RCSTA = 0x90;    // RX enable
    SPBRG = 25;      // 9600 baud @ 4MHz
}

void UART_Tx(char d)
{
    while(TXIF==0); 
    TXREG = d;
}
unsigned int ADC_Read(void)
{
    ADCON0 = 0x01;    // AN0, ADC ON
    __delay_ms(2);
    GO_nDONE = 1;
    while(GO_nDONE);
    return ((ADRESH << 8) + ADRESL);
}

// Map ADC (0?1022) ? Fuel % (0?100)
unsigned char ADC_to_Fuel_Percent(int adc)
{
    long temp;

    if(adc <= 0) return 0;
    if(adc >= 1022) return 100;

    temp = (long)adc * 100;
    temp = temp / 1022;

    return (unsigned char)temp;
}

// ---------------- MAIN ----------------
void main(void)
{
    unsigned int adc;
    unsigned char fuel;
    unsigned char doors;

    // --------- Setup ----------
    ANSEL  = 0x01;    // AN0 analog
    ANSELH = 0x00;
    TRISA  = 0x1F;    // RA0=ADC, RA1-RA4=doors input
    TRISC6 = 0;       // TX
    TRISC7 = 1;       // RX
    ADCON1 = 0x80;    // Right justified
    UART_Init();

    while(1)
    {
        doors = 0;

        if(RA1 == 1) doors |= 0x02; // Door1 closed
        if(RA2 == 1) doors |= 0x04; // Door2 closed
        if(RA3 == 1) doors |= 0x08; // Door3 closed
        if(RA4 == 1) doors |= 0x10; // Door4 closed

        // Read fuel
        adc  = ADC_Read();
        fuel = ADC_to_Fuel_Percent(adc);

        // Transmit doors byte & fuel byte
        UART_Tx(doors);  
        UART_Tx(fuel);

        __delay_ms(500);  // update every 0.5 sec
    }
}