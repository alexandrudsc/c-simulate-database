#ifndef _DINLIST_H_
#define _DINLIST_H_

#include "struct.h"

#define NMAX 4

#define TRUE 1
#define FALSE 0


typedef Angajat DATA, *DATAP;
typedef char BOOLEAN;


struct list{
    int listSize;   //Current allocated size
    int last_elem;  //FIRST UNOCCUPIED position
    DATAP v;        //Info
};

typedef struct list List, *LIST;

LIST newl();
LIST addFront(LIST l, DATA x);
LIST addBack(LIST l, DATA x);
LIST remove_front(LIST l);
LIST remove_back(LIST l);
DATA first(LIST l);
DATA last (LIST l);
int lengthl (LIST l);
BOOLEAN isFULL(LIST l);
BOOLEAN isEmpty(LIST l);
void displayl(LIST l);
void destroyl(LIST l);

#endif
