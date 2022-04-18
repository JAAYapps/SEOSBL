#include "../includes/SEOSBLMemory.h"
#include "../includes/Graphics.h"

BLOCKINFO bi __attribute__((section(".text"))) = {0};

BLOCKINFO InitMemoryBlock()
{
    bi.Graphics = GetGraphicsBuffer();

    bi.LoaderFileSize = 0;
    bi.MMap = NULL;
    bi.MMapSize = 0;
    bi.MMapDescriptorSize = 0;
    bi.MemerySectionStrings = NULL;
    bi.rsdp = NULL;
    bi.fontInfo.FONT_DRIVER = NULL;
    bi.fontInfo.CUSTOM_FONT = NULL;
    bi.fontInfo.driverSize = 0;
    bi.fontInfo.fontBufferSize = 0;
    bi.fontInfo.GetCharSize = NULL;
    bi.fontInfo.GetFontPixel = NULL;
    bi.fontInfo.GetFontSize = NULL;
    bi.fontInfo.GetLineSize = NULL;
    bi.fontInfo.GetMaxLines = NULL;
    bi.fontInfo.SetFontSize = NULL;
    return bi;
}

BLOCKINFO *GetBlockInfo()
{
    return &bi;
}

void CopyMemoryBlock(BLOCKINFO block)
{
    bi.Graphics = block.Graphics;
    bi.LoaderFileSize = block.LoaderFileSize;
    bi.MMap = block.MMap;
    bi.MMapDescriptorSize = block.MMapDescriptorSize;
    bi.MMapSize = block.MMapSize;
    bi.MemerySectionStrings = block.MemerySectionStrings;
    bi.rsdp = block.rsdp;
    bi.fontInfo.FONT_DRIVER = block.fontInfo.FONT_DRIVER;
    bi.fontInfo.CUSTOM_FONT = block.fontInfo.CUSTOM_FONT;
    bi.fontInfo.driverSize = block.fontInfo.driverSize;
    bi.fontInfo.fontBufferSize = block.fontInfo.fontBufferSize;
    bi.fontInfo.GetCharSize = block.fontInfo.GetCharSize;
    bi.fontInfo.GetFontPixel = block.fontInfo.GetFontPixel;
    bi.fontInfo.GetFontSize = block.fontInfo.GetFontSize;
    bi.fontInfo.GetLineSize = block.fontInfo.GetLineSize;
    bi.fontInfo.GetMaxLines = block.fontInfo.GetMaxLines;
    bi.fontInfo.SetFontSize = block.fontInfo.SetFontSize;
}

UINT64 GetMemoryMapEntries()
{
    return bi.MMapSize / bi.MMapDescriptorSize;
}

UINT64 GetMaxMemorySize()
{
    UINT64 MapEntries = GetMemoryMapEntries();

    UINT64 TotalRam = 0;
    for (UINT64 i = 0; i < MapEntries; i++)
    {
        MEMORY_DESCRIPTOR *desc = (MEMORY_DESCRIPTOR *)((UINT64)bi.MMap + (i * bi.MMapDescriptorSize));
        TotalRam += desc->NumberOfPages * 4096;
    }
    return TotalRam;
}