CC		= gcc
CFLAGS		= -ansi -std=c99 -Wall -Wextra -O2 -Werror -DDEBUG
LIBS		= #-lcurl

# all source files
_SOURCES	= main.c hello.c util.c memmanageman.c

# the directories used during build
SRCDIR		= src
OBJDIR		= obj
BINDIR		= bin
DOCDIR		= doc

# the output executable
EXECUTABLE	= executable_name.out

# fixing directories and stuff - do not change
_OBJECTS	= $(_SOURCES:.c=.o)
OBJECTS 	= $(patsubst %,$(OBJDIR)/%,$(_OBJECTS))

SOURCES 	= $(patsubst %,$(SRCDIR)/%,$(_SOURCES))


all: clean $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $(BINDIR)/$(EXECUTABLE) $(CFLAGS) $(OBJECTS) $(LIBS)

$(EXECUTABLE)_static: $(OBJECTS)
	$(CC) -o $(BINDIR)/$(EXECUTABLE) -static-libgcc $(CFLAGS) $(OBJECTS) `curl-config --static-libs`


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $(CFLAGS) $<

.PHONY: doc
doc:
	doxygen Doxyfile

clean:
	rm -f $(OBJDIR)/*.o
	rm -f *.tmp
	rm -f $(BINDIR)/$(EXECUTABLE)
	rm -f $(DOCDIR)/html/*
	rm -f $(DOCDIR)/html || rmdir $(DOCDIR)/html

run: $(EXECUTABLE)
	echo "==== starting ===="
	./$(BINDIR)/$(EXECUTABLE)

analysis: $(EXECUTABLE)
	ltrace -n 2 -fiS -o ltrace.tmp ./$(BINDIR)/$(EXECUTABLE)
	objdump -D $(BINDIR)/$(EXECUTABLE) > disas.tmp
