#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conversion.h"

void append_to_morse_file(FILE *dest, const char input, char *temp)
{
    char ch_morse[7] = "\0";
    to_morse(ch_morse, input);
    fprintf(dest, "%s", ch_morse);
    //printf("morse: '%c' = '%s'\n", input, ch_morse);
    strcat(temp, ch_morse);
}


void print_morse(FILE *source, FILE *destination)
{
    char ch_curr = fgetc(source), ch_next;
    int initial_whitespace = TRUE;
    char temp[1000] = "\0";
    while (!feof(source))
    {
        ch_next = fgetc(source);
        // check next char isn't EOF so we can continue
        if (feof(source))
        {
            printf("final charachter: '%c' '%c'\n", ch_curr, ch_next);
            append_to_morse_file(destination, ch_curr, temp);
            break;
        }

        printf("curr:'%c' next:'%c'\n", ch_curr, ch_next);

        /* skip whitespace if before the first char */
        if ((is_space(ch_curr) || is_newline(ch_curr)) &&
             initial_whitespace
            )
        {
            /* check if ch_next is the first morseable char */
            if (is_morseable(ch_next))
            {
                initial_whitespace = FALSE;
            }
            printf("whitespace skipped\n");

            ch_curr = ch_next;
            continue;
        }

        // skip duplicates: space+space or space+newline
        //                  or newline+newline
        if (is_space(ch_curr)   && is_newline(ch_next) ||
            is_space(ch_curr)   && is_space(ch_next) ||
            is_newline(ch_curr) && is_newline(ch_next)
            )
        {
            printf("\tskipped one blank char\n");
            ch_curr = ch_next;
            continue;
        }

        if (is_newline(ch_curr) && is_space(ch_next))
        {
            initial_whitespace = TRUE;
        }

        append_to_morse_file(destination, ch_curr, temp);
        ch_curr = ch_next;
    }

    printf("char temp: '%s'\n", temp);
}
