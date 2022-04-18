#ifndef SEOSBLcommon
#define SEOSBLcommon

#include "../Common-Code-For-C-Projects/common.h"

typedef struct MEMORY_DESCRIPTOR
{
    UINT32 Type;
    UINT64 PhysicalStart;
    UINT64 VirtualStart;
    UINT64 NumberOfPages;
    UINT64 Attribute;
} MEMORY_DESCRIPTOR;

typedef struct GRAPHICSBUFFER
{
    UINT64 *BaseAddress;
    UINT64 *BufferSize;
    UINT32 ScreenWidth;
    UINT32 ScreenHeight;
    UINT32 PixelsPerScanLine;
} GRAPHICSBUFFER;

typedef struct BOOTDRIVER
{
    void (*Main)(UINT8 *data);
    UINT64 size;
} BOOTDRIVER;

typedef struct BOOTINFO
{
    BOOTDRIVER *item;
    UINT64 bootItemsListSize;
} BOOTINFO;

typedef struct FONTINFO
{
    UINT64 driverSize;
    UINT64 fontBufferSize;
    UINT8 *FONT_DRIVER;
    UINT8 *CUSTOM_FONT;
    UINT8(*GetFontPixel)
    (unsigned short, unsigned int, unsigned int);
    UINT32(*GetFontSize)
    (void);
    UINT32(*GetCharSize)
    (void);
    UINT32(*GetLineSize)
    (void);
    UINT32(*GetMaxLines)
    (void);
    void (*SetFontSize)(UINT32);
} FONTINFO;

typedef struct LOADERDRIVER
{
    UINT8 *LoaderDriver;
    UINT64 Size;
} LOADERDRIVER;

typedef struct BLOCKINFO
{
    GRAPHICSBUFFER *Graphics;
    UINT64 LoaderFileSize;
    FONTINFO fontInfo;
    LOADERDRIVER *LoaderDrivers;
    MEMORY_DESCRIPTOR *MMap;
    UINT64 MMapSize;
    UINT64 MMapDescriptorSize;
    unsigned short int **MemerySectionStrings;
    UINT64 *rsdp;
} __attribute__((__packed__)) BLOCKINFO;

#endif /* SEOSBLcommon */
