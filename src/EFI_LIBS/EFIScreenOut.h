#ifndef EFI_SCREEN_OUT_H
#define EFI_SCREEN_OUT_H

#include "..\UEFI_API\BasicTypes.h"
#include "EFICommon.h"

void ResetScreen();

void SetColor(UINTN Attribute);

void EfiPrint(CHAR16 *str);

void SetTextPosition(UINT32 Col, UINT32 Row);

void ClearScreen();

#endif
