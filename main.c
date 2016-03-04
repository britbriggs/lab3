// ******************************************************************************************* //
//
// File:         lab1p2.c
// Date:         12-30-2014
// Authors:      Garrett Vanhoy
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "switch.h"
#include "config.h"
#include "interrupt.h"


// ******************************************************************************************* //
#define DEBOUNCE_DELAY_MS 1

typedef enum stateTypeEnum{
    init, debouncePress, debounceRelease, waitForPress, waitForRelease
} stateType;

volatile stateType state = waitForPress;
volatile int switchPressedFlag = 0;
volatile long int counter=0;
volatile int resetFlag=0;
volatile char lcdNum;
volatile char keyCode[4];
volatile int count=0;
volatile int firstStarCount=0;
volatile int setModeFlag=0;
int main(void)
{
    SYSTEMConfigPerformance(10000000);
    initKeypad();
    initLCD();                  // Initialize LCD
    enableInterrupts();
    clearLCD();
    printStringLCD("Enter");
    moveCursorLCD(0,1);
    keyCode[0]='7';
    keyCode[1]='2';
    keyCode[2]='1';
    keyCode[3]='4';
    int i;
    
    while(1)
    {
        switch(state){
            case debouncePress:
                for(i=0;i<1;i++){
                  delayUs(5000);

                }
                
                lcdNum=scanKeypad();
                printCharLCD(lcdNum);
                
                if(lcdNum=='*' && count==0){
                    
                    firstStarCount=1;
                }
                else if(lcdNum=='*' && count==1 && firstStarCount==1){
                    clearLCD();
                    printStringLCD("Set Mode");
                    moveCursorLCD(0,1);
                    setModeFlag=1;
                    count=-1;
                }
               
                
             
                
                else if(lcdNum!='*' && lcdNum==keyCode[count] && count==3 && setModeFlag!=1){
                    clearLCD();
                    printStringLCD("Good");
                    for(i=0;i<150;i++){
                        delayUs(500);
                    }
                    count=-1;
                    clearLCD();
                    printStringLCD("Enter");
                    moveCursorLCD(0,1);
                }
                
                else if(lcdNum!='*' && lcdNum!=keyCode[count] && setModeFlag!=1){
                    clearLCD();
                    printStringLCD("Bad");
                    for(i=0;i<150;i++){
                        delayUs(500);
                    }
                    count=-1;
                    clearLCD();
                    printStringLCD("Enter");
                    moveCursorLCD(0,1);
                }
                
                else if(setModeFlag){
                    if(count==3){
                        delayUs(1000);
                        keyCode[count]=lcdNum;
                        count=-1;
                        clearLCD();
                        printStringLCD("Good");
                        for(i=0;i<150;i++){
                            delayUs(500);
                        }
                        clearLCD();
                        printStringLCD("Enter");
                        moveCursorLCD(0,1);
                        setModeFlag=0;
                    }
                    else{
                        delayUs(1000);
                        keyCode[count]=lcdNum;
                    }
                }
                
                

                count=count+1;
                
                state=waitForRelease;
                
                break;
            case waitForRelease:
                break;
            case waitForPress:
                break;
            case debounceRelease:
                for(i=0;i<1;i++){
                  delayUs(5000);

                }
                state=init;
                break;
                
            case init:
                state=waitForPress;
                break;
        }
        
    }
    
    return 0;
}


void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt( void ){
    
    PORTF;
    PORTG;
    PORTD;
    
    IFS1bits.CNFIF = 0;         // Put down the flag
    IFS1bits.CNGIF = 0;         // Put down the flag
    IFS1bits.CNDIF = 0;         // Put down the flag
    
    if (state == waitForPress) state = debouncePress;            //Same state machine as p1
    else if(state == waitForRelease) state = debounceRelease; 
    
   // else{
      
  //  }

}


