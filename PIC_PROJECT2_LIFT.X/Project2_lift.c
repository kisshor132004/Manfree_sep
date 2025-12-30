#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = ON
#pragma config FCMEN = ON
#pragma config LVP = OFF
#pragma config BOR4V = BOR40V
#pragma config WRT  = OFF

#include <xc.h>
#define _XTAL_FREQ 4000000

#define btn1 RA0
#define btn2 RA1
#define btn3 RA2
#define btn4 RA3

#define sen1 RB0
#define sen2 RB1
#define sen3 RB2
#define sen4 RB3

#define motor_up   RC0
#define motor_down RC1

#define f4 RC2
#define f3 RC3
#define f2 RC4
#define f1 RC5

int t ;

int Lcd(char rs, char data) 
{
    RE0 = rs;
    PORTD = data;
    RE1 = 1;
    for (t = 0; t <= 100; t++);
    RE1 = 0;
    for (t = 0; t <= 100; t++);
}

int Lcd_String(char *stop) 
{
    while (*stop) 
    {
        Lcd(0, 0x80);
        Lcd(1, *stop++);
    }
}

int display_floor(int f1o)
{
    f1 = f2 = f3 = f4 = 0;
    if (f1o == 1) f1 = 1;
    if (f1o == 2) f2 = 1;
    if (f1o == 3) f3 = 1;
    if (f1o == 4) f4 = 1;
    Lcd(0, 0xC0);
    Lcd(1,f1o + '0');
}
    
void main()
{
    PORTA = PORTC = PORTD = PORTE = 0;
    TRISA = 0xFF;  
    TRISB = 0xFF;  
    TRISC = 0x00;       
    TRISD = TRISE = 0;  
    ANSEL = ANSELH = 0; 
    Lcd(0,0x38);
    Lcd(0,0x0C);
    Lcd(0,0x80);
    while(1)
    {  
        if(sen1==1)
        {
            display_floor(1);
            if(btn2 == 1)
            {
                motor_down=1;
                motor_up=0;
                Lcd_String("^"); 
                display_floor(1);
                while(sen1==1);
                motor_down=0;
                motor_up=0;
                display_floor(2);
                
            }
            if(btn3 == 1)
            {
                motor_down=1;
                motor_up=0;
                Lcd_String("^"); 
                display_floor(1);
                while(sen1==1);
                motor_down=0;
                motor_up=0;
                display_floor(3);
            }
            if(btn4 == 1)
            {
                motor_down=0;
                motor_up=1;
                Lcd_String("^"); 
                display_floor(1);
                while(sen1==1);
                motor_down=0;
                motor_up=0;
                display_floor(4);
            }
        }
        
        if(sen2==1)
        {
            display_floor(2);
            if(btn1 == 1)
            {
                motor_down=0;
                motor_up=1;
                Lcd_String("v"); 
                display_floor(2);
                while(sen2==1);
                motor_down=0;
                motor_up=0;
                display_floor(1);
            }
            if(btn3 == 1)
            {
                motor_down=1;
                motor_up=0;
                Lcd_String("^"); 
                display_floor(2);
                while(sen2==1);
                motor_down=0;
                motor_up=0;
                display_floor(3);
            }
            if(btn4 == 1)
            {
                motor_down=1;
                motor_up=0;
                Lcd_String("^"); 
                display_floor(2);
                while(sen2==1);
                motor_down=0;
                motor_up=0;
                display_floor(4);
            }
        }
        
        if(sen3==1)
        {
//            display_floor(3);
            if(btn1 == 1)
            {
                motor_down=0;
                motor_up=1;
                Lcd_String("v"); 
                display_floor(3);
                while(sen3==1);
                motor_down=0;
                motor_up=0;
                display_floor(1);
            }
            if(btn2 == 1)
            {
                motor_down=0;
                motor_up=1;
                Lcd_String("v"); 
                display_floor(3);
                while(sen3==1);
                motor_down=0;
                motor_up=0;
                display_floor(2);
            }
            if(btn4 == 1)
            {
                motor_down=1;
                motor_up=0;
                Lcd_String("^"); 
                display_floor(3);
                while(sen3==1);
                motor_down=0;
                motor_up=0;
                display_floor(4);
            }
        }
        
        if(sen4==1)
        {
            display_floor(4);
            if(btn1 == 1)
            {
                motor_down=0;
                motor_up=1;
                Lcd_String("v"); 
                display_floor(4);
                while(sen4==1);
                motor_down=0;
                motor_up=0;
                display_floor(1);
            }
            if(btn2 == 1)
            {
                motor_down=0;
                motor_up=1;
                Lcd_String("v"); 
                display_floor(4);
                while(sen4==1);
                motor_down=0;
                motor_up=0;
                display_floor(2);
            }
            if(btn3 == 1)
            {
                motor_down=0;
                motor_up=1;
                Lcd_String("v"); 
                display_floor(4);
                while(sen4==1);
                motor_down=0;
                motor_up=0;
                display_floor(3);
            }
        }
            
        motor_up=motor_down=0;
    }    
}

