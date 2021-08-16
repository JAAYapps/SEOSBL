#include "EFIKeyboardInput.h"

void HitAnyKey()
{
    // This clears the keyboard buffer.
    GetSystemTable()->ConIn->Reset(GetSystemTable()->ConIn, 1);

    // We setup the struct to take keyboard input.
    EFI_INPUT_KEY Key;

    // In a while loop to see if the keyboard has a key stroke in the buffer.
    while((GetSystemTable()->ConIn->ReadKeyStroke(GetSystemTable()->ConIn, &Key)) == EFI_NOT_READY);
}

void ResetKeyboard()
{
    GetSystemTable()->ConIn->Reset(GetSystemTable()->ConIn, 1);
}

EFI_INPUT_KEY CheckKeystroke;
BOOLEAN GetKey(CHAR16 key)
{
    if(CheckKeystroke.UnicodeChar == key)
    {
        return 1;
    } else {
        return 0;
    }
}

EFI_STATUS CheckKey()
{
    return GetSystemTable()->ConIn->ReadKeyStroke(GetSystemTable()->ConIn, &CheckKeystroke);
}