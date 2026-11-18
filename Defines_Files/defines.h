//defines .h
// Give a readable name to a fixed value or setting.
#define SETBIT(WORD,BITPOS) WORD |=1<<BITPOS

// Give a readable name to a fixed value or setting.
#define CLRBIT(WORD,BITPOS) WORD &=~(1<<BITPOS)

// Give a readable name to a fixed value or setting.
#define CPLBIT(WORD,BITPOS) WORD^= 1<<BITPOS

// Give a readable name to a fixed value or setting.
#define WRITEBIT(WORD,BITPOS,BIT) WORD=((WORD & ~(1<<BITPOS)) | (BIT<<BITPOS))

// Give a readable name to a fixed value or setting.
#define READBIT(WORD,BITPOS) ((WORD>>BITPOS)&1)

// Give a readable name to a fixed value or setting.
#define READWRITEBIT(WORD,DBIT,SBIT) WORD=((WORD & ~(1<<DBIT))|(((WORD>>SBIT)&1)<<DBIT))

// Give a readable name to a fixed value or setting.
#define READWRITEBIT2(DWORD,DBIT,SWORD,SBIT) DWORD=((DWORD & ~(1<<DBIT))|(((SWORD>>SBIT)&1)<<DBIT))

// Give a readable name to a fixed value or setting.
#define WRITENIBBLE(WORD,STARTBIT,VAL) WORD=((WORD&~(15<<STARTBIT))|(VAL<<STARTBIT))

// Give a readable name to a fixed value or setting.
#define READNIBBLE(WORD,STARTBIT) ((WORD>>STARTBIT)&15)

// Give a readable name to a fixed value or setting.
#define WRITEBYTE(WORD,STARTBIT,VAL) WORD=((WORD & ~((u32)255<<STARTBIT))|((u32)VAL<<STARTBIT))

// Give a readable name to a fixed value or setting.
#define READBYTE(WORD,STARTBIT) ((WORD>>START)&255)

