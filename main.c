#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "struct.h"
#include "dinlist.h"
#include "util_ang.h"
#include "op_liste.h"


int nrAngajati(FILE *f);
Angajat** citesteAngajati(FILE *f, int nr_ang);
void search (char * filename, int  s, int *vlen, char ***vp);


int main()
{
	// vector de angajati cititi din fisiser
	Angajat** ang_vector;	
	// numar de angajati
	int nr_ang = 0;
	int i ;
	
	// citesc numele fisierului
	printf("Alegeti fisierul:\n");
	char* s = (char*)malloc(sizeof(char) *100);
	gets(s);
	
	FILE* fisier = fopen(s, "r");
	
	if (fisier == NULL)
    {
        printf("Eroare la citire: cod: %d, mesaj:(%s)\n", errno, strerror(errno));
        return -1;
    }
	nr_ang = nrAngajati(fisier);

	ang_vector = citesteAngajati(fisier, nr_ang);
	free(s);
	
    // -------------------- 1. afisare angajati -------------------- //
    printf("-------------------- 1. afisare angajati --------------------\n");
    for (i = 0; i < nr_ang; i++)
        afAngajat(ang_vector[i]);


    // -------------------- 2.a afisare angajati ultimele 6 luni -------------------- //
    printf("\n-------------------- 2.a afisare angajati ultimele 6 luni -------------------- \n");
    data_cal data_curenta;
    dataCurenta(&data_curenta.zi, &data_curenta.luna, &data_curenta.an);

    for (i = 0; i < nr_ang; i++)
        if (difInLuni(&data_curenta, &ang_vector[i]->zi_start) <= 6)
        {
            afNumeDep(ang_vector[i]);
        }

    // -------------------- 2.b afisare angajati incheiere contract -------------------- //
    printf("\n-------------------- 2.b afisare angajati incheiere contract-------------------- \n");

    for (i = 0; i < nr_ang; i++)
    {
        int dif_luni = difInLuni(&data_curenta, &ang_vector[i]->zi_stop);

        if ( dif_luni == -1)// &&       //
            //data_curenta.an == ang_vector[i].an &&
            //data_curenta.luna == [i]->zi_stop.luna)
        {
            afNumeDepSalariu(ang_vector[i]);
        }
    }

    // -------------------- 2.c afisare angajati decrescator -------------------- //
    printf("\n-------------------- 2.c afisare angajati decrescator -------------------- \n");
    char * dep_ales = (char *)malloc(sizeof(char) * LUNG_ELEM_MAX );
    printf("Alegeti nume departament \n");
    gets(dep_ales);

    LIST l = newl();

    for (i = 0; i < nr_ang; i++)
        if ( strcmp(dep_ales, ang_vector[i]->dep)  == 0)
            addBack(l, *ang_vector[i]);

    sortazaListaSalariu(l);
    afListaNumeSalariu(l);

    destroyl(l);

    // -------------------- 2.d salvare angajati alfabetic -------------------- //
    printf("\n-------------------- 2.d salvare angajati alfabetic -------------------- \n");
    l = newl();
    char* dep_salariu_maxim = (char *)malloc(sizeof(char) * LUNG_ELEM_MAX );
    for (i = 0; i < nr_ang; i++)
        addBack(l, *ang_vector[i]);

    salvareDepartamente(l,dep_salariu_maxim);

    destroyl(l);
    printf("Salvare.\n");

    // -------------------- 2.e cost maxim -------------------- //
    printf("\n-------------------- 2.e cost maxim -------------------- \n");
    printf("Departament cost salarial maxim: %s\n", dep_salariu_maxim);
    free(dep_salariu_maxim);

    // -------------------- 3. angajati salariu mai mic decat "s" -------------------- //
    printf("\n-------------------- 3. angajati salariu mai mic decat \"s\" -------------------- \n");
	
	// citesc salariu
	printf("Alegeti salariul:\n");
	int salariu;
	scanf("%d", &salariu);
	fflush(stdin);
	
	// citesc numele fisierului
	printf("Alegeti fisierul:\n");
	char* sir = (char*)malloc(sizeof(char) *100);
	gets(sir);
	
	int vlen;
	char** vp;
	search(sir, salariu, &vlen, &vp);
	
	free(sir);
	
	for (i = 0; i < vlen; i++)
		printf ("%s; ", vp[i]);
	// eliberez stringurile indicate in vectorul de pointeri
	for (i = 0; i < vlen; i++)
		free(*(vp)[i]);
	// eliberez vectorul de pointeri
	free (vp);
	
    // eliberare memorie angajati
    for (i = 0; i < nr_ang; i++)
        free_Angajat(ang_vector[i]);
	
	
    fclose(fisier);
    return 0;
}

// calculeaza nr de angajati din fisier
int nrAngajati(FILE *f)
{
	int ch;
	int nr_ang = 0;
    while ((ch = fgetc(f)) != EOF)
    {
        if ( ch == '\n' )
            nr_ang++;
    }
	rewind(f);
	return nr_ang;
}

// citeste angajati din fisier
Angajat** citesteAngajati(FILE *f, int nr_ang)
{
	// vector de angajati
    Angajat** ang_vector = (Angajat**)malloc(sizeof(Angajat) * nr_ang);
	
    int i;
    // citesc fiecare angajat din fisier
    for (i = 0; i < nr_ang; i++)
        ang_vector[i] = read_Angajat(f);
	
	return ang_vector;
}

// calculeaza cati si care angajati din fisier au salariu mai mare ca s
void search (char* filename, int  s, int *vlen, char ***vp)
{
	// deschid fisier pentru citire
	FILE* fisier_nou = fopen(filename, "r");
	if (fisier_nou == NULL)
    {
        printf("Eroare la citire: cod: %d, mesaj:(%s)\n", errno, strerror(errno));
        return;
    }
	
	Angajat** angajati; 
	int nr_ang;
	
	nr_ang = nrAngajati(fisier_nou);
	angajati = citesteAngajati(fisier_nou, nr_ang);
	
	int i;
	int j;
	*vlen = 0;

	for (i = 0; i < nr_ang; i++)
		if (angajati[i]->salariu > s)
			(*vlen)++;
		
	// creez vectorul de pointer catre string-uri
	j=0;
	char** nume = (char**)malloc(sizeof (char*) * (*vlen));
	
	for (i = 0; i  <nr_ang; i++)
		if (angajati[i]->salariu > s){
			// aloc spatiu pentru pointer catre string
			nume[j] = (char*)malloc(sizeof (char)* LUNG_ELEM_MAX);
			//cpoiez nume
			strcpy(nume[j], angajati[i]->nume);
			j++;
		}
	
	*vp = nume;
		
	// eliberare memorie noi angajati
    for (i = 0; i < nr_ang; i++)
        free_Angajat(angajati[i]);
	
	fclose(fisier_nou);
	
}