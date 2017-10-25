#include "Definitions.h"
#include "xlcd.h"
#include "adc.h"
#include <stdio.h>

void main(void) 
{
LATA = 0xFF;
LATB = 0xFF;
init_XLCD();                    // Call the Initialize LCD display function

int tmp;
int testbuffer;
unsigned char config1=0x00,config2=0x00,config3=0x00,portconfig=0x00,i=0;
TRISAbits.RA0 = 1;
config1 = ADC_FOSC_4 | ADC_RIGHT_JUST | ADC_4_TAD ;
config2 = ADC_CH0 | ADC_INT_OFF | ADC_REF_VDD_VSS ;
portconfig = ADC_1ANA ;
OpenADC( config1,config2,portconfig);

Nop();

while(1) {
    
    ConvertADC();
    while(BusyADC());
    tmp = ReadADC();
    char buffer[10];
 
    if(testbuffer != tmp) {
        
        sprintf(buffer, "%d", tmp);  
        while(BusyXLCD());
        init_XLCD();
        while(BusyXLCD());
        putrsXLCD(buffer);
        while(BusyXLCD());
    }
    
   
    testbuffer = tmp;
    __delay_ms(100);
}  
CloseADC();

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
