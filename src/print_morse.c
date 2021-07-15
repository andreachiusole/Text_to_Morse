#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conversion.h"

void append_to_morse_file(FILE *dest, const char input)
{
    char ch_morse[7];
    to_morse(ch_morse, input);
    fprintf(dest, "%s", ch_morse);
    printf("%s", ch_morse);
}


void print_fun(FILE *source, FILE *destination)
{
    char ch_curr = fgetc(source), ch_next;
    int initial_whitespace = TRUE;

    while (!feof(source))
    {
        ch_next = fgetc(source);
        printf("'%c' '%c'\n", ch_curr, ch_next);
        // check next char isn't EOF so we can continue
        if (feof(source))
        {
            printf("serterte'%c' '%c'\n", ch_curr, ch_next);
            append_to_morse_file(destination, ch_curr);
            break;
        }

        // skip if: char not morseable or space+space or
        //          space+newline or newline+newline
        if (!is_morseable(ch_curr) ||

            strncmp(&ch_curr, SPACE, sizeof(SPACE)) &&
            strncmp(&ch_next, NEWLINE, sizeof(NEWLINE)) ||

            strncmp(&ch_curr, SPACE, sizeof(SPACE)) &&
            strncmp(&ch_next, SPACE, sizeof(SPACE)) ||

            strncmp(&ch_curr, NEWLINE, sizeof(NEWLINE)) &&
            strncmp(&ch_next, NEWLINE, sizeof(NEWLINE))
            )
        {
            ch_curr = ch_next;
            continue;
        }
        if ((strncmp(&ch_curr, SPACE, sizeof(SPACE)) ||
             strncmp(&ch_curr, NEWLINE, sizeof(NEWLINE))) &&
             is_morseable(ch_next) &&
             initial_whitespace
            )
        {
            // ch_next is the first morseable char
            initial_whitespace = FALSE;

            ch_curr = ch_next;
            continue;
        }
        printf("'%c' '%c'\n", ch_curr, ch_next);

        append_to_morse_file(destination, ch_curr);
    }
}
