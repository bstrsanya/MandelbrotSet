CC = g++
FLAGS = -lcsfml-graphics -lcsfml-system -lcsfml-window -O3
II = -I ./common

all: directory mandelbrot

directory:
	@mkdir -p obj

mandelbrot: ./obj/main.o ./obj/draw.o ./obj/count.o ./obj/count1.o ./obj/count2.o ./obj/tests.o ./obj/color.o
	g++ $(II) ./obj/main.o ./obj/draw.o ./obj/count.o ./obj/count1.o ./obj/count2.o ./obj/tests.o ./obj/color.o -o main $(FLAGS)

./obj/main.o: ./main.cpp
	$(CC) $(II) -c ./main.cpp -o ./obj/main.o $(FLAGS)

./obj/count.o: ./count_set/src/count.cpp
	$(CC) $(II) -c ./count_set/src/count.cpp -o ./obj/count.o $(FLAGS)

./obj/count1.o: ./count_set/src/count1.cpp
	$(CC) $(II) -c ./count_set/src/count1.cpp -o ./obj/count1.o $(FLAGS)

./obj/count2.o: ./count_set/src/count2.cpp
	$(CC) $(II) -c ./count_set/src/count2.cpp -o ./obj/count2.o $(FLAGS)

./obj/draw.o: ./draw_set/draw.cpp
	$(CC) $(II) -c ./draw_set/draw.cpp -o ./obj/draw.o $(FLAGS)

./obj/tests.o: ./tests_set/src/tests.cpp
	$(CC) $(II) -c ./tests_set/src/tests.cpp -o ./obj/tests.o $(FLAGS)

./obj/color.o: ./count_set/src/color.cpp
	$(CC) $(II) -c ./count_set/src/color.cpp -o ./obj/color.o $(FLAGS)

clean:
	rm -rf ./obj main
