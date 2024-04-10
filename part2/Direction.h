#ifndef OOPHW5_DIRECTION_H
#define OOPHW5_DIRECTION_H

#include "GameBoard.h"
#include "List.h"
#include "Utilities.h"


enum Direction {
    UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3
};

///BASIC STRUCTS FOR COMPARING UP/DOWN && RIGHT/LEFT
template<Direction dir>
struct DirectionValue{
    constexpr static int value = 0;
};

///HORIZONTAL DIRECTIONS
template<>
struct DirectionValue<RIGHT> {
    constexpr static int value = 1;
};

template<>
struct DirectionValue<LEFT> {
    constexpr static int value = 1;
};

///VERTICAL DIRECTIONS
template<>
struct DirectionValue<UP> {
    constexpr static int value = 2;
};

template<>
struct DirectionValue<DOWN> {
    constexpr static int value = 2;
};

///SPECIFIC COORDINATION ---- SPECIFIC CELL
template<int ROW, int COLUMN>
struct Coordinate {
    constexpr static int row = ROW;
    constexpr static int col = COLUMN;
    typedef Coordinate<row, col> place;
};

///FIND THE FRONT
template<typename GameBoard, int ROW, int COL, Direction DIR>
struct GetFront {
    constexpr static int row = ROW + (DIR == RIGHT) - (DIR == LEFT);
    constexpr static int col = COL + (DIR == DOWN) - (DIR == UP);

    static_assert((row >= 0) && (col >= 0), "Can't Be in Both Directions!");
    static_assert((row < GameBoard::length) && (col < GameBoard::Width), "Bad Coordinates");

    typedef typename GetAtIndex<COL, typename GetAtIndex<ROW, typename GameBoard::board>:: value>::value boardOldCell;
    typedef typename GetAtIndex<col, typename GetAtIndex<row, typename GameBoard::board>:: value>::value boardNewCell;

    static_assert((boardNewCell::type == EMPTY) || (boardOldCell::type == boardNewCell::type), "Wrong Direction!");

    constexpr static bool isFront = (boardNewCell::type == EMPTY);
    typedef Coordinate<row, col> tempCoordinate;
    ///FIND THE FIRST EMPTY CELL
    typedef typename Conditional<isFront, tempCoordinate, GetFront<GameBoard, row, col, DIR>>::value value;
};

#endif //OOPHW5_DIRECTION_H
