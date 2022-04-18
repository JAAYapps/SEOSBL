#ifndef EFI_RUNTIME_SERVICES_H
#define EFI_RUNTIME_SERVICES_H

#include "BasicTypes.h"
#include "EFITableHeader.h"
#include "EFITime.h"
#include "EFIMemoryAllocater.h"
#include "EFICapsule.h"

#define EFI_RUNTIME_SERVICES_SIGNATURE 0x56524553544e5552
#define EFI_RUNTIME_SERVICES_REVISION EFI_SPECIFICATION_VERSION

#define EFI_RT_PROPERTIES_TABLE_GUID                                                   \
    {                                                                                  \
        0xeb66918a, 0x7eef, 0x402a, { 0x84, 0x2e, 0x93, 0x1d, 0x21, 0xc3, 0x8a, 0xe9 } \
    }
typedef struct
{
    uint16_t Version;
    uint16_t Length;
    UINT32 RuntimeServicesSupported;
} EFI_RT_PROPERTIES_TABLE;

#define EFI_RT_PROPERTIES_TABLE_VERSION 0x1

#define EFI_RT_SUPPORTED_GET_TIME 0x0001
#define EFI_RT_SUPPORTED_SET_TIME 0x0002
#define EFI_RT_SUPPORTED_GET_WAKEUP_TIME 0x0004
#define EFI_RT_SUPPORTED_SET_WAKEUP_TIME 0x0008
#define EFI_RT_SUPPORTED_GET_VARIABLE 0x0010
#define EFI_RT_SUPPORTED_GET_NEXT_VARIABLE_NAME 0x0020
#define EFI_RT_SUPPORTED_SET_VARIABLE 0x0040
#define EFI_RT_SUPPORTED_SET_VIRTUAL_ADDRESS_MAP 0x0080
#define EFI_RT_SUPPORTED_CONVERT_POINTER 0x0100
#define EFI_RT_SUPPORTED_GET_NEXT_HIGH_MONOTONIC_COUNT 0x0200
#define EFI_RT_SUPPORTED_RESET_SYSTEM 0x0400
#define EFI_RT_SUPPORTED_UPDATE_CAPSULE 0x0800
#define EFI_RT_SUPPORTED_QUERY_CAPSULE_CAPABILITIES 0x1000
#define EFI_RT_SUPPORTED_QUERY_VARIABLE_INFO 0x2000

typedef EFI_STATUS (*EFI_CONVERT_POINTER)(UINTN DebugDisposition, void **Address);
typedef EFI_STATUS (*EFI_QUERY_VARIABLE_INFO)(UINT32 Attributes, UINT64 *MaximumVariableStorageSize, UINT64 *RemainingVariableStorageSize, UINT64 *MaximumVariableSize);
typedef EFI_STATUS (*EFI_GET_VARIABLE)(CHAR16 *VariableName, EFI_GUID *VendorGuid, UINT32 *Attributes, UINTN *DataSize, void *Data);
typedef EFI_STATUS (*EFI_GET_NEXT_VARIABLE_NAME)(UINTN *VariableNameSize, CHAR16 *VariableName, EFI_GUID *VendorGuid);
typedef EFI_STATUS (*EFI_SET_VARIABLE)(CHAR16 *VariableName, EFI_GUID *VendorGuid, UINT32 Attributes, UINTN DataSize, void *Data);
typedef EFI_STATUS (*EFI_GET_NEXT_HIGH_MONO_COUNT)(UINT32 *HighCount);

typedef struct EFI_RUNTIME_SERVICES
{
    EFI_TABLE_HEADER Hdr;
    //
    // Time Services
    //
    EFI_GET_TIME GetTime;
    EFI_SET_TIME SetTime;
    EFI_GET_WAKEUP_TIME GetWakeupTime;
    EFI_SET_WAKEUP_TIME SetWakeupTime;
    //
    // Virtual Memory Services
    //
    EFI_SET_VIRTUAL_ADDRESS_MAP SetVirtualAddressMap;
    EFI_CONVERT_POINTER ConvertPointer;
    //
    // Variable Services
    //
    EFI_GET_VARIABLE GetVariable;
    EFI_GET_NEXT_VARIABLE_NAME GetNextVariableName;
    EFI_SET_VARIABLE SetVariable;
    //
    // Miscellaneous Services
    //
    EFI_GET_NEXT_HIGH_MONO_COUNT GetNextHighMonotonicCount;
    EFI_RESET_SYSTEM ResetSystem;
    //
    // UEFI 2.0 Capsule Services
    //
    EFI_UPDATE_CAPSULE UpdateCapsule;
    EFI_QUERY_CAPSULE_CAPABILITIES QueryCapsuleCapabilities;
    //
    // Miscellaneous UEFI 2.0 Service
    //
    EFI_QUERY_VARIABLE_INFO QueryVariableInfo;
} EFI_RUNTIME_SERVICES;

#endif
