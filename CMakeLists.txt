cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Werror -Wextra -g")

enable_testing()
add_subdirectory(third-party/googletest)
add_subdirectory(test)
