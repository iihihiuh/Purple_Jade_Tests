CC = g++
CFLG = -std=c++11 -Wall -g
OBJS = processor.o spoke.o
HEADERs = util.h encoding.h

all: spoke

spoke: $(OBJS)
	$(CC) $(CFLG) $(OBJS) -o $@

spke.o: encoding.h spoke.cc processor.h
	$(CC) $(CFLG) -c spoke.cc -o $@

processor.o : processor.h processor.cc $(HEADERs)
	$(CC) $(CFLG) -c processor.cc -o $@

clean:
	rm -rf *.o *~ *# spoke