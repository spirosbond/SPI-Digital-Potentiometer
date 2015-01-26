/*
 * utils.c
 *
 * Created: 16/10/2014 16:26:27
 *  Author: bontom38
 */ 


#include <stdio.h>
#include "utils.h"

uint8_t reverseByte( uint8_t x )
{
	x = ((x >> 1) & 0x55) | ((x << 1) & 0xaa);
	x = ((x >> 2) & 0x33) | ((x << 2) & 0xcc);
	x = ((x >> 4) & 0x0f) | ((x << 4) & 0xf0);
	return x;
}