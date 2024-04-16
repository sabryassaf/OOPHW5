#ifndef OOPHW5_BOARDCELL_H
#define OOPHW5_BOARDCELL_H

#include "CellType.h"
#include "Direction.h"

///CELL TYPE := EMPTY/RED CAR/ OTHER CARS/TRUCKS
///Direction := THE DIRECTION OF THE CAR IS CURRENTLY ON THE CELL -- HORIZONTAL/VERTICAL --
///CAR'S LENGTH THAT IS ON THE CURRENT CELL
template<CellType CT, Direction Dir, int Len>
struct BoardCell {
    constexpr static CellType type = CT;
    constexpr static Direction direction = Dir;
    constexpr static int length = Len;
};



#endif //OOPHW5_BOARDCELL_H
