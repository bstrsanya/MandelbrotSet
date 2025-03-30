CC = gcc
FLAGS = -lcsfml-graphics -lcsfml-system -lcsfml-window -msse4.1 -msse4.2 -mavx2 -mavx -O3
II = -I ./common

all: directory mandelbrot

directory:
	@mkdir -p obj

mandelbrot: ./obj/main.o ./obj/draw.o ./obj/count_1_type.o ./obj/count_2_type.o ./obj/tests.o ./obj/color.o ./obj/count_3_type.o
	g++ $(II) ./obj/main.o ./obj/draw.o ./obj/count_1_type.o ./obj/count_2_type.o ./obj/tests.o ./obj/color.o ./obj/count_3_type.o -o main $(FLAGS)

./obj/main.o: ./main.cpp
	$(CC) $(II) -c ./main.cpp -o ./obj/main.o $(FLAGS)

./obj/count_1_type.o: ./count_set/src/count_1_type.cpp
	$(CC) $(II) -c ./count_set/src/count_1_type.cpp -o ./obj/count_1_type.o $(FLAGS)

./obj/count_2_type.o: ./count_set/src/count_2_type.cpp
	$(CC) $(II) -c ./count_set/src/count_2_type.cpp -o ./obj/count_2_type.o $(FLAGS)

./obj/count_3_type.o: ./count_set/src/count_3_type.cpp
	$(CC) $(II) -c ./count_set/src/count_3_type.cpp -o ./obj/count_3_type.o $(FLAGS)

./obj/draw.o: ./draw_set/draw.cpp
	$(CC) $(II) -c ./draw_set/draw.cpp -o ./obj/draw.o $(FLAGS)

./obj/tests.o: ./tests_set/src/tests.cpp
	$(CC) $(II) -c ./tests_set/src/tests.cpp -o ./obj/tests.o $(FLAGS)

./obj/color.o: ./count_set/src/color.cpp
	$(CC) $(II) -c ./count_set/src/color.cpp -o ./obj/color.o $(FLAGS)

clean:
	rm -rf ./obj main
