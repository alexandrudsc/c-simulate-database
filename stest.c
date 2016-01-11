#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "struct.h"

int main()
{
    printf("Starting program stest.\n");

    // Anybody recognize these names?
    Employee harry; // Declare a local variable (a struct).
    harry.salary = 5000;
    harry.name = strdup("Harry Palmer"); // Make a dynamic copy.
    harry.department = strdup("Engineering");

    Employee bluejay; // Declare a local variable (a struct).
    bluejay.salary = 10000;
    bluejay.name = strdup("Erik Grantby"); // Make a dynamic copy.
    bluejay.department = strdup("Marketing");
    
    Employee* fry = make_employee(1000, "Fry", "Shipping");
    Employee* leela = make_employee(500000, "Leela", "Receiving");
    Employee* input_emp = prompt_for_employee();

    // Output the employees to stdout.
    printEmployee(&harry);
    printEmployee(&bluejay);
    printEmployee(fry);
    printEmployee(leela);
    printEmployee(input_emp);

    // Output the employees to a file.
    printf("About to write to file.\n");
    FILE *outfile = fopen("stest.txt", "w"); // Open or create file for writing
    if (outfile == NULL)
    {
        printf("Error in stest: %d (%s)\n", errno, strerror(errno));
        return 1;
    }
    outputEmployee(outfile, &harry);
    outputEmployee(outfile, &bluejay);
    outputEmployee(outfile, fry);
    outputEmployee(outfile, leela);
    outputEmployee(outfile, input_emp);

    fclose(outfile); // Close the file

    printf("Ending program stest.\n");
#ifdef DEBUG
    printf("Program was run in debug mode.\n");
#endif
    return 0;
}

