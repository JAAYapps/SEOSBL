#include "../../includes/SEOSBLMemory.h"
#include "../../includes/Graphics.h"
#include "../../includes/text.h"
#include "../../includes/String.h"
#include "../../Common-Code-For-C-Projects/common.h"

unsigned int GetDriverEntryPoint(UINT8 *loadedDriver);

void DisplayMemory(void);

void ShowEdgeBorders(void);

void main(BLOCKINFO *bi)
{
    CopyMemoryBlock(*bi);
    InitGraphicsForBlockInfo(GetBlockInfo());
    TextInit(GetBlockInfo(), GetDriverEntryPoint);
    ClearBufferScreen(0x00004584);
    ShowEdgeBorders();
    SetCursorPosition(0, 0);
    UINT64 size = GetMaxMemorySize() / 1024 / 1024;
    UINT16 TOTALRAM[30];
    i64toa16(size, TOTALRAM, DECIMAL);
    SetGraphicsColor(GREEN);
    wprintf((const short *)TOTALRAM);
    DisplayMemory();
    // TODO : Paging

    const char st4[] = "\r\nEnd of Program I guess. What now? I don't know what else to do. Give me more stuff to do!!! NOW, or I will do nothing for all of time!!!";
    SetGraphicsColor(GREEN);
    printf(st4);

    // TestASCII(18);

    while (1)
    {
        __asm__("hlt");
    }
}

unsigned int GetDriverEntryPoint(UINT8 *loadedDriver)
{
    UINT8 *test1 = loadedDriver;
    UINT8 p1, p2, p3, p4;
    p1 = *test1;
    test1 += 1;
    p2 = *test1;
    test1 += 1;
    p3 = *test1;
    test1 += 1;
    p4 = *test1;

    if (p1 == 100 && p2 == 134)
    {
        test1 += 37;
        p1 = *test1;
        test1 += 1;
        p2 = *test1;
        test1 += 1;
        p3 = *test1;
        test1 += 1;
        p4 = *test1;

        return (p4 << 24) | (p3 << 16) | (p2 << 8) | p1;
    }
    else
    {
        for (UINT8 i = 0; i < GetBlockInfo()->fontInfo.driverSize; i++)
        {
            loadedDriver[i] = 0;
        }
        return 0;
    }
}

void ShowEdgeBorders()
{
    SetGraphicsColor(BLACK);
    CreateBufferFilledBox(0, 0, GetScreenWidth() - 1, 4);
    CreateBufferFilledBox(0, 0, 4, GetScreenHeight() - 1);
    CreateBufferFilledBox(0, GetScreenHeight() - 4, GetScreenWidth() - 1, 4);
    CreateBufferFilledBox(GetScreenWidth() - 4, 0, 4, GetScreenHeight() - 1);
}

void DisplayMemory()
{
    SetCursorPosition(8, 4);
    const char str[] = "******************MEMORY MAP******************\r\n\r\n";
    printf(str);

    long long MapEntries = GetBlockInfo()->MMapSize / GetBlockInfo()->MMapDescriptorSize;
    int t = (MapEntries / 2) + 1;
    UINT64 TotalRam = 0;
    for (long long i = 0; i < t; i++)
    {
        MEMORY_DESCRIPTOR *desc = (MEMORY_DESCRIPTOR *)((UINT64)GetBlockInfo()->MMap + (i * GetBlockInfo()->MMapDescriptorSize));
        SetGraphicsColor(CYAN);
        wprintf((const short *)GetBlockInfo()->MemerySectionStrings[desc->Type]);
        SetGraphicsColor(YELLOW);
        const char str1[] = " ";
        printf((const char *)str1);
        UINT16 buf[8];
        itoa16(desc->NumberOfPages * 4096 / 1024, buf, DECIMAL);
        wprintf((const short *)buf);
        SetGraphicsColor(GREEN);
        const char str2[] = " KB\r\n";
        printf((const char *)str2);
        TotalRam += desc->NumberOfPages * 4096 / 1024;
    }

    int pos = 6;
    for (long long i = t; i < MapEntries; i++)
    {
        SetCursorPosition(40, pos);
        MEMORY_DESCRIPTOR *desc = (MEMORY_DESCRIPTOR *)((UINT64)GetBlockInfo()->MMap + (i * GetBlockInfo()->MMapDescriptorSize));
        SetGraphicsColor(CYAN);
        wprintf((const short *)GetBlockInfo()->MemerySectionStrings[desc->Type]);
        SetGraphicsColor(YELLOW);
        const char str1[] = " ";
        printf((const char *)str1);
        UINT16 buf[8];
        itoa16(desc->NumberOfPages * 4096 / 1024, buf, DECIMAL);
        wprintf((const short *)buf);
        SetGraphicsColor(GREEN);
        const char str2[] = " KB\r\n";
        printf((const char *)str2);
        TotalRam += desc->NumberOfPages * 4096 / 1024;
        pos++;
    }

    SetGraphicsColor(YELLOW);
    SetCursorPosition(0, 30);
    const char str3[] = "Total System Ram : ";
    printf((const char *)str3);
    SetGraphicsColor(CYAN);
    UINT16 tr[8];
    itoa16(TotalRam, tr, DECIMAL);
    wprintf((const short *)tr);
    SetGraphicsColor(GREEN);
    const char str4[] = " KBytes";
    printf((const char *)str4);

    const char str5[] = "\r\n";
    printf((const char *)str5);
}

#include "../SEOSBLMemory.c"
#include "../Graphics.c"
#include "../text.c"
#include "../String.c"