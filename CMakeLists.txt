cmake_minimum_required(VERSION 3.17)
project(BrickBreaker)

set(CMAKE_CXX_STANDARD 17)

add_library(graphics graphics.cpp Obj.hpp Ball.hpp Brick.hpp Slider.hpp StatusDir.hpp Button.hpp BrickBreaker.hpp Picture.hpp)

include_directories(include)
link_directories(lib)

target_link_libraries( graphics SDL2 SDL2.dll SDL2main SDL2_ttf SDL2_ttf.dll)


add_executable(BrickBreaker main.cpp)
target_link_libraries(BrickBreaker graphics)
