#include "Definitions.h"
#include "xlcd.h"
#include <stdio.h>

void main(void) 
{
LATA = 0xFF;
LATB = 0xFF;
TRISD = 0;
TRISDbits.RD0 = 1;
TRISDbits.RD1 = 1;
TRISDbits.RD2 = 1;

init_XLCD();
char order[2];
int rd0end = 1;
int rd1end = 1;
int rd2end = 1;
int duration;
unsigned long tempcounter = 0;
unsigned long count = 0;
while(1) {
    ++count;
    if(count == 100000) {
        
        init_XLCD();
        order[0] = NULL;
        order[1] = NULL;
        rd0end = 1;
        rd1end = 1;
        rd2end = 1;
        count = 0;
    }
    
    
    if(PORTDbits.RD0 == 1 && rd0end == 1) {
        
        rd0end = 0;
        if(order[0] == NULL) {
            order[0] = 'M';
            tempcounter = count;
        }
        else if(order[1] == NULL) {
            order[1] = 'M';
            duration = count - tempcounter;
        }
        else {
            if(duration > 0x000F) {
                order[1] = NULL;
            }
            init_XLCD();
            putrsXLCD(order);
            order[0] = NULL;
            order[1] = NULL;
            rd0end = 1;
            rd1end = 1;
            rd2end = 1;
            duration = 0;
            __delay_ms(2000);
            
        }    
    }
    
    if(PORTDbits.RD1 == 1 && rd1end == 1) {
        rd1end = 0;
        if(order[0] == NULL) {
            order[0] = 'L';
            tempcounter = count;
        }
        else if(order[1] == NULL) {
            order[1] = 'L';
            duration = count - tempcounter;
        }
        else {
            if(duration > 0x000F) {
                order[1] = NULL;
            }
            init_XLCD();
            putrsXLCD(order);
            order[0] = NULL;
            order[1] = NULL;
            rd0end = 1;
            rd1end = 1;
            rd2end = 1;
            duration = 0;
            __delay_ms(2000);
            
        } 
    }
    
    if(PORTDbits.RD2 == 1 && rd2end == 1) {
        rd2end = 0;
        if(order[0] == NULL) {
            order[0] = 'R';
            tempcounter = count;
        }
        else if(order[1] == NULL) {
            order[1] = 'R';
            duration = count - tempcounter;
        }
        else {
            if(duration > 0x000F) {
                order[1] = NULL;
            }
            init_XLCD();
            putrsXLCD(order);
            order[0] = NULL;
            order[1] = NULL;
            order[2] = NULL;
            rd0end = 1;
            rd1end = 1;
            rd2end = 1;
            duration = 0;
            __delay_ms(2000);
            
        } 
    }
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
