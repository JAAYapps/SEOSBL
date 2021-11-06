#include "EFI_LIBS\EFICommon.h"
#include "EFI_LIBS\EFIScreenOut.h"
#include "EFI_LIBS\EFIKeyboardInput.h"
#include "EFI_LIBS\Interval.h"
#include "EFI_LIBS\EFIPower.h"
#include "UEFI_API\EFIIO.h"
#include "EFI_LIBS\EFIFS.h"
#include "common.h"
#include "text.h"
#include "Graphics.h"
#include "memory.h"
#include "GDT.h"
#include "Date.h"
#include "String.h"

// Some Bootloader is a bootloader (Lol, not very original. Until I make up a name)

// This is like int main() in a typical C program.
// In this case, we create an ImageHandle for the overall EFI interface,
// as well as a System Table pointer to the EFI_SYSTEM_TABLE struct.
// UEFI 2.9 Specs PDF Page 91
EFI_STATUS efi_main(EFI_HANDLE IH, EFI_SYSTEM_TABLE *ST)
{
    InitUEFIServices(IH, ST);
    
    InitGraphics();

    InitializeFILESYSTEM();

    BLOCKINFO bi = InitMemoryBlock();

    ClearScreen();

    TextInit();

    bi.LoaderFileSize = readLoader(u"SEOSBL\\loader.bin");

    UINT16 GOPINFO[12];
    
	Print(L"\r\n\r\n");
	SetColor(EFI_WHITE);
    Print(L"BaseAddress       : ");
	SetColor(EFI_YELLOW);
    Print(L"0x");
    itoa(*(unsigned long int*)&bi.BaseAddress, GOPINFO, HEX);
    Print(GOPINFO);
    Print(L"\r\n");
    
    SetColor(EFI_WHITE);
    Print(L"BufferSize        : ");
    SetColor(EFI_YELLOW);
    Print(L"0x");
    itoa(bi.BufferSize, GOPINFO, HEX);
    SetColor(EFI_YELLOW);
    Print(GOPINFO);
    Print(L"\r\n");

    SetColor(EFI_WHITE);
    Print(L"Width             : ");
    itoa(bi.ScreenWidth, GOPINFO, DECIMAL);
    SetColor(EFI_YELLOW);
    Print(GOPINFO);
    Print(L"\r\n");
    
    SetColor(EFI_WHITE);
    Print(L"Height            : ");
    itoa(bi.ScreenHeight, GOPINFO, DECIMAL);
    SetColor(EFI_YELLOW);
    Print(GOPINFO);
    Print(L"\r\n");

    SetColor(EFI_WHITE);
    Print(L"PixelsPerScanLine : ");
    itoa(bi.PixelsPerScanLine, GOPINFO, DECIMAL);
    SetColor(EFI_YELLOW);
    Print(GOPINFO);
	
	SetColor(EFI_CYAN);
	Print(L"\r\n\r\nDATE ");
	SetColor(EFI_WHITE);
	Print(L": ");
	EFI_TIME Time;
	GetSystemTable()->RuntimeServices->GetTime(&Time, NULL);
	
	CHAR16 snum[4];
	SetColor(EFI_YELLOW);
	Print(GetMonth(Time.Month));
	SetColor(EFI_LIGHTRED);
	Print(L" / ");
	SetColor(EFI_YELLOW);
	itoa(Time.Day, snum, DECIMAL);
	Print(snum);
	Print(GetDayExtension(Time.Day));
	SetColor(EFI_LIGHTRED);
    Print(L" / ");
	SetColor(EFI_YELLOW);
	itoa(Time.Year, snum, DECIMAL);
	Print(snum);
	Print(L"\r\n\r\n");
	
	UINT8* loader = GetLoaderHandle();
	
	SetColor(EFI_WHITE);
    Print(L"LOADER FILE SIZE : ");
    itoa(*(unsigned long int*)&bi.LoaderFileSize, GOPINFO, DECIMAL);
    SetColor(EFI_YELLOW);
    Print(GOPINFO);
	SetColor(EFI_CYAN);
    Print(L" Bytes\r\n\r\n");

	SetColor(EFI_WHITE);
    Print(L"Loading SEOSBL ...");
	
    UINTN                  MemoryMapSize = 0;
    EFI_MEMORY_DESCRIPTOR  *MemoryMap;
    UINTN                  MapKey;
    UINTN                  DescriptorSize;
    UINT32                 DescriptorVersion;
    
    GetSystemTable()->BootServices->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);
    MemoryMapSize += 2 * DescriptorSize;
    GetSystemTable()->BootServices->AllocatePool(2, MemoryMapSize, (void **)&MemoryMap);
    GetSystemTable()->BootServices->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);

    // We look for the Root System Description Pointer ( RSDP )
	// https://wiki.osdev.org/RSDP
	// ACPI Specs PDF Page 140 Section 5.2.5.2
    EFI_CONFIGURATION_TABLE* configTable = GetSystemTable()->ConfigurationTable;
	unsigned long long* tempRSDP = NULL;
	for(UINTN index = 0; index < GetSystemTable()->NumberOfTableEntries; index++)
	{
		if(CompareGuid(&configTable[index].VendorGuid, &ACPI_20_TABLE_GUID))
		{
			if(strcmp((char*)"RSD PTR ", (char*)configTable->VendorTable) == 1)
			{
				tempRSDP = (void*)configTable->VendorTable;
			}
		}
		configTable++;
	}

	void (*KernelBinFile)(BLOCKINFO*) = ((__attribute__((ms_abi)) void (*)(BLOCKINFO*)) &loader[GetLoaderEntryPoint()]);
	
	bi.MMap = (MEMORY_DESCRIPTOR*)MemoryMap;
	bi.MMapSize = MemoryMapSize;
	bi.MMapDescriptorSize = DescriptorSize;
	bi.rsdp = tempRSDP;
	
    GetSystemTable()->BootServices->ExitBootServices(GetImageHandle(), MapKey);
	
	gdt_init();
	
    SetGraphicsColor(BLUE);
    //printf(loader);
    KernelBinFile(&bi);

    while(1){__asm__ ("hlt");}

    // The EFI needs to have a 0 ( or EFI_SUCCESS ) in order to know everything is ok.
    //However, this should not reach the return. The hlt is supposed to stop the cpu from running any further.
    return EFI_SUCCESS;
}
