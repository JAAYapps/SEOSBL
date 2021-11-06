#include "text.h"
#include "Graphics.h"
#include "font.h"

PIXELPOSITIONS pixelpos __attribute__ ((section (".text"))) = {0};

void TextInit()
{
	SetCursorPosition(0, 0);
	SetFontSpacing(2);
	SetFontSize(8);
}

UINT32 CurrentFontSize __attribute__ ((section (".text"))) = {0};
void SetFontSize(UINT32 fs)
{
	if(fs < 4) { fs = 4; }
	CurrentFontSize = (UINT32)((fs / 4));
}

CPOS cursorPos __attribute__ ((section (".text"))) = {0};
void SetCursorPosition(UINT32 x, UINT32 y)
{
	cursorPos.cmX = x;
	cursorPos.cmY = y;
	if(cursorPos.cmX < 0){cursorPos.cmX = 0;}
	if(cursorPos.cmY < 0){cursorPos.cmY = 0;}
}

// Font / printf()
UINT32 FontSpacing __attribute__ ((section (".text"))) = {0};
void SetFontSpacing(UINT32 fspacing)
{
	if(fspacing < 0) { fspacing = 0; }
	FontSpacing = fspacing;
}

void GetCharacter(UINT32 character, UINT32 xPos, UINT32 yPos)
{
	pixelpos.PixelxPos = xPos;
	pixelpos.PixelyPos = yPos;
	UINT32 SelectASCII  = character;

	UINT32 mcX = pixelpos.PixelxPos;
	UINT32 mcY = pixelpos.PixelyPos;
	UINT32 pPos = 0;
	UINT32 sPos = 0;
	UINT32 FontSize = CurrentFontSize;

	for(UINT32 t = (SelectASCII * 128); t < ((SelectASCII * 128) + 128); t++)
	{
		if(pPos > 7)
		{
			pPos = 0;
			mcY += FontSize;
			mcX = pixelpos.PixelxPos;
			sPos++;
			if(sPos > 15)
			{
				sPos = 0;
				mcY += FontSize;
			}
		}
		UINT32 ASCIIColor = asciifont[t];
		switch(ASCIIColor)
		{
			case 0:
			{
				break;
			}
			case 1:
			{
				CreateBufferFilledBox(mcX, mcY, FontSize, FontSize);
				break;
			}
		}
		mcX += FontSize;
		pPos++;
	}
}

void wprintf(UINT16 str[])
{	
	for (UINT32 k = 0; str[k]; k++)
    {
		if(str[k] == 10)
		{
			cursorPos.cmY += 10 + ((CurrentFontSize * 5) + FontSpacing);
		} else if(str[k] == 13)
		{
			cursorPos.cmX = 0;
		} else {
			cursorPos.cmX += CurrentFontSize + CurrentFontSize;
			if(cursorPos.cmX > (GetScreenWidth() - ((10 + CurrentFontSize) + CurrentFontSize)))
			{
				cursorPos.cmX = 10;
				cursorPos.cmY += (CurrentFontSize * 2) + (CurrentFontSize * 2);
			}			
			GetCharacter(str[k], cursorPos.cmX, cursorPos.cmY);
		    cursorPos.cmX += ((CurrentFontSize * 7) + FontSpacing);
		}
	}

	// for (UINT32 j = 0; str[j]; j++)
	// {
	// 	if(str[j] == 10)
	// 	{
	// 		cursorPos.cmY += 10 + ((CurrentFontSize * 5) + FontSpacing);
	// 	} else if(str[j] == 13)
	// 	{
	// 		cursorPos.cmX = 0;
	// 	} else {
	// 		// UINT32 chr = 58;
	// 		GetCharacter(j, cursorPos.cmX, cursorPos.cmY, CurrentFontSize);
	// 	    cursorPos.cmX += ((CurrentFontSize * 7) + FontSpacing);
	// 	}
    // }
}

void printf(unsigned char str[])
{	
	for (UINT32 k = 0; str[k]; k++)
    {
		if(str[k] == 10)
		{
			cursorPos.cmY += 10 + ((CurrentFontSize * 5) + FontSpacing);
		} else if(str[k] == 13)
		{
			cursorPos.cmX = 0;
		} else {
			cursorPos.cmX += CurrentFontSize + CurrentFontSize;
			if(cursorPos.cmX > (GetScreenWidth() - ((10 + CurrentFontSize) + CurrentFontSize)))
			{
				cursorPos.cmX = 10;
				cursorPos.cmY += (CurrentFontSize * 2) + (CurrentFontSize * 2);
			}			
			GetCharacter(str[k], cursorPos.cmX, cursorPos.cmY);
		    cursorPos.cmX += ((CurrentFontSize * 7) + FontSpacing);
		}
	}
}

void TestASCII(UINT32 sizeme)
{
	SetGraphicsColor(BLUE);
	
	CreateBufferFilledBox(5, 5, (GetScreenWidth() - 15), (GetScreenHeight() - 15));
	
	SetGraphicsColor(GRAY);
		
	UINT32 tX = 8;
	UINT32 tY = 12;
	UINT32 fSize = sizeme;
	UINT32 fSize2 = sizeme;
	
	SetFontSize(fSize);

	for(UINT32 k = 0; k < 256; k++)
    {
	    GetCharacter(k, tX, tY);
		tX += fSize + fSize;
		if(tX > (GetScreenWidth() - ((10 + fSize) + fSize)))
		{
			tX = 10;
			tY += (fSize * 2) + (fSize * 2);
		}
	}
	
	SetGraphicsColor(WHITE);
		
	tX = 10;
	tY = 10;
	
	SetFontSize(fSize2);

	for(UINT32 k = 0; k < 256; k++)
    {
	    GetCharacter(k, tX, tY);
		tX += fSize2 + fSize2;
		if(tX > (GetScreenWidth() - ((10 + fSize2) + fSize2)))
		{
			tX = 10;
			tY += (fSize2 * 2) + (fSize2 * 2);
		}
	}
}