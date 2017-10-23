#include "Definitions.h"
#include "xlcd.h"

void main(void) 
{
LATA = 0xFF;
LATB = 0xFF;
init_XLCD();                    // Call the Initialize LCD display function


Nop();

//while(1) {
    putrsXLCD("Das ist Zeile 1");
    SetDDRamAddr(0x40);
    
    putrsXLCD("Das ist Zeile 2");
   __delay_ms(100);
//}    
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
