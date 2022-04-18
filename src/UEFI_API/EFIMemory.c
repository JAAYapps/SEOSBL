//#include "EFIBootServices.h"
#include "EFIMemory.h"

CHAR16 *EFI_MEMORY_TYPE_STRINGS[16] =
    {
        L"EfiReservedMemoryType",
        L"EfiLoaderCode",
        L"EfiLoaderData",
        L"EfiBootServicesCode",
        L"EfiBootServicesData",
        L"EfiRuntimeServicesCode",
        L"EfiRuntimeServicesData",
        L"EfiConventionalMemory",
        L"EfiUnusableMemory",
        L"EfiACPIReclaimMemory",
        L"EfiACPIMemoryNVS",
        L"EfiMemoryMappedIO",
        L"EfiMemoryMappedIOPortSpace",
        L"EfiPalCode",
        L"EfiPersistentMemory",
        L"EfiMaxMemoryType"};