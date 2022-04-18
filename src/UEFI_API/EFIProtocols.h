#ifndef EFI_PROTOCOL_H
#define EFI_PROTOCOL_H

#include "BasicTypes.h"
#include "EFIStatus.h"
#include "EFISearch.h"

// UEFI 2.9 Specs PDF Page 202
typedef struct EFI_OPEN_PROTOCOL_INFORMATION_ENTRY
{
    EFI_HANDLE AgentHandle;
    EFI_HANDLE ControllerHandle;
    UINT32 Attributes;
    UINT32 OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

// The GUID to set the correct Protocol.
// These GUIDs are all over the UEFI 2.9 Specs PDF.
extern struct EFI_GUID EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
extern struct EFI_GUID EFI_LOADED_IMAGE_PROTOCOL_GUID;
extern struct EFI_GUID EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
extern struct EFI_GUID EFI_DEVICE_PATH_PROTOCOL_GUID;
extern struct EFI_GUID ACPI_20_TABLE_GUID;

typedef EFI_STATUS (*EFI_OPEN_PROTOCOL)(EFI_HANDLE Handle, EFI_GUID *Protocol, void **Interface, EFI_HANDLE AgentHandle, EFI_HANDLE ControllerHandle, UINT32 Attributes);
typedef EFI_STATUS (*EFI_CLOSE_PROTOCOL)(EFI_HANDLE Handle, EFI_GUID *Protocol, EFI_HANDLE AgentHandle, EFI_HANDLE ControllerHandle);
typedef EFI_STATUS (*EFI_OPEN_PROTOCOL_INFORMATION)(EFI_HANDLE Handle, EFI_GUID *Protocol, EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **EntryBuffer, UINTN *EntryCount);
typedef EFI_STATUS (*EFI_PROTOCOLS_PER_HANDLE)(EFI_HANDLE Handle, EFI_GUID ***ProtocolBuffer, UINTN *ProtocolBufferCount);
typedef EFI_STATUS (*EFI_LOCATE_HANDLE_BUFFER)(EFI_LOCATE_SEARCH_TYPE SearchType, EFI_GUID *Protocol, void *SearchKey, UINTN *NoHandles, EFI_HANDLE **Buffer);
typedef EFI_STATUS (*EFI_LOCATE_PROTOCOL)(EFI_GUID *Protocol, void *Registration, void **Interface);

#endif
