#pragma once

#include "common.h"

typedef struct CPOS
{
	UINT32 cmX;
	UINT32 cmY;
} CPOS;

void TextInit(void);

void GetCharacter(UINT32 character, UINT32 xPos, UINT32 yPos);

void SetFontSize(UINT32 fs);

void SetCursorPosition(UINT32 x, UINT32 y);

void SetFontSpacing(UINT32 fspacing);

void printf(unsigned char str[]);

void wprintf(UINT16 str[]);

void TestASCII(UINT32 sizeme);