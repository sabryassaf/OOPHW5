#ifndef CODE_MOVEVEHICLE_H
#define CODE_MOVEVEHICLE_H

#include "CellType.h"
#include "Direction.h"
#include "GameBoard.h"
#include "Utilities.h"
#include "TransposeList.h"

#include <iostream>
#include "Printer.h"

using namespace std;

template<CellType Type, Direction Dir, int A>
struct Move {
    static_assert(Type != EMPTY, "Cannot move empty cell");

    constexpr static CellType type = Type;
    constexpr static Direction direction  = Dir;
    constexpr static int amount = A;
};

template <typename , int, int, Direction, int>
struct MoveVehicle;

template <typename BOARD, int R, int C, Direction D, CellType, bool>
struct MoveVehicleOneStep;

// MoveVehicle horizontally - recursive case
template <typename gameBoard, int R, int C ,int A>
struct MoveVehicle <gameBoard, R, C, Direction::RIGHT, A>  {
    // boundaries check
    static_assert(gameBoard::length - 1 >= R, "Bad row");
    static_assert(gameBoard::width - 1 >= C, "Bad column");
    // get the cell to move and check if it's not empty
    typedef typename GetAtIndex<C, typename GetAtIndex<R,typename gameBoard::board>::value>::value cell;
    static_assert(cell::type != EMPTY, "Cannot move empty cell");

    // recursive call
    typedef GameBoard<typename MoveVehicleOneStep<typename MoveVehicle <gameBoard, R, C, Direction::RIGHT, A-1>::board::board, R, C+A-1, Direction::RIGHT, cell::type, false>::board> board;
};

template <typename gameBoard, int R, int C ,int A>
struct MoveVehicle <gameBoard, R, C, Direction::LEFT, A>  {
    // boundaries check
    static_assert(gameBoard::length - 1 >= R, "Bad row");
    static_assert(gameBoard::width - 1 >= C, "Bad column");
    // get the cell to move and check if it's not empty
    typedef typename GetAtIndex<C, typename GetAtIndex<R,typename gameBoard::board>::value>::value cell;
    static_assert(cell::type != EMPTY, "Cannot move empty cell");

    // recursive call
    typedef GameBoard<typename MoveVehicleOneStep<typename MoveVehicle <gameBoard, R, C, Direction::LEFT,
            A-1>::board::board, R, C-A+1, Direction::LEFT, cell::type, false>::board> board;
};

// MoveVehicle horizontally - base cases
template <typename gameBoard, int R, int C>
struct MoveVehicle <gameBoard, R, C, Direction::RIGHT, 1>  {
    // boundaries check
    static_assert(gameBoard::length - 1 >= R, "Bad row");
    static_assert(gameBoard::width - 1 >= C, "Bad column");
    // get the cell to move and check if it's not empty
    typedef typename GetAtIndex<C, typename GetAtIndex<R,typename gameBoard::board>::value>::value cell;
    static_assert(cell::type != EMPTY, "Cannot move empty cell");

    typedef GameBoard<typename MoveVehicleOneStep<typename gameBoard::board, R, C, Direction::RIGHT, cell::type,
        false>::board> board;
};

template <typename gameBoard, int R, int C>
struct MoveVehicle <gameBoard, R, C, Direction::LEFT, 1>  {
    // boundaries check
    static_assert(gameBoard::length - 1 >= R, "Bad row");
    static_assert(gameBoard::width - 1 >= C, "Bad column");
    // get the cell to move and check if it's not empty
    typedef typename GetAtIndex<C, typename GetAtIndex<R,typename gameBoard::board>::value>::value cell;
    static_assert(cell::type != EMPTY, "Cannot move empty cell");

    typedef GameBoard<typename MoveVehicleOneStep<typename gameBoard::board, R, C, Direction::LEFT, cell::type,
            false>::board> board;
};

// MoveCar vertically - recursive case
// In this case, we can utilize RIGHT and LEFT calls when handling DOWN and UP calls respectively
template <typename gameBoard, int R, int C ,int A>
struct MoveVehicle <gameBoard, R, C, Direction::UP, A>  {
    // boundaries check
    static_assert(gameBoard::length - 1 >= R, "Bad row");
    static_assert(gameBoard::width - 1 >= C, "Bad column");
    // get the cell to move and check if it's not empty
    typedef typename GetAtIndex<C, typename GetAtIndex<R,typename gameBoard::board>::value>::value cell;
    static_assert(cell::type != EMPTY, "Cannot move empty cell");
    // check if the car in cell is vertical
    static_assert(cell::direction == UP || cell::direction == DOWN, "Bad movement direction");

    typedef GameBoard<typename Transpose<typename MoveVehicle<GameBoard<typename Transpose<typename gameBoard::board>::matrix>, C, R, LEFT, A>::board::board>::matrix> board;
};


template <typename gameBoard, int R, int C ,int A>
struct MoveVehicle <gameBoard, R, C, Direction::DOWN, A>  {
    // boundaries check
    static_assert(gameBoard::length - 1 >= R, "Bad row");
    static_assert(gameBoard::width - 1 >= C, "Bad column");
    // get the cell to move and check if it's not empty
    typedef typename GetAtIndex<C, typename GetAtIndex<R,typename gameBoard::board>::value>::value cell;
    static_assert(cell::type != EMPTY, "Cannot move empty cell");
    // check if the car in cell is vertical
    static_assert(cell::direction == UP || cell::direction == DOWN, "Bad movement direction");

    typedef GameBoard<typename Transpose<typename MoveVehicle<GameBoard<typename Transpose<typename gameBoard::board>::matrix>, C, R, RIGHT, A>::board::board>::matrix> board;
};

// Since we handle horizontal movement directly, and transpose vertical movement into horizontal,
// we only need to implement OneStep for horizontal movement.
// --
// MoveVehicleOneStep horizontally - recursive case
template <typename gameBoard, int R, int C, CellType Type, bool B>
struct MoveVehicleOneStep <gameBoard, R, C, Direction::RIGHT, Type, B>  {
    typedef typename GetAtIndex<R, gameBoard>::value currentRow;
    typedef typename GetAtIndex<C, currentRow>::value currentCell;
    typedef typename GetAtIndex<C-1, currentRow>::value closeCell;

    static constexpr int vehicleLength = currentCell::length;
    static constexpr int index = ConditionalInteger<closeCell::type != currentCell::type,
            vehicleLength + C,
            C
    >::value;
    static_assert(index <= gameBoard::head::size - 1, "exiting bounds");
    typedef typename GetAtIndex<index, currentRow>::value objToReplace;
    static_assert(!(currentCell::type == Type && closeCell::type != currentCell::type && objToReplace::type != EMPTY), "movement blocked");


    typedef typename SetAtIndex<index, currentCell, currentRow>::list updatedRow;
    typedef typename SetAtIndex<C, objToReplace, updatedRow>::list updatedRow2;
    typedef typename SetAtIndex<R, updatedRow2, gameBoard>::list changedBoard;

    static constexpr bool stepCondition = closeCell::type == currentCell::type;
    typedef typename Conditional<stepCondition,
            typename MoveVehicleOneStep <gameBoard, R, C-1, Direction::RIGHT, Type, !stepCondition || B>::board,
            changedBoard
    >::value board;
};

template <typename gameBoard, int R, int C, CellType Type, bool B>
struct MoveVehicleOneStep <gameBoard, R, C, Direction::LEFT, Type, B>  {
    typedef typename GetAtIndex<R, gameBoard>::value currentRow;
    typedef typename GetAtIndex<C, currentRow>::value currentCell;
    typedef typename GetAtIndex<C-1, currentRow>::value closeCell;

    static constexpr int vehicleLength = currentCell::length;
    static constexpr int index = ConditionalInteger<closeCell::type != currentCell::type,
            vehicleLength + C - 1,
            C
    >::value;

    static_assert(!(closeCell::type != EMPTY && closeCell::type != currentCell::type && currentCell::type == Type), "movement blocked");

    typedef typename SetAtIndex<index, closeCell, currentRow>::list updatedRow;
    typedef typename SetAtIndex<C - 1, currentCell, updatedRow>::list updatedRow2;
    typedef typename SetAtIndex<R, updatedRow2, gameBoard>::list changedBoard;

    static constexpr bool stepCondition = closeCell::type == currentCell::type;
    typedef typename Conditional<stepCondition,
            typename MoveVehicleOneStep <gameBoard, R, C-1, Direction::LEFT, Type, !stepCondition || B>::board,
            changedBoard
    >::value board;
};

// MoveVehicleOneStep horizontally - base cases
template <typename gameBoard, int R, CellType Type, bool B>
struct MoveVehicleOneStep <gameBoard, R, 0, Direction::RIGHT, Type, B>  {
    typedef typename GetAtIndex<R, gameBoard>::value currentRow;
    typedef typename GetAtIndex<0, currentRow>::value cell;
    static constexpr int vehicleLength = cell::length;

    static_assert(vehicleLength <= gameBoard::head::size - 1, "exiting bounds");
    typedef typename GetAtIndex<vehicleLength, currentRow>::value objToReplace;
    static_assert(!(objToReplace::type != EMPTY && cell::type != EMPTY && !B), "movement blocked");

    typedef typename SetAtIndex<vehicleLength, cell, currentRow>::list updatedRow;
    typedef typename SetAtIndex<0, objToReplace, updatedRow>::list updatedRow2;
    typedef typename SetAtIndex<R, updatedRow2, gameBoard>::list board;
};

template <typename gameBoard, int R, CellType Type, bool B>
struct MoveVehicleOneStep <gameBoard, R, 1, Direction::LEFT, Type, B>  {
    typedef typename GetAtIndex<R, gameBoard>::value currentRow;
    typedef typename GetAtIndex<1, currentRow>::value cell;
    typedef typename GetAtIndex<0, currentRow>::value closeCell;
    static constexpr int vehicleLength = cell::length;

    static_assert(closeCell::type == EMPTY || B, "movement blocked");

    typedef typename SetAtIndex<vehicleLength, closeCell, currentRow>::list first_updated_list;
    typedef typename SetAtIndex<0, cell, first_updated_list>::list updated_list;
    typedef typename SetAtIndex<R, updated_list, gameBoard>::list board;
};

#endif //CODE_MOVEVEHICLE_H
