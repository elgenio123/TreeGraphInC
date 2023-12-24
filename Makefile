CC = gcc
CFLAGS = -Wall -g -fopenmp

TARGET = my_program

SRCS = tree.c graph.c others.c main.c

# Targets and dependencies
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) 


