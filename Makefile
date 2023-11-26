.PHONY: all clean

TARGET=profs

all: ${TARGET}

profs: profs.o fat.o dentry.o blockset.o fsfunctions.c messages.c

profs.o: profs.c profs.h
fat.o: fat.c profs.h
dentry.o: dentry.c profs.h
blockset.o: blockset.c profs.h
fsfunctions.o: fsfunctions.c profs.h
messages.o: messages.c profs.h

clean:
	rm -f *~
	rm -f *.o
	rm -f ${TARGET}
