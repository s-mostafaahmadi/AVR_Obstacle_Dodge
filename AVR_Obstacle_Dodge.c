#include <mega32.h>

// Alphanumeric LCD functions

#include <alcd.h>
#include <sleep.h>
#include <delay.h>
#include <stdlib.h>

// Declare your global variables here
flash char Pattern[4] = {0xFE, 0xFD, 0xFB, 0xF7};
flash unsigned char key_number [4][4]={'7', '8', '9', '/',
                              '4', '5', '6', '*',
                              '1', '2', '3', '-',
                              'C', '0', '=', '+'};

void check(char);
int level=1;
int a = 3, b = 10;
// External Interrupt 2 service routine
interrupt [EXT_INT2] void ext_int2_isr(void)
{
// Place your code here
   int row, column = 4;
   for (row = 0; row <4; row++)
   {
       PORTD = Pattern[row];
       
       if(PIND.4 == 0)
       {
          column = 0;
          break;
       }
       else
       {
           if(PIND.5 == 0)
           {
              column = 1;
              break;
           }
           else
           {
               if(PIND.6 == 0)
               {
                  column = 2;
                  break;
               }
               else
               {
                   if(PIND.7 == 0)
                   {
                      column = 3;
                      break;
                   }
               }
           }
       
       }
   }

    if (key_number[row][column] != 'C')
        {
        char result=key_number[row][column];
        PORTD = 0xF0;
        check(result);
        }
    else
        lcd_clear();
        PORTD = 0xF0;
}

void main(void)
{
// Declare your local variables here
int i=0 ;

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=P Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (1<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
// State: Bit7=P Bit6=P Bit5=P Bit4=P Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTD=(1<<PORTD7) | (1<<PORTD6) | (1<<PORTD5) | (1<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: On
// INT2 Mode: Falling Edge
GICR|=(0<<INT1) | (0<<INT0) | (1<<INT2);
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);
GIFR=(0<<INTF1) | (0<<INTF0) | (1<<INTF2);

lcd_init(16);

lcd_puts("LEVEL1");
delay_ms(1000);
lcd_gotoxy(0,0);
lcd_puts("      ");

// Global enable interrupts
#asm("sei")


while(1)
{

int n=rand()%16;


if(level==2 && n==15)
    n--;
    
if(level==3 && (n==14 || n==15))
    n=n-2;


for(i=0;i<4;i++)
{
lcd_gotoxy(b,a);
lcd_puts("<^>");
delay_ms(200);

lcd_gotoxy(n,i);

//create obstacles
if(level==1)
lcd_puts("*");
else
    if(level==2)
    lcd_puts("**");
    else
        if(level==3)
        lcd_puts("***");

//clear obstacles        
delay_ms(200);
lcd_gotoxy(n,i);
lcd_putchar(' ');

if(level==2){
lcd_gotoxy(n,i);
lcd_puts("  ");
}
else
    if(level==3){
    lcd_gotoxy(n,i);
    lcd_puts("   ");
    }
    

 //(n,i) obstacle
 //(b,a) character
    
//collision detection

if((b==n||b+1==n||b+2==n)&&a==i)
{
lcd_clear();
lcd_puts("LOST");
delay_ms(1000);
lcd_clear();
}

if(level==2 || level==3)
{
    if((b==n+1||b==n||b+1==n)&&a==i)
    {
    lcd_clear();
    lcd_puts("LOST");
    delay_ms(1000);
    lcd_clear();
    }
}
if(level==3)
{
    if((b==n+2||b==n+1||b==n)&&a==i)
    {
    lcd_clear();
    lcd_puts("LOST");
    delay_ms(1000);
    lcd_clear();
    }    
}
}
      }
}

void check(char ch)
{
    if(ch=='+' && level<3)
    {   level=level+1;
        lcd_clear();
        if(level==2)      
        lcd_puts("LEVEL2");
        else
            if(level==3)
            lcd_puts("LEVEL3");
        delay_ms(1000);
        lcd_gotoxy(0,0);
        lcd_puts("      ");
        
    }
        
    if(ch=='6' && b<13)
        {lcd_gotoxy(b,a);
        lcd_putchar(' ');  
        b++;}
        else
        if(ch=='8'&& a>0)
        {
         lcd_gotoxy(b,a);
         lcd_puts("   ");
        a--;
        }
            else
            if(ch=='4'&& b>0)
            {
            lcd_gotoxy(b+2,a);
            lcd_putchar(' ');  
            b--;
            }
                else
                if(ch=='2'&& a<3)
                {
                lcd_gotoxy(b,a);
                lcd_puts("   "); 
                a++;
                }
}
