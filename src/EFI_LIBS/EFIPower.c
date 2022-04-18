#include "EFIPower.h"
#include "EFICommon.h"

void COLD_REBOOT()
{
    // Hardware Reboot
    GetSystemTable()->RuntimeServices->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, 0);
}

void WARM_REBOOT()
{
    // Software reboot
    GetSystemTable()->RuntimeServices->ResetSystem(EfiResetWarm, EFI_SUCCESS, 0, 0);
}

void SHUTDOWN()
{
    // Shuts off the computer
    // NOTE : This does not work in VirtualBox.
    // WORKS in QEMU !!!
    GetSystemTable()->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, 0);
}