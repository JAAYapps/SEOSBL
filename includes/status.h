#ifndef STATUS_H
#define STATUS_H

#define SUCCESS 0x00    // the most significant bit is 0 for a base success status.
#define ERROR_BASE 0x80 // the most significant bit is 1 for a base failure status.

#define LOAD_SUCCESS SUCCESS | 0x01
#define LOAD_FAILURE ERROR_BASE | 0x01
#define FILE_SIGNITURE_MATCHED SUCCESS | 0x02
#define FILE_SIGNITURE_NOT_MATCHED ERROR_BASE | 0x02
#define MEMORY_ACCESS_SUCCESS SUCCESS | 0x03
#define MEMORY_ACCESS_FAILURE ERROR_BASE | 0x03
#define UNKOWN_ERROR ERROR_BASE | 0x7f

#endif
