#ifndef OOPHW5_RUSHHOUR_H
#define OOPHW5_RUSHHOUR_H

#include "MoveVehicle.h"

template <typename Board, int ROW, int COL, CellType CT>
struct FindIndexes{
    typedef typename GetAtIndex<COL, typename GetAtIndex<ROW,typename Board::board>::value>::value object;

    static constexpr int row = ConditionalInteger<object::type == CT, ROW, FindIndexes<Board, ROW - 1, COL, CT>::row>::value;
    static constexpr int col = ConditionalInteger<object::type == CT, COL, FindIndexes<Board, ROW - 1, COL, CT>::col>::value;
};

template <typename Board, int ROW, int COL, int Left>
struct CheckWayEmpty{
    typedef typename GetAtIndex<C, typename GetAtIndex<ROW,typename Board::board>::value>::value object;
    static constexpr bool result = object::type == EMPTY && CheckWayEmpty<Board, ROW, C + 1, Left - 1>::result;
};

template <typename Board, int ROW, int COL>
struct CheckWayEmpty<Board, ROW, COL, 1>{
    typedef typename GetAtIndex<COL, typename GetAtIndex<ROW,typename Board::board>::value>::value object;
    static constexpr bool result = object::type == EMPTY;
};

template <typename Board, int ROW, int COL>
struct CheckWayEmpty<Board, ROW, COL, 0>{
    static constexpr bool result = true;
};

// Check Win
template<typename Board>
struct CheckWin {
    typedef FindIndexes<Board, Board::length - 1, Board::width - 1, CellType::X> position;
    constexpr static int row = position::row;
    constexpr static int col = position::col;
    constexpr static bool result = CheckWayEmpty<Board, row, col+1, Board::width - col - 1>::result;
};

template<typename Board, CellType CT>
struct FindIndexes<Board, 0, 0, CT> {
    typedef typename GetAtIndex<0, typename GetAtIndex<0,typename Board::board>::value>::value object;
    static constexpr int row = 5;
    static constexpr int col = 2;
};

template<typename Board , int COL, CellType CT>
struct FindIndexes<Board, 0, COL, CT> {
    typedef typename GetAtIndex<COL, typename GetAtIndex<0,typename Board::board>::value>::value object;

    static constexpr int row = ConditionalInteger<object::type == CT, 0,
                                            FindIndexes<Board, Board::length-1, COL - 1, CT>::row>::value;
    static constexpr int col = ConditionalInteger<object::type == CT, COL,
                                            FindIndexes<Board, Board::length-1, COL - 1, CT>::col>::value;
};

template<typename Board, typename T, int LEFT>
struct CheckSolutionAux{};

template<typename Board, typename T, typename... TT, int Left>
struct CheckSolutionAux<Board, List<T, TT...>, Left> {
    typedef T move;
    typedef FindIndexes<Board, Board::length - 1, Board::width - 1, move::type> position;
    typedef typename MoveVehicle<Board, position::row, position::col, move::direction, move::amount>::board one_move_board;
    typedef typename CheckSolutionAux<one_move_board, List<TT...>, Left - 1>::board board;
};

template<typename Board, typename T>
struct CheckSolutionAux<Board, List<T>, 1> {
    typedef T move;
    typedef FindIndexes<Board, Board::length - 1, Board::width - 1, move::type> position;
    typedef typename MoveVehicle<Board, position::row, position::col, move::direction, move::amount>::board board;
};

template<typename Board , typename Moves>
struct CheckSolution {
    typedef typename CheckSolutionAux<Board, Moves, Moves::size>::board board;
    constexpr static bool result = CheckWin<board>::result;
};

template<typename Board>
struct CheckSolution<Board, List<>> {
    static constexpr bool result = CheckWin<Board>::result;
};


#endif //OOPHW5_RUSHHOUR_H
