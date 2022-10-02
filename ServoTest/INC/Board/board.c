#include "includes.h"
// ----------------------------------------------------------------------------------
void BoardInit (void)
{
   // Flash accelerator init
  FLASHCFG = (0x5UL<<12) | 0x3AUL;  
  
  // 1. Init OSC
  SCS_bit.OSCRANGE = 0;             // „астота основного генератора  от 0 до 20ћ√ц
  SCS_bit.OSCEN = 1;                // ¬кл основной генератор 12ћ√ц
  // 2.  Wait for OSC ready
  while(!SCS_bit.OSCSTAT);
  // 3. Disconnect PLL
  PLL0CON_bit.PLLC = 0;
  PLL0FEED = 0xAA;
  PLL0FEED = 0x55;
  // 4. Disable PLL
  PLL0CON_bit.PLLE = 0;
  PLL0FEED = 0xAA;
  PLL0FEED = 0x55;
  // 5. Select source clock for PLL
  CLKSRCSEL_bit.CLKSRC = 1;          // Selects the main oscillator as a PLL clock source.
  PCLKSEL0 = PCLKSEL1  = 0;          // other peripherals 100/4 = 25MHz
  // 6. Set PLL settings 300 MHz
  PLL0CFG_bit.MSEL = 25-1;
  PLL0CFG_bit.NSEL = 2-1;
  PLL0FEED = 0xAA;
  PLL0FEED = 0x55;
  // 7. Enable PLL
  PLL0CON_bit.PLLE = 1;
  PLL0FEED = 0xAA;
  PLL0FEED = 0x55;
  // 8. Wait for the PLL to achieve lock
  while(!PLL0STAT_bit.PLOCK);
  // 9. Set clk divider settings
  CCLKCFG   = 3-1;            // 1/3 Fpll
  // 10. Connect the PLL
  PLL0CON_bit.PLLC = 1;
  PLL0FEED = 0xAA;
  PLL0FEED = 0x55;   

  // Reset all GPIO pins to default primary function
  PINSEL0 = 0;
  PINSEL1 = 0;
  PINSEL2 = 0;
  PINSEL3 = 0;
  PINSEL4 = 0;
  PINSEL7 = 0;
  PINSEL8 = 0;
  PINSEL9 = 0;  
  
  // Set to inputs
  FIO0DIR = 0;
  FIO1DIR = 0;
  FIO2DIR = 0;
  FIO3DIR = 0;
  FIO4DIR = 0;

  // clear mask registers
  FIO0MASK = 0;
  FIO1MASK = 0;
  FIO2MASK = 0;
  FIO3MASK = 0;
  FIO4MASK = 0;
}
//------------------------------------------------------------------------------
void InitPerepherals (void)
{

  GREEN_LED1_DIR; GREEN_LED2_DIR; YELLOW_LED1_DIR;YELLOW_LED2_DIR; RED_LED1_DIR;RED_LED2_DIR; POWER_LED_DIR; //Beeper_DIR; Relay_DIR; 
  GREEN_LED1_Off; GREEN_LED2_Off; YELLOW_LED1_Off; YELLOW_LED2_Off; RED_LED1_Off; RED_LED2_Off; POWER_LED_Off; //Beeper_Off; Relay_Off; 
  
  S1_DIR; S2_DIR;

}