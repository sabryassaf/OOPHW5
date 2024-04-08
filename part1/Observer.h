#ifndef OOPHW5_OBSERVER_H
#define OOPHW5_OBSERVER_H

template <typename T>
class Observer {
public:
    Observer() = default;
    virtual void handleEvent(const T&) = 0;
};


#endif //OOPHW5_OBSERVER_H
