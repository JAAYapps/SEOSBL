#ifndef EFI_TIME_H
#define EFI_TIME_H

#include "BasicTypes.h"
#include "EFIStatus.h"

// UEFI 2.9 Specs PDF Page 258
typedef struct EFI_TIME
{
	UINT16 Year;
	UINT8 Month;
	UINT8 Day;
	UINT8 Hour;
	UINT8 Minute;
	UINT8 Second;
	UINT8 Pad1;
	UINT32 Nanosecond;
	UINT16 TimeZone;
	UINT8 DayLight;
	UINT8 Pad2;
} EFI_TIME;

// UEFI 2.9 Specs PDF Page 260
typedef struct EFI_TIME_CAPABILITIES
{
	UINT32 Resolution;
	UINT32 Accuracy;
	BOOLEAN SetsToZero;
} EFI_TIME_CAPABILITIES;

// Runtime services are services that run before and after you exit the EFI environment.
typedef EFI_STATUS (*EFI_GET_TIME)(EFI_TIME *Time, EFI_TIME_CAPABILITIES *Capabilities);
typedef EFI_STATUS (*EFI_SET_TIME)(EFI_TIME *Time);
typedef EFI_STATUS (*EFI_GET_WAKEUP_TIME)(BOOLEAN *Enabled, BOOLEAN *Pending, EFI_TIME *Time);
typedef EFI_STATUS (*EFI_SET_WAKEUP_TIME)(BOOLEAN Enable, EFI_TIME *Time);

#endif
