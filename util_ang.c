#include "struct.h"
#include "dinlist.h"

void afNumeDepSalariu(Angajat *angajat)
{
    printf("Angajat. nume = %s, dep = %s, salariu = %d\n", angajat->nume, angajat->dep, angajat->salariu);
}

void afNumeSalariu(Angajat *angajat)
{
    printf("Angajat. nume = %s, salariu = %d\n", angajat->nume, angajat->salariu);
}

void afNumeDep(Angajat *angajat)
{
    printf("Angajat. nume = %s, dep = %s\n", angajat->nume, angajat->dep);
}

void afInfo(Angajat *angajat )
{
    printf("Angajat. nume = %s, salariu = %d, zi inceput: %d.%d.%d, zi sfarsit: %d.%d.%d\n",
            angajat->nume, angajat->salariu,
            angajat->zi_start.zi, angajat->zi_start.luna, angajat->zi_start.an,
            angajat->zi_stop.zi, angajat->zi_stop.luna, angajat->zi_stop.an);
}
