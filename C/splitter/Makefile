CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = splitter_demo
SOURCES = main.c splitter.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

.PHONY: clean