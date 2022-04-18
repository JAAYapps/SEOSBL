#include "Interval.h"
#include "EFICommon.h"

void Delay(UINTN d)
{
    // The Stall function is set is microseconds. So you have to convert
    // from microseconds ( µs ) to milliseconds ( ms ). EXAMPLE : 1ms = 1000µs.
    // The microsecond is the smallest unit of time measurement the EFI provides.
    GetSystemTable()->BootServices->Stall(d * 1000);
}

void Delay1()
{
    // The Stall function is set as microseconds. We stall 1 microsecond.
    GetSystemTable()->BootServices->Stall(1);
}