#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include <errno.h>

int main1()
{
    int cont = 1;
    char line[100];
    int num_Angajats;

    while (cont)
    {
        printf("Numar angajati?\n");
        gets(line);
        if (sscanf(line, "%d", &num_Angajats)) cont = 0;
        free(line);
    }

    Angajat** ang_vector = (Angajat**)malloc(sizeof(Angajat) * num_Angajats);
    int i;
    for (i = 0; i < num_Angajats; i++)
    {
        ang_vector[i] = prompt_for_Angajat();
    }

    FILE *outfile = fopen("angajati.txt", "w");
    if (outfile == NULL)
    {
        printf("Error in Angajat_write_text: %d (%s)\n", errno, strerror(errno));
        return 1;
    }

    for (i = 0; i < num_Angajats; i++)
    {
        afAngajat(ang_vector[i]);
        afAngajatRaw(outfile, ang_vector[i]);
        free_Angajat(ang_vector[i]);
    }

    fclose(outfile); 
    return 0;
}

