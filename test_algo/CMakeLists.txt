cmake_minimum_required(VERSION 3.20)
project(ALGO)

set(SOURCES HashTableFuncRegAndLogInChat/chat.cpp HashTableFuncRegAndLogInChat/hash_table.cpp HashTableFuncRegAndLogInChat/sha1.cpp)
set(BINARY_NAME test_algo CACHE STRING "A name of an app")

add_executable(test_algo ${SOURCES})
target_include_directories(test_algo INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(test_algo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
