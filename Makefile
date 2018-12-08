.SUFFIXES: .c .o

CC = gcc
SRCDIR = src/
CFLAGS = -g

SERVER_SRC = $(SRCDIR)server.c
CLIENT_SRC = $(SRCDIR)client.c
RESULT = received.txt

TARGET = server client
all : $(TARGET)

server : $(SERVER_SRC)
	$(CC) -o $@ $<

client : $(CLIENT_SRC)
	$(CC) -o $@ $<

clean:
	rm $(TARGET) $(RESULT)
