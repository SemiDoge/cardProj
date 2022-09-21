cmake_minimum_required(VERSION 3.23.3)
project(test)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} test.cpp)
target_link_libraries(test ${CONAN_LIBS})