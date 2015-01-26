/*
 * adc.h
 *
 * Created: 22/10/2014 16:00:54 μμ
 *  Author: SPIROS
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <adc.h>

// ADC selection and input pins
#define MY_ADC			ADCA
//#define ADC_PIN_BAT		ADCCH_POS_PIN14
#define ADC_PIN_PVV		ADCCH_POS_PIN12	//PB4 for voltage
#define ADC_PIN_PVC		ADCCH_POS_PIN13	//PB5 for current

// ADC configuration
#define ADC_FREQ			16000	//Frequency
#define ADC_GAIN			1		//Gain
#define ADC_RESULT_MAX		2047.0	//Maximum result 2^11
#define ADC_REF_VOLTAGE		1.0		//Reference voltage
#define ADC_DEFAULT_OSMPL	128.0	//Default oversampling
#define ADC_LOW_OSMPL		32.0	//Low oversampling
#define ADC_HIGH_OSMPL		256.0	//High oversampling

#define ADC_PVVOC_CTRL	IOPORT_CREATE_PIN(PORTF, PIN1_bp) //PIN F1 used to Open Circuit the cell to measure Voc
#define ADC_PVISC_CTRL	IOPORT_CREATE_PIN(PORTF, PIN0_bp) //PIN F0 used to Short Circuit the cell to measure Isc

//ADC Ratios to compute the real values
//#define ADC_BAT_RATIO	(402.0 + 100.0) / 100.0
#define ADC_PVV_RATIO	(402.0 + 200.0) / 200.0
#define ADC_PVC_RATIO	255 / 20.5
#define ADC_PVC_RSENSE	10.0

extern struct adc_config adc_conf;				//ADC configuration
extern struct adc_channel_config adcch_conf;	//ADC channel configuration

/************************************************************************/
/*	Initialize the ADC with the configuration specified above and enable
	it.
                                                                        */
/************************************************************************/
void adc_init(void);

/************************************************************************/
/*	Returns the calibration data of ADCA. Never worked for me though... :(
                                                                        */
/************************************************************************/
uint16_t getCalibrationData(void);

/************************************************************************/
/*	Read the ADC value of a pin. The first ADC result is thrown away
	since it's considered noisy.
	uint8_t adc_pin: The ADC pin to get the measurement
	from (ADC_PIN_PVV,ADC_PIN_PVC)
	double oversampling: The oversampling to be performed
	return: A double between [-2047,2047]
                                                                        */
/************************************************************************/
double getADCValue(uint8_t adc_pin, double oversampling);

/************************************************************************/
/*	Read the ADC voltage of a pin using the getADCValue()
	uint8_t adc_pin: The ADC pin to get the measurement
	from (ADC_PIN_PVV,ADC_PIN_PVC)
	double oversampling: The oversampling to be performed
	return: A double between [-1,1]
                                                                        */
/************************************************************************/
double getADCVoltage(uint8_t adc_pin, double oversampling);

/************************************************************************/
/*	Read the ADC value of the Battery voltage pin using the getADCValue()
	return: A double between [-2047,2047]
                                                                        */
/************************************************************************/
//double getBatteryADCValue(void);

/************************************************************************/
/*	Read the ADC value of the Voltage pin using the getADCValue()
	return: A double between [-2047,2047]
                                                                        */
/************************************************************************/
double getPVVADCValue(void);

/************************************************************************/
/*	Read the ADC value of the Current pin using the getADCValue()
	return: A double between [-2047,2047]
                                                                        */
/************************************************************************/
double getPVCADCValue(void);

/************************************************************************/
/*	Read the ADC Voltage of the Battery pin using the getBatteryADCValue()
	return: A double between [-1,1]
                                                                        */
/************************************************************************/
//double getBatteryADCVoltage(void);

/************************************************************************/
/*	Read the ADC Voltage of the Voltage pin using the getPVVADCValue()
	return: A double between [-1,1]
                                                                        */
/************************************************************************/
double getPVVADCVoltage(void);

/************************************************************************/
/*	Read the ADC Voltage of the Current pin using the getPVCADCValue()
	return: A double between [-1,1]
                                                                        */
/************************************************************************/
double getPVCADCVoltage(void);

/************************************************************************/
/*	Read the Real Voltage of the Battery pin using the
	getBatteryADCVoltage()
	return: A double between [-ADC_PVV_RATIO,ADC_PVV_RATIO]
                                                                        */
/************************************************************************/
//double getBatteryVoltage(void);

/************************************************************************/
/*	Read the Real Voltage of the Voltage pin using the getPVVADCVoltage()
	return: A double between [-ADC_PVV_RATIO,ADC_PVV_RATIO]
                                                                        */
/************************************************************************/
double getPVVVoltage(void);

/************************************************************************/
/*	Read the Real Voltage of the Current pin using the getPVVADCVoltage().
	Implemented for compatibility reasons because it is exactly like
	getPVCADCVoltage() since the LT6105 is configured to give voltage
	from [-1,1].
	return: A double between [-ADC_PVV_RATIO,ADC_PVV_RATIO]
                                                                        */
/************************************************************************/
double getPVCVoltage(void);

/************************************************************************/
/*	Read the Real Current of the Current pin using the getPVCADCVoltage()
	return: A double between
	[-(ADC_PVC_RATIO/ADC_PVC_RSENSE),(ADC_PVC_RATIO/ADC_PVC_RSENSE)].
	In reality the current can only flow in one direction so the real
	range is [0,(ADC_PVC_RATIO/ADC_PVC_RSENSE)].
                                                                        */
/************************************************************************/
double getPVCCurrent(void);

/************************************************************************/
/*	Read the Power of the input using the getPVVVoltage()
	and getPVCCurrent().
	return: A double representing the power generated at this moment.
                                                                        */
/************************************************************************/
double getPVPower(void);

/************************************************************************/
/*	Read the Voc the input using the getPVVVoltage() and opening 
	transistor at ADC_PVVOC_CTRL.
	return: A double representing the Voc.
                                                                        */
/************************************************************************/
double getPVVoc(void);

/************************************************************************/
/*	Read the Isc the input using the getPVCCurrent() and opening 
	transistor at ADC_PVVOC_CTRL while closing transistor at
	ADC_PVISC_CTRL.
	return: A double representing the Isc.
                                                                        */
/************************************************************************/
double getPVIsc(void);

#endif /* ADC_H_ */