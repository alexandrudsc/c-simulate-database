#ifndef OP_LISTE_
#define OP_LISTE_
#include "dinlist.h"


void afListaNumeSalariu(LIST l);

void sortazaListaSalariu(LIST l);
// sortare angajati dupa departament
void sortazaListaDepartamente(LIST l);
// sortare angajati dupa nume
void sortazaListaNume(LIST l);
// salveza angajatii pe fisiere si returneaza departamentul salariul maxim
void salvareDepartamente(LIST l, char* dep_sal_maxim);
// scrie un departament intr-un fisier
void salveazaDepartament(LIST l);

#endif
