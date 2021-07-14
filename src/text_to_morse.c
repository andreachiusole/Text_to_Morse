#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>      //used for tolower() function

#include "conversion.h"

void append_to_morse_file(FILE *dest, const char input)
{
    char ch_morse[7];
    to_morse(ch_morse, input);
    fprintf(dest, "%s", ch_morse);
    //printf("%s", ch_morse);
}

int is_morseable(const char input)
{
    return (input >= '0' && input <= '9') ||
           (input >= 'A' && input <= 'Z') ||
           (input >= 'a' && input <= 'z');
}

/*--------------------------*/
// appends to the given string the morse equivalent of input
void to_morse(char *string, const char input)
{
    if (strncmp(&input, NEWLINE, 1))
    {
        strcat(string, NEWLINE);
        return;
    }

    if (input == ' ')
    {
        strcat(string, WORDSEP);
        return;
    }

    if (is_morseable(input))
    {
        switch(tolower(input))
        {
            case 'a':   strcat(string, ".-");     break;
            case 'b':   strcat(string, "-...");   break;
            case 'c':   strcat(string, "-.-.");   break;
            case 'd':   strcat(string, "-..");    break;
            case 'e':   strcat(string, ".");      break;
            case 'f':   strcat(string, "..-.");   break;
            case 'g':   strcat(string, "--.");    break;
            case 'h':   strcat(string, "....");   break;
            case 'i':   strcat(string, "..");     break;
            case 'j':   strcat(string, ".---");   break;
            case 'k':   strcat(string, "-.-");    break;
            case 'l':   strcat(string, ".-..");   break;
            case 'm':   strcat(string, "--");     break;
            case 'n':   strcat(string, "-.");     break;
            case 'o':   strcat(string, "---");    break;
            case 'p':   strcat(string, ".--.");   break;
            case 'q':   strcat(string, "--.-");   break;
            case 'r':   strcat(string, ".-.");    break;
            case 's':   strcat(string, "...");    break;
            case 't':   strcat(string, "-");      break;
            case 'u':   strcat(string, "..-");    break;
            case 'v':   strcat(string, "...-");   break;
            case 'w':   strcat(string, ".--");    break;
            case 'x':   strcat(string, "-..-");   break;
            case 'y':   strcat(string, "-.--");   break;
            case 'z':   strcat(string, "--..");   break;

            case '1':   strcat(string, ".----");  break;
            case '2':   strcat(string, "..---");  break;
            case '3':   strcat(string, "...--");  break;
            case '4':   strcat(string, "....-");  break;
            case '5':   strcat(string, ".....");  break;
            case '6':   strcat(string, "-....");  break;
            case '7':   strcat(string, "--...");  break;
            case '8':   strcat(string, "---..");  break;
            case '9':   strcat(string, "----.");  break;
            case '0':   strcat(string, "-----");  break;
        }
    }
    return;
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
        if (!feof(source))
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
