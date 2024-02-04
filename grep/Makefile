CC=gcc
CFLAGS=-Wall -Wextra -Werror

TARGET=s21_grep

SRCS=grep.c grep_realization.c ../common/input_data.c ../common/test.c ../common/check_files.c ../cat/cat_realization.c

OBJS=$(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

all: s21_grep

rebuild: clean all

s21_grep: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(TARGET)
