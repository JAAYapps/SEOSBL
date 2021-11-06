#pragma once

#define true    1
#define false   0
#define NULL (void*)0

typedef unsigned char       UINT8;
typedef unsigned short      UINT16;
typedef unsigned int        UINT32;
typedef unsigned long long  UINT64;

typedef struct MEMORY_DESCRIPTOR
{
    UINT32 Type;
    UINT64 PhysicalStart;
    UINT64 VirtualStart;
    UINT64 NumberOfPages;
    UINT64 Attribute;
} MEMORY_DESCRIPTOR;

typedef struct BLOCKINFO
{
    UINT64             BaseAddress;
    UINT64             BufferSize;
    UINT32             ScreenWidth;
    UINT32             ScreenHeight;
    UINT32             PixelsPerScanLine;
    UINT64             LoaderFileSize;
    MEMORY_DESCRIPTOR* MMap;
    UINT64             MMapSize;
    UINT64             MMapDescriptorSize;
    UINT64*            rsdp;
} __attribute__((__packed__)) BLOCKINFO;