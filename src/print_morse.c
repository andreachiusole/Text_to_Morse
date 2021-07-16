#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conversion.h"

/*------------------------------------------------------- *
* Print at dest the result of the translation of input    *
* into morse code. The parameter char_sep is used to add  *
* the separator between letters before translating.       *
* ------------------------------------------------------- */
void append_to_morse_file(FILE *dest, const char input, int char_sep)
{
    char ch_morse[7] = "\0";

    // Concatenate the separator between chars
    if (char_sep)
    {
        strcat(ch_morse, CHARSEP);
    }
    to_morse(ch_morse, input);

    fprintf(dest, "%s", ch_morse);
}


/*------------------------------------------------------- *
* Reads the content of source char by char and after      *
* skipping non morseable chars and duplicates of spaces   *
* and newlines calls the function to print the result of  *
* the conversion in destination.                          *
* The values of the flags initial_whitespace and          *
* word_finished are updated at the end of every cycle.    *
* ------------------------------------------------------- */
void print_morse(FILE *source, FILE *destination)
{
    char ch_curr = fgetc(source), ch_next;
    int initial_whitespace = TRUE;
    int word_finished = TRUE;

    while (!feof(source))
    {
        ch_next = fgetc(source);
        // Check if next char is EOF to print last char
        if (feof(source))
        {
            append_to_morse_file(destination, ch_curr, !word_finished);
            break;
        }

        // Skip non morseable char until a morsable one is reached
        if (!(is_morseable(ch_next) ||
              ch_next == SPACE ||
              ch_next == NEWLINE)
            )
        {
            continue;
        }

        // Skip whitespaces before the first char
        if ((ch_curr == SPACE || ch_curr == NEWLINE) &&
             initial_whitespace
            )
        {
            // Check if ch_next is the first char
            if (is_morseable(ch_next))
            {
                initial_whitespace = FALSE;
            }
            ch_curr = ch_next;
            continue;
        }

        // Skip: duplicates (space+space or newline+newline)
        //       and space before space+newline
        if ((ch_curr == SPACE)   && (ch_next == SPACE) ||
            (ch_curr == NEWLINE) && (ch_next == NEWLINE) ||
            (ch_curr == SPACE)   && (ch_next == NEWLINE)
            )
        {
            ch_curr = ch_next;
            continue;
        }

        append_to_morse_file(destination, ch_curr, !word_finished);

        // Update flag for initial whitespace.
        // The checks done to skip duplicates prevent from having
        // other scenarios
        if ((ch_curr == NEWLINE) && (ch_next == SPACE))
        {
            initial_whitespace = TRUE;
        }

        //Update flag for word end reached.
        if (is_morseable(ch_curr) &&
            (ch_next == SPACE || ch_next == NEWLINE))
        {
            word_finished = TRUE;
        }
        else if (is_morseable(ch_curr) && is_morseable(ch_next))
        {
            word_finished = FALSE;
        }

        ch_curr = ch_next;
    }
}
