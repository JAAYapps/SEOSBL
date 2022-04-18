#ifndef SEOSBLMemory
#define SEOSBLMemory
#include "SEOSBLCommon.h"

BLOCKINFO InitMemoryBlock(void);

BLOCKINFO *GetBlockInfo(void);

void CopyMemoryBlock(BLOCKINFO block);

UINT64 GetMemoryMapEntries(void);

UINT64 GetMaxMemorySize(void);

#endif // SEOSBLMemory
