#include "../includes/Graphics.h"
#include "../Common-Code-For-C-Projects/common.h"
#include "../includes/GraphicsDriver.h"

GRAPHICSBUFFER gBuffer __attribute__((section(".text"))) = {0};
COLOR Color __attribute__((section(".text"))) = {0};

UINT64 InitGraphics()
{
    return InitGraphicsDriver((GRAPHICSBUFFER *)&gBuffer);
}

void InitGraphicsForBlockInfo(BLOCKINFO *block)
{
    gBuffer.BaseAddress = block->Graphics->BaseAddress;
    gBuffer.BufferSize = block->Graphics->BufferSize;
    gBuffer.ScreenHeight = block->Graphics->ScreenHeight;
    gBuffer.ScreenWidth = block->Graphics->ScreenWidth;
    gBuffer.PixelsPerScanLine = block->Graphics->PixelsPerScanLine;
}

GRAPHICSBUFFER *GetGraphicsBuffer()
{
    return &gBuffer;
}

void SetGraphicsColor(UINT32 color)
{
    COLOR GColor;
    GColor.Alpha = (color >> 24);
    GColor.Red = (color >> 16);
    GColor.Green = (color >> 8);
    GColor.Blue = color;
    Color = GColor;
}

UINT32 *GetGraphicsColor()
{
    return (UINT32 *)&Color;
}

// This creates a filled box of pixels using the GRAPHICSBUFFER.
// NOTE : Call SetGraphicsColor prior to using this function.
void CreateBufferFilledBox(UINT32 xPos, UINT32 yPos, UINT32 w, UINT32 h)
{
    // This functions puts a color filled box on the screen
    UINT32 ByteOffset = 4;
    if (xPos < 0)
    {
        xPos = 0;
    }
    if (yPos < 0)
    {
        yPos = 0;
    }
    if (w < 1)
    {
        w = 1;
    }
    if (h < 1)
    {
        h = 1;
    }
    UINT32 x;
    UINT32 y = yPos;
    UINT32 width = (xPos + w) * ByteOffset;
    UINT32 height = yPos + h;
    UINT64 buffer = *gBuffer.BaseAddress;
    for (y = yPos; y <= height; y++)
    {
        for (x = xPos * ByteOffset; x <= width; x += ByteOffset)
        {
            *(UINT32 *)(x + (y * gBuffer.PixelsPerScanLine * ByteOffset) + buffer) = *(UINT32 *)&Color;
        }
    }
}

void ClearBufferScreen(UINT32 color)
{
    SetGraphicsColor(color);
    CreateBufferFilledBox(0, 0, gBuffer.PixelsPerScanLine, gBuffer.ScreenHeight);
}

UINT32 GetScreenWidth()
{
    return gBuffer.PixelsPerScanLine;
}

UINT32 GetScreenHeight()
{
    return gBuffer.ScreenHeight;
}