#pragma once
#include "..\UEFI_API\SystemTable.h"
#include "..\UEFI_API\EFIStatus.h"
#include "..\UEFI_API\EFIBasicColorTypes.h"
#include "..\common.h"

#define UNICODE
#define DECIMAL 10
#define HEX     16

void InitUEFIServices(EFI_HANDLE IH, EFI_SYSTEM_TABLE *ST);

EFI_SYSTEM_TABLE* GetSystemTable();
EFI_BOOT_SERVICES* GetBootServices();
EFI_RUNTIME_SERVICES* GetRuntimeServices();
EFI_HANDLE GetImageHandle();

// From the GNU-EFI
INTN RtCompareGuid(EFI_GUID* Guid1, EFI_GUID* Guid2);

INTN CompareGuid(EFI_GUID* Guid1, EFI_GUID* Guid2);