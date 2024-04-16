#ifndef OOPHW5_SUBJECT_H
#define OOPHW5_SUBJECT_H

#include "Observer.h"
#include "OOP5EventException.h"
#include <vector>

using std::vector;
using namespace std;

template<typename T>
class Subject {
    vector<Observer<T> *> observers;
public:
    void notify(const T& message) {
        for(Observer<T>* obs : observers)
            obs->handleEvent(message);
    }

    void addObserver(Observer<T>& observer) {
        typename vector<Observer<T> *>::iterator it = find(observers.begin(), observers.end(), &observer);
        if (it != observers.end())
            throw ObserverAlreadyKnownToSubject();

        observers.push_back(&observer);
    }

    void removeObserver(Observer<T>& observer) {
        typename vector<Observer<T> *>::iterator it = find(observers.begin(), observers.end(), &observer);
        if (it == observers.end())
            throw ObserverUnknownToSubject();

        observers.erase(it);
    }

    Subject<T>& operator+=(Observer<T>& observer) {
        addObserver(observer);
        return *this;
    }

    Subject<T>& operator-=(Observer<T>& observer) {
        removeObserver(observer);
        return *this;
    }

    Subject<T>& operator()(const Observer<T>& message) {
        notify(message);
        return *this;
    }
};

#endif //OOPHW5_SUBJECT_H
