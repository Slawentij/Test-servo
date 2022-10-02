#include <NXP/iolpc1768.h>

#include "pwm.h"


void Delay_mS (unsigned int mSec);
void NVIC_ClrPend(int IntNumber);


//------------------------------------------------------------------------------
void InitPWM (void)
{ 

  PCONP_bit.PCPWM1 = 1;         // Enable power to PWM1
  PCLKSEL0_bit.PCLK_PWM1 = 1;   // PCLK_peripheral = 100MHz / 2 = 50MHz
  PINSEL4_bit.P2_1 = 1;         // P2.1  PWM1.1
  
  PWM1TCR_bit.CE = 1;           // The PWM Timer Counter and PWM Prescale Counter are enabled for counting
  PWM1TCR_bit.PWMEN = 1;        // PWM mode is enabled (counter resets to 1).
  PWM1PR = 99;                  // Prescale Register. The TC is incremented every PR+1 cycles of PCLK. 
  PWM1MCR_bit.PWMMR0R = 1;      // Reset on PWMMR0: the PWMTC will be reset if PWMMR0 matches it.
  
  PWM1MR0 = 20000;                // Match Register 0. (PWM rate) - выводить HI каждые MR0 тиков  resolution=1uS
  PWM1MR1 = 1;                  // выводим LO когда TC = MR1
  PWM1LER_bit.EM0L = 1;         // Load Enable Register. Enables use of new PWM match values
  PWM1LER_bit.EM1L = 1;         // Load Enable Register. Enables use of new PWM match values

  PWM1TC = 0;                   // Reset Timer

  PWM1PCR_bit.PWMENA2 = 1;      // The PWM1.2 output enabled 
}
/*************************************************************************/
void PWM1_IRQHandler (void)
{ 
   PWM1MR1 = 0;              // выводим LO когда TC = MR5           
   
   PWM1LER_bit.EM1L = 1;      // Load Enable Register. Enables use of new PWM match values
   
   PWM1IR_bit.PWMMR0I = 1;    // Clear Interrupt flag for PWM match channel 0  
   NVIC_ClrPend(NVIC_PWM1);

}
//------------------------------------------------------------------------------
void SetPWM1 (unsigned char Cannel, unsigned int Offset)
{
   switch (Cannel)
   { 
   case 1: { PWM1MR1 = Offset; PWM1LER_bit.EM1L = 1; break; }
   case 2: { PWM1MR2 = Offset; PWM1LER_bit.EM2L = 1; break; }
   case 3: { PWM1MR3 = Offset; PWM1LER_bit.EM3L = 1; break; }
   case 4: { PWM1MR4 = Offset; PWM1LER_bit.EM4L = 1; break; }
   case 5: { PWM1MR5 = Offset; PWM1LER_bit.EM5L = 1; break; }
   case 6: { PWM1MR6 = Offset; PWM1LER_bit.EM6L = 1; break; }
   default: { break;}
   } 
}
//------------------------------------------------------------------------------

