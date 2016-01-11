#ifndef _DATACAL_H_
#define _DATACAL_H_
#include <time.h>

#define SEC_IN_LUNA 2592000

// structura pentru data calendaristica
typedef struct
{
    int zi;
    int luna;
    int an;
} data_cal;

void dataCurenta( int * zi, int * luna, int * an);
int difInLuni(data_cal* d1, data_cal* d2);
#endif
