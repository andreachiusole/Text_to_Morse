# -*- Makefile -*-
CC      = gcc
CFLAGS  = -I. -g -std=c89


SRCDIR    = src
OBJDIR    = obj

SOURCES   = $(wildcard $(SRCDIR)/*.c)
DEPS      = $(wildcard $(SRCDIR)/*.h)
OBJECTS   = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

TESTUNITS = $(wildcard tests/units/*)

morse: $(OBJECTS)
	@$(CC) -o $@ $^ $(CFLAGS)
	@echo -e "\n\tEverything compiled successfully\n"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(DEPS)
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo -e "  Compiled "$<""

# Target to run tests

test: $(TESTUNITS)
	@$(RM) tmpfile

$(TESTUNITS): morse
	@./$< $@ -o tmpfile
	@diff -q tmpfile $(patsubst tests/units/%,tests/checks/%_check,$@) && \
		echo -e "  $(patsubst tests/units/%,%,$@): test passed"


.PHONY: clean

clean:
	$(RM) -r $(OBJDIR)
	$(RM) morse
	@$(RM) tmpfile

# #credits
# https://www.gnu.org/software/make/manual/make.html#Text-Functions
# https://cs.colby.edu/maxwell/courses/tutorials/maketutor/
