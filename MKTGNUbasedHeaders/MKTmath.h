#ifndef MKTGNUBASEDLIBRARY
#define MKTGNUBASEDLIBRARY
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MKTDOUBLE double

MKTDOUBLE MKTfabs(MKTDOUBLE inputDouble)
{
    MKTDOUBLE finalReturn = inputDouble;
    void * address = &finalReturn;
    *(char*)address = *(char*)address&128;// simple pointer hack
    
    return finalReturn;
}

long long MKTfloor(MKTDOUBLE input)
{
    long long returnValue = input;
    return returnValue;
}

MKTDOUBLE MKTmodf(MKTDOUBLE inputDouble, long long * intpart)
{
    MKTDOUBLE returnDouble = inputDouble - MKTfloor(inputDouble);
    *intpart = MKTfloor(inputDouble);
    return returnDouble;
}
#endif