CC = g++
FLAGS = -lcsfml-graphics -lcsfml-system -lcsfml-window -O3


all: directory mandelbrot

directory:
	@mkdir -p obj

mandelbrot: ./obj/main.o ./obj/draw.o ./obj/count.o ./obj/count1.o ./obj/count2.o ./obj/tests.o 
	g++ ./obj/main.o ./obj/draw.o ./obj/count.o ./obj/count1.o ./obj/count2.o ./obj/tests.o -o main $(FLAGS)

./obj/main.o: ./main.cpp
	$(CC) $(II) -c ./main.cpp -o ./obj/main.o $(FLAGS)

./obj/count.o: ./count.cpp
	$(CC) $(II) -c ./count.cpp -o ./obj/count.o $(FLAGS)

./obj/count1.o: ./count1.cpp
	$(CC) $(II) -c ./count1.cpp -o ./obj/count1.o $(FLAGS)

./obj/count2.o: ./count2.cpp
	$(CC) $(II) -c ./count2.cpp -o ./obj/count2.o $(FLAGS)

./obj/draw.o: ./draw.cpp
	$(CC) $(II) -c ./draw.cpp -o ./obj/draw.o $(FLAGS)

./obj/tests.o: ./tests.cpp
	$(CC) $(II) -c ./tests.cpp -o ./obj/tests.o $(FLAGS)

clean:
	rm -rf ./obj main
