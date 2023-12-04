cmake_minimum_required(VERSION 3.5.0)
project(matrix_fltk VERSION 0.1.0 LANGUAGES C CXX)


set(SOURCES test_main.cpp
            src/graphic.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${FLTK_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
