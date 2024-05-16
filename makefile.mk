CC = gcc
CFLAGS = -Wall -Wextra -I.
LDFLAGS =
RM = rm -f

SRCS = main.c student.c
OBJS = $(SRCS:.c=.o)
HEADER = student.h
EXECUTABLE = grade_card_program

DATA_FILE = student_data.txt

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(EXECUTABLE) $(OBJS) $(DATA_FILE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

store_data: $(EXECUTABLE)
	./$(EXECUTABLE)

search_data: $(EXECUTABLE)
	./$(EXECUTABLE) search

.PHONY: all clean run store_data search_data
