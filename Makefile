CC = gcc
CFLAGS = -Wall -g -fopenmp

TARGET = prog

SRCS = src/tree.c src/queue.c main.c

# Targets and dependencies
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) 


