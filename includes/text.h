#ifndef TEXT_H
#define TEXT_H

#include "..\Common-Code-For-C-Projects\common.h"

typedef struct CPOS
{
	UINT32 cmX;
	UINT32 cmY;
} CPOS;

void TextInit(BLOCKINFO *bi, unsigned int (*GetDriverEntryPoint)(UINT8 *));

void GetCharacter(UINT32 character, UINT32 xPos, UINT32 yPos);

void SetCursorPosition(UINT32 x, UINT32 y);

void SetFontSpacing(UINT32 fspacing);

void printf(const char str[]);

void wprintf(const short str[]);

void TestASCII(UINT32 sizeme);

#endif
