/*
 * fontUtils.c
 *
 * Created: 26/11/2014 15:14:59
 *  Author: bontom38
 */ 

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "fontUtils.h"

char getDigitAsChar(uint8_t n){
	
	switch(n){
		case 0:
		return '0';
		break;
		case 1:
		return '1';
		break;
		case 2:
		return '2';
		break;
		case 3:
		return '3';
		break;
		case 4:
		return '4';
		break;
		case 5:
		return '5';
		break;
		case 6:
		return '6';
		break;
		case 7:
		return '7';
		break;
		case 8:
		return '8';
		break;
		case 9:
		return '9';
		break;
		default:
		return '0';
	}
	
}

uint8_t getCharAsDigit(char c){
	
	switch(c){
		case '0':
		return 0;
		break;
		case '1':
		return 1;
		break;
		case '2':
		return 2;
		break;
		case '3':
		return 3;
		break;
		case '4':
		return 4;
		break;
		case '5':
		return 5;
		break;
		case '6':
		return 6;
		break;
		case '7':
		return 7;
		break;
		case '8':
		return 8;
		break;
		case '9':
		return 9;
		break;
		default:
		return -1;
	}
	
}

char * getIntAsString(int num){
	/*char * charArrayZero = calloc(2, sizeof(char));
	//char charArrayZero[2];
	if(num==0){
		charArrayZero[0] = '0';
		charArrayZero[1] = '\0';
		return charArrayZero;
	}
	free(charArrayZero);
	uint8_t n = log10(num) + 1;
	int16_t i;
	char *charArray = calloc(n+1, sizeof(char));
	//char charArray[n+1];
	for (i=n-1; i>=0; i--, num /= 10){
		
		charArray[i] = getDigitAsChar(num % 10);

	}
	charArray[n] = '\0';
	
	char charArray[100];
	sprintf(charArray,"%u",num);
	*/
	char *charArray = calloc(64,sizeof(char)); //TODO Use charArray[64] and then memset(charArray, 0, sizeof(charArray[0]) * 64) to clear it so no need to free
	sprintf(charArray,"%d",num);
	
	return charArray;
}

char * getDoubleAsString(double num){
	/*char * charArrayZero = calloc(2, sizeof(char));
	if(num == 0){
		charArrayZero[0] = '0';
		charArrayZero[1] = '\0';
		return charArrayZero;
	}
	
	uint8_t n = log10(num) + 1;
	int16_t i;
	char *charArray = calloc(n+3+1+1, sizeof(char)); //decimal point + 3 floating point resolution + . + \0
	uint64_t numD = num;
	float numF = (num - numD)*10;
	
	for (i=n-1; i>=0; i--, numD /=10){
		
		charArray[i] = getDigitAsChar(numD % 10);
		
	}
	
	charArray[n] = '.';
	
	for(i=n+1; i<n+4; i++, numF *= 10){
		charArray[i] = getDigitAsChar((uint8_t) numF);
	}
	
	charArray[n+4] = '\0';*/
	//uint8_t n = log10(num) + 1;
	//char *charArray = calloc(n+3+1+1+1, sizeof(char)); //decimal point + 3 floating point resolution + . + \0 + minus (-) in case
	
	char *charArray = calloc(64,sizeof(char)); //TODO Use charArray[64] and then memset(charArray, 0, sizeof(charArray[0]) * 64) to clear it so no need to free
	sprintf(charArray,"%g",num);
	
	return charArray;
}

char getASCIIAsChar(uint8_t num){
	char c;
	sprintf(&c,"%c",num);
	return c;
}
