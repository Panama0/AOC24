cmake_minimum_required(VERSION 3.20)

project(Day2)
set(LANGUAGE CXX)
set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ../bin)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE H_FILES src/*.hpp)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${H_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()