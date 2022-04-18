#ifndef EFI_POWER_OPTIONS_H
#define EFI_POWER_OPTIONS_H

#include "EFIStatus.h"

// How we reboot the computer.
// UEFI 2.9 Specs PDF Page 269
typedef enum EFI_RESET_TYPE
{
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown,
    EfiResetPlatformSpecific
} EFI_RESET_TYPE;

typedef EFI_STATUS (*EFI_RESET_SYSTEM)(EFI_RESET_TYPE ResetType, EFI_STATUS ResetStatus, UINTN DataSize, void *ResetData);

#endif
