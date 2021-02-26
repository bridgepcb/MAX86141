/*
  MAX86141.cpp - Arduino library for the MAX86141 pulse oximeter and heart rate sensor from Maxim Integrated.
  Created by Leonardo Marquez, February 24, 2021.
  Bridge PCB Design: http://www.bridgepcbdesign.com
*/

#include "MAX86141.h"

/*
 * Constructor method
 * Params: 
 *    SS_pin - SPI Chip Select (SS) pin number
 */ 
Max86141::Max86141(int SS_pin)
{
  _SS_pin = SS_pin;
}


/*
 * Initializes MAX86141
 * Params: 
 *    None
 * Returns: 
 *    None
 */
void Max86141::begin(void)
{
  byte s;                                      // Variable used to form each setting byte
  pinMode(_SS_pin, OUTPUT);
  digitalWrite(_SS_pin, HIGH);
  SPI.begin();
  
  writeRegister(SYS_CTRL, 0x01);               // First, reset the sensor
  delay(1);
  readRegister(INT_STATUS_1);                  //  READ Interrupt Status 1
  readRegister(INT_STATUS_2);                  //  READ Interrupt Status 2
  writeRegister(SYS_CTRL, 0x02);               //  WRITE 0x1 to SHDN
  
  // PPG Configuration 2
  s = (settings.PPG_SR<<3) | (settings.SMP_AVE);
  writeRegister(PPG_CNF_2, s);
  
  // LED1 PA
  s = (settings.LED1_DRV);
  writeRegister(LED1_PA, s);
  
  // LED2 PA
  s = (settings.LED2_DRV);
  writeRegister(LED2_PA, s);
  
  // LED3 PA
  s = (settings.LED3_DRV);
  writeRegister(LED3_PA, s);
  
  // LED4 PA
  s = (settings.LED4_DRV);
  writeRegister(LED4_PA, s);
  
  // LED5 PA
  s = (settings.LED5_DRV);
  writeRegister(LED5_PA, s);
  
  // LED1 PA
  s = (settings.LED6_DRV);
  writeRegister(LED6_PA, s);
  
  // LED PILOT PA
  s = (settings.PILOT_PA);
  writeRegister(LED_PILOT_PA, s);
  
  // LED Sequence Register 1
  s = (settings.LEDC2<<4) | (settings.LEDC1);
  writeRegister(LED_SEQ_1, s);
  
  // LED Sequence Register 2
  s = (settings.LEDC4<<4) | (settings.LEDC3);
  writeRegister(LED_SEQ_2, s);
  
  // LED Sequence Register 3
  s = (settings.LEDC6<<4) | (settings.LEDC5);
  writeRegister(LED_SEQ_3, s);
  
    // System Control
  s = (settings.SINGLE_PPG<<3) | (settings.LP_MODE<<2);
  writeRegister(SYS_CTRL, s);
}


/*
 * Writes a byte to a register over SPI
 * Params: 
 *    addr - Register address to write
 *    data - data to write on the provided address
 * Returns: 
 *    None
 */ 
void Max86141::writeRegister(byte addr, byte data)
{
  digitalWrite(_SS_pin, LOW);
  SPI.transfer(addr);
  SPI.transfer(SPI_WRITE);          // Write mode
  SPI.transfer(data);
  digitalWrite(_SS_pin, HIGH);
}


/*
 * Reads a byte from registers over SPI
 * Params: 
 *    addr - Register address to read
 * Returns: 
 *    Data from register
 */
byte Max86141::readRegister(byte addr)
{
  byte resp;                     // Response from MAX86141
  digitalWrite(_SS_pin, LOW);
  SPI.transfer(addr);
  SPI.transfer(SPI_READ);           // Read mode
  resp = SPI.transfer(0x00);
  digitalWrite(_SS_pin, HIGH);
  return resp;
}


/*
 * Reads PPG data from FIFO ("burst read")
 * Params: 
 *    None
 * Returns: 
 *    Buffer with PPG data (128 samples, 3 byte each)
 */
unsigned long* Max86141::burstReadFIFO()
{
  static unsigned long fifoData[FIFO_SIZE];
  byte ppgSample[3];
  byte count;                    // To store how much data is in FIFO
  
  memset(fifoData, 0, FIFO_SIZE);   // Flush buffer
  
  count = readRegister(FIFO_DATA_CTR);
  if (count > 0) {
    digitalWrite(_SS_pin, LOW);
    SPI.transfer(FIFO_DATA);
    SPI.transfer(SPI_READ);
    for (int i=0; i<count; i++) {
      ppgSample[0] = SPI.transfer(0x00);
      ppgSample[1] = SPI.transfer(0x00);
      ppgSample[2] = SPI.transfer(0x00);
      fifoData[i] = ((unsigned long)ppgSample[0]<<16) | ((unsigned long)ppgSample[1]<<8) | (unsigned long)ppgSample[2];
    }
  }
  return fifoData;
}