cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -g")

add_subdirectory(src)

enable_testing()
add_subdirectory(third-party/googletest)
add_subdirectory(test)
