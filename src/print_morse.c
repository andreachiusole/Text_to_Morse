#include <stdio.h>
#include <string.h>

#include "conversion.h"

/*------------------------------------------------------- *
* Print at dest the result of the translation of input    *
* into morse code. The parameter separator_flag is used   *
* to add the separator between letters before translating.*
* ------------------------------------------------------- */
static void append_to_morse_file(FILE *dest, const char input,
                                 const int separator_flag,
                                 const int is_there_output_file,
                                 const char *ch_sep, const char *wd_sep)
{
    char ch_morse[20] = "\0";

    /* Concatenate the separator between chars */
    if (separator_flag)
    {
        strcat(ch_morse, ch_sep);
    }

    to_morse(ch_morse, wd_sep, input);

    if (is_there_output_file)
    {
        fprintf(dest, "%s", ch_morse);
    }
    else
    {
        printf("%s", ch_morse);
    }
}


/*------------------------------------------------------- *
* Reads the content of source char by char and after      *
* skipping non morseable chars and duplicates of spaces   *
* and newlines calls the function to print the result of  *
* the conversion in destination.                          *
* The values of the flags initial_whitespace and          *
* word_finished are updated at the end of every cycle.    *
* ------------------------------------------------------- */
void print_morse(FILE *source, FILE *destination,
                 int is_there_output_file,
                 const char *ch_sep, const char *wd_sep)
{
    char ch_curr = fgetc(source), ch_next;
    int initial_whitespace = TRUE;
    int word_finished = TRUE;

    while (!feof(source))
    {
        ch_next = fgetc(source);
        /* Check if next char is EOF to print last char */
        if (feof(source))
        {
            append_to_morse_file(destination, ch_curr,
                                 !word_finished, is_there_output_file,
                                 ch_sep, wd_sep);
            if (is_there_output_file)
                printf("\n\tEnd of file reached.\n");
            break;
        }

        /* Tabs are converted into spaces */
        if (ch_next == '\t')
        {
            ch_next = ' ';
        }

        /* Skip non morseable char until a morsable one is reached */
        if (!(is_morseable(ch_next) ||
              ch_next == SPACE ||
              ch_next == NEWLINE)
            )
        {
            continue;
        }

        /* Check if ch_curr is the first char */
        if (is_morseable(ch_curr) && initial_whitespace == TRUE)
        {
            initial_whitespace = FALSE;
        }
        else
        /* Skip whitespaces before the first char */
        if ((ch_curr == SPACE || ch_curr == NEWLINE) &&
             initial_whitespace
            )
        {
            ch_curr = ch_next;
            continue;
        }

        /* Skip: duplicates (space+space or newline+newline)
                 and space before space+newline */
        if ((ch_curr == SPACE)   && (ch_next == SPACE) ||
            (ch_curr == NEWLINE) && (ch_next == NEWLINE) ||
            (ch_curr == SPACE)   && (ch_next == NEWLINE)
            )
        {
            ch_curr = ch_next;
            continue;
        }

        append_to_morse_file(destination, ch_curr,
                             !word_finished, is_there_output_file,
                             ch_sep, wd_sep);

        /* Update flag for initial whitespace */
        if (ch_curr == NEWLINE)
        {
            initial_whitespace = TRUE;
        }

        /* Update flag for word end reached */
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
