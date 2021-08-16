#pragma once

#include "..\UEFI_API\EFIGraphicsOutputProtocol.h"

             // ARGB             
#define ORANGE 0xffffa500
#define CYAN   0xff00ffff
#define RED    0xffff0000
#define GREEN  0xff00ff00
#define BLUE   0xff0000ff
#define GRAY   0xff888888
#define WHITE  0xffffffff
#define BLACK  0xff000000

typedef struct PIXELPOSITIONS
{
    UINT32 PixelxPos;
    UINT32 PixelyPos;
} PIXELPOSITIONS;

typedef struct GRAPHICSBUFFER
{
    void*  BaseAddress;
    UINT64 BufferSize;
    UINT32 ScreenWidth;
    UINT32 ScreenHeight;
    UINT32 PixelsPerScanLine;
} GRAPHICSBUFFER;

EFI_STATUS InitGraphics();

EFI_GRAPHICS_OUTPUT_PROTOCOL* GetGraphics();

void SetGraphicsColor(UINT32 color);

// This positions the pixel in the row and column ( X and Y )
void SetPixel(UINT32 xPos, UINT32 yPos);

// This creates a filled box of pixels.
// NOTE : Call SetGraphicsColor prior to using this function.
void CreateFilledBox(UINT32 xPos, UINT32 yPos, UINT32 w, UINT32 h);

// This creates a filled box of pixels using the GRAPHICSBUFFER.
// NOTE : Call SetGraphicsColor prior to using this function.
void CreateBufferFilledBox(UINT32 xPos, UINT32 yPos, UINT32 w, UINT32 h);

UINT32 GetScreenWidth();

UINT32 GetScreenHeight();