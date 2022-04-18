#include "../includes/Tests.h"
#include "EFI_LIBS\EFICommon.h"
#include "EFI_LIBS\EFIScreenOut.h"
#include "EFI_LIBS\EFIKeyboardInput.h"
#include "EFI_LIBS\Interval.h"
#include "EFI_LIBS\EFIPower.h"
#include "UEFI_API\EFIIO.h"
#include "EFI_LIBS\EFIFS.h"
#include "../includes/Graphics.h"

void menuText()
{
    SetColor(EFI_WHITE);
    SetTextPosition(3, 2);
    Print((CHAR16 *)L"Welcome to the UEFI test menu.\r\nChoose a number that matches the\r\noption on screen.\r\n");
}

void testGraphics()
{
    ResetScreen();
    SetColor(EFI_GREEN);
    SetTextPosition(8, 4);
    Print((CHAR16 *)L"Hit Any Key to see Graphics.");

    HitAnyKey();

    if (GetGraphicsBuffer() != NULL)
    {
        // Testing our new Buffer pixel Graphics
        SetGraphicsColor(ORANGE);
        CreateBufferFilledBox(10, 10, GetScreenWidth() - 100, 200);
        SetGraphicsColor(BLUE);
        CreateBufferFilledBox(20, 20, 50, 80);
        SetGraphicsColor(CYAN);
        CreateBufferFilledBox(30, 30, 70, 40);
        SetColor(EFI_YELLOW);
        SetTextPosition(5, 8);
        Print((CHAR16 *)L"We have Graphics !!");
    }
}

void testTextFile()
{
    SetColor(EFI_GREEN);
    SetTextPosition(8, 4);
    Print((CHAR16 *)L"Hit Any Key to see text file read.");

    HitAnyKey();

    // We create the buffer, allocate memory for it, then read
    // the file into the buffer. After which, we close the file.
    void *TextBuffer_Handle;

    EFI_FILE_PROTOCOL *mytextfile = GetFileHandle((CHAR16 *)L"mytextfile.txt");
    if (mytextfile != NULL)
    {
        SetColor(EFI_BROWN);
        Print((CHAR16 *)L"AllocatingPool ... ");
        EFI_STATUS Status = GetSystemTable()->BootServices->AllocatePool(EfiLoaderData, 0x00100000, (void **)&TextBuffer_Handle);
        SetColor(EFI_CYAN);
        Print(CheckStandardEFIError(Status));

        UINT64 fileSize = 0x00100000;

        SetColor(EFI_BROWN);
        Print((CHAR16 *)L"Reading File ... ");
        Status = mytextfile->Read(mytextfile, &fileSize, TextBuffer_Handle);
        SetColor(EFI_CYAN);
        Print(CheckStandardEFIError(Status));

        closeFileHandle(mytextfile);

        Print((CHAR16 *)L"\r\n");

        // OSBuffer_Handle This is our new File Handle. We can access the file from here.

        SetColor(EFI_LIGHTGRAY);

        // What we do now is test to see what this buffer is holding.
        // The code below converts the binary code in the buffer,
        // into HEX Code. So as an exercise, see if you can figure out
        // the message without looking at the text file.
        UINT8 *test = (UINT8 *)TextBuffer_Handle;

        int m;
        for (m = 0; m < 22; m++)
        {
            UINT8 g = *test;
            UINT16 s[2];
            itoa(g, s, HEX);
            Print(s);
            Print((CHAR16 *)L" ");
            test++;
        }

        SetGraphicsColor(ORANGE);

        printf((UINT8 *)"Hello Graphical World !!!\r\nI will now display the text file that is still in memory.\r\n");

        UINT8 *textdisplaytest = (UINT8 *)TextBuffer_Handle;
        printf(textdisplaytest);

        SetColor(EFI_BROWN);
        Print((CHAR16 *)L"Freeing Pool ... ");
        EFI_STATUS Status = GetSystemTable()->BootServices->FreePool(TextBuffer_Handle);
        SetColor(EFI_CYAN);
        Print(CheckStandardEFIError(Status));
    }
    else
    {
        SetColor(EFI_BROWN);
        Print((CHAR16 *)L"Yeah, the text file is missing... ¯\\_(ツ)_/¯\r\n");
    }

    HitAnyKey();
}

void testKernelLoading()
{
    // Get Kernel or loader file
    void *ExternalFileBuffer;

    EFI_FILE_PROTOCOL *efimyfile = GetFileHandle((CHAR16 *)L"testloader.bin");

    UINT64 fsize = 0x00001000;
    EFI_STATUS Status = GetSystemTable()->BootServices->AllocatePool(EfiLoaderData, fsize, (void **)&ExternalFileBuffer);
    SetColor(EFI_BROWN);
    Print((CHAR16 *)L"AllocatePool ExternalFileBuffer");
    SetColor(EFI_LIGHTCYAN);
    Print((CHAR16 *)CheckStandardEFIError(Status));

    efimyfile->SetPosition(efimyfile, 0);

    efimyfile->Read(efimyfile, &fsize, ExternalFileBuffer);
    SetColor(EFI_GREEN);
    Print((CHAR16 *)L"\r\nRead ExternalFileBuffer");
    SetColor(EFI_LIGHTCYAN);
    Print((CHAR16 *)CheckStandardEFIError(Status));

    SetColor(EFI_LIGHTCYAN);
    Print((CHAR16 *)L"\r\nFile Signature\r\n");
    SetColor(EFI_LIGHTRED);
    UINT8 *test2 = (UINT8 *)ExternalFileBuffer;

    for (int m = 0; m < 5; m++)
    {
        int j = *test2;
        UINT16 s[2];
        itoa(j, s, HEX);
        Print(s);
        Print((CHAR16 *)L"  ");
        test2++;
    }

    Print((CHAR16 *)L"\r\n\r\n");

    efimyfile->SetPosition(efimyfile, 260);

    efimyfile->Read(efimyfile, &fsize, ExternalFileBuffer);
    SetColor(EFI_GREEN);
    Print((CHAR16 *)L"Read ExternalFileBuffer");
    SetColor(EFI_YELLOW);
    Print((CHAR16 *)CheckStandardEFIError(Status));

    closeFileHandle(efimyfile);

    SetColor(EFI_LIGHTCYAN);
    Print((CHAR16 *)L"\r\nEntry Point\r\n");
    SetColor(EFI_YELLOW);
    UINT8 *test3 = (UINT8 *)ExternalFileBuffer;
    for (int m = 0; m < 4; m++)
    {
        int j = *test3;
        UINT16 s[2];
        itoa(j, s, HEX);
        Print(s);
        Print((CHAR16 *)L"  ");
        test3++;
    }

    int (*KernelBinFile)() = ((__attribute__((ms_abi)) int (*)())(UINT8 *)ExternalFileBuffer);
    int g = KernelBinFile();

    UINT16 tmp[8];
    itoa(g, tmp, 10);
    SetColor(EFI_LIGHTCYAN);
    Print((CHAR16 *)L"\r\n\r\nThe returned number is : ");
    SetColor(EFI_LIGHTMAGENTA);
    Print(tmp);

    HitAnyKey();
}

void testMemoryMap()
{
    SetColor(EFI_GREEN);
    SetTextPosition(8, 4);
    Print((CHAR16 *)L"Hit Any Key to display the memory map\r\n");

    HitAnyKey();

    ClearScreen();

    // Memory Map

    SetColor(EFI_LIGHTGREEN);
    Print((CHAR16 *)L"******************MEMORY MAP******************\r\n\r\n");

    // Setup Memory Map
    UINTN MemoryMapSize = 0;
    EFI_MEMORY_DESCRIPTOR *MemoryMap;
    UINTN MapKey;
    UINTN DescriptorSize;
    UINT32 DescriptorVersion;

    GetSystemTable()->BootServices->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);
    MemoryMapSize += 2 * DescriptorSize;
    GetSystemTable()->BootServices->AllocatePool(EfiLoaderData, MemoryMapSize, (void **)&MemoryMap);
    GetSystemTable()->BootServices->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);

    long long MapEntries = MemoryMapSize / DescriptorSize;
    int t = (MapEntries / 2) + 1;
    UINT64 TotalRam = 0;
    for (long long i = 0; i < t; i++)
    {
        EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)((UINT64)MemoryMap + (i * DescriptorSize));
        SetColor(EFI_LIGHTCYAN);
        Print((CHAR16 *)EFI_MEMORY_TYPE_STRINGS[desc->Type]);
        SetColor(EFI_BROWN);
        Print((CHAR16 *)L" ");
        CHAR16 buf[8];
        itoa(desc->NumberOfPages * 4096 / 1024, buf, 10);
        Print((CHAR16 *)buf);
        SetColor(EFI_LIGHTGRAY);
        Print((CHAR16 *)L" KB\r\n");
        TotalRam += desc->NumberOfPages * 4096 / 1024;
    }

    int pos = 2;
    for (long long i = t; i < MapEntries; i++)
    {
        SetTextPosition(40, pos);
        EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)((UINT64)MemoryMap + (i * DescriptorSize));
        SetColor(EFI_LIGHTCYAN);
        Print(EFI_MEMORY_TYPE_STRINGS[desc->Type]);
        SetColor(EFI_BROWN);
        Print((CHAR16 *)L" ");
        CHAR16 buf[8];
        itoa(desc->NumberOfPages * 4096 / 1024, buf, 10);
        Print((CHAR16 *)buf);
        SetColor(EFI_LIGHTGRAY);
        Print((CHAR16 *)L" KB");
        TotalRam += desc->NumberOfPages * 4096 / 1024;
        pos++;
    }

    SetColor(EFI_LIGHTGREEN);
    SetTextPosition(0, 20);
    Print((CHAR16 *)L"Total System Ram : ");
    SetColor(EFI_CYAN);
    CHAR16 tr[8];
    itoa(TotalRam, tr, 10);
    Print((CHAR16 *)tr);
    SetColor(EFI_LIGHTGRAY);
    Print((CHAR16 *)L" KBytes");

    Print((CHAR16 *)L"\r\n");

    HitAnyKey();
}

void testFileSystemFunctions()
{
    SetColor(EFI_GREEN);
    Print((CHAR16 *)L"Hit Any Key to create a directory, write to a file,\r\n");
    Print((CHAR16 *)L"Read the new file in the folder, and display file size.\r\n");
    Print((CHAR16 *)L"Then we just delete the file and directory in that order.\r\n");

    HitAnyKey();

    ClearScreen();

    makeDir(u"MyTest");

    WriteToFile("This is where the file in the ourOS folder is!", u"MyTest\\test.txt");

    UINT64 size = 0;
    readFile(u"MyTest\\test.txt", &size);

    deleteFile(u"MyTest\\test.txt");

    removeDir(u"MyTest");

    HitAnyKey();
}

void testFont()
{
    SetColor(EFI_GREEN);
    Print((CHAR16 *)L"\nHit Any Key to see a custom Font.");
    HitAnyKey();

    SetGraphicsColor(0xfff652fa);
    CreateBufferFilledBox(5, 5, (GetScreenWidth() - 10), (GetScreenHeight() - 10));

    UINT32 FontSizeMin = 4;
    UINT32 FontSizeMax = 190;

    UINT32 ChangeSize = FontSizeMin;

    TestASCII(ChangeSize);

    while (1)
    {
        Delay1();

        EFI_STATUS Status = CheckKey();
        if (Status == EFI_SUCCESS)
        {
            if (GetKey('w') == 1)
            {
                ChangeSize++;
                if (ChangeSize > FontSizeMax)
                {
                    ChangeSize = FontSizeMax;
                }
                TestASCII(ChangeSize);
            }
            if (GetKey('s') == 1)
            {
                ChangeSize--;
                if (ChangeSize < FontSizeMin)
                {
                    ChangeSize = FontSizeMin;
                }
                TestASCII(ChangeSize);
            }
            if (GetKey('s') != 1 && GetKey('w') != 1)
                break;
        }
    }

    ClearScreen();

    SetGraphicsColor(WHITE);
    SetCursorPosition(50, 100);
    SetFontSpacing(2);
    SetFontSize(8);

    printf((UINT8 *)"And now, text using the font!!!\r\n");

    SetGraphicsColor(GREEN);
    SetFontSize(5);

    printf((UINT8 *)"\r\nIt is good to have a font.\r\n");

    HitAnyKey();
}

void testCPUPausing()
{
    SetColor(EFI_MAGENTA);

    Print(L"\r\n");
    for (UINTN i = 0; i < 60; i++)
    {
        Delay(18); // This is in the efi_libs folder in both the interval .h and .c files. It delays the CPU for 18 milliseconds.
        Print((CHAR16 *)L".");
    }

    SetColor(EFI_LIGHTGRAY);
    SetTextPosition(5, 9);
    Print((CHAR16 *)L"We Delayed 18 milliseconds per dot");
}

void optionCheck()
{
    while (1)
    {
        Delay1();

        ResetScreen();

        menuText();

        if (CheckKey() == EFI_SUCCESS)
        {
            if (GetKey('1') == 1)
            {
                testGraphics();
            }
            if (GetKey('2') == 1)
            {
                testTextFile();
            }
            if (GetKey('3') == 1)
            {
                testKernelLoading();
            }
            if (GetKey('4') == 1)
            {
                testFont();
            }
            if (GetKey('5') == 1)
            {
                testCPUPausing();
            }
            if (GetKey('q') == 1)
            {
                SHUTDOWN();
                break;
            }
            if (GetKey('r') == 1)
            {
                COLD_REBOOT();
                break;
            }
            ResetKeyboard();
        }
    }
}

void testMenu()
{
    ResetScreen();

    optionCheck();
}