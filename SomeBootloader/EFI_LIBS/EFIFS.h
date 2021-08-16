#pragma once
#include "EFICommon.h"
#include "..\UEFI_API\EFIIO.h"

void InitializeFILESYSTEM();

EFI_FILE_PROTOCOL* openFile(CHAR16* FileName);

void closeFile(EFI_FILE_PROTOCOL* FileHandle);

void WriteToFile(char* buf, CHAR16* FileName);

EFI_FILE_PROTOCOL* createFile(CHAR16* FileName);