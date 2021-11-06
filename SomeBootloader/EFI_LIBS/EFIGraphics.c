#include "EFIGraphics.h"
#include "EFICommon.h"
#include "EFIScreenOut.h"
#include "..\Graphics.h"
#include "..\GraphicsDriver.h"

EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;

UINT64 InitGraphicsDriver(void* GRAPHICS)
{
    return (UINT64)EFIInitGraphics((GRAPHICSBUFFER*)GRAPHICS);
}

void InitializeGOPScreen(GRAPHICSBUFFER* gBuffer)
{
	UINT32 NewNativeMode = 9000000;
	UINTN  GOPSizeOfInfo      = gop->Mode->SizeOfInfo;
	UINT32 MaxResolutionModes = gop->Mode->MaxMode;
	
	EFI_STATUS Status;
	for (UINT32 i = 0; i < MaxResolutionModes; i++)
	{
		EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *info;
        Status = gop->QueryMode(gop, i, &GOPSizeOfInfo, &info);
		if(Status == EFI_SUCCESS)
		{
			if((info->HorizontalResolution == 1920) && (info->VerticalResolution == 1080))
			{
				NewNativeMode = i;
				SetColor(EFI_LIGHTGREEN);
				Print(L"Setting 1920 x 1080 MODE ... \r\n");
			}
		}
	}
	if(NewNativeMode == 9000000)
	{
		SetColor(EFI_LIGHTRED);
		Print(L"WARNING : Unable to find 1920 x 1080 MODE !\r\nUsing Default GOP.\r\n");
        gBuffer->BaseAddress        = (UINT64)gop->Mode->FrameBufferBase;
        gBuffer->BufferSize         = gop->Mode->FrameBufferSize;
        gBuffer->ScreenWidth        = gop->Mode->Info->HorizontalResolution;
        gBuffer->ScreenHeight       = gop->Mode->Info->VerticalResolution;
        gBuffer->PixelsPerScanLine  = gop->Mode->Info->PixelsPerScanLine;
	} else {
		Status = gop->SetMode(gop, NewNativeMode);
		if(Status == EFI_SUCCESS)
		{
            gBuffer->BaseAddress        = (UINT64)gop->Mode->FrameBufferBase;
            gBuffer->BufferSize         = gop->Mode->FrameBufferSize;
            gBuffer->ScreenWidth        = gop->Mode->Info->HorizontalResolution;
            gBuffer->ScreenHeight       = gop->Mode->Info->VerticalResolution;
            gBuffer->PixelsPerScanLine  = gop->Mode->Info->PixelsPerScanLine;
			SetColor(EFI_LIGHTGREEN);
			Print(L"1920 x 1080 MODE set.\r\n");
		} else {
			SetColor(EFI_LIGHTRED);
			Print(L"WARNING : Unable to find 1920 x 1080 MODE !\r\nUsing Default GOP.\r\n");
            gBuffer->BaseAddress        = (UINT64)gop->Mode->FrameBufferBase;
            gBuffer->BufferSize         = gop->Mode->FrameBufferSize;
            gBuffer->ScreenWidth        = gop->Mode->Info->HorizontalResolution;
            gBuffer->ScreenHeight       = gop->Mode->Info->VerticalResolution;
            gBuffer->PixelsPerScanLine  = gop->Mode->Info->PixelsPerScanLine;
		}
	}
}

EFI_STATUS EFIInitGraphics(GRAPHICSBUFFER* gBuffer)
{
    // We initialize the Graphics Output Protocol.
    // This is used instead of the VGA interface.
    SetColor(EFI_BROWN);
    Print(L"\r\n\r\nLoading Graphics Output Protocol ... ");
    EFI_STATUS Status = GetSystemTable()->BootServices->LocateProtocol(&EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, 0, (void**)&gop);
    SetColor(Status == EFI_SUCCESS ? EFI_CYAN : EFI_RED);
    Print(CheckStandardEFIError(Status));

    InitializeGOPScreen(gBuffer);

    return Status;
}



EFI_GRAPHICS_OUTPUT_PROTOCOL* GetGraphics()
{
    return gop;
}

// This positions the pixel in the row and column ( X and Y )
void SetPixel(UINT32 xPos, UINT32 yPos)
{
    gop->Blt(gop, (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)GetGraphicsColor(), EfiBltVideoFill, 0, 0, xPos, yPos, 1, 1, 0);
}

// This creates a filled box of pixels.
// NOTE : Call SetGraphicsColor prior to using this function.
void CreateFilledBox(UINT32 xPos, UINT32 yPos, UINT32 w, UINT32 h)
{
    gop->Blt(gop, (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)GetGraphicsColor(), EfiBltVideoFill, 0, 0, xPos, yPos, w, h, 0);
}