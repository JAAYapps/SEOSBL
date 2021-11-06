#pragma once
#include "EFICommon.h"
#include "..\UEFI_API\EFIIO.h"

void InitializeFILESYSTEM();

EFI_FILE_PROTOCOL* GetFileHandle(CHAR16* FileName);

EFI_FILE_PROTOCOL* getDirHandle(CHAR16* DirName);

void closeFileHandle(EFI_FILE_PROTOCOL* FileHandle);

void closeDirHandle(EFI_FILE_PROTOCOL* FileHandle);

EFI_FILE_PROTOCOL* createFileHandle(CHAR16* FileName);

UINTN* GetFileSize (EFI_FILE_PROTOCOL* FileName);

void* readFile(CHAR16* FileName);

UINT64 readLoader(CHAR16* FileName);

unsigned int GetLoaderEntryPoint();

UINT8* GetLoaderHandle();

void removeDir(CHAR16* dirName);

void makeDir(CHAR16* dirName);

void deleteFile(CHAR16* FileName);

void WriteToFile(char* buf, CHAR16* FileName);