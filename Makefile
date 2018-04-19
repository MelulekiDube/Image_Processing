#Make file for Image Processor
#Created on: Thu Feb 19 00:18:08 1970

#Meluleki Dube
CPP =g++
CPPFLAGS =-std=c++11
TARGET=imageops
SRC=Image.cpp main.cpp 
OBJECTS=Image.o main.o 


$(TARGET): $(OBJECTS)
	$(CPP) $(OBJECTS)-o $@ $(CPPFLAGS)

$(OBJECTS): $(SRC)
	$(CPP) $< -c $(SRC) $(CPPFLAGS)

run:
	./$(TARGET)

clean:
	rm -f -r *.o bin/*.o

# end of Makefile