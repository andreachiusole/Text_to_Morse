#include <stdio.h>
#include <stdlib.h>     // # define EXIT_FAILURE 1
#include <string.h>

#include "conversion.h"

#define INPUT   "./tests/text"
#define OUTPUT  "./out/morse.txt"


void start()
{
    printf("\n\t                             TEXT TO MORSE\n");
    printf("\n\t     The scope of this program is to convert text into Morse code.\n");
    printf("\n\t If you want to convert a text file of yours you have to place it in the");
    printf("\n\t           project folder and afterwards type here its name.\n");
    printf("\n\t  The name should be less than 31 characters including the extension.\n");
    printf("\n\t  A default text file is already present inside the project directory\n\n");
}

/*------------------------------------------------------- *
* Get source address                                      *
* ------------------------------------------------------- */
void get_source_address(char *source_address)
{
    printf("\n\tWhat is the name of the file? [Max 999 chars]");
    printf("\n\t   >>> ");

    if (fgets(source_address, 999, stdin) != NULL)
    {
        // Strip the newline char if present
        source_address[strcspn(source_address, "\n")] = '\0';
    }

    if (strcmp(source_address, NOCHAR) == 0) strcpy(source_address, INPUT);
    printf("\tFile to be converted is:     '%s'\n", source_address);

}

/*------------------------------------------------------- *
* Get separators for chars and words                      *
* ------------------------------------------------------- */
void get_separators(char *ch_sep, char *wd_sep)
{
    printf("\n\tWhat separator do you want between characters? [Max 9 chars]");
    printf("\n\t   >>> ");

    if (fgets(ch_sep, 9, stdin) != NULL) ch_sep[strcspn(ch_sep, "\n")] = '\0';

    if (strcmp(ch_sep, NOCHAR) == 0) strcpy(ch_sep, CHARSEP);
    printf("\tChars will be separated by:  '%s'\n", ch_sep);


    printf("\n\tWhat separator do you want between words? [Max 9 chars]");
    printf("\n\t   >>> ");

    if (fgets(wd_sep, 9, stdin) != NULL) wd_sep[strcspn(wd_sep, "\n")] = '\0';

    if (strcmp(wd_sep, NOCHAR) == 0) strcpy(wd_sep, WORDSEP);
    printf("\tWords will be separated by:  '%s'\n", wd_sep);
}


int main(int argc, char *argv[])
{
    char source_name[1000];
    char char_separator[10];
    char word_separator[10];
    FILE *source, *destination;

    start();
    get_source_address(source_name);


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

    get_separators(char_separator, word_separator);

    print_morse(source, destination, char_separator, word_separator);

    fclose(source);
    fclose(destination);
    return 0;
}
