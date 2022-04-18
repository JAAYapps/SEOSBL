#ifndef EFI_GRAPHICS_H
#define EFI_GRAPHICS_H

#include "../UEFI_API/EFIGraphicsOutputProtocol.h"
#include "../../includes/Graphics.h"

EFI_STATUS EFIInitGraphics(GRAPHICSBUFFER *gBuffer);

EFI_GRAPHICS_OUTPUT_PROTOCOL *GetGraphics();

void SetGraphicsColor(UINT32 color);

// This positions the pixel in the row and column ( X and Y )
void SetPixel(UINT32 xPos, UINT32 yPos);

// This creates a filled box of pixels.
// NOTE : Call SetGraphicsColor prior to using this function.
void CreateFilledBox(UINT32 xPos, UINT32 yPos, UINT32 w, UINT32 h);

#endif
