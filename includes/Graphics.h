#ifndef GRAPHICS_H
#define GRAPHICS_H

//#define GRAPHICS_INCLUDE

#include "SEOSBLcommon.h"

// A R G B
#define ORANGE 0xffffa500
#define CYAN 0xff00ffff
#define RED 0xffff0000
#define YELLOW 0xffffff00
#define GREEN 0xff00ff00
#define BLUE 0xff0000ff
#define GRAY 0xff888888
#define DARKGRAY 0xff111111
#define EXTREMEGRAY 0xff0a0a0a
#define WHITE 0xffffffff
#define BLACK 0xff000000
#define BADCYAN 0xff00aaaa
#define BADORANGE 0xff5a1100

typedef struct COLOR
{
    UINT8 Blue;
    UINT8 Green;
    UINT8 Red;
    UINT8 Alpha;
} COLOR;

typedef struct PIXELPOSITIONS
{
    UINT32 PixelxPos;
    UINT32 PixelyPos;
} PIXELPOSITIONS;

UINT64 InitGraphics(void);

void InitGraphicsForBlockInfo(BLOCKINFO *block);

GRAPHICSBUFFER *GetGraphicsBuffer(void);

void SetGraphicsColor(UINT32 color);

UINT32 *GetGraphicsColor(void);

// This creates a filled box of pixels using the GRAPHICSBUFFER.
// NOTE : Call SetGraphicsColor prior to using this function.
void CreateBufferFilledBox(UINT32 xPos, UINT32 yPos, UINT32 w, UINT32 h);

void ClearBufferScreen(UINT32 color);

UINT32 GetScreenWidth(void);

UINT32 GetScreenHeight(void);

#endif
