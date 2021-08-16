#include "text.h"
#include "EFI_LIBS\Graphics.h"
#include "font.h"

PIXELPOSITIONS* pixelpos;

void GetCharacter(UINT32 character, UINT32 xPos, UINT32 yPos, UINT32 fs)
{
	pixelpos->PixelxPos = xPos;
	pixelpos->PixelyPos = yPos;
	UINT32 SelectASCII  = character;

	UINT32 mcX = pixelpos->PixelxPos;
	UINT32 mcY = pixelpos->PixelyPos;
	UINT32 pPos = 0;
	UINT32 sPos = 0;
	UINT32 FontSize = (UINT32)(fs / 4);

	for(UINT32 t = (SelectASCII * 128); t < ((SelectASCII * 128) + 128); t++)
	{
		if(pPos > 7)
		{
			pPos = 0;
			mcY += FontSize;
			mcX = pixelpos->PixelxPos;
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
				CreateFilledBox(mcX, mcY, FontSize, FontSize);
				break;
			}
		}
		mcX += FontSize;
		pPos++;
	}
}

void TestASCII(UINT32 sizeme)
{
	SetGraphicsColor(BLUE);
	
	CreateFilledBox(5, 5, (GetScreenWidth() - 15), (GetScreenHeight() - 15));
	
	SetGraphicsColor(GRAY);
		
	UINT32 tX = 8;
	UINT32 tY = 12;
	UINT32 fSize = sizeme;
	UINT32 fSize2 = sizeme;
	
	for(UINT32 k = 0; k < 256; k++)
    {
	    GetCharacter(k, tX, tY, fSize);
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
	
	for(UINT32 k = 0; k < 256; k++)
    {
	    GetCharacter(k, tX, tY, fSize2);
		tX += fSize2 + fSize2;
		if(tX > (GetScreenWidth() - ((10 + fSize2) + fSize2)))
		{
			tX = 10;
			tY += (fSize2 * 2) + (fSize2 * 2);
		}
	}
}