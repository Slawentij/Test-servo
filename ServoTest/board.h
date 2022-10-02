void BoardInit (void);
void InitPerepherals (void);


#ifndef __BOARD_H
#define __BOARD_H

// GREEN_LED1 
#define GREEN_LED1_Off        FIO2CLR_bit.P2_7 = 1      // LED1 Off
#define GREEN_LED1_On         FIO2SET_bit.P2_7 = 1      // LED1 On
#define GREEN_LED1_DIR        FIO2DIR_bit.P2_7 = 1      // LED1 pin  -->  output
// GREEN_LED2 
#define GREEN_LED2_Off        FIO2CLR_bit.P2_6 = 1      // LED2 Off
#define GREEN_LED2_On         FIO2SET_bit.P2_6 = 1      // LED2 On
#define GREEN_LED2_DIR        FIO2DIR_bit.P2_6 = 1      // LED2 pin  -->  output
// YELLOW_LED1
#define YELLOW_LED1_Off       FIO2CLR_bit.P2_5 = 1      // LED3 Off
#define YELLOW_LED1_On        FIO2SET_bit.P2_5 = 1      // LED3 On
#define YELLOW_LED1_DIR       FIO2DIR_bit.P2_5 = 1      // LED3 pin  -->  output
// YELLOW_LED2 
#define YELLOW_LED2_Off       FIO2CLR_bit.P2_4 = 1      // LED4 Off
#define YELLOW_LED2_On        FIO2SET_bit.P2_4 = 1      // LED4 On
#define YELLOW_LED2_DIR       FIO2DIR_bit.P2_4 = 1      // LED4 pin  -->  output
// RED_LED1
#define RED_LED1_Off          FIO2CLR_bit.P2_3 = 1      // LED5 Off
#define RED_LED1_On           FIO2SET_bit.P2_3 = 1      // LED5 On
#define RED_LED1_DIR          FIO2DIR_bit.P2_3 = 1      // LED5 pin  -->  output
// RED_LED2 
#define RED_LED2_Off          FIO2CLR_bit.P2_2 = 1      // LED6 Off
#define RED_LED2_On           FIO2SET_bit.P2_2 = 1      // LED6 On
#define RED_LED2_DIR          FIO2DIR_bit.P2_2 = 1      // LED6 pin  -->  output
// POWER LED 
#define POWER_LED_Off         FIO2CLR_bit.P2_8 = 1      // PWRLED Off
#define POWER_LED_On          FIO2SET_bit.P2_8 = 1      // PWRLED On
#define POWER_LED_DIR         FIO2DIR_bit.P2_8 = 1      // PWRLED pin  -->  output


#define S1                 PINMODE0_bit.P0_19 = 0    // Pull up resistor connected
#define S1_DIR             FIO0DIR_bit.P0_19 = 0     //  pin  -->  input
#define S1_PIN             FIO0PIN_bit.P0_19         // read data from Pin

#define S2                 PINMODE0_bit.P0_20 = 0    // Pull up resistor connected
#define S2_DIR             FIO0DIR_bit.P0_20 = 0     //  pin  -->  input
#define S2_PIN             FIO0PIN_bit.P0_20         // read data from Pin


// PCLK offset
#define WDT_PCLK_OFFSET     0
#define TIMER0_PCLK_OFFSET  2
#define TIMER1_PCLK_OFFSET  4
#define UART0_PCLK_OFFSET   6
#define UART1_PCLK_OFFSET   8
#define PWM0_PCLK_OFFSET    10
#define PWM1_PCLK_OFFSET    12
#define I2C0_PCLK_OFFSET    14
#define SPI_PCLK_OFFSET     16
#define RTC_PCLK_OFFSET     18
#define SSP1_PCLK_OFFSET    20
#define DAC_PCLK_OFFSET     22
#define ADC_PCLK_OFFSET     24
#define CAN1_PCLK_OFFSET    26
#define CAN2_PCLK_OFFSET    28
#define ACF_PCLK_OFFSET     30
#define BAT_RAM_PCLK_OFFSET 32
#define GPIO_PCLK_OFFSET    34
#define PCB_PCLK_OFFSET     36
#define I2C1_PCLK_OFFSET    38
//#define                   40
#define SSP0_PCLK_OFFSET    42
#define TIMER2_PCLK_OFFSET  44
#define TIMER3_PCLK_OFFSET  46
#define UART2_PCLK_OFFSET   48
#define UART3_PCLK_OFFSET   50
#define I2C2_PCLK_OFFSET    52
#define I2S_PCLK_OFFSET     54
#define MCI_PCLK_OFFSET     56
//#define                   58
#define PCLK_PCLK_OFFSET    60
//#define                   62

#define IRQ_FLAG            0x80
#define FIQ_FLAG            0x40

#endif /* __BOARD_H */