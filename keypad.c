
#include <xc.h>
#include "keypad.h"
#include "timer.h"


#define TRIS_Row1 TRISGbits.TRISG0
#define TRIS_Row2 TRISDbits.TRISD9
#define TRIS_Row3 TRISDbits.TRISD3
#define TRIS_Row4 TRISDbits.TRISD12
#define TRIS_Col1 TRISFbits.TRISF1
#define TRIS_Col2 TRISGbits.TRISG13
#define TRIS_Col3 TRISDbits.TRISD6

#define LAT_Row1 LATGbits.LATG0
#define LAT_Row2 LATDbits.LATD9
#define LAT_Row3 LATDbits.LATD3
#define LAT_Row4 LATDbits.LATD12
#define PORT_Col1 PORTFbits.RF1
#define PORT_Col2 PORTGbits.RG13
#define PORT_Col3 PORTDbits.RD6

#define OUTPUT 0
#define INPUT 1
#define ENABLED 1
#define NUM_ROWS 4

/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */
void initKeypad(void){
    TRIS_Row1=OUTPUT;
    TRIS_Row2=OUTPUT;
    TRIS_Row3=OUTPUT;
    TRIS_Row4=OUTPUT;
    
    ANSELDbits.ANSD3=0;
    
    ODCGbits.ODCG0=1;
    ODCDbits.ODCD9=1;
    ODCDbits.ODCD3=1;
    ODCDbits.ODCD12=1;
    
    LAT_Row1=0;
    LAT_Row2=0;
    LAT_Row3=0;
    LAT_Row4=0;
    
    
    
    TRIS_Col1=INPUT;
    TRIS_Col2=INPUT;
    TRIS_Col3=INPUT;
    
    CNCONFbits.ON=1;
    CNCONGbits.ON=1;
    CNCONDbits.ON=1;
    
    CNENFbits.CNIEF1=ENABLED;
    CNENGbits.CNIEG13=ENABLED;
    CNENDbits.CNIED6=ENABLED;
            
    
    IFS1bits.CNFIF = 0;         // Put down the flag
    IFS1bits.CNGIF = 0;         // Put down the flag
    IFS1bits.CNDIF = 0;         // Put down the flag
    
    IPC8bits.CNIP = 7;          // Configure interrupt priority
    
    IEC1bits.CNFIE = ENABLED;   // Enable interrupt for F pins
    IEC1bits.CNGIE = ENABLED;   // Enable interrupt for G pins
    IEC1bits.CNDIE = ENABLED;   // Enable interrupt for D pins
    
    
    
}

/* This function will be called AFTER you have determined that someone pressed
 * SOME key. This function is to figure out WHICH key has been pressed.
 * This function should return -1 if more than one key is pressed or if
 * no key is pressed at all. Otherwise, it should return the ASCII character of
 * the key that is pressed. The ascii character c programmatically is just 'c'
 */
char scanKeypad(void){
    char key = -1;
    int i;
    int numPresses=0;
                
                

                
                LAT_Row1=1;
                LAT_Row2=1;
                LAT_Row3=1;
                LAT_Row4=0;

                 delayUs(5);
                
                if(PORT_Col1==0){
                    key='*';
                    numPresses++;
                }
                else if(PORT_Col2==0){
                    key='0';
                    numPresses++;
                }
                else if(PORT_Col3==0){
                    key='#';
                    numPresses++;
                }



                LAT_Row1=1;
                LAT_Row2=1;
                LAT_Row3=0;
                LAT_Row4=1;
                
                 delayUs(5);
                
                if(PORT_Col1==0){
                    key='7';
                    numPresses++;
                }
                else if(PORT_Col2==0){
                    key='8';
                    numPresses++;
                }
                else if(PORT_Col3==0){
                    key='9';
                    numPresses++;
                }


                LAT_Row1=1;
                LAT_Row2=0;
                LAT_Row3=1;
                LAT_Row4=1;
                
                delayUs(5);
                
                if(PORT_Col1==0){
                    key='4';
                    numPresses++;
                }
                else if(PORT_Col2==0){
                    key='5';
                    numPresses++;
                }
                else if(PORT_Col3==0){
                    key='6';
                    numPresses++;
                }


                LAT_Row1=0;
                LAT_Row2=1;
                LAT_Row3=1;
                LAT_Row4=1;
                
                delayUs(5);
                
                if(PORT_Col1==0){
                    key='1';
                    numPresses++;
                }
                else if(PORT_Col2==0){
                    key='2';
                    numPresses++;
                }
                else if(PORT_Col3==0){
                    key='3';
                    numPresses++;
                }
          
                

    if(numPresses>1){
        key=-1;
    }
    
   
    LAT_Row1=0;
    LAT_Row2=0;
    LAT_Row3=0;
    LAT_Row4=0;
    
    
    return key;
}
