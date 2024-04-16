#include <iostream>

#include "Observer.h"
#include "Subject.h"

class TemperatureSensor : public Subject<int> {};

class AirConditioner : public Observer<int> {

    static int nextId;
    int id;

    void onTemperatureChange(int temperature){
        std::cout << "Air Conditioner #" << id << " got a report from TemperatureSensor, reading " << temperature << std::endl;
    }

public:
    AirConditioner() : Observer() {
        id = (++nextId);
    }

    void handleEvent(const int& param) override {
        onTemperatureChange(param);
    }
};
int AirConditioner::nextId = 0;

