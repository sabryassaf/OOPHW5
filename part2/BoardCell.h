#ifndef OOPHW5_BOARDCELL_H
#define OOPHW5_BOARDCELL_H

#include "Direction.h"
#include "CellType.h"


template<CellType CT, Direction Dir, int Len>
struct BoardCell {
    constexpr static CellType type = CT;
    constexpr static Direction direction = Dir;
    constexpr static int length = Len;
};



#endif //OOPHW5_BOARDCELL_H
