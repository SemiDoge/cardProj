cmake_minimum_required(VERSION 3.23.3)
project(cardproj)

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SOURCES src/main.cpp src/cardproj.cpp src/entity.cpp src/textureManager.cpp src/logging.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ../inc/)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS} -lSDL2_image)