TARGET = bitarray
CC = gcc
CFALGS = -Wall
CCOV = -fprofile-arcs -ftest-coverage

all: $(TARGET)

$(TARGET): main.o $(TARGET).o
	$(CC) main.o $(TARGET).o -o $(TARGET)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ $(CCOV)

test: $(TARGET).o main.o
	$(CC) $^ -o $@ $(CCOV)
	./test
	gcov $(TARGET)

run:
	./$(TARGET)

clean:
	rm -f *.o $(TARGET) *.gcno *.gcda test