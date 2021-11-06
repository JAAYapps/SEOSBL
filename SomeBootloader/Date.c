#include "Date.h"

unsigned short int* GetMonth(unsigned short m)
{
    switch(m)
    {
        case 1:
        {
            return (unsigned short int*)L"January";
        }
        case 2:
        {
            return (unsigned short int*)L"February";
        }
        case 3:
        {
            return (unsigned short int*)L"March";
        }
        case 4:
        {
            return (unsigned short int*)L"April";
        }
        case 5:
        {
            return (unsigned short int*)L"May";
        }
        case 6:
        {
            return (unsigned short int*)L"June";
        }
        case 7:
        {
            return (unsigned short int*)L"July";
        }
        case 8:
        {
            return (unsigned short int*)L"August";
        }
        case 9:
        {
            return (unsigned short int*)L"September";
        }
        case 10:
        {
            return (unsigned short int*)L"October";
        }
        case 11:
        {
            return (unsigned short int*)L"November";
        }
        case 12:
        {
            return (unsigned short int*)L"December";
        }
    }
    return (unsigned short int*)L"N/A";
}

unsigned short int* GetDayExtension(unsigned short m)
{
    switch(m)
    {
        case 1:
        {
            return (unsigned short int*)L"st";
        }
        case 2:
        {
            return (unsigned short int*)L"nd";
        }
        case 3:
        {
            return (unsigned short int*)L"rd";
        }
		case 21:
		{
			return (unsigned short int*)L"st";
		}
		case 22:
		{
			return (unsigned short int*)L"nd";
		}
	    case 23:
		{
			return (unsigned short int*)L"rd";
		}
		case 31:
		{
			return (unsigned short int*)L"st";
		}
    }
    return (unsigned short int*)L"th";
}