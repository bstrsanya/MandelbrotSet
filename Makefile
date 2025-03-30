CC = gcc

DEBUG_FLAGS = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations \
		-Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts \
		-Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal \
		-Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op \
		-Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self \
		-Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel \
		-Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types \
		-Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code \
		-Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers \
		-Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new \
		-fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging \
		-fno-omit-frame-pointer -pie -fPIE -Werror=vla \
		-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

LINK_FLAGS = -lcsfml-graphics -lcsfml-system -lcsfml-window -lm

INTRINSIC = -msse4.1 -msse4.2 -mavx2 -mavx

OPTIMIZATIONS = -O3

II = -I ./include

all: directory mandelbrot

directory:
	@mkdir -p obj

mandelbrot: ./obj/main.o ./obj/draw.o ./obj/count_pixel.o ./obj/tests.o
	$(CC) $(II) ./obj/main.o ./obj/draw.o ./obj/count_pixel.o ./obj/tests.o -o main $(LINK_FLAGS)

./obj/main.o: ./main.cpp
	$(CC) $(II) -c ./main.cpp -o ./obj/main.o $(OPTIMIZATIONS)

./obj/draw.o: ./src/draw.cpp
	$(CC) $(II) -c ./src/draw.cpp -o ./obj/draw.o $(OPTIMIZATIONS)

./obj/tests.o: ./src/tests.cpp
	$(CC) $(II) -c ./src/tests.cpp -o ./obj/tests.o $(OPTIMIZATIONS)

./obj/count_pixel.o: ./src/count_pixel.cpp
	$(CC) $(II) -c ./src/count_pixel.cpp -o ./obj/count_pixel.o $(INTRINSIC) $(OPTIMIZATIONS)

clean:
	rm -rf ./obj main
