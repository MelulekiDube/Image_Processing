#Make file for Image Processor
#Created on: Thu Feb 19 00:18:08 1970
#Meluleki Dube

#Directories
SRCDIR=src
BUILDDIR=build
TESTDIR= test
BINDIR = bin

CPP =g++
CPPFLAGS =-std=c++11 -g -Wall
TARGET=imageops.run
TEST_TARGET =$(BINDIR)/imageops_testing.run
SRC=$(SRCDIR)/Image.cpp $(SRCDIR)/iterator.cpp $(SRCDIR)/Filter.cpp $(SRCDIR)/main.cpp $(TESTDIR)/Testingfile.cpp 
OBJECTS=$(BUILDDIR)/Image.o $(BUILDDIR)/iterator.o $(BUILDDIR)/Filter.o $(BUILDDIR)/main.o 
TEST_OBJECTS= $(BUILDDIR)/Image.o $(BUILDDIR)/iterator.o $(BUILDDIR)/Filter.o $(BUILDDIR)/Testingfile.o 

$(TARGET): $(OBJECTS)
	@echo "-------------------------------------------------------------------------------------------";
	@echo "Linking the object files to create imageops.run";
	$(CPP) $(OBJECTS)-o $@ $(CPPFLAGS)
	@mv $@ $(BINDIR)
$(OBJECTS): $(SRC)
	@echo "-------------------------------------------------------------------------------------------";
	@echo "Producing Object files";
	$(CPP) $< -c $(SRC) $(CPPFLAGS)
	@mv *.o $(BUILDDIR)

test:$(OBJECTS)
	@echo "-------------------------------------------------------------------------------------------";
	@echo "Linking the object files to create imageops_test.run";
	$(CPP) $(TEST_OBJECTS) -o $(TEST_TARGET) $(CPPFLAGS)

run:
	./$(TARGET)

run_test:
	./$(TEST_TARGET)

clean:
	@echo "Cleaning.............";
	rm -f -r $(BUILDDIR)/*.o $(BINDIR)/*.run
# end of Makefile