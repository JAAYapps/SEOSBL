#include "Graphics.h"
#include "EFICommon.h"
#include "EFIScreenOut.h"

EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;
EFI_GRAPHICS_OUTPUT_BLT_PIXEL Color;
GRAPHICSBUFFER gBuffer;

EFI_STATUS InitGraphics()
{
    // We initialize the Graphics Output Protocol.
    // This is used instead of the VGA interface.
    SetColor(EFI_BROWN);
    Print(L"\r\n\r\nLoading Graphics Output Protocol ... ");
    EFI_STATUS Status = GetSystemTable()->BootServices->LocateProtocol(&EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, 0, (void**)&gop);
    SetColor(Status == EFI_SUCCESS ? EFI_CYAN : EFI_RED);
    Print(CheckStandardEFIError(Status));

    gBuffer.BaseAddress        = (void*)gop->Mode->FrameBufferBase;
    gBuffer.BufferSize         = gop->Mode->FrameBufferSize;
    gBuffer.ScreenWidth        = gop->Mode->Info->HorizontalResolution;
    gBuffer.ScreenHeight       = gop->Mode->Info->VerticalResolution;
    gBuffer.PixelsPerScanLine  = gop->Mode->Info->PixelsPerScanLine;
    return Status;
}

EFI_GRAPHICS_OUTPUT_PROTOCOL* GetGraphics()
{
    return gop;
}

GRAPHICSBUFFER* GetGraphicsBuffer()
{
    return &gBuffer;
}

void SetGraphicsColor(UINT32 color)
{
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL GColor;
    GColor.Reserved = color >> 24;
    GColor.Red      = color >> 16;
    GColor.Green    = color >> 8;
    GColor.Blue     = color;
    Color = GColor;
}

// This positions the pixel in the row and column ( X and Y )
void SetPixel(UINT32 xPos, UINT32 yPos)
{
    gop->Blt(gop, &Color, EfiBltVideoFill, 0, 0, xPos, yPos, 1, 1, 0);
}

// This creates a filled box of pixels.
// NOTE : Call SetGraphicsColor prior to using this function.
void CreateFilledBox(UINT32 xPos, UINT32 yPos, UINT32 w, UINT32 h)
{
    gop->Blt(gop, &Color, EfiBltVideoFill, 0, 0, xPos, yPos, w, h, 0);
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

UINT32 GetScreenWidth()
{
    return gBuffer.ScreenWidth;
}

UINT32 GetScreenHeight()
{
    return gBuffer.ScreenHeight;
}