#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * @brief Writes a binary file containing input Angajats. This file
 * has the following format:
 *
 * first 16 bits: number of Angajats in file
 * next 16 bits: Angajat 1's salary
 * next 16 bits: number of characters in Angajat name
 * next n bits: Angajat name
 * next 16 bits: number of characters in Angajat department
 * next n bits: Angajat department
 *
 * This pattern repeats for as many Angajats as specified in the first block.
 *
 * @return
 */
int main()
{
    int cont = 1;
    char* line;
    int num_Angajats;

    while (cont)
    {
        line = readline("How many Angajats are there? ");
        if (sscanf(line, "%d", &num_Angajats)) cont = 0;
        free(line);
    }

    Angajat** emp_array = (Angajat**)malloc(sizeof(Angajat) * num_Angajats);
    int i;
    for (i = 0; i < num_Angajats; i++)
    {
        emp_array[i] = prompt_for_Angajat();
    }
    int outfile = open("Angajat_output.dat", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR |
                       S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    if (outfile < 0)
    {
        printf("Error in Angajat_write_binary: %d (%s)\n", errno, strerror(errno));
        return 1;
    }

    write(outfile, &num_Angajats, sizeof(int));
    for (i = 0; i < num_Angajats; i++)
    {
        printAngajat(emp_array[i]);
        outputAngajatBinary(outfile, emp_array[i]);
        free_Angajat(emp_array[i]);
    }

    close(outfile);
}

