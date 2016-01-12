#include <stdio.h>
#include <stdlib.h>
#include "dinlist.h"

#define VOID_LIST void_cuvant
#define VOID -1

#define FORMAT"%s"

DATA void_cuvant;

static void copyData(int n, DATAP buf1, DATAP buf2)
{
    int i;
    for(i = 0; i < n; i++)
        buf2[i] = buf1[i];
}

LIST newlC()
{
    LIST w = (LIST)malloc(sizeof(List));
    if(w != NULL)
    {
        w->last_elem = 0;
        w->v = (DATAP) malloc(sizeof(DATA) * NMAX);
        w->listSize = NMAX;
        if(w->v == NULL)
            return NULL;
    }
    return w;
}

LIST addBackC(LIST l, DATA x)
{
    if( isFULL(l))
    {
        //lista plina, extindere cu  NMAX
        DATAP w = (DATAP) malloc(sizeof(DATA) * (l->listSize + NMAX));
        l->listSize += NMAX;
        if( w != NULL)
            copyData(l->listSize, l->v, w);
        else
            return NULL;
        free (l->v);
        l->v = w;
    }
    l->v[l->last_elem] =x;
    l->last_elem++;
    return l;
}

LIST addFrontC(LIST l, DATA x)
{
    if(isEmpty(l))
    {
        l = addBack(l, x);
    }
    else
    {
        DATAP w;
        // mut elementele cu o pozitie la dreapta
        w = (DATAP)malloc(sizeof(DATA)* (l->listSize + 1));
        copyData(l->listSize, l->v, w+1);
        w[0] =x;
        l->last_elem++;
        //daca list e plina, crestem capacitatea
        if(isFULL(l))
            l->listSize++;
        free(l->v);
        l->v =w;
    }
    return l;
}

DATA firstC(LIST l)
{
    if(!isEmpty(l))
        return l->v[0];
    return VOID_LIST;
}

DATA lastC(LIST l)
{
    if(!isEmpty(l))
        return l->v[l->last_elem-1];
    return VOID_LIST;
}

int lengthlC(LIST l)
{
    if(!isEmpty(l))
        return l->last_elem-1;
    return VOID;
}

LIST removeBackC(LIST l)
{
    if(!isEmpty(l))
    {
        free( &(l->v[l->last_elem-1]) );
        l->last_elem--;
    }
    return l;
}

LIST removeFrontC(LIST l)
{
    int i;
    if(!isEmpty(l))
    {
        for(i=0; i<l->last_elem-1; i++)
            l->v[i] = l->v[i+1];
        free( &(l->v[l->last_elem-1]) );
        l->last_elem--;
    }
    return l;

}

void destroylC(LIST l)
{
    free(l->v);
    free(l);
}


BOOLEAN isFULLC(LIST l)
{
    return l->last_elem >= l->listSize-1 ? TRUE : FALSE;
}

BOOLEAN isEmptyC(LIST l)
{
    return l->last_elem == 0 ? TRUE : FALSE;
}
