/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>
#include <stdio.h>
#include <stdlib.h>
#include <delay.h>
#include <led.h>
#include <string.h>
#include "DPot.h"
#include "usbUtils.h"
#include "RegisterUtils.h"
#include "measurements.h"
#include "fontUtils.h"

int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).

	board_init();
	sysclk_init();
	irq_initialize_vectors();
	cpu_irq_enable();

	udc_start();
	
	adc_init();
	
	dPotInit();
	dPotEnableRDAC();
	
	
	//dPotSetValue(1023);
	
	//delay_ms(2000);
	
	//dPotSetValue(511);
	
	//delay_ms(2000);
	//uint16_t v = 100;
	//dPotSetValue(1023);
	
	while(1){
		//char * doubleAsString = getDoubleAsString(dPotReadFromMem(0x00));
		//udi_hid_generic_send_report_in(doubleAsString);
		//free(doubleAsString);
		//delay_ms(200);
		//udi_hid_generic_send_report_in(getUIntAsString(data[1]));
		//v=(v+5)%1024;
		//delay_ms(200);
		
		//doubleAsString = getDoubleAsString(dPotReadFromMem(0x01));
		//udi_hid_generic_send_report_in(doubleAsString);
		//free(doubleAsString);
		LED_On(LED0);
		usbSendPVVVoltage();
		LED_Off(LED0);
		LED_On(LED1);
		usbSendPVCCurrent();
		LED_Off(LED1);
		LED_On(LED0);
		usbSendPVPower();
		LED_Off(LED0);
		LED_On(LED1);
		usbSendPVVoc();
		LED_Off(LED1);
		LED_On(LED0);
		usbSendPVIsc();
		LED_Off(LED0);
		
		delay_ms(2000);
	
	}
	
}
