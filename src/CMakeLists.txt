cmake_minimum_required(VERSION 3.23.3)
project(cardproj)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SOURCES main.cpp cardproj.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ../inc/)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})