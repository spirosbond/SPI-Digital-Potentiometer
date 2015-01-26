/*
 * RegisterUtils.h
 *
 * Created: 03/09/2014 17:43:14
 *  Author: bontom38
 */ 


#ifndef REGISTERUTILS_H_
#define REGISTERUTILS_H_

#define BIT(Position)          (1 << (Position))
#define SETBITS(Register,Word)    ((Register) |= (Word))
#define CLEARBITS(Register,Word)    ((Register) &= (~(Word)))
#define SETBIT(Register,Position)    SETBITS((Register), (BIT((Position))))
#define CLEARBIT(Register,Position)    CLEARBITS((Register), (BIT((Position))))
#define BITSET(Word,Position)    ((Word) & (BIT(Position)))
#define BITCLEAR(Word,Position)    !BITSET((Word), (Position))
#define BITSSET(Word1,Word2)    (((Word1) & (Word2)) == (Word2))
#define BITSCLEAR(Word1,Word2)    (((Word2) & (Word2)) == 0)
#define BITVAL(Word,Position)    (((Word)>>(Position)) & 1)
#define TOGGLEBIT(Register,Position) Register ^= _BV(Position) //toggle bit - using bitwise XOR operator



#endif /* REGISTERUTILS_H_ */