cmake_minimum_required(VERSION 3.11)
project("mandelbrot")

SET(SRCS
  src/count_pixel.cpp
  src/draw.cpp
  src/main.cpp
  src/tests.cpp
)

add_library(lclib STATIC ${SRCS})
target_include_directories(lclib PUBLIC "include")
target_compile_options(lclib PRIVATE -msse4.1 -msse4.2 -mavx2 -mavx -O3) 

add_executable(main src/main.cpp)
target_link_libraries(main lclib -lcsfml-graphics -lcsfml-system -lcsfml-window -lm)

