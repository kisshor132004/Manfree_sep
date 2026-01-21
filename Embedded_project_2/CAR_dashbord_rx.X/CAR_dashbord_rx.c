#include <xc.h>
#define _XTAL_FREQ 4000000

#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, PWRTE = ON
#pragma config MCLRE = ON, CP = OFF, CPD = OFF, BOREN = ON
#pragma config IESO = OFF, FCMEN = OFF, LVP = OFF

#define RS RE0
#define EN RE1
#define FUEL_LED RA5

int p,a,b,c;
unsigned char doors, fuel;

// -------- LCD --------
void lcd_cmd(unsigned char c)
{
    PORTD = c;
    RS = 0;
    EN = 1;
    __delay_ms(2);
    EN = 0;
    __delay_ms(2);
}

void lcd_data(unsigned char d)
{
    PORTD = d;
    RS = 1;
    EN = 1;
    __delay_ms(2);
    EN = 0;
    __delay_ms(2);
}

void lcd_init(void)
{
    __delay_ms(20);
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
}

void lcd_string(const char *s)
{
    while(*s)
        lcd_data(*s++);
}

// -------- UART --------
void UART_Init(void)
{
    TXSTA = 0x24;
    RCSTA = 0x90;
    SPBRG = 25;
}

unsigned char UART_Rx(void)
{
    while(!RCIF);
    return RCREG;
}

// -------- DOOR DISPLAY --------
void show_open_door(char status)
{
    lcd_cmd(0x86);
    if     (!(status & (1<<1))) lcd_string("FRONT LEFT ");
    else if(!(status & (1<<2))) lcd_string("FRONT RIGHT");
    else if(!(status & (1<<3))) lcd_string("BACK LEFT  ");
    else if(!(status & (1<<4))) lcd_string("BACK RIGHT ");
    else                        lcd_string("ALL CLOSED ");
}

void door(unsigned char door_status)
{
    lcd_cmd(0xC0);
    if((door_status & 0x1E) == 0x1E)
    {
        lcd_string("CAR RUN     ");
        show_open_door(door_status);

    }
    else
    {
        lcd_string("CAR STOP    ");
        show_open_door(door_status);
    }
}

// -------- FUEL --------
void fuel_status(unsigned char fuel)
{
    if(fuel < 20)
        FUEL_LED = 1;
    else
        FUEL_LED = 0;
}

void lcd_percentage(unsigned char fuel)
{
    p = fuel;
    a = p / 100;
    b = (p % 100) / 10;
    c = p % 10;

    lcd_cmd(0x80);
    lcd_data(a + '0');
    lcd_data(b + '0');
    lcd_data(c + '0');
    lcd_data('%');
}

// -------- MAIN --------
void main(void)
{
    ANSEL  = 0x00;
    ANSELH = 0x00;

    TRISA  = 0x00;   // LED output
    TRISD  = 0x00;   // LCD
    TRISE  = 0x00;
    TRISC6 = 0;      // TX output
    TRISC7 = 1;      // RX input

    lcd_init();
    UART_Init();

    while(1)
    {
        doors = UART_Rx();
        fuel  = UART_Rx();

        door(doors);
        lcd_percentage(fuel);
        fuel_status(fuel);
    }
}
