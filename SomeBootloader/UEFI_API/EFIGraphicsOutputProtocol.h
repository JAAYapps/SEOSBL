#pragma once
#include "BasicTypes.h"
#include "EFIStatus.h"

struct EFI_GRAPHICS_OUTPUT_PROTOCOL;

// GRAPHICS
// UEFI 2.9 Specs PDF Page 491
typedef enum EFI_GRAPHICS_OUTPUT_BLT_OPERATION
{
    EfiBltVideoFill,
    EfiBltVideoToBltBuffer,
    EfiBltBufferToVideo,
    EfiBltVideoToVideo,
    EfiGraphicsOutputBltOperationMax
} EFI_GRAPHICS_OUTPUT_BLT_OPERATION;

// UEFI 2.9 Specs PDF Page 491
typedef struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL
{
    UINT8   Blue;
    UINT8   Green;
    UINT8   Red;
    UINT8   Reserved;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL;

// UEFI 2.9 Specs PDF Page 486
typedef enum EFI_GRAPHICS_PIXEL_FORMAT
{
    PixelRedGreenBlueReserved8BitPerColor,
    PixelBlueGreenRedReserved8BitPerColor,
    PixelBitMask,
    PixelBltOnly,
    PixelFormatMax
} EFI_GRAPHICS_PIXEL_FORMAT;

// UEFI 2.9 Specs PDF Page 485
typedef struct EFI_PIXEL_BITMASK
{
    UINT32    RedMask;
    UINT32    GreenMask;
    UINT32    BlueMask;
    UINT32    ReservedMask;
} EFI_PIXEL_BITMASK;

// UEFI 2.9 Specs PDF Page 486
typedef struct EFI_GRAPHICS_OUTPUT_MODE_INFORMATION
{
    UINT32                      Version;
    UINT32                      HorizontalResolution;
    UINT32                      VerticalResolution;
    EFI_GRAPHICS_PIXEL_FORMAT   PixelFormat;
    EFI_PIXEL_BITMASK           PixelInformation;
    UINT32                      PixelsPerScanLine;
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

// UEFI 2.9 Specs PDF Page 488
typedef struct EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE
{
    UINT32                                MaxMode;
    UINT32                                Mode;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  *Info;
    UINTN                                 SizeOfInfo;
    EFI_PHYSICAL_ADDRESS                  FrameBufferBase;
    UINTN                                 FrameBufferSize;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

typedef EFI_STATUS (*EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE)(struct EFI_GRAPHICS_OUTPUT_PROTOCOL *This, UINT32 ModeNumber, UINTN *SizeOfInfo, EFI_GRAPHICS_OUTPUT_MODE_INFORMATION **Info);
typedef EFI_STATUS (*EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE)(struct EFI_GRAPHICS_OUTPUT_PROTOCOL *This, UINT32 ModeNumber);
typedef EFI_STATUS (*EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT)(struct EFI_GRAPHICS_OUTPUT_PROTOCOL *This, EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer, EFI_GRAPHICS_OUTPUT_BLT_OPERATION BltOperation, UINTN SourceX, UINTN SourceY, UINTN DestinationX, UINTN DestinationY, UINTN Width, UINTN Height, UINTN Delta);

// UEFI 2.9 Specs PDF Page 485
typedef struct EFI_GRAPHICS_OUTPUT_PROTOCOL
{
    EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE  QueryMode;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE    SetMode;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT         Blt;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE        *Mode;
} EFI_GRAPHICS_OUTPUT_PROTOCOL;