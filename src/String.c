#include "../includes/String.h"

unsigned long long strlen(const char *str)
{
	const char *strCount = str;

	while (*strCount++)
		;
	return strCount - str - 1;
}

unsigned long long str16Len(unsigned short int *str)
{
	const unsigned short int *strCount = str;

	while (*strCount++)
		;
	return strCount - str - 1;
}

void itoa(unsigned long int n, char *buffer, int basenumber)
{
	unsigned long int hold;
	int i, j;
	hold = n;
	i = 0;

	do
	{
		hold = n % basenumber;
		buffer[i++] = (hold < 10) ? (hold + '0') : (hold + 'a' - 10);
	} while (n /= basenumber);
	buffer[i--] = 0;

	for (j = 0; j < i; j++, i--)
	{
		hold = buffer[j];
		buffer[j] = buffer[i];
		buffer[i] = hold;
	}
}

void itoa16(unsigned long int n, unsigned short int *buffer, int basenumber)
{
	unsigned long int hold;
	int i, j;
	hold = n;
	i = 0;

	do
	{
		hold = n % basenumber;
		buffer[i++] = (hold < 10) ? (hold + '0') : (hold + 'a' - 10);
	} while (n /= basenumber);
	buffer[i--] = 0;

	for (j = 0; j < i; j++, i--)
	{
		hold = buffer[j];
		buffer[j] = buffer[i];
		buffer[i] = hold;
	}
}

void i64toa(unsigned long long n, char *buffer, int basenumber)
{
	unsigned long long hold;
	int i, j;
	hold = n;
	i = 0;

	do
	{
		hold = n % basenumber;
		buffer[i++] = (hold < 10) ? (hold + '0') : (hold + 'a' - 10);
	} while (n /= basenumber);
	buffer[i--] = 0;

	for (j = 0; j < i; j++, i--)
	{
		hold = buffer[j];
		buffer[j] = buffer[i];
		buffer[i] = hold;
	}
}

void i64toa16(unsigned long long n, unsigned short int *buffer, int basenumber)
{
	unsigned long long hold;
	int i, j;
	hold = n;
	i = 0;

	do
	{
		hold = n % basenumber;
		buffer[i++] = (hold < 10) ? (hold + '0') : (hold + 'a' - 10);
	} while (n /= basenumber);
	buffer[i--] = 0;

	for (j = 0; j < i; j++, i--)
	{
		hold = buffer[j];
		buffer[j] = buffer[i];
		buffer[i] = hold;
	}
}

int strcmp(const char *a, const char *b)
{
	int length = strlen(a);
	int length2 = strlen(b);
	if (length == length2)
	{
		for (int i = 0; i < length; i++)
		{
			if (a[i] != b[i])
			{
				return 0;
			}
		}
	}
	else
		return 0;
	return 1;
}

int strcmp16(unsigned short int *a, unsigned short int *b)
{
	int length = str16Len(a);
	int length2 = str16Len(b);
	if (length == length2)
	{
		for (int i = 0; i < length; i++)
		{
			if (a[i] != b[i])
			{
				return 0;
			}
		}
	}
	else
		return 0;
	return 1;
}