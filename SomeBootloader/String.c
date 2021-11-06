#include "String.h"

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

int strcmp(const char* a, const char* b)
{
	int length = strlen(a);
	for(int i = 0; i < length; i++)
	{
		if(a[i] != b[i]){return 0;}
	}
	return 1;
}