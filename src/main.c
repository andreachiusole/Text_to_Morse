#include <stdio.h>
#include <stdlib.h>     /* # define EXIT_FAILURE 1 */
#include <string.h>
#include <getopt.h>

#include "conversion.h"

/*
struct option {
    const char *name; // long version option name
    int has_args;
    int *flag;
    int val;
};
*/

void help()
{
    printf("Usage: ./morse FILE [OPTION]...\n");
    printf("    Encode FILE in morse code.\n\n");
    printf("    Options:\n");
    printf("      -o, --output DEST     set DEST as the output file where to save the \n");
    printf("                              encoded text\n");
    printf("      -c, --char-sep SEP    use SEP as separator between characters [default:' ']\n");
    printf("      -w, --word-sep SEP    use SEP as separator between words     [default:'//']\n");
    printf("      -h, --help            show usage\n");
}

int main(int argc, char *argv[])
{
    int help_flag = FALSE;
    int err_flag  = FALSE;
    char *output_name = NULL;
    char *char_separator = CHARSEP;
    char *word_separator = WORDSEP;
    int c;

    FILE *source, *destination;

    static struct option long_options[] =
    {
        {"output",      required_argument, 0, 'o'},
        {"char-sep",    required_argument, 0, 'c'},
        {"word-sep",    required_argument, 0, 'w'},
        {"help",        no_argument,       0, 'h'},
        {0, 0, 0, 0}
    };

    while ((c = getopt_long(argc, argv, ":ho:c:w:", long_options, NULL)) != -1)
    {
        switch (c)
        {
            case 'o': output_name    = optarg;  break;
            case 'c': char_separator = optarg;  break;
            case 'w': word_separator = optarg;  break;
            case 'h': help_flag = TRUE;         break;

            case ':': /* missing option argument */
                fprintf(stderr, "%s: option '-%c' requires an argument\n", argv[0], optopt);
                err_flag = TRUE;
                break;
            case '?': /* invalid option */
                fprintf(stderr, "%s: option '-%c' is invalid: ignored\n", argv[0], optopt);
                err_flag = TRUE;
                break;
        }
    }

    if (help_flag == TRUE || err_flag == TRUE)
    {
        help();
        if (help_flag == TRUE)
            exit(EXIT_SUCCESS);
        else
            exit(EXIT_FAILURE);
    }

    /* Check if source file has been passed correctly */
    if (argc == optind)
    {
        fprintf(stderr, "%s: source file missing\n", argv[0]);
        exit(EXIT_FAILURE);

    }

    if ((argc - optind) > 1)
    {
        fprintf(stderr, "%s: too many arguments: ", argv[0]);

        while (optind < argc)
            {
                fprintf(stderr, "'%s' ", argv[optind++]);
            }
        fputc('\n', stderr);

        exit(EXIT_FAILURE);
    }

    if ((argc - optind) == 1)
    {
        source = fopen(argv[optind], "r");
        if (source == NULL)
        {
            perror("Error opening source file");
            exit(EXIT_FAILURE);
        }
    }

    /* Check if destination file has been passed */
    if (output_name != NULL)
    {
        destination = fopen(output_name, "w+");
        if (destination == NULL) {
            perror("Error opening destination file");
            exit(EXIT_FAILURE);
        }
        print_morse(source, destination, TRUE, char_separator, word_separator);
        fclose(destination);
    }
    else
    {
        printf("   Encoding of file: '%s'\n\n", argv[optind]);
        print_morse(source, NULL, FALSE, char_separator, word_separator);
        printf("\n   End of file reached.\n");
    }


    fclose(source);
    return 0;
}
