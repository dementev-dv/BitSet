TARGET = bitarray
CC = gcc
CFALGS = -Wall

all: $(TARGET)

$(TARGET): main.o $(TARGET).o
	$(CC) main.o $(TARGET).o -o $(TARGET)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm *.o $(TARGET)