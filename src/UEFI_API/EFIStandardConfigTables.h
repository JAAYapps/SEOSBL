#ifndef EFI_STANDARD_CONFIG_TABLES_H
#define EFI_STANDARD_CONFIG_TABLES_H

#define EFI_ACPI_20_TABLE_GUID                                                         \
    {                                                                                  \
        0x8868e871, 0xe4f1, 0x11d3, { 0xbc, 0x22, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81 } \
    }
#define ACPI_TABLE_GUID                                                                \
    {                                                                                  \
        0xeb9d2d30, 0x2d88, 0x11d3, { 0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d } \
    }
#define SAL_SYSTEM_TABLE_GUID                                                          \
    {                                                                                  \
        0xeb9d2d32, 0x2d88, 0x11d3, { 0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d } \
    }
#define SMBIOS_TABLE_GUID                                                              \
    {                                                                                  \
        0xeb9d2d31, 0x2d88, 0x11d3, { 0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d } \
    }
#define SMBIOS3_TABLE_GUID                                                             \
    {                                                                                  \
        0xf2fd1544, 0x9794, 0x4a2c, { 0x99, 0x2e, 0xe5, 0xbb, 0xcf, 0x20, 0xe3, 0x94 } \
    }
#define MPS_TABLE_GUID                                                                  \
    {                                                                                   \
        0xeb9d2d2f, 0x2d88, 0x11d3,\ { 0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d } \
    }
//
// ACPI 2.0 or newer tables should use EFI_ACPI_TABLE_GUID
//
#define EFI_ACPI_TABLE_GUID                                                            \
    {                                                                                  \
        0x8868e871, 0xe4f1, 0x11d3, { 0xbc, 0x22, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81 } \
    }
#define EFI_ACPI_20_TABLE_GUID EFI_ACPI_TABLE_GUID
#define ACPI_TABLE_GUID                                                                \
    {                                                                                  \
        0xeb9d2d30, 0x2d88, 0x11d3, { 0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d } \
    }
#define ACPI_10_TABLE_GUID ACPI_TABLE_GUID

//UEFI Specification, Version 2.9       Page 107
#define EFI_MEMORY_ATTRIBUTES_TABLE_GUID                                               \
    {                                                                                  \
        0xdcfa911d, 0x26eb, 0x469f, { 0xa2, 0x20, 0x38, 0xb7, 0xdc, 0x46, 0x12, 0x20 } \
    }

#endif
