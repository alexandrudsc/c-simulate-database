#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include <errno.h>

/**
 * @brief This program writes some input Angajats to a
 * text file that can then be read by Angajat_read_file.
 *
 * It writes the Angajats one per line with the following
 * format for each line:
 * [Angajat name] [Angajat salary] [Angajat department]
 *
 * @return 1 if file error, 0 otherwise.
 */
int main1()
{
    int cont = 1;
    char line[100];
    int num_Angajats;

    while (cont)
    {
//        line = readline("How many Angajats are there? ");
        printf("How many Angajats are there?\n");
        gets(line);
        if (sscanf(line, "%d", &num_Angajats)) cont = 0;
        free(line);
    }

    Angajat** emp_array = (Angajat**)malloc(sizeof(Angajat) * num_Angajats);
    int i;
    for (i = 0; i < num_Angajats; i++)
    {
        emp_array[i] = prompt_for_Angajat();
    }

    FILE *outfile = fopen("Angajat_output.txt", "w"); // Open or create file for writing
    if (outfile == NULL)
    {
        printf("Error in Angajat_write_text: %d (%s)\n", errno, strerror(errno));
        return 1;
    }

    for (i = 0; i < num_Angajats; i++)
    {
        afAngajat(emp_array[i]);
        afAngajatRaw(outfile, emp_array[i]);
        free_Angajat(emp_array[i]);
    }

    fclose(outfile); // Close the file
    return 0;
}

