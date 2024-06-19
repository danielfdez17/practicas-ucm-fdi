TARGET = main
CC = gcc
CFLAGS = -g -Wall 
OBJS = main.o
SOURCES = $(addsuffix .c, $(basename $(OBJS)))
HEADERS = 
LIBS = -lpthread

all: $(TARGET)

$(TARGET): $(OBJS) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

.c.o: 
	$(CC) $(CFLAGS) -c  $< -o $@

$(OBJS): $(HEADERS)

clean: 
	-rm -f *.o $(TARGET) 
