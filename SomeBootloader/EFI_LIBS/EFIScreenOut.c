#include "EFIScreenOut.h"

void ResetScreen()
{
    // This resets the whole console ( A.K.A. your display screen ) interface.
    GetSystemTable()->ConOut->Reset(GetSystemTable()->ConOut, 1);
}

void SetColor(UINTN Attribute)
{
    // We set the color for the text output.
    GetSystemTable()->ConOut->SetAttribute(GetSystemTable()->ConOut, Attribute);
}

void Print(CHAR16* str)
{
    // Text Output  ( A.K.A. ConOut is Console Out )
    GetSystemTable()->ConOut->OutputString(GetSystemTable()->ConOut, str);
}

void SetTextPosition(UINT32 Col, UINT32 Row)
{
    // Sets the Column and Row of the text screen cursor position.
    GetSystemTable()->ConOut->SetCursorPosition(GetSystemTable()->ConOut, Col, Row);
}

void ClearScreen()
{
    // This clears the screen buffer, but does not reset it.
    GetSystemTable()->ConOut->ClearScreen(GetSystemTable()->ConOut);
}