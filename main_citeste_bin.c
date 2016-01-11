#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int infile = open("Angajat_output.dat", O_RDONLY);
    if (infile < 0)
    {
        printf("Error in Angajat_read_binary: %d (%s)\n", errno, strerror(errno));
        return 1;
    }
    int num_Angajats;
    read(infile, &num_Angajats, sizeof(int));
    Angajat** Angajats = (Angajat**)malloc(num_Angajats * sizeof(Angajat));
    int i;
    for (i = 0; i < num_Angajats; i++)
    {
        Angajats[i] = read_Angajat_binary(infile);
        afAngajat(Angajats[i]);
    }

    for (i = 0; i < num_Angajats; i++)
    {
        free_Angajat(Angajats[i]);
    }
    close(infile);

    return 0;
}
