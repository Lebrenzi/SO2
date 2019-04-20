

run:
	g++ -std=c++14 -o program  main.cpp Circle.h Circle.cpp Direction.h -lncurses -lpthread
	./program

clean:
	rm -f program
