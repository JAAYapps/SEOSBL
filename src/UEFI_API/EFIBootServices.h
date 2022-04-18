#ifndef EFI_BOOT_SERVICES_H
#define EFI_BOOT_SERVICES_H

#include "EFITableHeader.h"
#include "EFIStatus.h"
#include "EFIDevices.h"
#include "EFIMemoryAllocater.h"
#include "EFIProtocols.h"
#include "EFIConfigTable.h"
#include "EFIInterfaces.h"
#include "EFITimer.h"

#define EFI_BOOT_SERVICES_SIGNATURE 0x56524553544f4f42
#define EFI_BOOT_SERVICES_REVISION EFI_SPECIFICATION_VERSION

typedef void *EFI_EVENT;

struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
struct EFI_BOOT_SERVICES;
struct EFI_GRAPHICS_OUTPUT_PROTOCOL;
struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;
struct EFI_FILE_PROTOCOL;

// We check for the event.
typedef void (*EFI_EVENT_NOTIFY)(EFI_EVENT Event, void *Context);
typedef EFI_STATUS (*EFI_REGISTER_PROTOCOL_NOTIFY)(EFI_GUID *Protocol, EFI_EVENT Event, void **Registration);
typedef EFI_STATUS (*EFI_CREATE_EVENT)(UINT32 Type, EFI_TPL NotifyTpl, EFI_EVENT_NOTIFY NotifyFunction, void *NotifyContext, EFI_GUID *EventGroup, EFI_EVENT *Event);
typedef EFI_STATUS (*EFI_CREATE_EVENT_EX)(UINT32 Type, EFI_TPL NotifyTpl, EFI_EVENT_NOTIFY NotifyFunction, void *NotifyContext, EFI_GUID *EventGroup, EFI_EVENT *Event);

typedef EFI_STATUS (*EFI_RAISE_TPL)(EFI_TPL NewTpl);
typedef EFI_STATUS (*EFI_RESTORE_TPL)(EFI_TPL OldTpl);

typedef EFI_STATUS (*EFI_IMAGE_LOAD)(BOOLEAN BootPolicy, EFI_HANDLE ParentImageHandle, EFI_DEVICE_PATH_PROTOCOL *DevicePath, void *SourceBuffer, UINTN SourceSize, EFI_HANDLE *ImageHandle);
typedef EFI_STATUS (*EFI_IMAGE_START)(EFI_HANDLE ImageHandle, UINTN *ExitDataSize, CHAR16 **ExitData);
typedef EFI_STATUS (*EFI_EXIT)(EFI_HANDLE ImageHandle, EFI_STATUS ExitStatus, UINTN ExitDataSize, CHAR16 *ExitData);
typedef EFI_STATUS (*EFI_IMAGE_UNLOAD)(EFI_HANDLE ImageHandle);
typedef EFI_STATUS (*EFI_EXIT_BOOT_SERVICES)(EFI_HANDLE ImageHandle, UINTN MapKey);

typedef EFI_STATUS (*EFI_GET_NEXT_MONOTONIC_COUNT)(UINT64 *Count);

typedef EFI_STATUS (*EFI_STALL)(UINTN Microseconds);
typedef EFI_STATUS (*EFI_SET_WATCHDOG_TIMER)(UINTN Timeout, UINT64 WatchdogCode, UINTN DataSize, CHAR16 *WatchdogData);

typedef EFI_STATUS (*EFI_CONNECT_CONTROLLER)(EFI_HANDLE ControllerHandle, EFI_HANDLE *DriverImageHandle, EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath, BOOLEAN Recursive);
typedef EFI_STATUS (*EFI_DISCONNECT_CONTROLLER)(EFI_HANDLE ControllerHandle, EFI_HANDLE DriverImageHandle, EFI_HANDLE ChildHandle);

typedef EFI_STATUS (*EFI_CALCULATE_CRC32)(void *Data, UINTN DataSize, UINT32 *Crc32);

typedef struct EFI_BOOT_SERVICES
{
    EFI_TABLE_HEADER Hdr;
    //
    // Task Priority Services
    //
    EFI_RAISE_TPL RaiseTPL;     // EFI 1.0+
    EFI_RESTORE_TPL RestoreTPL; // EFI 1.0+
    //
    // Memory Services
    //
    EFI_ALLOCATE_PAGES AllocatePages; // EFI 1.0+
    EFI_FREE_PAGES FreePages;         // EFI 1.0+
    EFI_GET_MEMORY_MAP GetMemoryMap;  // EFI 1.0+
    EFI_ALLOCATE_POOL AllocatePool;   // EFI 1.0+
    EFI_FREE_POOL FreePool;           // EFI 1.0+
    //
    // Event & Timer Services
    //
    EFI_CREATE_EVENT CreateEvent;    // EFI 1.0+
    EFI_SET_TIMER SetTimer;          // EFI 1.0+
    EFI_WAIT_FOR_EVENT WaitForEvent; // EFI 1.0+
    EFI_SIGNAL_EVENT SignalEvent;    // EFI 1.0+
    EFI_CLOSE_EVENT CloseEvent;      // EFI 1.0+
    EFI_CHECK_EVENT CheckEvent;      // EFI 1.0+
    //
    // Protocol Handler Services
    //
    EFI_INSTALL_PROTOCOL_INTERFACE InstallProtocolInterface;     // EFI 1.0+
    EFI_REINSTALL_PROTOCOL_INTERFACE ReinstallProtocolInterface; // EFI 1.0+
    EFI_UNINSTALL_PROTOCOL_INTERFACE UninstallProtocolInterface; // EFI 1.0+
    EFI_HANDLE_PROTOCOL HandleProtocol;                          // EFI 1.0+
    void *Reserved;                                              // EFI 1.0+
    EFI_REGISTER_PROTOCOL_NOTIFY RegisterProtocolNotify;         // EFI 1.0+
    EFI_LOCATE_HANDLE LocateHandle;                              // EFI 1.0+
    EFI_LOCATE_DEVICE_PATH LocateDevicePath;                     // EFI 1.0+
    EFI_INSTALL_CONFIGURATION_TABLE InstallConfigurationTable;   // EFI 1.0+
    //
    // Image Services
    //
    EFI_IMAGE_LOAD LoadImage;                // EFI 1.0+
    EFI_IMAGE_START StartImage;              // EFI 1.0+
    EFI_EXIT Exit;                           // EFI 1.0+
    EFI_IMAGE_UNLOAD UnloadImage;            // EFI 1.0+
    EFI_EXIT_BOOT_SERVICES ExitBootServices; // EFI 1.0+
    //
    // Miscellaneous Services
    //
    EFI_GET_NEXT_MONOTONIC_COUNT GetNextMonotonicCount; // EFI 1.0+
    EFI_STALL Stall;                                    // EFI 1.0+
    EFI_SET_WATCHDOG_TIMER SetWatchdogTimer;            // EFI 1.0+
    //
    // DriverSupport Services
    //
    EFI_CONNECT_CONTROLLER ConnectController;       // EFI 1.1
    EFI_DISCONNECT_CONTROLLER DisconnectController; // EFI 1.1+
    //
    // Open and Close Protocol Services
    //
    EFI_OPEN_PROTOCOL OpenProtocol;                        // EFI 1.1+
    EFI_CLOSE_PROTOCOL CloseProtocol;                      // EFI 1.1+
    EFI_OPEN_PROTOCOL_INFORMATION OpenProtocolInformation; // EFI 1.1+
    //
    // Library Services
    //
    EFI_PROTOCOLS_PER_HANDLE ProtocolsPerHandle;                                    // EFI 1.1+
    EFI_LOCATE_HANDLE_BUFFER LocateHandleBuffer;                                    // EFI 1.1+
    EFI_LOCATE_PROTOCOL LocateProtocol;                                             // EFI 1.1+
    EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES InstallMultipleProtocolInterfaces;     // EFI 1.1+
    EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces; // EFI 1.1+
    //
    // 32-bit CRC Services
    //
    EFI_CALCULATE_CRC32 CalculateCrc32; // EFI 1.1+
    //
    // Miscellaneous Services
    //
    EFI_COPY_MEM CopyMem;              // EFI 1.1+
    EFI_SET_MEM SetMem;                // EFI 1.1+
    EFI_CREATE_EVENT_EX CreateEventEx; // UEFI 2.0+
} EFI_BOOT_SERVICES;

#endif
