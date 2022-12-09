#ifndef __VEHICLE_H__
#define __VEHICLE_H__

#include "driver.h"

class Vehicle {
public:
    Vehicle(std::string name)
        : modelName(name)
    {}

    virtual void run() { std::cout << modelName << " is running.\n"; }

protected:
    const std::string modelName;
    Driver* owner;
    std::string license;
};

#endif