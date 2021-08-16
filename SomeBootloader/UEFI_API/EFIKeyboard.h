#pragma once

#include "BasicTypes.h"
#include "EFIStatus.h"

// We are forward declaring these structs so that the function typedefs can operate.
struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

// We check for the scan code of the key with this struct
// Notice the 16-Bit interface, instead of the normal 8-Bit.
// This is because EFI uses UNICODE.
// UEFI 2.9 Specs PDF Page 448
typedef struct EFI_INPUT_KEY
{
	UINT16    ScanCode;
	UINT16    UnicodeChar;
}EFI_INPUT_KEY;

// We check for the event.
typedef void(*EFI_EVENT_NOTIFY)(EFI_EVENT Event, void *Context);

// We use this to reset the buffer.
typedef EFI_STATUS (*EFI_INPUT_RESET)(struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, BOOLEAN ExtendedVerification);

// This is where we actually read the key stroke from the keyboard buffer.
typedef EFI_STATUS (*EFI_INPUT_READ_KEY)(struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, EFI_INPUT_KEY *Key);

// The struct for the keyboard input.
// UEFI 2.9 Specs PDF Page 446
typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL
{
	EFI_INPUT_RESET        Reset;
	EFI_INPUT_READ_KEY     ReadKeyStroke;
	EFI_EVENT              WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;