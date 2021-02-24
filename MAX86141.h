/*
  MAX86141.h - Arduino library for the MAX86141 pulse oximeter and heart rate sensor from Maxim Integrated.
  Created by Leonardo Marquez, February 24, 2021.
  Bridge PCB Design: http://www.bridgepcbdesign.com
*/

#ifndef MAX86141_H
#define MAX86141_H

#include <Arduino.h>
#include <SPI.h>

// Register Mapping:
#define INT_STATUS_1    0x00
#define INT_STATUS_2    0x01
#define INT_ENABLE_1    0x02
#define INT_ENABLE_2    0x03
#define FIFO_WR_PTR     0x04
#define FIFO_RD_PTR     0x05
#define FIFO_OVF_CTR    0x06
#define FIFO_DATA_CTR   0x07
#define FIFO_DATA       0x08
#define FIFO_CNF_1      0x09
#define FIFO_CNF_2      0x0A
#define SYS_CTRL        0x0D
#define PPG_SYNC_CTRL   0x10
#define PPG_CNF_1       0x11
#define PPG_CNF_2       0x12
#define PPG_CNF_3       0x13
#define PROX_INT_THRESH 0x14
#define PDBIAS          0x15
#define PICKET_FENCE    0x16
#define LED_SEQ_1       0x20
#define LED_SEQ_2       0x21
#define LED_SEQ_3       0x22
#define LED1_PA         0x23
#define LED2_PA         0x24
#define LED3_PA         0x25
#define LED4_PA         0x26
#define LED5_PA         0x27
#define LED6_PA         0x28
#define LED_PILOT_PA    0x29
#define LED_RGE_1       0x2A
#define LED_RGE_2       0x2B
#define S1_HI_RES_DAC1  0x2C
#define S2_HI_RES_DAC1  0x2D
#define S3_HI_RES_DAC1  0x2E
#define S4_HI_RES_DAC1  0x2F
#define S5_HI_RES_DAC1  0x30
#define S6_HI_RES_DAC1  0x31
#define S1_HI_RES_DAC2  0x32
#define S2_HI_RES_DAC2  0x33
#define S3_HI_RES_DAC2  0x34
#define S4_HI_RES_DAC2  0x35
#define S5_HI_RES_DAC2  0x36
#define S6_HI_RES_DAC2  0x37
#define TEMP_CNF        0x40
#define TEMP_INT        0x41
#define TEMP_FRAC       0x42
#define SHA_CMD         0xF0
#define SHA_CNF         0xF1
#define MEM_CTRL        0xF2
#define MEM_INDEX       0xF3
#define MEM_DATA        0xF4
#define PART_ID         0xFF

// Resgister R/W Modes:
#define SPI_WRITE       0x00
#define SPI_READ        0xFF

class Max86141
{
  public:
    Max86141(int SS_pin);         // Constructor
    
    // Structure to hold all the device's settings
    struct sensorSettings {
      // System Control (0x0D):
      uint8_t RESET = 0x00;
      uint8_t SHDN = 0x00;
      uint8_t LP_MODE = 0x00;
      uint8_t SINGLE_PPG = 0x00;
      
      // PPG Configuration 1 (0x11):
      uint8_t PPG_TINT = 0x03;
      uint8_t PPG1_ADC_RGE = 0x00;
      uint8_t PPG2_ADC_RGE = 0x00;
      uint8_t ADD_OFFSET = 0x00;
      uint8_t ALC_DISABLE = 0x00;
      
      // PPG Configuration 2 (0x12):
      uint8_t SMP_AVE = 0x00;
      uint8_t PPG_SR = 0x11;
      
      // LED Sequence Register 1 (0x20)
      uint8_t LEDC1 = 0x00;
      uint8_t LEDC2 = 0x00;
      
      // LED Sequence Register 2 (0x21)
      uint8_t LEDC3 = 0x00;
      uint8_t LEDC4 = 0x00;
      
      // LED Sequence Register 3 (0x22)
      uint8_t LEDC5 = 0x00;
      uint8_t LEDC6 = 0x00;
      
      // LED1 PA (0x23)
      uint8_t LED1_DRV = 0x00;
      
      // LED2 PA (0x24)
      uint8_t LED2_DRV = 0x00;
      
      // LED3 PA (0x25)
      uint8_t LED3_DRV = 0x00;
      
      // LED4 PA (0x26)
      uint8_t LED3_DRV = 0x00;
      
      // LED5 PA (0x27)
      uint8_t LED5_DRV = 0x00;
      
      // LED6 PA (0x28)
      uint8_t LED6_DRV = 0x00;
      
      // LED PILOT PA (0x29)
      uint8_t PILOT_PA = 0x00;
      
    } settings;
    
    void begin(void);
    void writeRegister(uint8_t addr, uint8_t data);
    uint8_t readRegister(uint8_t addr);
    uint8_t burstReadFIFO();
    
  private:
    uint8_t _SS_pin;
};


#endif