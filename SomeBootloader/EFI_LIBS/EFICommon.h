#pragma once
#include "..\UEFI_API\SystemTable.h"
#include "..\UEFI_API\EFIStatus.h"
#include "..\UEFI_API\EFIBasicColorTypes.h"

#define UNICODE
#define NULL (void*)0
#define DECIMAL 10
#define HEX     16
#define true    1
#define false   0

void InitUEFIServices(EFI_HANDLE IH, EFI_SYSTEM_TABLE *ST);

EFI_SYSTEM_TABLE* GetSystemTable();
EFI_BOOT_SERVICES* GetBootServices();
EFI_RUNTIME_SERVICES* GetRuntimeServices();
EFI_HANDLE GetImageHandle();
unsigned long long strlen(const char* str);
void itoa(unsigned long int n, unsigned short int* buffer, int basenumber);