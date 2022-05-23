TARGET = bitarray
CC = gcc
CFALGS = -Wall
#CCOV = -fprofile-arcs -ftest-coverage
CCOV = --coverage
TEST = test
DIR = report 

.PHONY: test

$(TARGET): main.o $(TARGET).o
	$(CC) main.o $(TARGET).o -o $(TARGET)

main.o: main.c $(TARGET).h
	$(CC) -c $(CFLAGS) $< -o $@

%.o: %.c %.h
	$(CC) -c $(CFLAGS) $< -o $@

%.o_test: %.c %.h
	$(CC) $(CCOV) -c $(CFLAGS) $< -o $@

test: $(TARGET).o_test main.o
	$(CC) $(CCOV) $^ -o $(TEST)
	./$(TEST)
	#gcov $@
	lcov -t "$(TEST)" -o $(TARGET).info -c -d .
	genhtml -o $(DIR) $(TARGET).info

run: $(TARGET)
	./$(TARGET)

mem_check:
	valgrind ./$(TEST)

clean: clean_regular clean_test

clean_regular:
	rm -f *.o $(TARGET)
	
clean_test:
	rm -f *.gcno *.gcda $(TEST) *.o_test *.info *.gcov
	rm -rf $(DIR)
