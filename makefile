# the compiler: gcc for C program, define as g++ for C++
  CC = g++

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
  #  -Werror turns every warning into an
  CFLAGS = -g -Wall -Wpedantic -Werror
  NAME = cKontakte.run
  SOURCEDIR = source
  OBJDIR = obj

  IDEPS = 
  _OBJ = main.o
  OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

  # the build target executable:

  $(NAME) : $(OBJ)
	$(CC) $^ -o $(NAME) $(CFLAGS)
	rm -f $(OBJDIR)/*.o *~ core $(SOURCEDIR)/*~ $(SOURCEDIR)/core

  $(OBJDIR)/%.o: $(SOURCEDIR)/%.cpp $(IDEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
