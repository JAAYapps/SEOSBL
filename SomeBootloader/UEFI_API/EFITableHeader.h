#pragma once
#include "BasicTypes.h"

// This is the main EFI header for all of the EFI.
// UEFI 2.9 Specs PDF Page 93
typedef struct EFI_TABLE_HEADER
{
    UINT64    Signature;
    UINT32    Revision;
    UINT32    HeaderSize;
    UINT32    CRC32;
    UINT32    Reserved;
} EFI_TABLE_HEADER;