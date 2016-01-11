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
Angajat* make_Angajat(int salariu, char* emp_nume, char* dep, data_cal* zi_start, data_cal* zi_stop )
{
    Angajat * emp = (Angajat*)malloc(sizeof(Angajat));
    emp->salariu = salariu;
    emp->nume = strdup(emp_nume);
    emp->dep = strdup(dep);
    emp->zi_start = *zi_start;
    emp->zi_stop = *zi_stop;
    return emp;
}

// citesc un angajat de la tastatura
Angajat* prompt_for_Angajat()
{
    // date specifice unui angajat
    char* line = (char*)malloc(LUNG_MAX * sizeof(char));
    char emp_nume[100];
    char emp_dep[100];
    int emp_salariu;
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
            //line = readline("Enter the Angajat's nume: ");
            state = 1;
            break;
        case 1:
            // validare nume
            if (sscanf(line, "%1000[0-9a-zA-Z ]s", emp_nume)) state = 2;
            else
            {
                state = 0;
                printf("Please try again.\n");
                free(line);
            }
            break;
        case 2:
            // citire departament
            free(line);
            printf("Departament angajat");
            line = gets(line);
            //line = readline("Enter the Angajat's dep: ");
            state = 3;
            break;
        case 3:
            // validare departament
            if (sscanf(line, "%1000[0-9a-zA-Z ]s", emp_dep)) state = 4;
            else
            {
                state = 2;
                printf("Please try again.\n");
            }
            break;
        case 4:
            // citire salariu
            free(line);
            printf("Salariu angajat");
            line = gets(line);
            //line = readline("Enter the Angajat's salariu: ");
            state = 5;
            break;
        case 5:
            // validare salariu
            if (sscanf(line, "%d", &emp_salariu)) state = 6;
            else
            {
                state = 4;
                printf("Please try again.\n");
            }
            break;
        case 6:
            // citire zi start
            free(line);
            printf("Zi inceput contract (ZZ.LL.AAAA) ");
            line = gets(line);
            //line = readline("Enter the Angajat's salariu: ");
            state = 7;
            break;
        case 7:
            // validare zi start
            if (sscanf(line, "%d.%d.%d", &zi_start.zi, &zi_start.luna, &zi_start.an) == 3) state = 8;
            else
            {
                state = 6;
                printf("Please try again.\n");
            }
        case 8:
            // citire zi stop
            free(line);
            printf("Zi incheiere contract (ZZ.LL.AAAA) ");
            line = gets(line);
            //line = readline("Enter the Angajat's salariu: ");
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
                printf("Please try again.\n");
            }
        }
    }

    // creez angajat si ii asociez datele citite
    Angajat* emp = malloc(sizeof(Angajat));
    emp->nume = strdup(emp_nume);
    emp->dep = strdup(emp_dep);
    emp->salariu = emp_salariu;
    emp->zi_start = zi_start;
    emp->zi_stop = zi_stop;
    return emp;
}

// sterg un angajat din memorie
void free_Angajat(Angajat* emp)
{
    free(emp->nume);
    free(emp->dep);
    free(emp);
}

// citesc un angajat dintr-un fisier text
Angajat* read_Angajat(FILE *stream)
{
    char*  line = (char*)malloc(sizeof(char) * LUNG_MAX);
    size_t len = 0;
    size_t readsize;
    char*  emp_nume = (char*)malloc(sizeof(char) * 100);
    char*  emp_dep = (char*)malloc(sizeof(char) * 100);
    int    emp_salariu;
    data_cal zi_start;
    data_cal zi_stop;

    if ((readsize = fgets(line, LUNG_MAX, stream)) != -1)
    {
        sscanf(line, "%s %d %s %d.%d.%d %d.%d.%d", emp_nume, &emp_salariu, emp_dep,
                                                &zi_start.zi, &zi_start.luna, &zi_start.an,
                                                &zi_stop.zi, &zi_stop.luna, &zi_stop.an);
        return make_Angajat(emp_salariu, emp_nume, emp_dep, &zi_start, &zi_stop);
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

/**
 * @brief Reads one Angajat in from a binary file.
 * The file stream must be opened in binary mode.
 *
 * @param stream The stream to read from.
 *
 * @return A pointer to the newly created Angajat.
 */
Angajat* read_Angajat_binary(int stream)
{
    int emp_salariu;
    read(stream, &emp_salariu, sizeof(int));
    size_t emp_nume_len;
    read(stream, &emp_nume_len, sizeof(size_t));
    char* emp_nume = (char*)malloc(emp_nume_len + 1);
    emp_nume[emp_nume_len] = '\0';
    read(stream, emp_nume, emp_nume_len);
    size_t emp_dept_len;
    read(stream, &emp_dept_len, sizeof(size_t));
    char* emp_dept = (char*)malloc(emp_dept_len + 1);
    emp_dept[emp_dept_len] = '\0';
    read(stream, emp_dept, emp_dept_len);
    Angajat* emp = (Angajat*)malloc(sizeof(Angajat));
    emp->salariu = emp_salariu;
    emp->dep = strdup(emp_dept);
    emp->nume = strdup(emp_nume);
    return emp;
}

