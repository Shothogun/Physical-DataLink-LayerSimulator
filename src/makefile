IDIR = ../include

CC = g++
CXXFLAGS = -W -Wall -std=c++14 -I$(IDIR)

EDIR = ../exec
ODIR = ../obj

LIBS = -lm
DEBUG = -g

_DEPS = $(patsubst $(IDIR)/%,%,$(DEPS))
DEPS = $(wildcard $(IDIR)/*.hpp)

_OBJ = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS) $(DEBUG)

PDLSimulator: $(OBJ)
	$(CC) -o $(EDIR)/$@ $^ $(CXXFLAGS) $(LIBS) $(DEBUG)

.PHONY: clean

clean:
	rm -f $(wildcard $(ODIR)/*.o)
