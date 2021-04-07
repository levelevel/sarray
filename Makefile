CFLAGS=-std=c11 -g -Wall -pedantic-errors -Wunused-parameter

TARGET=sarray
SRC=$(TARGET).c
HEAD=$(SRC:.c=.h)
OBJ=$(SRC:.c=.o)

TEST_SRC=test.c
TEST_OBJ=$(TEST_SRC:.c=.o)
TEST=a.out

$(OBJ): $(SRC) $(HEAD)
$(TEST_OBJ): $(TEST_SRC) $(HEAD)

$(TEST): $(TEST_OBJ) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test: $(TEST)
	./$(TEST)

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TEST)

.PHONY: clean test
