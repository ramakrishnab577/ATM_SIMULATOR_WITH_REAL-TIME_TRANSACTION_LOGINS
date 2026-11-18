// defines.h

// Set the specified bit to 1 without changing the other bits.
#define SETBIT(WORD,BITPOS) WORD |=1<<BITPOS

// Clear the specified bit to 0 without changing the other bits.
#define CLRBIT(WORD,BITPOS) WORD &=~(1<<BITPOS)

// Toggle the specified bit from 0 to 1 or from 1 to 0.
#define CPLBIT(WORD,BITPOS) WORD^= 1<<BITPOS

// Write the given bit value (0 or 1) at the specified bit position.
#define WRITEBIT(WORD,BITPOS,BIT) WORD=((WORD & ~(1<<BITPOS)) | (BIT<<BITPOS))

// Read the bit at the specified position and return its value (0 or 1).
#define READBIT(WORD,BITPOS) ((WORD>>BITPOS)&1)

// Copy a bit from the source position to the destination position within the same word.
#define READWRITEBIT(WORD,DBIT,SBIT) WORD=((WORD & ~(1<<DBIT))|(((WORD>>SBIT)&1)<<DBIT))

// Copy a bit from one word to a specified bit position in another word.
#define READWRITEBIT2(DWORD,DBIT,SWORD,SBIT) DWORD=((DWORD & ~(1<<DBIT))|(((SWORD>>SBIT)&1)<<DBIT))

// Write a 4-bit value (nibble) starting at the specified bit position.
#define WRITENIBBLE(WORD,STARTBIT,VAL) WORD=((WORD&~(15<<STARTBIT))|(VAL<<STARTBIT))

// Read 4 consecutive bits starting at the specified bit position.
#define READNIBBLE(WORD,STARTBIT) ((WORD>>STARTBIT)&15)

// Write an 8-bit value (byte) starting at the specified bit position.
#define WRITEBYTE(WORD,STARTBIT,VAL) WORD=((WORD & ~((u32)255<<STARTBIT))|((u32)VAL<<STARTBIT))

// Read 8 consecutive bits starting at the specified bit position.
#define READBYTE(WORD,STARTBIT) ((WORD>>START)&255)
