#include <stdio.h>
#include <string.h>
#include <ctype.h>      /* tolower() function */

#include "conversion.h"

/*------------------------------------------------------- *
* Check if the given char can be converted to morse       *
* or is either a space or a new line.                     *
* ------------------------------------------------------- */
int is_morseable(const char input)
{
    return (input >= '0' && input <= '9') ||
           (input >= 'A' && input <= 'Z') ||
           (input >= 'a' && input <= 'z') ||
           (input == '.') || (input == ',') ||
           (input == ':') || (input == '?') ||
           (input == '=') || (input == '-') ||
           (input == '(') || (input == ')') ||
           (input == '\"') || (input == '\'') ||
           (input == '/') || (input == '@') ||
           (input == '!');
}


/*------------------------------------------------------- *
* Appends to the given string the morse equivalent of     *
* input.                                                  *
* ------------------------------------------------------- */
void to_morse(char *string, const char *wd_sep, const char input)
{
    if (input == NEWLINE)
    {
        strcpy(string, "\n");
        return;
    }

    if (input == SPACE)
    {
        strcat(string, wd_sep);
        return;
    }

    if (is_morseable(input))
    {
        switch(tolower(input))
        {
            case 'a':   strcat(string, ".-");      break;
            case 'b':   strcat(string, "-...");    break;
            case 'c':   strcat(string, "-.-.");    break;
            case 'd':   strcat(string, "-..");     break;
            case 'e':   strcat(string, ".");       break;
            case 'f':   strcat(string, "..-.");    break;
            case 'g':   strcat(string, "--.");     break;
            case 'h':   strcat(string, "....");    break;
            case 'i':   strcat(string, "..");      break;
            case 'j':   strcat(string, ".---");    break;
            case 'k':   strcat(string, "-.-");     break;
            case 'l':   strcat(string, ".-..");    break;
            case 'm':   strcat(string, "--");      break;
            case 'n':   strcat(string, "-.");      break;
            case 'o':   strcat(string, "---");     break;
            case 'p':   strcat(string, ".--.");    break;
            case 'q':   strcat(string, "--.-");    break;
            case 'r':   strcat(string, ".-.");     break;
            case 's':   strcat(string, "...");     break;
            case 't':   strcat(string, "-");       break;
            case 'u':   strcat(string, "..-");     break;
            case 'v':   strcat(string, "...-");    break;
            case 'w':   strcat(string, ".--");     break;
            case 'x':   strcat(string, "-..-");    break;
            case 'y':   strcat(string, "-.--");    break;
            case 'z':   strcat(string, "--..");    break;

            case '1':   strcat(string, ".----");   break;
            case '2':   strcat(string, "..---");   break;
            case '3':   strcat(string, "...--");   break;
            case '4':   strcat(string, "....-");   break;
            case '5':   strcat(string, ".....");   break;
            case '6':   strcat(string, "-....");   break;
            case '7':   strcat(string, "--...");   break;
            case '8':   strcat(string, "---..");   break;
            case '9':   strcat(string, "----.");   break;
            case '0':   strcat(string, "-----");   break;

            case '.':   strcat(string, ".-.-.-");  break;
            case ',':   strcat(string, "--..--");  break;
            case ':':   strcat(string, "---...");  break;
            case '?':   strcat(string, "..--..");  break;
            case '=':   strcat(string, "-...-");   break;
            case '-':   strcat(string, "-....-");  break;
            case '(':   strcat(string, "-.--.");   break;
            case ')':   strcat(string, "-.--.-");  break;
            case '\"':  strcat(string, ".-..-.");  break;
            case '\'':  strcat(string, ".----.");  break;
            case '/':   strcat(string, "-..-.");   break;
            case '@':   strcat(string, ".--.-.");  break;
            case '!':   strcat(string, "-.-.--");  break;

            default: /* input is not a morseable char */
                break;
        }
    }
}
