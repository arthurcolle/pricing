CC = g++
TARGET = pricing
RM = rm

CFLAGS  = -Wall -I/usr/local/include
LFLAGS_0 = -L/usr/local/lib/
LFLAGS_1 = -lgsl -lgslcblas -lm

all: $(TARGET).exe

$(TARGET).exe: $(TARGET).o
	$(CC) $(LFLAGS_0) $(TARGET).o $(LFLAGS_1) -o $(TARGET).exe

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $(TARGET).c

clean:
	$(RM) *.exe *.o

