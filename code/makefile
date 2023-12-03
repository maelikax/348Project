# Team Orange - Fall 2023 EECS 348 Project
# Using info from: https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
# Using info from: https://www.twoistoomany.com/blog/2020/07/23/make-order-only-prerequisites/

IDIR=include
SRCDIR=src
ODIR=obj
#LDIR=lib


CC=g++
CFLAGS=-I$(IDIR) -O3 -std=c++11
#CFLAGS=-I$(IDIR) -g -Og -Wall -Werror -Wpedantic -std=c++11
LIBS=-lm


_DEPS = solver.hpp token.hpp shunyard.hpp rpn.hpp tests.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o solver.o token.o shunyard.o rpn.o tests.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# TODO: make object files only depend on the headers they actually use!
$(ODIR)/%.o: $(SRCDIR)/%.cpp $(DEPS) | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

calculator: $(OBJ)
	$(CC) -o calculator $^ $(CFLAGS) $(LIBS)

$(ODIR):
	mkdir $(ODIR)

.PHONY: clean
clean:
	rm -r $(ODIR)/*.o
	rm -f calculator
