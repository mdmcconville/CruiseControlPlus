CC = clang++
CFLAGS = -std=c++14 -stdlib=libc++ -w

main: main.o driving.o
	xcrun $(CC) $(CFLAGS) -o main main.o driving.o

main.o: main.cpp driving.h
	$(CC) $(CFLAGS) -c main.cpp

driving.o: driving.cpp driving.h
	$(CC) $(CFLAGS) -c driving.cpp
	
clean:
	$(RM) main *.o *~