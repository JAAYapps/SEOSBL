#pragma once

//This is the unsigned type definitions
// NOTE : CHAR16 is supposed to be Minimum of 16-Bit.
//        But on some machines it will be 32-Bit.
//        ThatOSDev included both typedefs as a means of reference.
// UEFI 2.9 Specs PDF Page 20
typedef unsigned short int  uint16_t;
typedef unsigned short int  uint_least16_t;
typedef uint_least16_t      CHAR16;

typedef unsigned char       UINT8;
typedef unsigned short      UINT16;
typedef unsigned int        UINT32;
typedef unsigned long long  UINT64;

// UINTN can be used for both 64-Bit ( 8 Bytes ) and 32-Bit ( 4 Bytes ).
// We set this for 64-Bit since this tutorial series is 64-Bit only.
// UEFI 2.9 Specs PDF Page 20
typedef unsigned long long  UINTN;

typedef unsigned char       BOOLEAN;

//This is all the signed type definitions
typedef int                 INT32;

#define NULL                (void*)0

typedef void                *EFI_HANDLE;

typedef void                *EFI_EVENT;

typedef UINT64              EFI_LBA;

typedef UINTN               EFI_TPL;

typedef UINT64              EFI_PHYSICAL_ADDRESS;

typedef UINT64              EFI_VIRTUAL_ADDRESS;

// The struct to hold our GUID data.
// UEFI 2.9 Specs PDF Page 181
typedef struct EFI_GUID
{
    UINT32    Data1;
    UINT16    Data2;
    UINT16    Data3;
    UINT8     Data4[8];
} EFI_GUID;