TARGET = bitarray
CC = gcc
CFALGS = -Wall
#CCOV = -fprofile-arcs -ftest-coverage
CCOV = --coverage

all: $(TARGET)

$(TARGET): main.o $(TARGET).o
	$(CC) main.o $(TARGET).o -o $(TARGET)

%.o: %.c %.h
	$(CC) -c $(CFLAGS) $< -o $@

%.o_test: %.c %.h
	$(CC) -c $(CFLAGS) $< -o $@ $(CCOV)

test: $(TARGET).o_test main.o
	$(CC) $^ -o $@ $(CCOV)
	./test
	gcov $(TARGET)

run:
	./$(TARGET)

clean:
	rm -f *.o $(TARGET) *.gcno *.gcda test *.o_test