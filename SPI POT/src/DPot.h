/*
 * digPot.h
 *
 * Created: 06/11/2014 10:26:34 πμ
 *  Author: SPIROS
 */ 


#ifndef DIGPOT_H_
#define DIGPOT_H_

#include <stdio.h>
#include <asf.h>

/************************************************************************/
/*	SPI Parameters
*/
/************************************************************************/
#define SPI_DPOT_MDL	SPIC								//SPI module
#define SPI_DPOT_PORT	PORTC								//SPI port
#define SPI_DPOT_MODE	SPI_MODE_1							//SPI mode
#define SPI_DPOT_BAUD	2000000								//SPI frequency
#define SPI_DPOT_SCS	IOPORT_CREATE_PIN(PORTC, PIN4_bp)	//Chip Select pin (SS)

/************************************************************************/
/*	Digital Potentiometer command list
*/
/************************************************************************/
#define DPOT_NOP		0b0000	//NOP: do nothing
#define DPOT_WRDAC		0b0001	//Write contents of serial register data to RDAC
#define DPOT_RRDAC		0b0010	//Read contents of RDAC wiper register
#define DPOT_STRDAC		0b0011	//Store wiper setting: store RDAC setting to 50-TP
#define DPOT_SWRESET	0b0100	//Software reset: refresh RDAC with last 50-TP memory stored value
#define DPOT_R50TP		0b0101	//Read contents of 50-TP from SDO output in the next frame
#define DPOT_RADDR50TP	0b0110	//Read address of last 50-TP programmed memory location
#define DPOT_WCREG		0b0111	//Write contents of serial register data to control register
#define DPOT_RCREG		0b1000	//Read contents of control register
#define DPOT_SHUTDOWN	0b1001	//Software shutdown. D0 = 0; normal mode. D0 = 1; device placed in shutdown mode

/************************************************************************/
/*	Digital Potentiometer parameters
*/
/************************************************************************/
#define DPOT_NOM_RES	10000.0	//Dig. Pot. nominal value
#define DPOT_RESOLUTION	1024.0	//Dig. Pot. resolution
#define DPOT_C0			0		//Position of C0 bit of Control Register
#define DPOT_C1			1		//Position of C1 bit of Control Register

extern struct spi_device spi_device_conf;	//SPI configuration device

/************************************************************************/
/*	Initialize the pins used for SPI
*/
/************************************************************************/
void spi_dpot_init_pins(void);

/************************************************************************/
/*	Initialize SPI
*/
/************************************************************************/
void spi_dpot_init_module(void);

/************************************************************************/
/*	Initialize Digital Potentiometer
*/
/************************************************************************/
void dPotInit(void);

/************************************************************************/
/*	Select this potentiometer with ^SS pin
*/
/************************************************************************/
void dPotSelect(void);

/************************************************************************/
/*	De-select this potentiometer with ^SS pin
*/
/************************************************************************/
void dPotDeselect(void);

/************************************************************************/
/*	Enable write ability for RDAC register
*/
/************************************************************************/
void dPotEnableRDAC(void);

/************************************************************************/
/*	Enable write ability for 50TP memory
*/
/************************************************************************/
void dPotEnable50TP(void);

/************************************************************************/
/*	Set integer value to RDAC
	value: 0-1023
*/
/************************************************************************/
void dPotSetValue(uint16_t value);

/************************************************************************/
/*	Set resistance value to potentiometer
	value: 0-10000
*/
/************************************************************************/
void dPotSetRes(uint16_t value);

/************************************************************************/
/*	Get the current integer value of RDAC register
	return: unsigned 16-bit integer between 0-1023
*/
/************************************************************************/
uint16_t dPotReadRDAC(void);

/************************************************************************/
/*	Get the current resistance value of RDAC register
	return: double between 0-DPOT_NOM_RES
*/
/************************************************************************/
double dPotReadRes(void);

/************************************************************************/
/*	Read from 50TP memory
	addr: 0x01-0x3A
	return: unsigned 16-bit integer
*/
/************************************************************************/
uint16_t dPotReadFromMem(uint8_t addr);

/************************************************************************/
/*	Read Calibration values from memory and update the nominal resistance
	return: new calibrated nominal resistance
*/
/************************************************************************/
double dPotCalibrate(void);

/************************************************************************/
/*	Calibrates the conversions with the real nominal resistance
	newNomRes: new value of nominal resistance
*/
/************************************************************************/
void dPotSetNomRes(double newNomRes);

/************************************************************************/
/*	Increase the integer value of the resistance by one.
	Possible range 0-1023.
*/
/************************************************************************/
void dPotIncResValue(void);

/************************************************************************/
/*	Decrease the integer value of the resistance by one.
	Possible range 0-1023.
*/
/************************************************************************/
void dPotDecResValue(void);

#endif /* DIGPOT_H_ */