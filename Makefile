CC = gcc
FLAGS = -lcsfml-graphics -lcsfml-system -lcsfml-window -msse4.1 -msse4.2 -mavx2 -mavx -O0 
# -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations \
# 		-Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts \
# 		-Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal \
# 		-Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op \
# 		-Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self \
# 		-Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel \
# 		-Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types \
# 		-Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code \
# 		-Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers \
# 		-Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new \
# 		-fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging \
# 		-fno-omit-frame-pointer -pie -fPIE -Werror=vla \
# 		-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

II = -I ./common

all: directory mandelbrot

directory:
	@mkdir -p obj

mandelbrot: ./obj/main.o ./obj/draw.o ./obj/count.o ./obj/count2.o ./obj/tests.o ./obj/color.o
	g++ $(II) ./obj/main.o ./obj/draw.o ./obj/count.o ./obj/count2.o ./obj/tests.o ./obj/color.o -o main $(FLAGS)

./obj/main.o: ./main.cpp
	$(CC) $(II) -c ./main.cpp -o ./obj/main.o $(FLAGS)

./obj/count.o: ./count_set/src/count.cpp
	$(CC) $(II) -c ./count_set/src/count.cpp -o ./obj/count.o $(FLAGS)

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
