#ifndef OOPHW5_DIRECTION_H
#define OOPHW5_DIRECTION_H

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


#endif //OOPHW5_DIRECTION_H
