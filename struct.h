#ifndef STRUCT_H
#define STRUCT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_cal.h"

#define LUNG_MAX 400
#define LUNG_ELEM_MAX 100

// structura pentru angajat
typedef struct
{
    int salariu;
    char *nume;
    char *dep;
    data_cal zi_start;
    data_cal zi_stop;
} Angajat;

void afAngajat(Angajat *Angajat);
void afAngajatStream(FILE *stream, Angajat *Angajat);
Angajat* make_Angajat(int salariu, char* emp_nume, char* dep, data_cal* zi_start, data_cal* zi_stop );
Angajat* prompt_for_Angajat();
void free_Angajat(Angajat* emp);
void afAngajatRaw(FILE *stream, Angajat *Angajat);
Angajat* read_Angajat(FILE *stream);
void outputAngajatBinary(int stream, Angajat *Angajat);
Angajat* read_Angajat_binary(int stream);
char* str_padleft(const char* str, char pad, size_t bytes);

#endif

