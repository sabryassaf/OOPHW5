#ifndef OOPHW5_GAMEBOARD_H
#define OOPHW5_GAMEBOARD_H

#include "List.h"
#include "BoardCell.h"


template<typename List>
struct GameBoard {
    typedef List board;
    constexpr static int width = List::head::size;
    constexpr static int length = List::size;
};



#endif //OOPHW5_GAMEBOARD_H
