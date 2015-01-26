/*
 * usbUtils.c
 *
 * Created: 19/12/2014 11:47:09
 *  Author: bontom38
 */ 

#include <stdio.h>
#include <string.h>
#include "usbUtils.h"
#include "fontUtils.h"
#include "DPot.h"
#include "measurements.h"

uint16_t getUIntFromReport(uint8_t *report){
	uint8_t numOfDigits = 0;
	int i;
	while(report[numOfDigits]!=0){
		numOfDigits++;
	}
	uint16_t value = 0, dec = 1;
	for(i=numOfDigits-1; i>=0; i--){
		value += getCharAsDigit(report[i]) * dec;
		dec*=10;
	}
	
	return value;
}

void my_callback_generic_report_out(uint8_t *report){
	char cmd = report[0];
	uint16_t v = getUIntFromReport(&report[1]);
	char * c = getIntAsString(v);
	char * res;
	char resp[64];
	memset(resp, 0, sizeof(cmd) * UDI_HID_REPORT_IN_SIZE);
	switch(cmd){
		case '1':
			//udi_hid_generic_send_report_in("Nominal Resistance set to: ");
			res = getDoubleAsString(dPotCalibrate());
			strcpy(resp, USB_CMD1_RESP);
			strcat(resp, res);
			udi_hid_generic_send_report_in((uint8_t*) resp); //Send report to host
			free(res);
			//dPotSetNomRes(v);
			break;
		case '2':
			//udi_hid_generic_send_report_in("Var Resistance set to: ");
			strcpy(resp, USB_CMD2_RESP);
			strcat(resp,c);
			udi_hid_generic_send_report_in((uint8_t*) resp); //Send report to host
			dPotSetRes(v);
			break;
		case '3':
			//udi_hid_generic_send_report_in("Var Resistance set to: ");
			strcpy(resp, USB_CMD3_RESP);
			strcat(resp,c);
			udi_hid_generic_send_report_in((uint8_t*) resp); //Send report to host
			dPotSetValue(v);
			break;
		case '4':
			res = getDoubleAsString(dPotReadRes());
			strcpy(resp, USB_CMD4_RESP);
			strcat(resp,res);
			udi_hid_generic_send_report_in((uint8_t*) resp); //Send report to host
			free(res);
			break;
		case '5':
			res = getIntAsString(dPotReadRDAC());
			strcpy(resp, USB_CMD5_RESP);
			strcat(resp,res);
			udi_hid_generic_send_report_in((uint8_t*) resp); //Send report to host
			free(res);
			break;
		case '6':
			res = getIntAsString(dPotReadFromMem(v));
			strcpy(resp, USB_CMD6_RESP);
			strcat(resp,res);
			udi_hid_generic_send_report_in((uint8_t*) resp); //Send report to host
			free(res);
			break;
		default:
			//udi_hid_generic_send_report_in("Unidentified Command: ");
			strcpy(resp,"Unidentified Command ");
			uint8_t cur_len = strlen(resp);
			resp[cur_len] = cmd;
			resp[cur_len + 1] = '\0';
			strcat(resp,": ");
			strcat(resp,c);
			udi_hid_generic_send_report_in((uint8_t*) resp); //Send report to host
			LED_On(LED0);
			break;
	}
	
	free(c);
	
	
}

void usbSendPVVVoltage(void){
	double pvVVV = getPVVVoltage();
	char resp[64];
	memset(resp, 0, sizeof(char) * UDI_HID_REPORT_IN_SIZE);
	char * res = getDoubleAsString(pvVVV);
	strcpy(resp,USB_PVVV_RESP);
	strcat(resp,res);
	udi_hid_generic_send_report_in((uint8_t*) resp);
	free(res);
	delay_ms(300);
}

void usbSendPVCCurrent(void){
	double pvCC = getPVCCurrent();
	char resp[64];
	memset(resp, 0, sizeof(char) * UDI_HID_REPORT_IN_SIZE);
	char * res = getDoubleAsString(pvCC);
	strcpy(resp,USB_PVCC_RESP);
	strcat(resp,res);
	udi_hid_generic_send_report_in((uint8_t*) resp);
	free(res);
	delay_ms(300);
}

void usbSendPVPower(void){
	double pvP = getPVPower();
	char resp[64];
	memset(resp, 0, sizeof(char) * UDI_HID_REPORT_IN_SIZE);
	char * res = getDoubleAsString(pvP);
	strcpy(resp,USB_PVP_RESP);
	strcat(resp,res);
	udi_hid_generic_send_report_in((uint8_t*) resp);
	free(res);
	delay_ms(300);
}

void usbSendPVVoc(void){
	double pvVoc = getPVVoc();
	char resp[64];
	memset(resp, 0, sizeof(char) * UDI_HID_REPORT_IN_SIZE);
	char * res = getDoubleAsString(pvVoc);
	strcpy(resp,USB_PVVOC_RESP);
	strcat(resp,res);
	udi_hid_generic_send_report_in((uint8_t*) resp);
	free(res);
	delay_ms(300);
}

void usbSendPVIsc(void){
	double pvIsc = getPVIsc();
	char resp[64];
	memset(resp, 0, sizeof(char) * UDI_HID_REPORT_IN_SIZE);
	char * res = getDoubleAsString(pvIsc);
	strcpy(resp,USB_PVISC_RESP);
	strcat(resp,res);
	udi_hid_generic_send_report_in((uint8_t*) resp);
	free(res);
	delay_ms(300);
}