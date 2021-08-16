#pragma once
#include "EFICommon.h"

void HitAnyKey();

void ResetKeyboard();

BOOLEAN GetKey(CHAR16 key);

EFI_STATUS CheckKey();