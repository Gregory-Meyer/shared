cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

find_package(benchmark REQUIRED)
find_package(Threads REQUIRED)

include_directories(include)

add_library(vecc SHARED src/vec.c)
add_library(veccxx SHARED src/vec.cpp)

add_library(vec_wrapper STATIC src/vec_wrapper.cpp)
target_link_libraries(vec_wrapper ${CMAKE_DL_LIBS})

add_executable(client src/main.cpp)
target_link_libraries(client vec_wrapper)

add_executable(bench_vec_wrapper src/bench.cpp)
target_link_libraries(bench_vec_wrapper benchmark benchmark_main
                                        Threads::Threads vec_wrapper)
