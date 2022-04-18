#include "../includes/Date.h"

char *GetMonth(unsigned short m)
{
    switch (m)
    {
    case 1:
    {
        return "January";
    }
    case 2:
    {
        return "February";
    }
    case 3:
    {
        return "March";
    }
    case 4:
    {
        return "April";
    }
    case 5:
    {
        return "May";
    }
    case 6:
    {
        return "June";
    }
    case 7:
    {
        return "July";
    }
    case 8:
    {
        return "August";
    }
    case 9:
    {
        return "September";
    }
    case 10:
    {
        return "October";
    }
    case 11:
    {
        return "November";
    }
    case 12:
    {
        return "December";
    }
    }
    return "N/A";
}

char *GetDayExtension(unsigned short m)
{
    switch (m)
    {
    case 1:
    {
        return "st";
    }
    case 2:
    {
        return "nd";
    }
    case 3:
    {
        return "rd";
    }
    case 21:
    {
        return "st";
    }
    case 22:
    {
        return "nd";
    }
    case 23:
    {
        return "rd";
    }
    case 31:
    {
        return "st";
    }
    }
    return "th";
}