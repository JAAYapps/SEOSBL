#include "EFI_LIBS\EFICommon.h"
#include "EFI_LIBS\EFIScreenOut.h"
#include "EFI_LIBS\EFIKeyboardInput.h"
#include "EFI_LIBS\Graphics.h"
#include "EFI_LIBS\Interval.h"
#include "EFI_LIBS\EFIPower.h"
#include "UEFI_API\EFIIO.h"
#include "EFI_LIBS\EFIFS.h"
#include "text.h"

// Some Bootloader is a bootloader (Lol, not very original. Until I make up a name)

// This is like int main() in a typical C program.
// In this case, we create an ImageHandle for the overall EFI interface,
// as well as a System Table pointer to the EFI_SYSTEM_TABLE struct.
// UEFI 2.9 Specs PDF Page 91
EFI_STATUS efi_main(EFI_HANDLE IH, EFI_SYSTEM_TABLE *ST)
{
    InitUEFIServices(IH, ST);
    
    ResetScreen();
    
    SetColor(EFI_WHITE);
    SetTextPosition(3, 2);
    Print(L"Welcome to the UEFI From Scratch Tutorials\r\n\r\n");
    
    SetColor(EFI_GREEN);
    SetTextPosition(8, 4);
    Print(L"Hit Any Key to see Graphics, text file read, and loader code execution.");

    HitAnyKey();
    
    Print(L"\r\n\r\nLoading Graphics Output Protocol ... ");
    if(InitGraphics() == EFI_SUCCESS)
    {
        SetGraphicsColor(ORANGE);
        CreateFilledBox(50, 50, 100, 200);
        SetGraphicsColor(RED);
        CreateFilledBox(60, 60, 80, 30);
        SetColor(EFI_YELLOW);
        SetTextPosition(5, 8);
        Print(L"We have Graphics !!");
    }

    SetColor(EFI_GREEN);
    SetTextPosition(8, 4);
    Print(L"Hit Any Key to test Buffered Graphics\r\n");

    HitAnyKey();

    ClearScreen();

    if(GetGraphics() != NULL)
	{
        // Testing our new Buffer pixel Graphics
        SetGraphicsColor(ORANGE);
        CreateBufferFilledBox(10, 10, GetScreenWidth() - 100, 200);
        SetGraphicsColor(BLUE);
        CreateBufferFilledBox(20, 20, 50, 80);
        SetGraphicsColor(CYAN);
        CreateBufferFilledBox(30, 30, 70, 40);
	}

    SetColor(EFI_GREEN);
    SetTextPosition(8, 4);
    Print(L"Hit Any Key to see text file read, and loader code execution.");

    HitAnyKey();

    ClearScreen();

    InitializeFILESYSTEM();

    // We create the buffer, allocate memory for it, then read
    // the file into the buffer. After which, we close the file.
    void* OSBuffer_Handle;
    
    EFI_FILE_PROTOCOL* mytextfile = openFile(L"mytextfile.txt");
    if(mytextfile != NULL)
    {
        SetColor(EFI_BROWN);
        Print(L"AllocatingPool ... ");
        EFI_STATUS Status = GetSystemTable()->BootServices->AllocatePool(EfiLoaderData, 0x00100000, (void**)&OSBuffer_Handle);
        SetColor(EFI_CYAN);
        Print(CheckStandardEFIError(Status));
    
        UINT64 fileSize = 0x00100000;
        
        SetColor(EFI_BROWN);
        Print(L"Reading File ... ");
        Status = mytextfile->Read(mytextfile, &fileSize, OSBuffer_Handle);
        SetColor(EFI_CYAN);
        Print(CheckStandardEFIError(Status));

        closeFile(mytextfile);
    }

    Print(L"\r\n");

    // OSBuffer_Handle This is our new File Handle. We can access the file from here.
    
    SetColor(EFI_LIGHTGRAY);
    
    // What we do now is test to see what this buffer is holding.
    // The code below converts the binary code in the buffer,
    // into HEX Code. So as an exercise, see if you can figure out
    // the message without looking at the text file.
    // I included clibs.h to house the C function known as itoa().
    UINT8* test = (UINT8*)OSBuffer_Handle;
    
    int m;
    for(m = 0; m < 22; m++)
    {
        UINT8 g = *test;
        UINT16 s[2];
        itoa(g, s, HEX);
        Print(s);
        Print(L" ");
        test++;
    }

    //Get Kernel or loader file
    void* ExternalFileBuffer;

    EFI_FILE_PROTOCOL* efimyfile = openFile(L"loader.bin");

    UINT64 fsize = 0x00001000;
    EFI_STATUS Status = GetSystemTable()->BootServices->AllocatePool(EfiLoaderData, fsize, (void**)&ExternalFileBuffer);
	SetColor(EFI_BROWN);
    Print(L"AllocatePool ExternalFileBuffer");
	SetColor(EFI_LIGHTCYAN);  
    Print(CheckStandardEFIError(Status));

    efimyfile->SetPosition(efimyfile, 0);
    
    efimyfile->Read(efimyfile, &fsize, ExternalFileBuffer);
    SetColor(EFI_GREEN);
    Print(L"\r\nRead ExternalFileBuffer");
	SetColor(EFI_LIGHTCYAN);  
    Print(CheckStandardEFIError(Status));

    SetColor(EFI_LIGHTCYAN);    
    Print(L"\r\nFile Signature\r\n");
    SetColor(EFI_LIGHTRED);    
    UINT8* test2 = (UINT8*)ExternalFileBuffer;

    for(int m = 0; m < 5; m++)
    {
        int j = *test2;
        UINT16 s[2];
        itoa(j, s, HEX);
        Print(s);
        Print(L"  ");
        test2++;
    }

    Print(L"\r\n\r\n");
    
    efimyfile->SetPosition(efimyfile, 262);
    
    efimyfile->Read(efimyfile, &fsize, ExternalFileBuffer);
    SetColor(EFI_GREEN);
    Print(L"Read ExternalFileBuffer");
	SetColor(EFI_YELLOW);
    Print(CheckStandardEFIError(Status));
    
    closeFile(efimyfile);
    
    SetColor(EFI_LIGHTCYAN);    
    Print(L"\r\nEntry Point\r\n");
    SetColor(EFI_YELLOW);
    UINT8* test3 = (UINT8*)ExternalFileBuffer;
    for(int m = 0; m < 4; m++)
    {
        int j = *test3;
        UINT16 s[2];
        itoa(j, s, HEX);
        Print(s);
        Print(L"  ");
        test3++;
    }

    int (*KernelBinFile)() = ((__attribute__((ms_abi)) int (*)() ) (UINT8*)ExternalFileBuffer);
    int g = KernelBinFile();
    
    UINT16 tmp[8];
    itoa(g, tmp, 10);
	SetColor(EFI_LIGHTCYAN);
    Print(L"\r\n\r\nThe returned number is : ");
    SetColor(EFI_LIGHTMAGENTA);
    Print(tmp);
    
    SetColor(EFI_GREEN);
    SetTextPosition(8, 4);
    Print(L"Hit Any Key to display the memory map\r\n");

    HitAnyKey();

    ClearScreen();

    // Memory Map
	    
    SetColor(EFI_LIGHTGREEN);
    Print(L"******************MEMORY MAP******************\r\n\r\n");
    
    // Setup Memory Map
    UINTN                  MemoryMapSize = 0;
    EFI_MEMORY_DESCRIPTOR  *MemoryMap;
    UINTN                  MapKey;
    UINTN                  DescriptorSize;
    UINT32                 DescriptorVersion;
    
    GetSystemTable()->BootServices->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);
    MemoryMapSize += 2 * DescriptorSize;
    GetSystemTable()->BootServices->AllocatePool(EfiLoaderData, MemoryMapSize, (void **)&MemoryMap);
    GetSystemTable()->BootServices->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);

    long long MapEntries = MemoryMapSize / DescriptorSize;
    int t = (MapEntries / 2) + 1;
    UINT64 TotalRam = 0;
    for(long long i = 0; i < t; i++)
    {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((UINT64)MemoryMap + (i * DescriptorSize));
        SetColor(EFI_LIGHTCYAN);
        Print(EFI_MEMORY_TYPE_STRINGS[desc->Type]);
        SetColor(EFI_BROWN);
        Print(L" ");
        CHAR16 buf[8];
        itoa(desc->NumberOfPages * 4096 / 1024, buf, 10);
        Print(buf);
        SetColor(EFI_LIGHTGRAY);
        Print(L" KB\r\n");
        TotalRam += desc->NumberOfPages * 4096 / 1024;
    }
    
    int pos = 2;
    for(long long i = t; i < MapEntries; i++)
    {
        SetTextPosition(40, pos);
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((UINT64)MemoryMap + (i * DescriptorSize));
        SetColor(EFI_LIGHTCYAN);
        Print(EFI_MEMORY_TYPE_STRINGS[desc->Type]);
        SetColor(EFI_BROWN);
        Print(L" ");
        CHAR16 buf[8];
        itoa(desc->NumberOfPages * 4096 / 1024, buf, 10);
        Print(buf);
        SetColor(EFI_LIGHTGRAY);
        Print(L" KB");
        TotalRam += desc->NumberOfPages * 4096 / 1024;
        pos++;
    }
    
    SetColor(EFI_LIGHTGREEN);
    SetTextPosition(0, 20);
    Print(L"Total System Ram : ");
    SetColor(EFI_CYAN);
    CHAR16 tr[8];
    itoa(TotalRam, tr, 10);
    Print(tr);
    SetColor(EFI_LIGHTGRAY);
    Print(L" KBytes");

    SetColor(EFI_GREEN);
    Print(L"\nHit Any Key to see ThatOSDev's custom Font.");
    ResetKeyboard();
    HitAnyKey();

    ClearScreen();

	SetGraphicsColor(0xfff652fa);
	CreateFilledBox(5, 5, (GetScreenWidth() - 10), (GetScreenHeight() - 10));
	
	UINT32 FontSizeMin = 4;
	UINT32 FontSizeMax = 190;
	
    UINT32 ChangeSize = FontSizeMin;
	
    TestASCII(ChangeSize);

	ResetKeyboard();

    while(1)
    {
		Delay1();
		
		EFI_STATUS Status = CheckKey();
		if(Status == EFI_SUCCESS)
		{
			if(GetKey('w') == 1)
			{
				ChangeSize++;
				if(ChangeSize > FontSizeMax) {ChangeSize = FontSizeMax;}
				TestASCII(ChangeSize);
			}
			if(GetKey('s') == 1)
			{
				ChangeSize--;
				if(ChangeSize < FontSizeMin) {ChangeSize = FontSizeMin;}
				TestASCII(ChangeSize);
			}
			if (GetKey('s') != 1 && GetKey('w') != 1)
				break;
		}
	}

    ClearScreen();

    SetColor(EFI_MAGENTA);

    Print(L"\r\n");
    for(UINTN i = 0; i < 60; i++)
    {
        Delay(18);      // This is in the efi_libs folder in both the interval .h and .c files. It delays the CPU for 18 milliseconds.
        Print(L".");
    } 

    SetColor(EFI_LIGHTGRAY);
    SetTextPosition(5, 9);
    Print(L"We Delayed 18 milliseconds per dot");

    SetColor(EFI_GREEN);
    SetTextPosition(2, 23);
    Print(L"Hit q to quit | Hit r to reboot");
    
    ResetKeyboard();

    SetColor(EFI_WHITE);

	UINTN u = 0;
	unsigned int x = 5;
	BOOLEAN y = 1;

    while(1)
    {
		u++;
		if(u > 36000)   // This is 36 * 1000 ==> 36 milliseconds
		{
            Delay1();
			u = 0;
			SetTextPosition(x, 17);
			Print(L"   ...   ");
			if(y == 1)
			{
			    x++;
			} else {
				x--;
			}
			if(x < 5)
			{
				x = 5;
				y = 1;
			} else if(x > 50)
			{
				x = 50;
				y = 0;
			}
		}
        EFI_STATUS Status = CheckKey();
        if(Status == EFI_SUCCESS)
        {
 		    if(GetKey('q') == 1)
		    {
                SHUTDOWN();
		        break;
		    }
            if(GetKey('r') == 1)
            {
                COLD_REBOOT();
		        break;
            }
        }
    }

    COLD_REBOOT();

    // The EFI needs to have a 0 ( or EFI_SUCCESS ) in order to know everything is ok.
    return EFI_SUCCESS;
}
