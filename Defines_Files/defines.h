// defines.h

// Set the specified bit position to 1 without affecting other bits.
#define SETBIT(WORD,BITPOS) WORD |= 1<<BITPOS

// Clear the specified bit position to 0 without affecting other bits.
#define CLRBIT(WORD,BITPOS) WORD &= ~(1<<BITPOS)

// Toggle the specified bit (0 to 1 or 1 to 0).
#define CPLBIT(WORD,BITPOS) WORD ^= 1<<BITPOS

// Write the given bit value (0 or 1) at the specified bit position.
#define WRITEBIT(WORD,BITPOS,BIT) WORD = ((WORD & ~(1<<BITPOS)) | (BIT<<BITPOS))

// Read the bit value (0 or 1) from the specified bit position.
#define READBIT(WORD,BITPOS) ((WORD>>BITPOS)&1)

// Copy a bit from the source bit position to the destination bit position within the same word.
#define READWRITEBIT(WORD,DBIT,SBIT) WORD = ((WORD & ~(1<<DBIT)) | (((WORD>>SBIT)&1)<<DBIT))

// Copy a bit from the source word to the specified bit position in the destination word.
#define READWRITEBIT2(DWORD,DBIT,SWORD,SBIT) DWORD = ((DWORD & ~(1<<DBIT)) | (((SWORD>>SBIT)&1)<<DBIT))

// Write a 4-bit value (nibble) starting at the specified bit position.
#define WRITENIBBLE(WORD,STARTBIT,VAL) WORD = ((WORD & ~(15<<STARTBIT)) | (VAL<<STARTBIT))

// Read a 4-bit value (nibble) starting at the specified bit position.
#define READNIBBLE(WORD,STARTBIT) ((WORD>>STARTBIT)&15)

// Write an 8-bit value (byte) starting at the specified bit position.
#define WRITEBYTE(WORD,STARTBIT,VAL) WORD = ((WORD & ~((u32)255<<STARTBIT)) | ((u32)VAL<<STARTBIT))

// Read an 8-bit value (byte) starting at the specified bit position.
#define READBYTE(WORD,STARTBIT) ((WORD>>STARTBIT)&255)
