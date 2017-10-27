#include "Definitions.h"
#include "xlcd.h"
#include "adc.h"
#include <stdio.h>

void main(void) 
{
LATA = 0xFF;
LATB = 0xFF;
TRISD = 0xFF;

TRISBbits.RB4 = 1;
TRISBbits.RB5 = 1;
init_XLCD();
int testbuffer = -1;
Nop();

while(1) {
    int tempvariable = PORTBbits.RB5;
    if(testbuffer != tempvariable) {
        char buffer[10];
        sprintf(buffer, "%d", tempvariable);
        while(BusyXLCD());
        init_XLCD();
        while(BusyXLCD());
        putrsXLCD(buffer);
        while(BusyXLCD());
        if(tempvariable == 1) {
            __delay_ms(1000);
        }
        
    }
    testbuffer = tempvariable;
}  

return;
}

void DelayFor18TCY( void ) //18+ cycles delay
{__delay_us(20);   
    return;
}

void DelayPORXLCD(void)         // 15ms delay
{
__delay_ms(15);                 // 15ms delay with 4MHz Clock
}

void DelayXLCD(void)            // 5ms delay
 {
__delay_ms(5);                  // 5ms delay with 4MHz Clock
 }



 
void init_XLCD(void)            // Initialize LCD display
{  
OpenXLCD(FOUR_BIT&LINES_5X7);   // configure LCD in 4-bit Data Interface mode
                                // and 5x7 characters, multiple line display
while(BusyXLCD());
// Check if the LCD controller is not busy                      // before writing some commands?
 WriteCmdXLCD(0x06);            // move cursor right, don?t shift display
 WriteCmdXLCD(0x0C);            // turn display on without cursor
 }
