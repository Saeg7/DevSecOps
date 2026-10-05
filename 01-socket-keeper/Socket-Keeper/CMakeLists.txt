cmake_minimum_required(VERSION 3.16)
project(SocketKeeper CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(socket_keeper src/main.cpp)

find_package(Threads REQUIRED)
target_link_libraries(socket_keeper PRIVATE Threads::Threads)
