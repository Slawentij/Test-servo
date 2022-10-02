#include "includes.h"

 
int DelayCounter;
unsigned int CurrentAngle;

#define ENC_NONE  0
#define ENC_LEFT  1
#define ENC_RIGHT 2   

//------------------------------------------------------------------------------
unsigned char TimeOutsFlags[8] = {0,0,0,0,0,0,0,0}; //  Массив флагов таймаутов
unsigned int TimeOutsCounter[8];                    //  Массив счетчиков таймаутов
unsigned int TimeOutsSetUp[8];                      //  Массив значений установленых таймаутов
unsigned char TimeOutsCount = 0;                    //  Колличество работающих таймаутов
//------------------------------------------------------------------------------  

Int32U CriticalSecCntr;

// ----------------------------------------------------------------------------------
void Delay_mS (unsigned int mSec)
{  
    T0TCR_bit.CE = 0;      // counting  disable
    T0TCR_bit.CR = 1;      // set reset
    T0TCR_bit.CR = 0;      // release reset
    DelayCounter = 0;
    T0TCR_bit.CE = 1;      // counting Enable
    while (DelayCounter  < mSec);
    T0TCR_bit.CE = 0;      // counting  disable
    T0TCR_bit.CR = 1;      // set reset
}
// ----------------------------------------------------------------------------------
unsigned char CheckTimeOut (unsigned char TimeOutID)
{
  return (TimeOutsFlags[TimeOutID]);
}
//*************************************************************************
void NVIC_IntEnable(int IntNumber)
{
volatile unsigned long * pNVIC_SetEn = &SETENA0;

  assert((NVIC_WDT <= IntNumber) && (NVIC_PLL1 >= IntNumber));
  IntNumber -= NVIC_WDT;

  pNVIC_SetEn += IntNumber/32;
  *pNVIC_SetEn = (1UL<<(IntNumber%32));

}
//*************************************************************************
void NVIC_ClrPend(int IntNumber)
{
volatile unsigned long * pNVIC_ClrPend = &CLRPEND0;

  assert((NVIC_WDT <= IntNumber) && (NVIC_PLL1 >= IntNumber));
  IntNumber -= NVIC_WDT;

  pNVIC_ClrPend += IntNumber/32;
  *pNVIC_ClrPend = (1UL<<(IntNumber%32));

}

//*************************************************************************
void InitTimer0 (void)
{
  PCONP_bit.PCTIM0 = 1; // Enable TMR0 clk
  T0TCR_bit.CE = 0;     // counting  disable
  T0TCR_bit.CR = 1;     // set reset
  T0TCR_bit.CR = 0;     // release reset
  T0CTCR_bit.CTM = 0;   // Timer Mode: every rising PCLK edge
  T0MCR_bit.MR0I = 1;   // Enable Interrupt on MR0
  T0MCR_bit.MR0R = 1;   // Enable reset on MR0
  T0MCR_bit.MR0S = 0;   // Disable stop on MR0
  T0PR = 0;
  T0MR0 = 0x61A8;                 // 0x61A8 =>> 1000 uS

  T0IR_bit.MR0INT = 1;            // clear pending interrupt
  NVIC_IntEnable(NVIC_TIMER0);    // Enable NVIC TMR0 Interrupt

  T0TCR_bit.CE = 1;               // counting Enable
}

//-------------------------------------------------------------------------------
void TIMER0_IRQHandler (void)
{
  DelayCounter++;
  T0IR_bit.MR0INT = 1;
  NVIC_ClrPend(NVIC_TIMER0);
}

//------------------------------------------------------------------------------
void SetServoAngle (unsigned int Angle)
{ float Nb00;
  
  Nb00 = (Angle * 8.666);                                                       // 1000 uS = 180 deg  =>  8.66 = 1 deg
  SetPWM1 (2, 2100 - (unsigned int) Nb00);                                      // 544 .... 2100 ms [0...180 deg]
}
//------------------------------------------------------------------------------
unsigned char ReadEncoder (void)
{ unsigned char EncState;
  
  EncState = ENC_NONE;
  if (S1_PIN == 0)
   {
     if (S2_PIN == 0) 
      {
         while (S1_PIN == 0);
         Delay_mS(1);
         EncState = ENC_RIGHT;
       } else
          { 
              while (S2_PIN == 1);
              Delay_mS(1);
              while (S2_PIN == 0);
              Delay_mS(1);
              EncState = ENC_LEFT;
          }
   }   
  return (EncState);
}
//------------------------------------------------------------------------------
int main()
{   
  __disable_interrupt();  
  BoardInit ();    
   
  InitTimer0();                                                                 // For Delay functions
  InitPerepherals();
  
  __enable_interrupt();
  
  InitPWM();                                           
  
  CurrentAngle = 90;
  SetServoAngle (CurrentAngle);
  
  RED_LED1_Off;
  GREEN_LED1_Off;

  while (1)
  {
    if (ReadEncoder() == ENC_LEFT) 
     {
       if (CurrentAngle > 0) 
         { 
           CurrentAngle = CurrentAngle - 5;
           SetServoAngle (CurrentAngle);
         }
     }
    
     if (ReadEncoder() == ENC_RIGHT) 
     {
       if (CurrentAngle < 180) 
         { 
           CurrentAngle = CurrentAngle + 5;
           SetServoAngle (CurrentAngle);
         }
     }
    
    if (CurrentAngle == 0)     GREEN_LED1_On; else GREEN_LED1_Off;
    if (CurrentAngle == 180)   RED_LED2_On;   else RED_LED2_Off;

  }  
}


