#ifndef EFI_DEVICES_H
#define EFI_DEVICES_H

#include "BasicTypes.h"
#include "EFIStatus.h"

// UEFI 2.9 Specs PDF Page 291
typedef struct EFI_DEVICE_PATH_PROTOCOL
{
    UINT8 Type;
    UINT8 SubType;
    UINT8 Length[2];
} EFI_DEVICE_PATH_PROTOCOL;

typedef EFI_STATUS (*EFI_LOCATE_DEVICE_PATH)(EFI_GUID *Protocol, EFI_DEVICE_PATH_PROTOCOL **DevicePath, EFI_HANDLE *Device);

#endif
