CC=gcc
OBJECTS=main.o darr.o
TARGET=darr



all:${OBJECTS}
	${CC} $^ -o ${TARGET}
clean:
	rm *.o ${TARGET}
	



