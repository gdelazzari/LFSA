TARGET=LFSA_example

$(TARGET): example.o LFSA.o
	gcc -o $(TARGET) example.o LFSA.o

example.o: example.c LFSA.h
	gcc -c example.c -o example.o

LFSA.o: LFSA.c LFSA.h
	gcc -c LFSA.c -o LFSA.o

run:
	$(TARGET)
	
clean:
	rm -f $(TARGET) example.o LFSA.o
