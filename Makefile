# -*- Makefile -*-
CC		= gcc
CFLAGS	= -I. -g


SRCDIR	= src
OBJDIR	= obj

SOURCES	= $(wildcard $(SRCDIR)/*.c)
DEPS	= $(wildcard $(SRCDIR)/*.h)
OBJECTS	= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

exe: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

test: exe
	@./$<

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(DEPS)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo -e "\tCompiled "$<" successfully!"

.PHONY: clean output_clean

output_clean:
	$(RM) ./tests/morse

clean: output_clean
	$(RM) -r ./obj
	$(RM) exe

# #credits
# https://cs.colby.edu/maxwell/courses/tutorials/maketutor/
# https://www.gnu.org/software/make/manual/make.html#Text-Functions
