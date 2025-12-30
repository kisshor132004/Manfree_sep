/*
 * File:   program1.c
 * Author: kissh
 *
 * Created on November 4, 2025, 12:57 PM
 */
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off) 
#include <xc.h>
int t, one_sec_flag = 0, count = 0, time = 0, sec = 1, stop_flag = 0, a = 0,led=0;

void Lcd(char rs, char data) 
{
    RE0 = rs;
    PORTD = data;
    RE1 = 1;
    for (t = 0; t <= 100; t++);
    RE1 = 0;
    for (t = 0; t <= 100; t++);
}

void string(char *stop) {
    while (*stop) 
    {
        Lcd(1, *stop++);
    }
}

void display(int sec) 
{
    Lcd(0, 0xC0);
    Lcd(1, (sec / 10) + '0');
    Lcd(1, (sec % 10) + '0');
}

void __interrupt() tmr() 
{
    if (TMR2IF == 1) {
        count++;
        led++;
        TMR2IF = 0;
        TMR2 = 0;
        if ((led >= 125)&&(led<=0)){ RC2=1;}
        if ((led>=126)&&(led<=250)){ RC2=0; }
        if (led>=256){ led = 0; }
    }        
    if (a == 1) 
    {
        if (sec > 0) 
        {
            display(sec);
            if (count >= 125) 
            {
                sec--;
                count = 0;
            }
            if (((sec <= 5) || (sec <= 15) || (sec <= 25) || (sec <= 35) || (sec <= 45))&&((sec >= 0) || (sec >= 31) || (sec >= 21) || (sec >= 11))) 
            {
                RC0 = 1;
                RC1 = 0;
            }
            if (((sec <= 10) || (sec <= 20) || (sec <= 30) || (sec <= 40))&&((sec >= 6) || (sec >= 16) || (sec >= 26) || (sec >= 36))) 
            {
                RC1 = 1;
                RC0 = 0;
            }
            if (sec == 0) 
            {
                Lcd(0, 0xC0);
                string("END");
                RC0 = RC1 = 0;
                a = 0;
            }
        }
    }
}

void main() 
{
    PORTB = PORTD = PORTE = TRISD = TRISE = ANSEL = ANSELH = PORTC = TRISC = 0x00;
    TRISB = 0xFF;
    Lcd(0, 0x38);
    Lcd(0, 0x0E);
    Lcd(0, 0x80);
    GIE = PEIE = TMR2IE = 1;
    T2CON = 0x7F;
    TMR2 = 0;
    PR2 = 125;
    Lcd(0, 0x80);
    string("WELCOME");
    while (1) {
        if (RB0 == 1) //increment 5
        {
            time += 5;
            if (time >= 20) 
            {
                time = 0;
            }
            sec = time;
            display(sec);
            while (RB0 == 1);
        }
        if (RB1 == 1) //10
        {
            sec = time + 10;
            display(sec);
            while (RB1 == 1);
        }
        if (RB2 == 1) //20
        {
            sec = time + 20;
            display(sec);
            while (RB2 == 1);
        }
        if (RB3 == 1) //30
        {
            sec = time + 30;
            display(sec);
            while (RB3 == 1);
        }
        if (RB4 == 1) //start
        {
            a = 1;
        }

        if (RB5 == 1) {
            Lcd(0, 0x80);
            string("EMERGENCY STOP");
            while (RB5 == 1);
        }
    }
}