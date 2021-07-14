#ifndef __CONVERSION_H__
#define __CONVERSION_H__

#define TRUE        1
#define FALSE       0

#define NEWLINE     "\n"
#define SPACE       " "
#define WORDSEP     "/"
#define CHARSEP     " "
#define NOCHAR      "\0"


void print_fun(FILE *source, FILE *destination);
void to_morse(char *string, const char input);
int is_morseable(const char input);

#endif
