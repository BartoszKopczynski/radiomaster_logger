cmake_minimum_required(VERSION 3.10)
project(boxer_stick_logger)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(boxer_logger
    src/main.cpp
    src/JoystickReader.cpp
    src/CSVLogger.cpp
)

