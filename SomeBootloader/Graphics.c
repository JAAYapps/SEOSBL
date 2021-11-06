//#ifndef GRAPHICS_INCLUDE
#include "Graphics.h"
#include "common.h"
//#endif  // GRAPHICS_INCLUDE
//#ifndef GRAPHICSDRIVER_INCLUDE
#include "GraphicsDriver.h"
//#endif  // GRAPHICSDRIVER_INCLUDE

GRAPHICSBUFFER gBuffer __attribute__ ((section (".text"))) = {0};
COLOR Color __attribute__ ((section (".text"))) = {0};

UINT64 InitGraphics()
{
    return InitGraphicsDriver((GRAPHICSBUFFER*)&gBuffer);
}

void InitGraphicsForBlockInfo(BLOCKINFO* block)
{
    gBuffer.BaseAddress         = block->BaseAddress;
    gBuffer.BufferSize          = block->BufferSize;
    gBuffer.ScreenHeight        = block->ScreenHeight;
    gBuffer.ScreenWidth         = block->ScreenWidth;
    gBuffer.PixelsPerScanLine   = block->PixelsPerScanLine;
}

GRAPHICSBUFFER* GetGraphicsBuffer()
{
    return &gBuffer;
}

void SetGraphicsColor(UINT32 color)
{
    COLOR GColor;
    GColor.Alpha    = (color >> 24);
    GColor.Red      = (color >> 16);
    GColor.Green    = (color >> 8);
    GColor.Blue     = color;
    Color = GColor;
}

UINT32* GetGraphicsColor()
{
    return (UINT32*)&Color;
}

// This creates a filled box of pixels using the GRAPHICSBUFFER.
// NOTE : Call SetGraphicsColor prior to using this function.
void CreateBufferFilledBox(UINT32 xPos, UINT32 yPos, UINT32 w, UINT32 h)
{
    // This functions puts a color filled box on the screen
    UINT32 ByteOffset = 4;
    if(xPos < 0){xPos = 0;}
    if(yPos < 0){yPos = 0;}
    if(w < 1){w = 1;}
    if(h < 1){h = 1;}
    UINT32 x;
    UINT32 y      = yPos;
    UINT32 width  = (xPos + w) * ByteOffset;
    UINT32 height = yPos + h;

    for(y = yPos; y <= height; y++)
    {
        for(x = xPos * ByteOffset; x <= width; x+=ByteOffset)
        {
            *(UINT32*)(x + (y * gBuffer.PixelsPerScanLine * ByteOffset) + gBuffer.BaseAddress) = *(UINT32*)&Color;
        }
    }
}

void ClearBufferScreen(UINT32 color)
{
    SetGraphicsColor(color);
    CreateBufferFilledBox(0,0,gBuffer.ScreenWidth, gBuffer.ScreenHeight);
}

UINT32 GetScreenWidth()
{
    return gBuffer.ScreenWidth;
}

UINT32 GetScreenHeight()
{
    return gBuffer.ScreenHeight;
}