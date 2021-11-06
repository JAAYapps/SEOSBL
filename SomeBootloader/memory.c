#include "memory.h"
#include "Graphics.h"

BLOCKINFO* bi __attribute__ ((section (".text"))) = {0};

BLOCKINFO InitMemoryBlock()
{
    bi->BaseAddress        = (UINT64)GetGraphicsBuffer()->BaseAddress;
    bi->BufferSize         = GetGraphicsBuffer()->BufferSize;
    bi->ScreenWidth        = GetGraphicsBuffer()->ScreenWidth;
    bi->ScreenHeight       = GetGraphicsBuffer()->ScreenHeight;
    bi->PixelsPerScanLine  = GetGraphicsBuffer()->PixelsPerScanLine;
    return *bi;
}

BLOCKINFO* GetBlockInfo()
{
    return bi;
}

void CopyMemoryBlock(BLOCKINFO block)
{
    bi->BaseAddress          = block.BaseAddress;
    bi->BufferSize           = block.BufferSize;
    bi->LoaderFileSize       = block.LoaderFileSize;
    bi->MMap                 = block.MMap;
    bi->MMapDescriptorSize   = block.MMapDescriptorSize;
    bi->MMapSize             = block.MMapSize;
    bi->PixelsPerScanLine    = block.PixelsPerScanLine;
    bi->ScreenHeight         = block.ScreenHeight;
    bi->ScreenWidth          = block.ScreenWidth;
    bi->rsdp                 = block.rsdp;
}

void* memcpy(void* dst, const void* src, unsigned long long size)
{
    for ( unsigned long long i = 0; i < size; i++ )
        ((unsigned char*) dst)[i] = ((const unsigned char*) src)[i];
    return dst;
}