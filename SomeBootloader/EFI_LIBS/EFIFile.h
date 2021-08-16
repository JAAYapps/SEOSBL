#pragma once
#include "..\UEFI_API\EFIIO.h"

void InitializeFILESYSTEM();

EFI_FILE_PROTOCOL* openFile(CHAR16* FileName);

void WriteToFile(char* buf, CHAR16* FileName);

void closeFile(EFI_FILE_PROTOCOL* FileHandle);