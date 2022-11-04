cmake_minimum_required(VERSION 3.23)
project(ECECITY C)

set(CMAKE_C_STANDARD 99)

add_executable(ECECITY main.c mabiblio.c mabiblio.h)

target_link_libraries(ECECITY -lmingw32 -lalleg44)

file(COPY "fichiers" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "saved_games" DESTINATION ${CMAKE_BINARY_DIR})