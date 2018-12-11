CC = g++
CXX = gcc
RM= rm -f
CPPFLAGS = -g -std=c++11 -Wall


SRCS = app.cpp Landmarks.cpp Node.cpp
OBJS = $(subst .cc,.o,$(SRCS))

all: app
	
app: $(OBJS)
	$(CC) $(CPPFLAGS) -o app $(OBJS)

app.o: app.cpp Landmarks.h Strategy.h

Landmarks.o: Landmarks.h Node.h Landmarks.cpp

Node.o: Node.h Node.cpp

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) tool


	
