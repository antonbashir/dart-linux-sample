cmake_minimum_required(VERSION 3.16.0)
project(sample_native C ASM)

add_definitions("-D_GNU_SOURCE")
set(CMAKE_REQUIRED_DEFINITIONS "-D_GNU_SOURCE")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fPIC -O0 -g  -fno-stack-protector")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} -fPIC -O3 -fno-stack-protector")

file(GLOB sources
  *.c
  *.h
)

set(INTERACTOR_PATH "")
set(INTERACTOR_PATH_TRIMMED "")
set(INTERACTOR_RESULT "")
set(INTERACTOR_DIRECTORY "")
execute_process(
  COMMAND dart run ../dart/bin/interactor.dart
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  RESULT_VARIABLE INTERACTOR_RESULT
  OUTPUT_VARIABLE INTERACTOR_PATH
)
cmake_path(GET INTERACTOR_PATH PARENT_PATH INTERACTOR_DIRECTORY)
string(REPLACE "\n" "" INTERACTOR_PATH_TRIMMED "${INTERACTOR_PATH}")
set(INTERACTOR_INCLUDE_DIRECTORY ${INTERACTOR_DIRECTORY}/../../native/include)

include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${INTERACTOR_INCLUDE_DIRECTORY})

add_library(sample_native SHARED ${sources})
target_link_libraries(sample_native PRIVATE "${INTERACTOR_PATH_TRIMMED}")
add_custom_command(TARGET sample_native POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sample_native> ${CMAKE_CURRENT_SOURCE_DIR}/../dart/native/libsample.so)