CC = gcc
CFLAGS = -Wall -g

TARGET = my_program

SRCS = main.c tree.c graph.c

# Targets and dependencies
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) 


