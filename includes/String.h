#ifndef STRING_H
#define STRING_H

unsigned long long strlen(const char *str);

unsigned long long str16Len(unsigned short int *str);

void itoa(unsigned long int n, char *buffer, int basenumber);

void itoa16(unsigned long int n, unsigned short int *buffer, int basenumber);

void i64toa(unsigned long long n, char *buffer, int basenumber);

void i64toa16(unsigned long long n, unsigned short int *buffer, int basenumber);

int strcmp(const char *a, const char *b);

int strcmp16(unsigned short int *a, unsigned short int *b);
#endif
