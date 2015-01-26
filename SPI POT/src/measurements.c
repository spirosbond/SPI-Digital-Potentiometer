/*
 * adc.c
 *
 * Created: 22/10/2014 15:54:32 μμ
 *  Author: SPIROS
 */ 

#include <asf.h>
#include <stdio.h>
#include <stdlib.h>
#include <adc.h>
#include <avr/pgmspace.h>
#include <stddef.h>
#include "measurements.h"

struct adc_config adc_conf;
struct adc_channel_config adcch_conf;
double pvvADCValue = 0, pvcADCValue = 0;
uint8_t ADC_PIN = ADC_PIN_PVV;

static void adc_handler(ADC_t *adc, uint8_t ch_mask, adc_result_t result)
{
	
	/*switch(multiplexer){
		case ADCCH_POS_PIN4:
			multiplexer = ADCCH_POS_PIN5;
			ADC_RESULT_4 = result;
			
			break;
		case ADCCH_POS_PIN5:
			multiplexer = ADCCH_POS_PIN4;
			ADC_RESULT_5 = result;
			
			break;
	}
	adcch_set_input(&adcch_conf,  multiplexer, ADCCH_NEG_PIN3, 1);
	adcch_write_configuration(&MY_ADC, ADC_CH0, &adcch_conf);
	
	ADC_RESULT_4 = result;
	*/
	
	/*if(ADC_PIN == ADC_PIN_PVV){
		batteryADCValue = result;
		ADC_PIN = ADC_PIN_PVC;
		adcch_set_input(&adcch_conf,ADC_PIN,ADCCH_NEG_NONE, ADC_GAIN);
		adcch_write_configuration(&MY_ADC, ADC_CH0, &adcch_conf);
	}else if (ADC_PIN == ADC_PIN_PVC){
		pvvADCValue = result;
		ADC_PIN = ADC_PIN_BAT;
		adcch_set_input(&adcch_conf,ADC_PIN,ADCCH_NEG_NONE, ADC_GAIN);
		adcch_write_configuration(&MY_ADC, ADC_CH0, &adcch_conf);
	} else if (ADC_PIN == ADC_PIN_BAT){
		pvcADCValue = result;
		ADC_PIN = ADC_PIN_PVV;
		adcch_set_input(&adcch_conf,ADC_PIN,ADCCH_NEG_NONE, ADC_GAIN);
		adcch_write_configuration(&MY_ADC, ADC_CH0, &adcch_conf);
	}
	//if (ch_mask==1)	{
		//batteryADCValue = result;
	//}
	*/
	
}

void adc_init(void){
	
	ioport_set_pin_dir(IOPORT_CREATE_PIN(PORTB, 4), IOPORT_DIR_INPUT);
	//ioport_set_pin_mode(IOPORT_CREATE_PIN(PORTB, 4), IOPORT_MODE_PULLUP);
	ioport_set_pin_dir(IOPORT_CREATE_PIN(PORTB, 5), IOPORT_DIR_INPUT);
	//ioport_set_pin_mode(IOPORT_CREATE_PIN(PORTB, 5), IOPORT_MODE_PULLUP);
	
	adc_read_configuration(&MY_ADC, &adc_conf);
	adcch_read_configuration(&MY_ADC, ADC_CH0, &adcch_conf);
	adc_set_conversion_parameters(&adc_conf, ADC_SIGN_ON, ADC_RES_12, ADC_REFSEL_INT1V_gc);
	adc_set_conversion_trigger(&adc_conf, ADC_TRIG_MANUAL, 1, 0);
	//adc_set_conversion_trigger(&adc_conf, ADC_TRIG_FREERUN, 1, 0);
	adc_set_clock_rate(&adc_conf, ADC_FREQ);
	//adc_enable_internal_input(&adc_conf, ADC_INT_BANDGAP);
	adc_set_callback(&MY_ADC, &adc_handler);
	adcch_enable_interrupt(&adcch_conf);
	adc_set_current_limit(&adc_conf,ADC_CURRENT_LIMIT_HIGH);
	//adcch_set_input(&adcch_conf, ADC_PIN_PVV, ADCCH_NEG_NONE, ADC_GAIN);
	//adcch_enable_oversampling(&adcch_conf,ADC_SAMPNUM_1024X,16);
	//adcch_set_input(&adcch_conf, ADCCH_POS_PIN9, ADCCH_NEG_NONE, 1);
	//adcch_set_pin_scan(&adcch_conf, ADC_PIN_PVV, ADC_PIN_PVV);
	adc_write_configuration(&MY_ADC, &adc_conf);
	adcch_write_configuration(&MY_ADC, ADC_CH0, &adcch_conf);
	
	adc_enable(&MY_ADC);
	
	ioport_configure_port_pin(&PORTF, PIN0_bm, IOPORT_INIT_LOW | IOPORT_DIR_OUTPUT);	// Close transistor of Voc
	ioport_configure_port_pin(&PORTF, PIN1_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);	// Open transistor of Jsc
}

double getADCVoltage(uint8_t adc_pin, double oversampling){
	
	return getADCValue(adc_pin, oversampling)*ADC_REF_VOLTAGE/(ADC_RESULT_MAX);
	
}

uint16_t getCalibrationData(void){
	return adc_get_calibration_data(ADC_CAL_ADCA);
}

double getADCValue(uint8_t adc_pin, double oversampling){
	uint16_t i;
	double result = 0.0;
	int16_t ADCValue = 0;
	
	adcch_read_configuration(&MY_ADC, ADC_CH0, &adcch_conf);
	adcch_set_input(&adcch_conf, adc_pin, ADCCH_NEG_NONE, ADC_GAIN);
	adcch_write_configuration(&MY_ADC, ADC_CH0, &adcch_conf);
	
	
	
	sleep_set_mode(SLEEP_SMODE_IDLE_gc);
	sleep_enable();
	adc_start_conversion(&MY_ADC, ADC_CH0);
	sleep_enter();
	sleep_disable();
	
	//adc_start_conversion(&MY_ADC, ADC_CH0);
	//adc_wait_for_interrupt_flag(&MY_ADC, ADC_CH0);
	
	for(i=0; i<oversampling; i++){
		sleep_set_mode(SLEEP_SMODE_IDLE_gc);
		sleep_enable();
		adc_start_conversion(&MY_ADC, ADC_CH0);
		sleep_enter();
		sleep_disable();
		//adc_start_conversion(&MY_ADC, ADC_CH0);
		//adc_wait_for_interrupt_flag(&MY_ADC, ADC_CH0);
		ADCValue = adc_get_result(&MY_ADC, ADC_CH0); //Has to be done in two steps, to keep the minus (-) sign.
		result += ADCValue/oversampling;
	}
	
	//adc_disable(&MY_ADC);
	return result;
}

/*double getBatteryADCValue(void){
	//gpio_set_pin_high(ADC_BAT_CTRL);
	//delay_ms(50);
	double v = getADCValue(ADC_PIN_BAT, ADC_DEFAULT_OSMPL);
	//gpio_set_pin_low(ADC_BAT_CTRL);
	return v;
	//return batteryADCValue;
	
}*/

double getPVVADCValue(void){
	//gpio_set_pin_high(ADC_PVV_CTRL);
	//delay_ms(50);
	double v = getADCValue(ADC_PIN_PVV, ADC_HIGH_OSMPL);
	//gpio_set_pin_low(ADC_PVV_CTRL);
	return v;
	//return pvvADCValue;
	
}

double getPVCADCValue(void){
	return getADCValue(ADC_PIN_PVC, ADC_HIGH_OSMPL);
	//return pvcADCValue;
}

/*double getBatteryADCVoltage(void){
	return getBatteryADCValue()*ADC_REF_VOLTAGE/(ADC_RESULT_MAX);
}*/

double getPVVADCVoltage(void){
	return getPVVADCValue()*ADC_REF_VOLTAGE/(ADC_RESULT_MAX);
}

double getPVCADCVoltage(void){
	return getPVCADCValue()*ADC_REF_VOLTAGE/(ADC_RESULT_MAX);
}

/*double getBatteryVoltage(void){
	return getBatteryADCVoltage()*ADC_BAT_RATIO;
}*/

double getPVVVoltage(void){
	return getPVVADCVoltage()*ADC_PVV_RATIO;
}

double getPVCVoltage(void){
	return getPVCADCVoltage();
}

double getPVCCurrent(void){
	return (getPVCADCVoltage() * ADC_PVC_RATIO) / ADC_PVC_RSENSE;
}

double getPVPower(void){
	double voltage = getPVVVoltage();
	double current = getPVCCurrent();
	return voltage*current;
}

double getPVVoc(void){
	gpio_set_pin_low(ADC_PVVOC_CTRL);
	gpio_set_pin_low(ADC_PVISC_CTRL);
	delay_ms(100);
	double pVVoc = getPVVVoltage();
	gpio_set_pin_high(ADC_PVVOC_CTRL);
	delay_ms(100);
	return pVVoc;
}

double getPVIsc(void){
	gpio_set_pin_low(ADC_PVVOC_CTRL);
	gpio_set_pin_high(ADC_PVISC_CTRL);
	delay_ms(100);
	double pVIsc = getPVCCurrent();
	gpio_set_pin_low(ADC_PVISC_CTRL);
	gpio_set_pin_high(ADC_PVVOC_CTRL);
	delay_ms(100);
	return pVIsc;
}