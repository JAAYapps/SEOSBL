#include "EFICommon.h"

EFI_HANDLE gIH;
EFI_SYSTEM_TABLE *gST;
void InitUEFIServices(EFI_HANDLE IH, EFI_SYSTEM_TABLE *ST)
{
    // Setup these as global variables in the EFICommon.h file.
    gIH = IH;
    gST = ST;
}

EFI_SYSTEM_TABLE* GetSystemTable()
{
    return gST;
}

EFI_BOOT_SERVICES* GetBootServices()
{
    return gST->BootServices;
}

EFI_RUNTIME_SERVICES* GetRuntimeServices()
{
    return gST->RuntimeServices;
}

EFI_HANDLE GetImageHandle()
{
    return gIH;
}

// From the GNU-EFI
INTN RtCompareGuid(EFI_GUID* Guid1, EFI_GUID* Guid2)
{
    INT32 *g1, *g2, r;
    g1 = (INT32 *) Guid1;
    g2 = (INT32 *) Guid2;
    r  = g1[0] - g2[0];
    r |= g1[1] - g2[1];
    r |= g1[2] - g2[2];
    r |= g1[3] - g2[3];
    return r;
}

INTN CompareGuid(EFI_GUID* Guid1, EFI_GUID* Guid2)
{
    return RtCompareGuid (Guid1, Guid2);
}