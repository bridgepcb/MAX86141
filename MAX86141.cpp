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
  uint8_t s;                  // Variable used to form each setting byte
  pinMode(_SS_pin, OUTPUT);
  SPI.begin();
  
}


/*
 * Writes a byte to a register over SPI
 * Params: 
 *    addr - Register address to write
 *    data - data to write on the provided address
 * Returns: 
 *    None
 */ 
void Max86141::writeRegister(uint8_t addr, uint8_t data)
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
uint8_t Max86141::readRegister(uint8_t addr)
{
  uint8_t resp;                     // Response from MAX86141
  digitalWrite(_SS_pin, LOW);
  SPI.transfer(addr);
  SPI.transfer(SPI_READ);           // Read mode
  resp = SPI.transfer(0x00);
  digitalWrite(_SS_pin, HIGH);
  return resp;
}
