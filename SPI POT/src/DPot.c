/*
 * digPot.c
 *
 * Created: 06/11/2014 10:26:47 πμ
 *  Author: SPIROS
 */ 

#include <math.h>
#include "DPot.h"
#include "RegisterUtils.h"

struct spi_device spi_device_conf = {
	.id = SPI_DPOT_SCS
};

static double nomRes = DPOT_NOM_RES;

void dPotSetNomRes(double newNomRes){
	nomRes = newNomRes;
}

void spi_dpot_init_pins(void)
{
	ioport_configure_port_pin(&SPI_DPOT_PORT, PIN4_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	
	//ioport_configure_port_pin(&PORTC, PIN4_bm, IOPORT_PULL_UP | IOPORT_DIR_OUTPUT);
	ioport_configure_port_pin(&SPI_DPOT_PORT, PIN5_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	ioport_configure_port_pin(&SPI_DPOT_PORT, PIN6_bm, IOPORT_DIR_INPUT);
	ioport_configure_port_pin(&SPI_DPOT_PORT, PIN7_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
}

void spi_dpot_init_module(void)
{
	spi_master_init(&SPI_DPOT_MDL);
	spi_master_setup_device(&SPI_DPOT_MDL, &spi_device_conf, SPI_DPOT_MODE, SPI_DPOT_BAUD, 0);
	spi_enable(&SPI_DPOT_MDL);
}

void dPotInit(void){
		spi_dpot_init_pins();
		spi_dpot_init_module();
}

void dPotSelect(void){
		spi_select_device(&SPI_DPOT_MDL, &spi_device_conf);
}

void dPotDeselect(void){
		spi_deselect_device(&SPI_DPOT_MDL, &spi_device_conf);
}

void dPotEnableRDAC(void){
	uint16_t data = 0;
	data = (DPOT_WCREG<<10)|(1<<DPOT_C1);
	uint8_t hi_lo[] = { (uint8_t)(data>> 8), (uint8_t) data};
	dPotSelect();
	spi_write_packet(&SPI_DPOT_MDL, hi_lo, 2);
	while(!spi_is_tx_ok(&SPI_DPOT_MDL));
	dPotDeselect();
}

void dPotEnable50TP(void){
	uint16_t data = 0;
	data = (DPOT_WCREG<<10)|(1<<DPOT_C0);
	uint8_t hi_lo[] = { (uint8_t)(data>> 8), (uint8_t) data};
	dPotSelect();
	spi_write_packet(&SPI_DPOT_MDL, hi_lo, 2);
	while(!spi_is_tx_ok(&SPI_DPOT_MDL));
	dPotDeselect();
}

void dPotSetValue(uint16_t value){
	uint16_t data = 0;
	data = (DPOT_WRDAC<<10)|value;
	uint8_t hi_lo[] = { (uint8_t)(data>> 8), (uint8_t) data};
	dPotSelect();
	spi_write_packet(&SPI_DPOT_MDL, hi_lo, 2);
	while(!spi_is_tx_ok(&SPI_DPOT_MDL));
	dPotDeselect();
}

void dPotSetRes(uint16_t value){
	dPotSetValue((value/nomRes)*DPOT_RESOLUTION - 1.0);
}

uint16_t dPotReadRDAC(void){
	uint16_t data = 0;
	data = (DPOT_RRDAC<<10);
	uint8_t hi_lo[] = { (uint8_t)(data>> 8), (uint8_t) data};
	dPotSelect();
	spi_write_packet(&SPI_DPOT_MDL, hi_lo, 2);
	while(!spi_is_tx_ok(&SPI_DPOT_MDL));
	dPotDeselect();
	
	dPotSelect();
	while(!spi_is_rx_ready(&SPI_DPOT_MDL));
	spi_read_packet(&SPI_DPOT_MDL, hi_lo,2);
	dPotDeselect();
	
	return (hi_lo[0]<<8) + hi_lo[1];
	
}

double dPotReadRes(void){
	
	return ( (dPotReadRDAC()+1)/DPOT_RESOLUTION )*nomRes;
	
}

uint16_t dPotReadFromMem(uint8_t addr){
	uint16_t data = 0;
	data = (DPOT_R50TP<<10)|addr;
	uint8_t hi_lo[] = { (uint8_t)(data>> 8), (uint8_t) data};
	dPotSelect();
	spi_write_packet(&SPI_DPOT_MDL, hi_lo, 2);
	while(!spi_is_tx_ok(&SPI_DPOT_MDL));
	dPotDeselect();
	
	dPotSelect();
	while(!spi_is_rx_ready(&SPI_DPOT_MDL));
	spi_read_packet(&SPI_DPOT_MDL, hi_lo, 2);
	dPotDeselect();
	
	return (CLEARBITS(hi_lo[0],0xFC)<<8) + hi_lo[1];
}

double dPotCalibrate(void){
	uint16_t newNomRes;
	uint8_t high = dPotReadFromMem(0x39);
	uint8_t low = dPotReadFromMem(0x3A);
	bool isPositive = BITSET(high,7);
	CLEARBIT(high,7);
	if(isPositive){
		newNomRes = DPOT_NOM_RES + DPOT_NOM_RES * (high + low*pow(2,-8))/100;
		dPotSetNomRes(newNomRes);
		return newNomRes;
	}
	else{
		newNomRes = DPOT_NOM_RES - DPOT_NOM_RES * (high + low*pow(2,-8))/100;
		dPotSetNomRes(newNomRes);
		return newNomRes;
	}
	
}

void dPotIncResValue(void){
	uint16_t newResV = dPotReadRDAC() + 1;
	if (newResV < DPOT_RESOLUTION){
		dPotSetValue(newResV);
	}
}

void dPotDecResValue(void){
	uint16_t newResV = dPotReadRDAC() - 1;
	if (newResV < DPOT_RESOLUTION){
		dPotSetValue(newResV);
	}
}