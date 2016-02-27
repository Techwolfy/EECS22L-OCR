#####################################################
# Makefile:       
#
#####################################################

# design names
DESIGN = OCR

#libs
LIBS   = libfilter.a libfileIO.a 

CC     = g++
DEBUG  = -g -DDEBUG
CFLAGS = -ansi -Wall -c
LFLAGS = -Wall
AR     = ar rc
RANLIB = ranlib




all:clean OCR

#target to generate Image.o
Image.o: ../inc/Image.h Image.cpp
	$(CC) $(CFLAGS) Image.cpp -o Image.o

#target to generate OCR.o
OCR.o:  ../inc/Image.h OCR.cpp
	$(CC) $(CFLAGS) OCR.cpp -o OCR.o 

#target to generate OCR
OCR: OCR.o Image.o
	$(CC) $(LFLAGS) OCR.o Image.o -L. -o OCR

#target to clean the directory
clean:
	rm -f *.o *.ppm $(DESIGN) $(IMAGES) $(LIBS)
    
