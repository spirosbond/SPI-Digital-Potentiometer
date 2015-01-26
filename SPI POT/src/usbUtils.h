/*
 * usbUtils.h
 *
 * Created: 19/12/2014 11:47:20
 *  Author: bontom38
 */ 


#ifndef USBUTILS_H_
#define USBUTILS_H_

//USB response identifiers. The response of the USB is in the form $identifier$$value$, for example PVVV:0.565
#define USB_PVVV_RESP	"PVVV:"		// Identifier for PV Voltage
#define USB_PVCC_RESP	"PVCC:"		// Identifier for PV Current
#define USB_PVP_RESP	"PVP:"		// Identifier for PV Power
#define USB_PVVOC_RESP	"PVVOC:"	// Identifier for PV Voc
#define USB_PVISC_RESP	"PVISC:"	// Identifier for PV Isc

//USB command responses.
#define USB_CMD1_RESP	"Nominal Resistance set to: "
#define USB_CMD2_RESP	"Var Resistance set to: "
#define USB_CMD3_RESP	"Var Resistance Value set to: "
#define USB_CMD4_RESP	"RDAC Resistance is: "
#define USB_CMD5_RESP	"RDAC Value is: "
#define USB_CMD6_RESP	"Memory values is: "

/************************************************************************/
/*	This function transforms the USB incoming report byte array to an 
	unsigned integer.
	uint8_t *report: The pointer of the first byte of the report that 
	needs to be transformed to integer.
	return: An unsigned 2-Byte integer
                                                                        */
/************************************************************************/
uint16_t getUIntFromReport(uint8_t *report);

/************************************************************************/
/*	This function is called automatically when there is an incoming report
	to the USB interface. See /config/conf_usb.h for more information.
	The incoming commands are:
	1: Calibrate
	2: Set resistance value in Ohms
	3: Set resistance value with integer value (0-1023)
	4: Read resistance in Ohms
	5: Read resistance value in integer value (0-1023)
	6: Read a memory address
	The command is stored in the first byte of the incoming report.
                                                                        */
/************************************************************************/
void my_callback_generic_report_out(uint8_t *report);

/************************************************************************/
/*	This functions gets the Voltage of the input and sends it via USB
	with the following form: PVVV:$value$.
                                                                        */
/************************************************************************/
void usbSendPVVVoltage(void);

/************************************************************************/
/*	This functions gets the Current of the input and sends it via USB
	with the following form: PVCC:$value$.
                                                                        */
/************************************************************************/
void usbSendPVCCurrent(void);

/************************************************************************/
/*	This functions gets the Power of the input and sends it via USB
	with the following form: PVP:$value$.
                                                                        */
/************************************************************************/
void usbSendPVPower(void);

/************************************************************************/
/*	This functions gets the Voc of the input and sends it via USB
	with the following form: PVVOC:$value$.
                                                                        */
/************************************************************************/
void usbSendPVVoc(void);

/************************************************************************/
/*	This functions gets the Isc of the input and sends it via USB
	with the following form: PVISC:$value$.
                                                                        */
/************************************************************************/
void usbSendPVIsc(void);

#endif /* USBUTILS_H_ */