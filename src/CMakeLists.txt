cmake_minimum_required(VERSION 3.5)
project("Event.ly")

file(GLOB SOURCES "*.cpp" "*.h")
add_executable(evently ${SOURCES})