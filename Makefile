# -*- Makefile -*-
CC		= gcc
CFLAGS	= -I. -g


SRCDIR	= src
OBJDIR	= obj
OUTDIR  = out

SOURCES	= $(wildcard $(SRCDIR)/*.c)
DEPS	= $(wildcard $(SRCDIR)/*.h)
OBJECTS	= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

exe: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)
	@echo -e "\n\tEverything compiled successfully!\n"

test: exe
	@./$<

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(DEPS)
	@mkdir -p $(OBJDIR) $(OUTDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo -e "\tCompiled "$<" successfully!"

.PHONY: clean output_clean

output_clean:
	$(RM) ./out/morse.txt

clean: output_clean
	$(RM) -r $(OBJDIR) $(OUTDIR)
	$(RM) exe

# #credits
# https://cs.colby.edu/maxwell/courses/tutorials/maketutor/
# https://www.gnu.org/software/make/manual/make.html#Text-Functions
