cmake_minimum_required(VERSION 3.5.0)


set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_C_COMPILER "/bin/gcc")
project(matrix VERSION 0.1.0 LANGUAGES   CXX)

include(CTest)
enable_testing()
add_executable(matrix main.cpp input.cpp matrix_window.cpp Editor.cpp Buffer.cpp)


find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(matrix ${CURSES_LIBRARIES})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
