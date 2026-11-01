TARGET = mse

COMMAND_NAME = mse

PREFIX ?= /usr/local

SRCS = mse.c func.c draw.c
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -g
LIBS = -lncurses

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.c *.h
	$(CC) $(CFLAGS) -c $< -o $@

install: all
	@echo " Instalando $(COMMAND_NAME) em $(PREFIX)/bin..."
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f $(TARGET) $(DESTDIR)$(PREFIX)/bin/$(COMMAND_NAME)
	chmod 755 $(DESTDIR)$(PREFIX)/bin/$(COMMAND_NAME)

uninstall:
	@echo " Removendo $(COMMAND_NAME) de $(PREFIX)/bin..."
	rm -f $(DESTDIR)$(PREFIX)/bin/$(COMMAND_NAME)

clean:
	rm -f $(TARGET) $(OBJS)
