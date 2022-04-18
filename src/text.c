#include "../includes/text.h"
#include "../includes/Graphics.h"

PIXELPOSITIONS pixelpos __attribute__((section(".text"))) = {0};
CPOS cursorPos __attribute__((section(".text"))) = {0};
UINT32 FontSpacing __attribute__((section(".text"))) = {0};
BLOCKINFO *bInfo __attribute__((section(".text"))) = {0};

void TextInit(BLOCKINFO *block, unsigned int (*GetEntryPoint)(UINT8 *))
{
	if (block->fontInfo.FONT_DRIVER != NULL)
	{
		unsigned int entry = GetEntryPoint(block->fontInfo.FONT_DRIVER);
		if (entry != 0)
		{
			UINT8 *loadedDriver = &block->fontInfo.FONT_DRIVER[entry];
			UINT8(*driver)
			(BLOCKINFO *) = ((__attribute__((ms_abi)) UINT8(*)(BLOCKINFO *))((UINT64)loadedDriver));
			driver(block);
			bInfo = block;
			SetCursorPosition(5, 5);
			SetFontSpacing(2);
			bInfo->fontInfo.SetFontSize(4);
		}
	}
	else
	{
		bInfo = block;
		SetCursorPosition(5, 5);
		SetFontSpacing(2);
		bInfo->fontInfo.SetFontSize(8);
	}
}

void SetCursorPosition(UINT32 x, UINT32 y)
{
	if (x < 0)
		cursorPos.cmX = 5 + FontSpacing;
	else
		cursorPos.cmX = 5 + FontSpacing + (x * ((bInfo->fontInfo.GetFontSize() * bInfo->fontInfo.GetLineSize()) + FontSpacing));
	if (y < 0)
		cursorPos.cmY = 5;
	else
		cursorPos.cmY = 5 + (y * bInfo->fontInfo.GetFontSize() * bInfo->fontInfo.GetMaxLines());
}

void SetFontSpacing(UINT32 fspacing)
{
	FontSpacing = fspacing;
}

void GetCharacter(UINT32 character, UINT32 xPos, UINT32 yPos)
{
	pixelpos.PixelxPos = xPos;
	pixelpos.PixelyPos = yPos;
	UINT32 SelectASCII = character;

	UINT32 mcX = pixelpos.PixelxPos;
	UINT32 mcY = pixelpos.PixelyPos;
	UINT32 pPos = 0;
	UINT32 sPos = 0;
	UINT32 FontScalerSize = bInfo->fontInfo.GetFontSize();

	for (UINT32 t = (SelectASCII * bInfo->fontInfo.GetCharSize()); t < ((SelectASCII * bInfo->fontInfo.GetCharSize()) + bInfo->fontInfo.GetCharSize()); t++)
	{
		if (pPos > bInfo->fontInfo.GetLineSize() - 1)
		{
			pPos = 0;
			mcY += FontScalerSize;
			mcX = pixelpos.PixelxPos;
			sPos++;
			if (sPos > bInfo->fontInfo.GetMaxLines() - 1)
			{
				sPos = 0;
				mcY += FontScalerSize;
			}
		}

		switch (bInfo->fontInfo.GetFontPixel(SelectASCII, sPos, pPos))
		{
		case 0:
		{
			break;
		}
		case 1:
		{
			CreateBufferFilledBox(mcX, mcY, FontScalerSize, FontScalerSize);
			break;
		}
		}
		mcX += FontScalerSize;
		pPos++;
	}
}

void wprintf(const short str[])
{
	for (UINT32 k = 0; str[k]; k++)
	{
		if (str[k] == '\n')
		{
			cursorPos.cmY += (bInfo->fontInfo.GetFontSize() * bInfo->fontInfo.GetMaxLines());
		}
		else if (str[k] == '\r')
		{
			cursorPos.cmX = 5 + FontSpacing;
		}
		else
		{
			GetCharacter(str[k], cursorPos.cmX, cursorPos.cmY);
			cursorPos.cmX += ((bInfo->fontInfo.GetFontSize() * bInfo->fontInfo.GetLineSize()) + FontSpacing);
			if (cursorPos.cmX > (GetScreenWidth() - ((10 + bInfo->fontInfo.GetFontSize()) + bInfo->fontInfo.GetFontSize())))
			{
				cursorPos.cmX = 5 + FontSpacing;
				cursorPos.cmY += (bInfo->fontInfo.GetFontSize() * bInfo->fontInfo.GetMaxLines());
			}
		}
	}
}

void printf(const char str[])
{
	for (UINT32 k = 0; str[k]; k++)
	{
		if (str[k] == '\n')
		{
			cursorPos.cmY += (bInfo->fontInfo.GetFontSize() * bInfo->fontInfo.GetMaxLines());
		}
		else if (str[k] == '\r')
		{
			cursorPos.cmX = 5 + FontSpacing;
		}
		else
		{
			GetCharacter(str[k], cursorPos.cmX, cursorPos.cmY);
			cursorPos.cmX += ((bInfo->fontInfo.GetFontSize() * bInfo->fontInfo.GetLineSize()) + FontSpacing);
			if (cursorPos.cmX > (GetScreenWidth() - ((10 + bInfo->fontInfo.GetFontSize()) + bInfo->fontInfo.GetFontSize())))
			{
				cursorPos.cmX = 5 + FontSpacing;
				cursorPos.cmY += (bInfo->fontInfo.GetFontSize() * bInfo->fontInfo.GetMaxLines());
			}
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

	bInfo->fontInfo.SetFontSize(fSize);

	for (UINT32 k = 0; k < 256; k++)
	{
		GetCharacter(k, tX, tY);
		tX += fSize + fSize;
		if (tX > (GetScreenWidth() - ((10 + fSize) + fSize)))
		{
			tX = 10;
			tY += (fSize * 2) + (fSize * 2);
		}
	}

	SetGraphicsColor(WHITE);

	tX = 10;
	tY = 10;

	bInfo->fontInfo.SetFontSize(fSize2);

	for (UINT32 k = 0; k < 256; k++)
	{
		GetCharacter(k, tX, tY);
		tX += fSize2 + fSize2;
		if (tX > (GetScreenWidth() - ((10 + fSize2) + fSize2)))
		{
			tX = 10;
			tY += (fSize2 * 2) + (fSize2 * 2);
		}
	}
}