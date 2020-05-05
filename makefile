# the compiler
CC = g++

# directories of various parts of the source code
SOURCEDIR = source
OBJDIR = obj
INCDIR = include

# compiler flags:
#  -g			adds debugging information to the executable file
#  -Wall		turns on most, but not all, compiler warnings
#  -Wpedantic	turns on additional compiler warnings
#  -Werror		turns every warning into an error
CFLAGS = -I$(INCDIR) -g -Wall -Wpedantic -Werror -DMEMTRACE

# executable name
NAME = cppKontakte.run

# dependencies
_IDEPS = cppStructures.hpp cppStatus.hpp cppExporter.hpp cppConsole.hpp
IDEPS = $(patsubst %,$(INCDIR)/%,$(_IDEPS))
_OBJ = main.o cppConsole.o memtrace.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

# final compilation and cleanup:
  $(NAME) : $(OBJ)
	$(CC) $^ -o $(NAME) $(CFLAGS)
	rm -f $(OBJDIR)/*.o *~ core $(SOURCEDIR)/*~ $(SOURCEDIR)/core $(INCDIR)/*~

# object file compilation:
  $(OBJDIR)/%.o: $(SOURCEDIR)/%.cpp $(IDEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
