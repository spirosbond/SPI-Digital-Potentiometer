/*
 * fontUtils.h
 *
 * Created: 26/11/2014 15:16:21
 *  Author: bontom38
 */ 


#ifndef FONTUTILS_H_
#define FONTUTILS_H_

/**
*   Get a digit as a normal character
*   uint8_t n: Digit to be translated to character
*/
char getDigitAsChar(uint8_t n);

/**
*   Returns the unsigned integer as string
*   uint8_t num: Number to be translated to string
*/
char * getIntAsString(int num);

/**
*   Returns the double as string
*   uint8_t num: Number to be translated to string
*/
char * getDoubleAsString(double num);

/**
*   Returns an ASCII number of a character as a character
*   uint8_t num: ASCII Number to be translated to character
*/
char getASCIIAsChar(uint8_t num);

/**
*   Returns a character representation of a digit as a digit
*   char c: Character of a digit
*/
uint8_t getCharAsDigit(char c);



#endif /* FONTUTILS_H_ */