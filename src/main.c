/*
*   Programma che legge un file di testo e lo converte in codice MORSE
*
*   PREMESSE:
*
*   - Le lettere ripetute (doppie) dovrebbero essere riportate una sola volta, ma
*   per poter fare una eventuale conversione da Morse a testo ho scelto di riportarle
*   come sono presenti nel source file.
*
*   - Non viene fatta distinzione tra lettere maiuscole o minuscole
*
*   - I segni di punteggiatura dal source file verranno ignorati e quindi non convertiti.
*
*   - Per una leggibilità più chiara la separazione tra lettere viene indicata con '/'
*   mentre quella tra parole con '//' all'interno del testo convertito.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conversion.h"

#define INPUT   "./tests/test"
#define OUTPUT  "./tests/morse"


int main(int argc, char *argv[])
{
    FILE *source, *destination;
    /*char *space = " ";

    printf("asci: %d %d %d %d %d %d %d %d\n\n\n", '0', '9', 'a', 'z', 'A', 'Z', ' ', '\n');


    printf("is morseable: %d\n", is_morseable(' '));
    printf("is strcmp space: %d\n", strncmp(" ", SPACE, sizeof(SPACE)));
    printf("is space: %d\n", !strncmp(" ", SPACE, sizeof(SPACE)));
    printf("is space: %d\n", is_space(" "));
    */
    source = fopen(INPUT, "r");
    if (source == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    destination = fopen(OUTPUT, "w+");
    if (destination == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    printf_morse(source, destination);

    printf("End of file reached successfully.\n");
    fclose(source);
    fclose(destination);
    return 0;
}
