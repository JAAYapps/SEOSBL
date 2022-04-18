#include "../includes/SEOSBLcommon.h"
#include "EFI_LIBS\EFICommon.h"
#include "EFI_LIBS\EFIScreenOut.h"
#include "EFI_LIBS\EFIKeyboardInput.h"
#include "EFI_LIBS\Interval.h"
#include "EFI_LIBS\EFIPower.h"
#include "UEFI_API\EFIIO.h"
#include "EFI_LIBS\EFIFS.h"
#include "../includes/Graphics.h"
#include "../Common-Code-For-C-Projects\memory.h"
#include "../includes/SEOSBLMemory.h"
#include "../includes/GDT.h"
#include "../includes/Date.h"
#include "../includes/String.h"
#include "../includes/font.h"
#include "../SimpleJSONtoC/JSON.h"

// SEOSBL is a bootloader that does not know anything.
// This main file is to grab all the resources from the UEFI.
// Once it calls the loader's main function, it then knows NOTHING!!!
// The only thing it knows is to call methods in memory, that's it.
// The driver files contain all the specific methods to actually perform tasks.

void DisplayGraphicsInfo(GRAPHICSBUFFER *gBuffer)
{
    char GOPINFO[12];

    Print("\r\n\r\n");
    SetColor(EFI_WHITE);
    Print("BaseAddress       : ");
    SetColor(EFI_YELLOW);
    Print("0x");
    i64toa(*gBuffer->BaseAddress, GOPINFO, HEX);
    Print(GOPINFO);
    Print("\r\n");

    SetColor(EFI_WHITE);
    Print("BufferSize        : ");
    SetColor(EFI_YELLOW);
    Print("0x");
    i64toa(*gBuffer->BufferSize, GOPINFO, HEX);
    SetColor(EFI_YELLOW);
    Print(GOPINFO);
    Print("\r\n");

    SetColor(EFI_WHITE);
    Print("Width             : ");
    itoa(gBuffer->ScreenWidth, GOPINFO, DECIMAL);
    SetColor(EFI_YELLOW);
    Print(GOPINFO);
    Print("\r\n");

    SetColor(EFI_WHITE);
    Print("Height            : ");
    itoa(gBuffer->ScreenHeight, GOPINFO, DECIMAL);
    SetColor(EFI_YELLOW);
    Print(GOPINFO);
    Print("\r\n");

    SetColor(EFI_WHITE);
    Print("PixelsPerScanLine : ");
    itoa(gBuffer->PixelsPerScanLine, GOPINFO, DECIMAL);
    SetColor(EFI_YELLOW);
    Print(GOPINFO);
    Print("\r\n");
}

// void gdt_init()
// {
//     UINT64 fs = 0;
//     Print("Read GDT.bin\r\n");
//     UINT8 *gdt = readFile(u"GDT.bin", &fs);

//     if (gdt != NULL)
//     {
//         UINT8 *test1 = gdt;
//         unsigned int ENTRY_POINT = 0;

//         UINT8 p1, p2, p3, p4;
//         p1 = *test1;
//         test1 += 1;
//         p2 = *test1;
//         test1 += 1;
//         p3 = *test1;
//         test1 += 1;
//         p4 = *test1;

//         if (p1 == 100 && p2 == 134)
//         {
//             Print("BINARY - 8664 Signature\r\n");
//             SetColor(EFI_WHITE);
//             test1 += 37;
//             p1 = *test1;
//             test1 += 1;
//             p2 = *test1;
//             test1 += 1;
//             p3 = *test1;
//             test1 += 1;
//             p4 = *test1;

//             UINT16 s[2];
//             itoa(p1, s, 16);
//             Print(s);
//             Print("  ");

//             itoa(p2, s, 16);
//             Print(s);
//             Print("  ");

//             itoa(p3, s, 16);
//             Print(s);
//             Print("  ");

//             itoa(p4, s, 16);
//             Print(s);
//             SetColor(EFI_BROWN);
//             Print("  \r\nENTRY POINT : ");
//             SetColor(EFI_GREEN);

//             ENTRY_POINT = (p4 << 24) | (p3 << 16) | (p2 << 8) | p1;

//             UINT16 s2[5];
//             itoa(ENTRY_POINT, s2, 10);
//             Print(s2);
//             Print("  ");

//             void (*GDTBinFile)() = ((__attribute__((ms_abi)) void (*)())((UINT64)ENTRY_POINT));
//             GDTBinFile();
//         }
//         else
//         {
//             ENTRY_POINT = 0;
//             Print("WARNING : RAW FILE HAS BEEN LOADED - No Signature DETECTED\r\n");
//             Print("This was supposed to be the GDT executable, what happened?\r\n");
//             Print("Without this I can't reset the CPU. WHAT HAVE YOU DONE!!!!\r\n");
//             Delay(1000);
//             ClearBufferScreen(DARKGRAY);
//             Print("      \\                 /          \\                 /        \r\n");
//             Print("       \\               /            \\               /         \r\n");
//             Print("        \\             /              \\             /          \r\n");
//             Print("         \\           /                \\           /           \r\n");
//             Print("          \\         /                  \\         /            \r\n");
//             Print("           \\       /                    \\       /             \r\n");
//             Print("            \\     /                      \\     /              \r\n");
//             Print("             \\   /                        \\   /               \r\n");
//             Print("              \\ /                          \\ /                \r\n");
//             Print("                O                             O                 \r\n");
//             Print("               / \\                          / \\               \r\n");
//             Print("              /   \\                        /   \\              \r\n");
//             Print("             /     \\                      /     \\             \r\n");
//             Print("            /       \\                    /       \\            \r\n");
//             Print("           /         \\                  /         \\           \r\n");
//             Print("          /           \\                /           \\          \r\n");
//             Print("         /             \\              /             \\         \r\n");
//             Print("        /               \\            /               \\        \r\n");
//             Print("       /                 \\          /                 \\       \r\n");
//             Print("                                                                \r\n");
//             Print("                                                                \r\n");
//             Print("                                                                \r\n");
//             Print("                _______________________________                 \r\n");
//             Print("                     |       |                                  \r\n");
//             Print("                     |       |                                  \r\n");
//             Print("                     |       |                                  \r\n");
//             Print("                      \\     /                                  \r\n");
//             Print("                       \\   /                                   \r\n");
//             Print("                        \\ /                                    \r\n");
//             Print("                          U                                     \r\n");
//             Print("                                                                \r\n");
//             Delay(1000);
//         }
//     }
// }

// This is like int main() in a typical C program.
// In this case, we create an ImageHandle for the overall EFI interface,
// as well as a System Table pointer to the EFI_SYSTEM_TABLE struct.
// UEFI 2.9 Specs PDF Page 91
EFI_STATUS efi_main(EFI_HANDLE IH, EFI_SYSTEM_TABLE *ST)
{
    InitUEFIServices(IH, ST);
    Print("UEFI Boot\r\n");
    Delay(1000);
    InitGraphics();
    Print("Init graphics\r\n");
    Delay(1000);
    InitializeFILESYSTEM();
    Print("Init filesystem\r\n");
    Delay(1000);
    // ClearScreen();

    SetGraphicsColor(ORANGE);

    CreateBufferFilledBox(0, 0, 500, 500);

    Delay(2000);

    SetTextPosition(0, 0);

    char BSIZE[12];

    SetColor(EFI_WHITE);
    Print("Block info size : ");
    itoa(sizeof(BLOCKINFO), BSIZE, HEX);
    SetColor(EFI_YELLOW);
    Print(BSIZE);
    Print("\r\n\r\n");

    BLOCKINFO bi = InitMemoryBlock();

    DisplayGraphicsInfo(bi.Graphics);

    Delay(1000);
    // Do not use Clear Screen, the method resets the resolution on some PCs like the Asrock desktop motherboard.
    ClearBufferScreen(DARKGRAY);
    SetTextPosition(0, 0);

    JSON_Element *config = BuildJSONFromFile("config.json");

    while (config->error.isError)
    {
        __asm__("hlt");
    }

    ClearBufferScreen(DARKGRAY);
    SetTextPosition(0, 0);

    char name[50];
    UINT64 count = 0;
    Print("Start ");
    JSON_Element *e = (JSON_Element *)config->object;
    while (e->name[count] != '\0')
    {
        name[count] = e->name[count];
        count++;
    }
    Print("Type: ");
    if (e->type == boolean)
        Print("Boolean\r\n");
    if (e->type == number)
        Print("Number\r\n");
    if (e->type == string)
        Print("String\r\n");
    if (e->type == empty)
        Print("Empty\r\n");
    if (e->type == null)
        Print("NULL\r\n");
    if (e->type == element)
        Print("Element\r\n");
    name[count] = '\0';
    Print("Name of JSON object: ");
    if (count != 0)
        Print(name);
    else
        Print("No name, JSON object has a problem.\r\n");
    Print("\r\n\r\n");
    Delay(10000);

    UINT64 fs = 0;
    bi.fontInfo.CUSTOM_FONT = readFile(u"zap-light16.psf", &fs);

    char BLINFO[12];

    BLOCKINFO *b = GetBlockInfo();
    SetColor(EFI_WHITE);
    Print("Block info : 0x");
    itoa(*(unsigned long int *)&b, BLINFO, HEX);
    SetColor(EFI_YELLOW);
    Print(BLINFO);
    Print("\r\n\r\n");

    char FONTINFO[12];

    SetColor(EFI_WHITE);
    Print("Font file size : ");
    itoa(fs, FONTINFO, DECIMAL);
    SetColor(EFI_YELLOW);
    Print(FONTINFO);
    Print("\r\n\r\n");

    bi.fontInfo.fontBufferSize = fs;
    if (bi.fontInfo.CUSTOM_FONT != NULL && bi.fontInfo.fontBufferSize != 0)
    {
        bi.fontInfo.FONT_DRIVER = readFile(u"font\\psf1Driver.bin", &fs);
        bi.fontInfo.driverSize = fs;
    }

    if (bi.fontInfo.FONT_DRIVER == NULL || bi.fontInfo.CUSTOM_FONT == NULL)
    {
        if (bi.fontInfo.CUSTOM_FONT != NULL || bi.fontInfo.fontBufferSize == 0)
            freeFileBuffer(bi.fontInfo.CUSTOM_FONT);
        bi.fontInfo.CUSTOM_FONT = NULL;
        font_main(&bi);
        Print("Unable to load the font or driver.\r\n");
        Print("Don't worry, you can have this embeded font.\r\n");
        Print("In 10 seconds booting will continue.");
        Delay(10000);
    }

    bi.LoaderFileSize = readLoader(u"SEOSBL\\loader.bin");
    if (bi.LoaderFileSize == -1)
    {
        Print("Unable to load \"SEOSBL\\loader.bin\"\r\n");
        Print("Will now send a failed to load status to UEFI.");
        Print("In 30 seconds the uefi shell will appear.");
        Delay(30000);
        return EFI_LOAD_ERROR;
    }

    SetColor(EFI_CYAN);
    Print("\r\n\r\nDATE ");
    SetColor(EFI_WHITE);
    Print(": ");
    EFI_TIME Time;
    GetSystemTable()->RuntimeServices->GetTime(&Time, NULL);

    char snum[4];
    SetColor(EFI_YELLOW);
    Print(GetMonth(Time.Month));
    SetColor(EFI_LIGHTRED);
    Print(" / ");
    SetColor(EFI_YELLOW);
    itoa(Time.Day, snum, DECIMAL);
    Print(snum);
    Print(GetDayExtension(Time.Day));
    SetColor(EFI_LIGHTRED);
    Print(" / ");
    SetColor(EFI_YELLOW);
    itoa(Time.Year, snum, DECIMAL);
    Print(snum);
    Print("\r\n\r\n");

    UINT8 *loader = GetLoaderHandle();

    char LOADERINFO[12];
    SetColor(EFI_WHITE);
    Print("LOADER FILE SIZE : ");
    itoa(*(unsigned long int *)&bi.LoaderFileSize, LOADERINFO, DECIMAL);
    SetColor(EFI_YELLOW);
    Print(LOADERINFO);
    SetColor(EFI_CYAN);
    Print(" Bytes\r\n\r\n");

    SetColor(EFI_WHITE);
    Print("Loading SEOSBL ...");

    UINTN MemoryMapSize = 0;
    EFI_MEMORY_DESCRIPTOR *MemoryMap;
    UINTN MapKey;
    UINTN DescriptorSize;
    UINT32 DescriptorVersion;

    GetSystemTable()->BootServices->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);
    MemoryMapSize += 2 * DescriptorSize;
    GetSystemTable()->BootServices->AllocatePool(2, MemoryMapSize, (void **)&MemoryMap);
    GetSystemTable()->BootServices->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);

    // We look for the Root System Description Pointer ( RSDP )
    // https://wiki.osdev.org/RSDP
    // ACPI Specs PDF Page 140 Section 5.2.5.2
    EFI_CONFIGURATION_TABLE *configTable = GetSystemTable()->ConfigurationTable;
    unsigned long long *tempRSDP = NULL;
    for (UINTN index = 0; index < GetSystemTable()->NumberOfTableEntries; index++)
    {
        if (CompareGuid(&configTable[index].VendorGuid, &ACPI_20_TABLE_GUID))
        {
            if (strcmp((char *)"RSD PTR ", (char *)configTable->VendorTable) == 1)
            {
                tempRSDP = (void *)configTable->VendorTable;
            }
        }
        configTable++;
    }
    UINT8 *loaderMain = &loader[GetLoaderEntryPoint()];
    void (*KernelBinFile)(BLOCKINFO *) = ((__attribute__((ms_abi)) void (*)(BLOCKINFO *))((UINT64)loaderMain));

    bi.MMap = (MEMORY_DESCRIPTOR *)MemoryMap;
    bi.MMapSize = MemoryMapSize;
    bi.MMapDescriptorSize = DescriptorSize;
    bi.MemerySectionStrings = EFI_MEMORY_TYPE_STRINGS;
    bi.rsdp = tempRSDP;

    DisplayGraphicsInfo(bi.Graphics);

    GetSystemTable()->BootServices->ExitBootServices(GetImageHandle(), MapKey);
    Print("Start GDT...\r\n\r\n");
    gdt_init();
    Print("Started GDT.\r\n\r\n");
    KernelBinFile(&bi);

    while (1)
    {
        __asm__("hlt");
    }

    // The EFI needs to have a 0 ( or EFI_SUCCESS ) in order to know everything is ok.
    // However, this should not reach the return. The hlt is supposed to stop the cpu from running any further.
    return EFI_SUCCESS;
}

// Implementation of decoupled version of the Print method
// In this case with SEOSBL it is loosely coupled to the EFIPrint method.
// This can also be changed in the future if need be to the printf method using the GOP.
// Printing can be turned off when printing is 0 in command argument.
void Print(char *str)
{
#ifdef PRINT
    long sz = 0;
    char *ostr = str;
    while (ostr != NULL && *ostr != '\0')
    {
        sz++;
        ostr++;
    }
    CHAR16 *efiStr = NULL;
    ostr = str;
    if (sz > 0)
    {
        efiStr = AssignAndInitMemory(sizeof(CHAR16), sz + 1);
        for (long i = 0; i <= sz; i++)
            efiStr[i] = ostr[i];
        efiStr[sz + 1] = '\0';
    }
    EfiPrint(efiStr);
    FreeMemory(efiStr);
#endif
}

unsigned char *OpenAndWriteFileToMemory(char *fileName, UINT64 *size)
{
    long sz = 0;
    char *name = fileName;
    while (name != NULL && *name != '\0')
    {
        sz++;
        name++;
    }
    CHAR16 *efiFileName = NULL;
    name = fileName;
    if (sz > 0)
    {
        efiFileName = AssignAndInitMemory(sizeof(CHAR16), sz + 1); // GetSystemTable()->BootServices->AllocatePool(EfiLoaderData, (sizeof(CHAR16) * sz) + 1, (void **)&efiFileName);
        for (long i = 0; i <= sz; i++)
            efiFileName[i] = name[i];
        efiFileName[sz + 1] = '\0';
    }
    UINT8 *fp = readFile(efiFileName, size);
    FreeMemory(efiFileName);
    return fp;
}

void *AssignMemory(UINT64 typeSize, UINT64 ElementSize)
{
    UINT8 *data = NULL;
    if ((GetSystemTable()->BootServices->AllocatePool(EfiLoaderData, typeSize * ElementSize, (void **)&data)) != EFI_SUCCESS)
        data = NULL;
    return data;
}

void FreeMemory(void *element)
{
    GetSystemTable()->BootServices->FreePool(element);
}

void *AssignAndInitMemory(UINT64 typeSize, UINT64 ElementSize)
{
    UINT8 *data = NULL;
    if ((GetSystemTable()->BootServices->AllocatePool(EfiLoaderData, typeSize * ElementSize, (void **)&data)) != EFI_SUCCESS)
        return NULL;
    for (UINT64 i = 0; i < typeSize * ElementSize; i++)
        data[i] = 0;
    return data;
}

void *ResizeMemory(void *element, UINT64 originalSize, UINT64 typeSize, UINT64 ElementSize)
{
    UINT8 *data = NULL;
    UINT8 *original = (UINT8 *)element;
    if ((GetSystemTable()->BootServices->AllocatePool(EfiLoaderData, typeSize * ElementSize, (void **)&data)) != EFI_SUCCESS)
        return element;
    UINT64 limit = typeSize * ElementSize < originalSize ? typeSize * ElementSize : originalSize;
    for (UINT64 i = 0; i < limit; i++)
        data[i] = original[i];
    if (limit < typeSize * ElementSize)
    {
        for (UINT64 i = limit; i < typeSize * ElementSize; i++)
            data[i] = 0;
    }
    FreeMemory(original);
    return (void *)data;
}