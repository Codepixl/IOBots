cmake_minimum_required(VERSION 3.9)
project(IOBot)

set(CMAKE_CXX_STANDARD 17)

add_executable(IOBot main.cpp Bot.cpp Bot.h Assembly.cpp Assembly.h Assembler.cpp Assembler.h Util.cpp Util.h)