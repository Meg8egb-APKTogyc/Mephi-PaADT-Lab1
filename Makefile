TARGET=test.exe

all: $(TARGET)

$(TARGET): main.o DynamicArray.o
	gcc main.o DynamicArray.o -o $(TARGET)

main.o: main.c
	gcc -c main.c -o main.o

DynamicArray.o: DynamicArray.c
	gcc -c DynamicArray.c -o DynamicArray.o

.PHONY: clean

clean:
	rm -f *.o

fullclean: clean
	rm -f *.exe