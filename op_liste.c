#include "dinlist.h"

void afListaNumeSalariu(LIST l)
{
    int i;
    for(i = 0; i < l->last_elem; i++)
        afNumeSalariu(&(l->v[i]));
}

// sortare angajati dupa salariu
void sortazaListaSalariu(LIST l)
{
    if (isEmpty(l))
        return;

    int i, j;
    DATA aux;
    for(i = 0; i < l->last_elem - 1; i++)
         for(j = i + 1; j < l->last_elem; j++)
             if (l->v[i].salariu < l->v[j].salariu)
             {
                 aux = l->v[j];
                 l->v[j] = l->v[i];
                 l->v[i] = aux;
             }
}
// sortare angajati dupa departament
void sortazaListaDepartamente(LIST l)
{
    if (isEmpty(l))
        return;

    int i, j;
    DATA aux;
    for(i = 0; i < l->last_elem - 1; i++)
         for(j = i + 1; j < l->last_elem; j++)
             if (strcmp(l->v[i].dep, l->v[j].dep) > 0)
             {
                 aux = l->v[j];
                 l->v[j] = l->v[i];
                 l->v[i] = aux;
             }
}

// sortare angajati dupa nume
void sortazaListaNume(LIST l)
{
    if (isEmpty(l))
        return;

    int i, j;
    DATA aux;
    for(i = 0; i < l->last_elem - 1; i++)
         for(j = i + 1; j < l->last_elem; j++)
             if (strcmp(l->v[i].nume, l->v[j].nume) > 0)
             {
                 aux = l->v[j];
                 l->v[j] = l->v[i];
                 l->v[i] = aux;
             }
}

// salveza angajatii pe fisiere si returneaza departamentul salariul maxim
void salvareDepartamente(LIST l, char* dep_sal_maxim)
{
    if (isEmpty(l))
        return NULL;

    // ordonez lista alfabetic dupa departamente
    sortazaListaDepartamente(l);

    long sal_maxim = -1;
    long sal_dep = 0;

    // lista angajati unui departament
    LIST angajati_dep = newl();

    // creez o lista pentru primul departament (exista macar un angajat)
    addBack(angajati_dep, l->v[0]);

    // initial, departamentul salariu maxim este singurul departament creat
    sal_dep = l->v[0].salariu;
    sal_maxim = sal_dep;
    strcpy(dep_sal_maxim, l->v[0].dep);


    // parcurg restul angatilor; daca fac parte din acelasi departament, ii adaug.
    // daca nu, salvez departamentul curent, si creez altul
    int i;
    for(i = 1; i < l->last_elem; i++)
    {
        // daca angajatul nu apartine listei curente, inseamna ca am parcurs un departament
        if (strcmp(l->v[i].dep, l->v[i-1].dep) != 0)
        {
            salveazaDepartament(angajati_dep);
            destroyl(angajati_dep);

            // creez lista pentru un nou departament
            angajati_dep = newl();
            addBack(angajati_dep, l->v[i]);

            // calculez salariu noului departament
            sal_dep = l->v[i].salariu;

            // verific daca salariul total al departamentului parcurs e maxim
            if (sal_dep > sal_maxim)
            {
                sal_maxim = sal_dep;
                strcpy(dep_sal_maxim, l->v[i].dep);
            }
        }
        else
        {
            // adaug salariul la salatriul total
            sal_dep += l->v[i].salariu;

            // adaug angajatul la lista departamentului
            addBack(angajati_dep, l->v[i]);
        }

    }

    // salvez si ultimul departament (ultimul nu se salveaza in for)
    salveazaDepartament(angajati_dep);
    destroyl(angajati_dep);

    return NULL;
}

// scrie un departament intr-un fisier
void salveazaDepartament(LIST l)
{
    FILE *f_dep = fopen(l->v[0].dep, "w");

    sortazaListaNume(l);

    if(f_dep == NULL)
        return;
    int i;

    for(i = 0; i < l->last_elem; i++)
        afAngajatStream(f_dep, &(l->v[i]));
    fclose(f_dep);
}


