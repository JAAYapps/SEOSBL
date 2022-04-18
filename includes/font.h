#ifndef FONT_H
#define FONT_H

#include "SEOSBLcommon.h"

UINT8 font_main(BLOCKINFO *bi);

UINT8 GetFontPixel(unsigned short chr, unsigned int line, unsigned int pIndex);

void SetFontSize(UINT32 size);

UINT32 GetFontSize(void);

UINT32 GetCharSize(void);

UINT32 GetLineSize(void);

UINT32 GetMaxLines(void);

#endif
