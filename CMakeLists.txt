cmake_minimum_required(VERSION 3.16)
project(la)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wpedantic")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(SOURCES
    la.h
    la.c
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
# set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C) 
target_include_directories(${PROJECT_NAME} PUBLIC . )

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.13.0
)
FetchContent_MakeAvailable(googletest)

include(CTest)

add_subdirectory(test)
