#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "struct.h"
#include "dinlist.h"

int main()
{
    FILE *outfile = fopen("Angajat_output.txt", "r"); //Open file for reading

    if (outfile == NULL)
    {
        printf("Error in Angajat_read_file: %d (%s)\n", errno, strerror(errno));
        return 1;
    }

    // numar liniile din fisier
    int ch;
    int lines = 0;
    while ((ch = fgetc(outfile)) != EOF)
    {
        if ( ch == '\n' )
            lines++;
    }
    rewind(outfile);

    // vector de angajati
    Angajat** emp_array = (Angajat**)malloc(sizeof(Angajat) * lines);

    int i;
    // citesc fiecare angajat din fisier
    for (i = 0; i < lines; i++)
        emp_array[i] = read_Angajat(outfile);


    // -------------------- 1. afisare angajati -------------------- //
    printf("-------------------- 1. afisare angajati --------------------\n");
    for (i = 0; i < lines; i++)
        afAngajat(emp_array[i]);


    // -------------------- 2.a afisare angajati ultimele 6 luni -------------------- //
    printf("\n-------------------- 2.a afisare angajati ultimele 6 luni -------------------- \n");
    data_cal data_curenta;
    dataCurenta(&data_curenta.zi, &data_curenta.luna, &data_curenta.an);

    for (i = 0; i < lines; i++)
        if (difInLuni(&data_curenta, &emp_array[i]->zi_start) <= 6)
        {
            afNumeDep(emp_array[i]);
        }

    // -------------------- 2.b afisare angajati incheiere contract -------------------- //
    printf("\n-------------------- 2.b afisare angajati incheiere contract-------------------- \n");

    for (i = 0; i < lines; i++)
    {
        int dif_luni = difInLuni(&data_curenta, &emp_array[i]->zi_stop);

        if ( dif_luni == -1)// &&       //
            //data_curenta.an == emp_array[i].an &&
            //data_curenta.luna == [i]->zi_stop.luna)
        {
            afNumeDepSalariu(emp_array[i]);
        }
    }

    // -------------------- 2.c afisare angajati decrescator -------------------- //
    printf("\n-------------------- 2.c afisare angajati decrescator -------------------- \n");
    char * dep_ales = (char *)malloc(sizeof(char) * LUNG_ELEM_MAX );
    printf("Alegeti nume departament \n");
    gets(dep_ales);

    LIST l = newl();

    for (i = 0; i < lines; i++)
        if ( strcmp(dep_ales, emp_array[i]->dep)  == 0)
            addBack(l, *emp_array[i]);

    sortazaListaSalariu(l);
    afListaNumeSalariu(l);

    destroyl(l);

    // -------------------- 2.d salvare angajati alfabetic -------------------- //
    printf("\n-------------------- 2.d salvare angajati alfabetic -------------------- \n");
    l = newl();
    char* dep_salariu_maxim = (char *)malloc(sizeof(char) * LUNG_ELEM_MAX );
    for (i = 0; i < lines; i++)
        addBack(l, *emp_array[i]);

    salvareDepartamente(l,dep_salariu_maxim);

    destroyl(l);
    printf("Salvare.\n");

    // -------------------- 2.e cost maxim -------------------- //
    printf("\n-------------------- 2.e cost maxim -------------------- \n");
    printf("Departament cost salarial maxim: %s\n", dep_salariu_maxim);
    free(dep_salariu_maxim);

    // -------------------- 3. angajati salariu mai mic decat "s" -------------------- //
    printf("\n-------------------- 3. angajati salariu mai mic decat \"s\" -------------------- \n");



    // eliberare memorie angajati
    for (i = 0; i < lines; i++)
        free_Angajat(emp_array[i]);

    fclose(outfile);
    return 0;
}

