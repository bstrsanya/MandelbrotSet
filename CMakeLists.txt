cmake_minimum_required(VERSION 3.11)
project("mandelbrot")

SET(SRCS
  ./../src/count_pixel.c
  ./../src/draw.c
  ./../src/main.c
  ./../src/tests.c
)

add_library(lclib STATIC ${SRCS})
target_include_directories(lclib PUBLIC "include")
target_compile_options(lclib PRIVATE -msse4.1 -msse4.2 -mavx2 -mavx -O3) 

add_executable(main ./../src/main.c)
target_link_libraries(main lclib -lcsfml-graphics -lcsfml-system -lcsfml-window -lm)

