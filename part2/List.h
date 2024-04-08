#ifndef OOPHW5_LIST_H
#define OOPHW5_LIST_H

///LIST INITIALIZATION
template<typename... TT>
struct List {
    constexpr static int size = 0;
};

template<typename T>
struct List<T> {
    typedef T head;
    constexpr static int size = 1;
};

template<typename T, typename... TT>
struct List<T,TT...> {
    typedef T head;
    typedef List<TT...> next;
    constexpr static int size = sizeof...(TT) + 1;
};

///PREPEND LIST
/// LT := LIST TYPE
template<typename LT,typename T>
struct prependList{};

template<typename LT,typename... T>
struct prependList<LT, List<T...>> {
    typedef List<LT, T...> list;
};

///GET AT INDEX
template<int N, typename T>
struct GetAtIndex {
    typedef T value;
};

template<typename T, typename... TT>
struct GetAtIndex<0, List<T,TT...>> {
    typedef T value;
};

template<int N, typename T, typename... TT>
struct GetAtIndex<N, List<T, TT...>> {
    typedef typename GetAtIndex<N-1, List<TT...>>::value value;
};

///SET AT INDEX
template<int N,typename U,typename T>
struct SetAtIndex {
    typedef List<> list;
};

template<typename U, typename T, typename... TT>
struct SetAtIndex<0, U, List<T,TT...>> {
    typedef List<U, TT...> list;
};

template<int N,typename U,typename T, typename... TT>
struct SetAtIndex<N, U, List<T, TT...>> {
    typedef typename prependList<T, typename SetAtIndex<N-1, U, List<TT...>>::list>::list list;
};

#endif //OOPHW5_LIST_H
