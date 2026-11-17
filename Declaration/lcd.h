//lcd.h
#include "types.h"
void WriteLCD(u16 byte);
void CmdLCD(u16 cmd);
void InitLCD(void);
void CharLCD(u16 asciiVal);
void StrLCD(char *);
void U32LCD(u32);
void S32LCD(s32);
void F32LCD(f32,u16 nDP);
