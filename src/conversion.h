#ifndef __CONVERSION_H__
#define __CONVERSION_H__

#define TRUE        1
#define FALSE       0

#define NEWLINE     '\n'
#define SPACE       ' '
#define WORDSEP     "//"
#define CHARSEP     " "
#define NOCHAR      "\0"


void print_morse(FILE *source, FILE *destination,
				 const char *ch_sep, const char *wd_sep);

void to_morse(char *string, const char *wd_sep, const char input);

int is_morseable(const char input);

#endif
