#include "data_cal.h"

void dataCurenta( int * zi, int * luna, int * an)
{
    struct tm *current;
    time_t timenow;
    time(&timenow);
    current = localtime(&timenow);
    *luna = current->tm_mon + 1;
    *zi = current->tm_mday;
    *an = current->tm_year + 1900;
}

int difInLuni(data_cal* d1, data_cal* d2)
{
    // scad lunile intre ele
    int diff_luni = d1->luna - d2->luna;

    // la diferenta de luni adun si diferenta dintre ani transformata in lini
    diff_luni += ( (d1->an - d2->an) * 12);
    return diff_luni;
}
