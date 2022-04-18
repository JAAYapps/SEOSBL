#ifndef EFI_KEYBOARD_INPUT_H
#define EFI_KEYBOARD_INPUT_H

#include "EFICommon.h"

void HitAnyKey();

void ResetKeyboard();

BOOLEAN GetKey(CHAR16 key);

EFI_STATUS CheckKey();

#endif
