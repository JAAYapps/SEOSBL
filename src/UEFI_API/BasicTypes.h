#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H

#include "../../Common-Code-For-C-Projects/common.h"

// This is the unsigned type definitions
//  NOTE : CHAR16 is supposed to be Minimum of 16-Bit.
//         But on some machines it will be 32-Bit.
//         Both typedefs are here as a means of reference.
//  UEFI 2.9 Specs PDF Page 20
typedef unsigned short int uint16_t;
typedef unsigned short int uint_least16_t;
typedef uint_least16_t CHAR16;

// UINTN can be used for both 64-Bit ( 8 Bytes ) and 32-Bit ( 4 Bytes ).
// Set this for 64-Bit since the goal is to not use 32-bit.
// UEFI 2.9 Specs PDF Page 20
typedef unsigned long long UINTN;

typedef long long INTN;

typedef unsigned char BOOLEAN;

// This is all the signed type definitions
typedef int INT32;

typedef void *EFI_HANDLE;

typedef void *EFI_EVENT;

typedef UINT64 EFI_LBA;

typedef UINTN EFI_TPL;

typedef UINT64 EFI_PHYSICAL_ADDRESS;

typedef UINT64 EFI_VIRTUAL_ADDRESS;

// The struct to hold our GUID data.
// UEFI 2.9 Specs PDF Page 181
typedef struct EFI_GUID
{
    UINT32 Data1;
    UINT16 Data2;
    UINT16 Data3;
    UINT8 Data4[8];
} EFI_GUID;

#endif
