TARGET = bitarray
CC = gcc
CFALGS = -Wall
#CCOV = -fprofile-arcs -ftest-coverage
CCOV = --coverage
TEST = test
DIR = report

# ya dima ya dima

.PHONY: $(TARGET)

$(TARGET): main.o $(TARGET).o
	$(CC) main.o $(TARGET).o -o $(TARGET)

%.o: %.c %.h
	$(CC) -c $(CFLAGS) $< -o $@

%.o_test: %.c %.h
	$(CC) $(CCOV) -c $(CFLAGS) $< -o $@

$(TEST): $(TARGET).o_test main.o
	$(CC) $(CCOV) $^ -o $@
	./$(TEST)
	#gcov $@
	lcov -t "$@" -o $(TARGET).info -c -d .
	genhtml -o $(DIR) $(TARGET).info

run: $(TARGET)
	./$(TARGET)

mem_check: $(TEST)
	valgrind ./$(TEST)

clean: clean_regular clean_test

clean_regular:
	rm -f *.o $(TARGET)
	
clean_test:
	rm -f *.gcno *.gcda $(TEST) *.o_test *.info *.gcov
	rm -rf $(DIR)
