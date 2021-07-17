#include <stdio.h>
#include <stdlib.h>     // # define EXIT_FAILURE 1
#include <string.h>

#include "conversion.h"

#define INPUT   "./tests/text"
#define OUTPUT  "./out/morse.txt"

void start()
{
    printf("\n                             TEXT TO MORSE");
    printf("\nauthor:        Andrea Chiusole");
    printf("\nbadge number:  209660\n");
    printf("\n     The scope of this program is to convert text into Morse code.\n");
    printf("\n If you want to convert a text file of yours you have to place it in the");
    printf("\n           project folder and afterwards type here its name.\n");
    printf("\n  The name should be less than 31 charachters including the extension.\n");
    printf("\n    (A default text file is already present inside the directory.");
    printf("\n        If you want to convert that one don't type anything)\n");
    printf("\nWhat is the name of the file? [Max 31 chars]");
    printf("\n   >>> ");
}


int main(int argc, char *argv[])
{
    char source_name[32];
    FILE *source, *destination;

    start();

    if (fgets(source_name , 31, stdin) != NULL)
    {
        // Strip the newline char if present
        source_name[strcspn(source_name, "\n")] = '\0';
    }

    if (!strcmp(source_name, ""))
    {
        strcpy(source_name, INPUT);
    }

    printf("source_name is: %s", source_name);


    source = fopen(source_name, "r");
    if (source == NULL)
    {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    destination = fopen(OUTPUT, "w+");
    if (destination == NULL) {
        perror("Error opening destination file");
        exit(EXIT_FAILURE);
    }

    print_morse(source, destination);

    fclose(source);
    fclose(destination);
    return 0;
}
