#pragma once
#include "..\UEFI_API\BasicTypes.h"
#include "EFICommon.h"

void ResetScreen();

void SetColor(UINTN Attribute);

void Print(CHAR16* str);

void SetTextPosition(UINT32 Col, UINT32 Row);

void ClearScreen();