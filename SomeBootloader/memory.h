#pragma once
#include "common.h"

BLOCKINFO InitMemoryBlock(void);

BLOCKINFO* GetBlockInfo(void);

void CopyMemoryBlock(BLOCKINFO block);

void* memcpy(void* dst, const void* src, unsigned long long size);