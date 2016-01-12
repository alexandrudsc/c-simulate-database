#include "struct.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// afisez un angajat
void afAngajat(Angajat *Angajat)
{
    afAngajatStream(stdout, Angajat);
}

// afisez un angajat intr-un flux specificat
void afAngajatStream(FILE *stream, Angajat *angajat)
{
    fprintf(stream, "Angajat. nume = %s, salariu = %d, dep = %s, zi inceput: %d.%d.%d, zi sfarsit: %d.%d.%d\n",
            angajat->nume, angajat->salariu, angajat->dep,
            angajat->zi_start.zi, angajat->zi_start.luna, angajat->zi_start.an,
            angajat->zi_stop.zi, angajat->zi_stop.luna, angajat->zi_stop.an);
}

// afisez un angajat intr-un flux specificat fara formatare
void afAngajatRaw(FILE *stream, Angajat *Angajat)
{
    fprintf(stream, "%s %d %s %d.%d.%d %d.%d.%d\n",
            Angajat->nume, Angajat->salariu, Angajat->dep,
            Angajat->zi_start.zi, Angajat->zi_start.luna, Angajat->zi_start.an,
            Angajat->zi_stop.zi, Angajat->zi_stop.luna, Angajat->zi_stop.an);
}

// creez un angajat pe baza datelor
Angajat* make_Angajat(int salariu, char* ang_nume, char* dep, data_cal* zi_start, data_cal* zi_stop )
{
    Angajat * ang = (Angajat*)malloc(sizeof(Angajat));
    ang->salariu = salariu;
    ang->nume = strdup(ang_nume);
    ang->dep = strdup(dep);
    ang->zi_start = *zi_start;
    ang->zi_stop = *zi_stop;
    return ang;
}

// citesc un angajat de la tastatura
Angajat* prompt_for_Angajat()
{
    // date specifice unui angajat
    char* line = (char*)malloc(LUNG_MAX * sizeof(char));
    char ang_nume[100];
    char ang_dep[100];
    int ang_salariu;
    data_cal zi_start;
    data_cal zi_stop;

    int state = 0;
    int cont = 1;
    while (cont)
    {
        switch (state)
        {
        case 0:
            // citire nume
            printf("Nume angajat");
            line = gets(line);
            state = 1;
            break;
        case 1:
            // validare nume
            if (sscanf(line, "%1000[0-9a-zA-Z ]s", ang_nume)) state = 2;
            else
            {
                state = 0;
                printf("Incercati din nou.\n");
                free(line);
            }
            break;
        case 2:
            // citire departament
            free(line);
            printf("Departament angajat");
            line = gets(line);
            state = 3;
            break;
        case 3:
            // validare departament
            if (sscanf(line, "%1000[0-9a-zA-Z ]s", ang_dep)) state = 4;
            else
            {
                state = 2;
                printf("Incercati din nou.\n");
            }
            break;
        case 4:
            // citire salariu
            free(line);
            printf("Salariu angajat");
            line = gets(line);
            state = 5;
            break;
        case 5:
            // validare salariu
            if (sscanf(line, "%d", &ang_salariu)) state = 6;
            else
            {
                state = 4;
                printf("Incercati din nou.\n");
            }
            break;
        case 6:
            // citire zi start
            free(line);
            printf("Zi inceput contract (ZZ.LL.AAAA) ");
            line = gets(line);
            state = 7;
            break;
        case 7:
            // validare zi start
            if (sscanf(line, "%d.%d.%d", &zi_start.zi, &zi_start.luna, &zi_start.an) == 3) state = 8;
            else
            {
                state = 6;
                printf("Incercati din nou.\n");
            }
        case 8:
            // citire zi stop
            free(line);
            printf("Zi incheiere contract (ZZ.LL.AAAA) ");
            line = gets(line);
            state = 9;
            break;
        case 9:
            // validare zi stop
            if (sscanf(line, "%d.%d.%d", &zi_stop.zi, &zi_stop.luna, &zi_stop.an) == 3)
            {
                cont = 0;
            }
            else
            {
                state = 8;
                printf("Incercati din nou.\n");
            }
        }
    }

    // creez angajat si ii asociez datele citite
    Angajat* ang = malloc(sizeof(Angajat));
    ang->nume = strdup(ang_nume);
    ang->dep = strdup(ang_dep);
    ang->salariu = ang_salariu;
    ang->zi_start = zi_start;
    ang->zi_stop = zi_stop;
    return ang;
}

// sterg un angajat din memorie
void free_Angajat(Angajat* ang)
{
    free(ang->nume);
    free(ang->dep);
    free(ang);
}

// citesc un angajat dintr-un fisier text
Angajat* read_Angajat(FILE *stream)
{
    char*  line = (char*)malloc(sizeof(char) * LUNG_MAX);
    size_t bytes_cititi;
    char*  ang_nume = (char*)malloc(sizeof(char) * 100);
    char*  ang_dep = (char*)malloc(sizeof(char) * 100);
    int    ang_salariu;
    data_cal zi_start;
    data_cal zi_stop;

    if ((bytes_cititi = fgets(line, LUNG_MAX, stream)) != -1)
    {
        sscanf(line, "%s %d %s %d.%d.%d %d.%d.%d", ang_nume, &ang_salariu, ang_dep,
                                                &zi_start.zi, &zi_start.luna, &zi_start.an,
                                                &zi_stop.zi, &zi_stop.luna, &zi_stop.an);
        return make_Angajat(ang_salariu, ang_nume, ang_dep, &zi_start, &zi_stop);
    }
    else
    {
        printf("No line.\n");
        return NULL;
    }
    if (line) free(line);
}

/**
 * @brief Writes an Angajat struct to a binary file
 * This file stream must be opened in binary mode.
 *
 * @param stream The af file steam.
 * @param Angajat The Angajat to write.
 */
void afAngajatBinary(int stream, Angajat *Angajat)
{
    size_t str_length;
    write(stream, &(Angajat->salariu), sizeof(int));
    str_length = strlen(Angajat->nume);
    write(stream, &str_length, sizeof(size_t));
    write(stream, Angajat->nume, strlen(Angajat->nume));
    str_length = strlen(Angajat->dep);
    write(stream, &str_length, sizeof(size_t));
    write(stream, Angajat->dep, strlen(Angajat->dep));
}
