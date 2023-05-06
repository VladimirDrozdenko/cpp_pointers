#pragma once 

#include <iostream>
#include "base.h"


class Derived: public Base {
public:
    Derived() : Base() {
        std::cout << "Derived created [" << this << "]" << std::endl;
    }

    virtual void speak() {
        std::cout << "-- I'm Derived [" << this << "]" << std::endl;
    }

    virtual ~Derived() {
        std::cout << "Derived destroyed [" << this << "]" << std::endl;
    }

    static void custom_deleter(Derived* ptr) {
        std::cout << "Calling custom Derived deleter." << std::endl;
        delete ptr;
    } 
};