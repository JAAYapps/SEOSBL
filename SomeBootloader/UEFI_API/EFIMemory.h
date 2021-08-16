#pragma once
#include "BasicTypes.h"

CHAR16* EFI_MEMORY_TYPE_STRINGS[16];

// UEFI 2.9 Specs PDF Page 163 - 168 ( BEFORE / AFTER BOOT EXIT )
typedef enum EFI_MEMORY_TYPE
{
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiPersistentMemory,
    EfiUnacceptedMemoryType,
    EfiMaxMemoryType
} EFI_MEMORY_TYPE;

// UEFI 2.9 Specs PDF Page 166
typedef enum EFI_ALLOCATE_TYPE
{
    AllocateAnyPages,
    AllocateMaxAddress,
    AllocateAddress,
    MaxAllocateType
} EFI_ALLOCATE_TYPE;

// UEFI 2.9 Specs PDF Page 170
typedef struct EFI_MEMORY_DESCRIPTOR
{
    UINT32                   Type;
    EFI_PHYSICAL_ADDRESS     PhysicalStart;
    EFI_VIRTUAL_ADDRESS      VirtualStart;
    UINT64                   NumberOfPages;
    UINT64                   Attribute;
} EFI_MEMORY_DESCRIPTOR;

/**********************************************
 *  EFI_MEMORY_ATTRIBUTES_TABLE
 **********************************************/
typedef struct { 
    UINT32          Version; 
    UINT32          NumberOfEntries; 
    UINT32          DescriptorSize ; 
    UINT32          Reserved; 
    // EFI_MEMORY_DESCRIPTOR   Entry [1];
} EFI_MEMORY_ATTRIBUTES_TABLE;

typedef EFI_STATUS (*EFI_COPY_MEM)(void *Destination, void *Source, UINTN Length);
typedef EFI_STATUS (*EFI_SET_MEM)(void *Buffer, UINTN Size, UINT8 Value);