#pragma once

#include "BasicTypes.h"
#include "EFIStatus.h"

typedef struct EFI_CONFIGURATION_TABLE{ 
    EFI_GUID            VendorGuid; 
    void                *VendorTable;
} EFI_CONFIGURATION_TABLE;

typedef EFI_STATUS (*EFI_INSTALL_CONFIGURATION_TABLE)(EFI_GUID *Guid, void *Table);