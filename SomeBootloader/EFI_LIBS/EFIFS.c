#include "EFIFS.h"
#include "EFIScreenOut.h"
#include "../memory.h"
#include "../String.h"

EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* Volume;
EFI_FILE_PROTOCOL *RootFS;
unsigned int ENTRY_POINT;
void* OSBuffer_Handle;
void InitializeFILESYSTEM()
{
    EFI_STATUS Status;
    // To load a file, you must have a file system. EFI takes advantage of the FAT32 file system.
    SetColor(EFI_BROWN);
    Print(L"LoadedImage ... ");
    EFI_LOADED_IMAGE_PROTOCOL *LoadedImage;
    Status = GetSystemTable()->BootServices->HandleProtocol(GetImageHandle(), &EFI_LOADED_IMAGE_PROTOCOL_GUID, (void**)&LoadedImage);
    SetColor(EFI_CYAN);
    Print(CheckStandardEFIError(Status));
    
    SetColor(EFI_BROWN);
    Print(L"DevicePath ... ");
    EFI_DEVICE_PATH_PROTOCOL *DevicePath;
    Status = GetSystemTable()->BootServices->HandleProtocol(LoadedImage->DeviceHandle, &EFI_DEVICE_PATH_PROTOCOL_GUID, (void**)&DevicePath);
    SetColor(EFI_CYAN);
    Print(CheckStandardEFIError(Status));
    
    SetColor(EFI_BROWN);
    Print(L"Volume ... ");
    Status = GetSystemTable()->BootServices->HandleProtocol(LoadedImage->DeviceHandle, &EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, (void**)&Volume);
    SetColor(EFI_CYAN);
    Print(CheckStandardEFIError(Status));
    
    SetColor(EFI_BROWN);
    Print(L"RootFS ... ");
    Status = Volume->OpenVolume(Volume, &RootFS);
    SetColor(EFI_CYAN);
    Print(CheckStandardEFIError(Status));
}

EFI_FILE_PROTOCOL* GetFileHandle(CHAR16* FileName)
{
    // This opens a file from the EFI FAT32 file system volume.
    // It loads from root, so you must supply full path if the file is not in the root.
    // Example : "somefolder//myfile"  <--- Notice the double forward slash.
    SetColor(EFI_BROWN);
    Print(L"Getting File Handle ... ");
    EFI_FILE_PROTOCOL* FileHandle = NULL;
    EFI_STATUS Status = RootFS->Open(RootFS, &FileHandle, FileName, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, 0);
    SetColor(EFI_CYAN);
	if(Status == EFI_NOT_FOUND)
	{
		Print(L"\r\nWARNING : Unable to find File.\r\n\r\n");
	}
    
    return FileHandle;
}

EFI_FILE_PROTOCOL* getDirHandle(CHAR16* DirName)
{
    SetColor(EFI_BROWN);
    Print(L"Opening Directory Handle ... ");
    EFI_FILE_PROTOCOL* FileHandle = NULL;
    EFI_STATUS Status = RootFS->Open(RootFS, &FileHandle, DirName, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, EFI_FILE_DIRECTORY);
    SetColor(EFI_CYAN);
	if(Status == EFI_NOT_FOUND)
	{
		Print(L"\r\nWARNING : Unable to find Directory.\r\n\r\n");
	}
    
    return FileHandle;
}

void closeFileHandle(EFI_FILE_PROTOCOL* FileHandle)
{
    // This closes the file.
    SetColor(EFI_BROWN);
    Print(L"Closing File Handle ... ");
    EFI_STATUS Status = FileHandle->Close(FileHandle);
    SetColor(EFI_CYAN);
    Print(CheckStandardEFIError(Status));
}

void closeDirHandle(EFI_FILE_PROTOCOL* FileHandle)
{
    SetColor(EFI_BROWN);
    Print(L"Closing Directory Handle ... ");
    EFI_STATUS Status = FileHandle->Close(FileHandle);
    SetColor(EFI_CYAN);
    Print(CheckStandardEFIError(Status));
}

EFI_FILE_PROTOCOL* createFileHandle(CHAR16* FileName)
{
    SetColor(EFI_BROWN);
    Print(L"Creating File Handle ... ");
    EFI_FILE_PROTOCOL* FileHandle = NULL;
    EFI_STATUS Status = RootFS->Open(RootFS, &FileHandle, FileName, EFI_FILE_MODE_CREATE | EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, 0);
    SetColor(EFI_CYAN);
	if(Status == EFI_NOT_FOUND)
	{
		Print(L"\r\nWARNING : Unable to create file. Please check your path.\r\n\r\n");
	}
    
    return FileHandle;
}

UINTN* GetFileSize (EFI_FILE_PROTOCOL* FileName)
{
    UINTN* Size = 0;
    FileName->SetPosition(FileName, 0xFFFFFFFFFFFFFFFFULL);
    FileName->GetPosition(FileName, Size);
	FileName->SetPosition(FileName, 0);
    return Size;
}

void* readFile(CHAR16* FileName)
{
    // We create the buffer, allocate memory for it, then read
    // the file into the buffer. After which, we close the file.
	// Currently we are using a fixed size. Eventually we will fix that.
	// Currently we have a fixed Buffer Handle as well. Eventually we will fix that.

    // We get the file size, allocate memory for it,
    // read the file into the buffer, then we close the file.
    EFI_FILE_PROTOCOL* FileHandle = GetFileHandle(FileName);
    if(FileHandle != NULL)
    {
		UINT64* FileSize = (UINT64*)GetFileSize(FileHandle);
		
		Print(L"File Size : ");
		UINT16 s[4];
        itoa(*FileSize, s, DECIMAL);
        Print(s);
		Print(L"\r\n");
		
        SetColor(EFI_BROWN);
        Print(L"Allocating Pool ... ");
        EFI_STATUS Status = GetSystemTable()->BootServices->AllocatePool(EfiLoaderData, *FileSize, (void**)&OSBuffer_Handle);
        SetColor(EFI_CYAN);
        Print(CheckStandardEFIError(Status));
    
        SetColor(EFI_BROWN);
        Print(L"Reading File ... ");
        Status = FileHandle->Read(FileHandle, FileSize, OSBuffer_Handle);
        SetColor(EFI_CYAN);
        Print(CheckStandardEFIError(Status));

        SetColor(EFI_LIGHTCYAN);    
        Print((CHAR16*)L"\r\nFile Signature\r\n");
        SetColor(EFI_LIGHTRED);    
        UINT8* test2 = (UINT8*)OSBuffer_Handle;

        for(int m = 0; m < 5; m++)
        {
            int j = *test2;
            UINT16 s[2];
            itoa(j, s, HEX);
            Print(s);
            Print((CHAR16*)L"  ");
            test2++;
        }

        closeFileHandle(FileHandle);
        return OSBuffer_Handle;
    }
    else
    {
        return NULL;
    }
}

UINT64 readLoader(CHAR16* FileName)
{
	// We get the file size, allocate memory for it,
    // read the file into the buffer, then we close the file.
    EFI_FILE_PROTOCOL* FileHandle = GetFileHandle(FileName);
    if(FileHandle != NULL)
    {
		UINT64* FileSize = GetFileSize (FileHandle);

		if((GetSystemTable()->BootServices->AllocatePool(EfiLoaderData, *FileSize, (void**)&OSBuffer_Handle)) != EFI_SUCCESS)
		{
			SetColor(EFI_BROWN);
			Print(L"Allocating Pool FAILED\r\n");
		}
		
		FileHandle->SetPosition(FileHandle, 0);

        if((FileHandle->Read(FileHandle, FileSize, OSBuffer_Handle)) != EFI_SUCCESS)
		{
			SetColor(EFI_BROWN);
			Print(L"Reading File FAILED\r\n");
		}
		
		SetColor(EFI_LIGHTCYAN);    
		Print(L"Dynamic File Signature\r\n");
		SetColor(EFI_BROWN);    
		UINT8* test1 = (UINT8*)OSBuffer_Handle;
		
		// 86 64    <---- BIN
		// 45 4C 46 <---- ELF
		
		UINT8 p1,p2,p3,p4;
		p1 = *test1;
		test1+=1;
		p2 = *test1;
		test1+=1;
		p3 = *test1;
		test1+=1;
		p4 = *test1;

		if(p1 == 100 && p2 == 134)
		{
			Print(L"BINARY - 8664 Signature\r\n");
			SetColor(EFI_WHITE);
			test1+=37;
			p1 = *test1;
			test1+=1;
			p2 = *test1;
			test1+=1;
			p3 = *test1;
			test1+=1;
			p4 = *test1;

				UINT16 s[2];
				itoa(p1, s, 16);
				Print(s);
				Print(L"  ");
				
				itoa(p2, s, 16);
				Print(s);
				Print(L"  ");
				
				itoa(p3, s, 16);
				Print(s);
				Print(L"  ");
				
				itoa(p4, s, 16);
				Print(s);
				SetColor(EFI_BROWN); 
				Print(L"  \r\nENTRY POINT : ");
				SetColor(EFI_GREEN); 
				
                ENTRY_POINT = (p4 << 24) | (p3 << 16) | (p2 << 8) | p1 ;
				
				UINT16 s2[5];
				itoa(ENTRY_POINT, s2, 10);
				Print(s2);
				Print(L"  ");
		}
		else if(p2 == 69 && p3 == 76 && p4 == 70)
		{
			Print(L"ELF - 45 4C 46 Signature\r\n");
			Print(L"Add your own code + the ELF Header file to make this work.\r\n");
		} else {
			ENTRY_POINT = 0;
			Print(L"WARNING : RAW FILE HAS BEEN LOADED - No Signature DETECTED\r\nYou need to place in your entry point position into the config.");
		}
		
        closeFileHandle(FileHandle);
	    return *FileSize;
    }
	return -1;
}

unsigned int GetLoaderEntryPoint()
{
	return ENTRY_POINT;
}

UINT8* GetLoaderHandle()
{
	return (UINT8*)OSBuffer_Handle;
}

void removeDir(CHAR16* dirName)
{
	EFI_FILE_PROTOCOL* FileHandle = getDirHandle(dirName);
	if(FileHandle != NULL)
	{
		SetColor(EFI_BROWN);
		Print(L"Deleting Directory ... ");
		EFI_STATUS Status = FileHandle->Delete(FileHandle);
		SetColor(EFI_CYAN);
		Print(CheckStandardEFIError(Status));
	}
}

void makeDir(CHAR16* dirName)
{
    SetColor(EFI_BROWN);
    Print(L"Creating Directory Handle ... ");
    EFI_FILE_PROTOCOL* FileHandle = NULL;
	Print(L"Creating Directory ... ");
    EFI_STATUS Status = RootFS->Open(RootFS, &FileHandle, dirName, EFI_FILE_MODE_CREATE | EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, EFI_FILE_DIRECTORY);
    SetColor(EFI_CYAN);
    Print(CheckStandardEFIError(Status));
	closeDirHandle(FileHandle);
}

void deleteFile(CHAR16* FileName)
{
	EFI_FILE_PROTOCOL* FileHandle = GetFileHandle(FileName);
	if(FileHandle != NULL)
	{
		SetColor(EFI_BROWN);
		Print(L"Deleting File ... ");
		EFI_STATUS Status = FileHandle->Delete(FileHandle);
		SetColor(EFI_CYAN);
		Print(CheckStandardEFIError(Status));
	}
}

void WriteToFile(char* buf, CHAR16* FileName)
{
	UINT64 fileSize = strlen(buf);
	EFI_FILE_PROTOCOL* writefilehandle = createFileHandle(FileName);
	if(writefilehandle != NULL)
	{
        SetColor(EFI_BROWN);
		Print(L"Writing to File ... ");
		EFI_STATUS Status = writefilehandle->Write(writefilehandle, &fileSize, buf);
		SetColor(EFI_CYAN);
		Print(CheckStandardEFIError(Status));

		closeFileHandle(writefilehandle);
	}
}