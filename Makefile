CXX = g++
LDFLAGS = -lGL -lglfw

exec: main.o
	$(CXX) -o $@ $^ $(LDFLAGS)


main.o: src/main.cpp
	$(CXX) -c src/main.cpp


clean:
	rm -f *.o exec
