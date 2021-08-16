#include "EFIFile.h"
#include "EFICommon.h"
#include "..\UEFI_API\EFIBasicColorTypes.h"
#include "..\UEFI_API\EFIDevices.h"

EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *Volume;
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
}

EFI_FILE_PROTOCOL* openFile(CHAR16* FileName)
{
    // This opens a file from the EFI FAT32 file system volume.
    // It loads from root, so you must supply full path if the file is not in the root.
    // Example : "somefolder//myfile"  <--- Notice the double forward slash.
    EFI_STATUS Status;
    SetColor(EFI_BROWN);
    Print(L"RootFS ... ");
    EFI_FILE_PROTOCOL* RootFS;
    Status = Volume->OpenVolume(Volume, &RootFS);
    SetColor(EFI_CYAN);
    Print(CheckStandardEFIError(Status));
    
    SetColor(EFI_BROWN);
    Print(L"Opening File ... ");
    EFI_FILE_PROTOCOL* FileHandle = NULL;
    Status = RootFS->Open(RootFS, &FileHandle, FileName, 0x0000000000000001, 0);
    SetColor(EFI_CYAN);
    Print(CheckStandardEFIError(Status));
    
    return FileHandle;
}

void closeFile(EFI_FILE_PROTOCOL* FileHandle)
{
    // This closes the file.
    EFI_STATUS Status;
    SetColor(EFI_BROWN);
    Print(L"Closing File ... ");
    Status = FileHandle->Close(FileHandle);
    SetColor(EFI_CYAN);
    Print(CheckStandardEFIError(Status));
}

void WriteToFile(char* buf, CHAR16* FileName)
{
	UINT64 fileSize = strlen(buf);
	EFI_FILE_PROTOCOL* writefilehandle = createFile(FileName);
	if(writefilehandle != NULL)
	{
        SetColor(EFI_BROWN);
		Print(L"Writing to File ... ");
		EFI_STATUS Status = writefilehandle->Write(writefilehandle, &fileSize, buf);
		SetColor(EFI_CYAN);
		Print(CheckStandardEFIError(Status));

		closeFile(writefilehandle);
	}
}