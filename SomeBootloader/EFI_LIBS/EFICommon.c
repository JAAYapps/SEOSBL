#include "EFICommon.h"

EFI_HANDLE gIH;
EFI_SYSTEM_TABLE *gST;
void InitUEFIServices(EFI_HANDLE IH, EFI_SYSTEM_TABLE *ST)
{
    // We setup this global variable in the efilibs.h file.
    gIH = IH;
    gST = ST;
}

EFI_SYSTEM_TABLE* GetSystemTable()
{
    return gST;
}

EFI_BOOT_SERVICES* GetBootServices()
{
    return gST->BootServices;
}

EFI_RUNTIME_SERVICES* GetRuntimeServices()
{
    return gST->RuntimeServices;
}

EFI_HANDLE GetImageHandle()
{
    return gIH;
}

unsigned long long strlen(const char* str)
{
	const char* strCount = str;

	while (*strCount++);
	return strCount - str - 1;
}

void itoa(unsigned long int n, unsigned short int* buffer, int basenumber)
{
	unsigned long int hold;
	int i, j;
	hold = n;
	i = 0;
	
	do{
		hold = n % basenumber;
		buffer[i++] = (hold < 10) ? (hold + '0') : (hold + 'a' - 10);
	} while(n /= basenumber);
	buffer[i--] = 0;
	
	for(j = 0; j < i; j++, i--)
	{
		hold = buffer[j];
		buffer[j] = buffer[i];
		buffer[i] = hold;
	}
}