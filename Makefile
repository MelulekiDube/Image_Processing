#Make file for Image Processor
#Created on: Thu Feb 19 00:18:08 1970
#Meluleki Dube


#Directories
SRCDIR=src/
BINDIR=bin/

CPP =g++
CPPFLAGS =-std=c++11 -g -Wall
TARGET=imageops
SRC=$(SRCDIR)Image.cpp $(SRCDIR)iterator.cpp $(SRCDIR)Testingfile.cpp 
OBJECTS=$(BINDIR)Image.o $(BINDIR)iterator.o $(BINDIR)Testingfile.o 


$(TARGET): $(OBJECTS)
	$(CPP) $(OBJECTS)-o $@ $(CPPFLAGS)

$(OBJECTS): $(SRC)
	$(CPP) $< -c $(SRC) $(CPPFLAGS)
	@mv *.o $(BINDIR)
run:
	./$(TARGET)

clean:
	rm -f -r bin/*.o

# end of Makefile