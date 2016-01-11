#ifndef STRUCT_H
#define STRUCT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_cal.h"
//#include <readline/readline.h>

#define LUNG_MAX 400
#define LUNG_ELEM_MAX 100

// A struct to hold information about an Angajat.
typedef struct
{
    int salariu;
    char *nume;
    char *dep;
    data_cal zi_start;
    data_cal zi_stop;
} Angajat;

void printAngajat(Angajat *Angajat);
void outputAngajat(FILE *stream, Angajat *Angajat);
Angajat* make_Angajat(int salariu, char* emp_nume, char* dep, data_cal* zi_start, data_cal* zi_stop );
Angajat* prompt_for_Angajat();
void free_Angajat(Angajat* emp);
void outputAngajatRaw(FILE *stream, Angajat *Angajat);
Angajat* read_Angajat(FILE *stream);
void outputAngajatBinary(int stream, Angajat *Angajat);
Angajat* read_Angajat_binary(int stream);
char* str_padleft(const char* str, char pad, size_t bytes);

#endif

