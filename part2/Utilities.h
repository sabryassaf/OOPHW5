#ifndef OOPHW5_Utilities_H
#define OOPHW5_Utilities_H

/////////// I AM NOT SURE THAT THIS FILE IS DONE



///CONDETIONAL STRUCT
/// T := THE VALUE IF TRUE
/// F := THE VALUE IF FALSE
template<bool b, typename T,typename F>
struct Conditional{};

template<typename T, typename F>
struct Conditional<true, T, F> {
    typedef T value;
};

template<typename T, typename F>
struct Conditional<false, T, F> {
    typedef F value;
};

///CONDITIONAL INTEGER STRUCT
template<bool b, int T,int F>
struct ConditionalInteger{};

template<int T, int F>
struct ConditionalInteger<true, T, F> {
    constexpr static int value = T;
};

template<int T, int F>
struct ConditionalInteger<false, T, F> {
    constexpr static int value = F;
};


#endif //OOPHW5_Utilities_H
