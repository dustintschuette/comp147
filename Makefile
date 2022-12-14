CC=g++
EXECUTABLE=scanner
all: $(EXECUTABLE)

$(EXECUTABLE): main.o
	$(CC) main.o -o $(EXECUTABLE)

main.o: main.cpp
	$(CC) -c main.cpp -std=c++11
clean:
	rm -rf *.o $(EXECUTABLE)

