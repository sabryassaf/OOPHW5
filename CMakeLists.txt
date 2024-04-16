cmake_minimum_required(VERSION 3.27)
project(OOPHW5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(part1)
include_directories(part2)
include_directories(Provided)
include_directories(Provided/part1)
include_directories(Provided/part2)

add_executable(OOPHW5
        part1/OOP5EventException.h
        part2/MoveVehicle.h
        part2/Printer.h
        part2/TransposeList.h
        Provided/part1/OOP5EventException.h
        Provided/part1/Part1Examples.cpp
        Provided/part2/Part2Examples.cpp
        Provided/part2/TransposeList.h
        part1/Observer.h
        part1/Subject.h
        part2/List.h
        part2/Utilities.h
        part2/Direction.h
        part2/BoardCell.h
        part2/CellType.h
        part2/GameBoard.h
        part2/RushHour.h)
