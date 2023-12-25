CC = gcc
CFLAGS = -Wall -g -fopenmp

TARGET = prog

SRCS = others.c main.c

# Targets and dependencies
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) 


