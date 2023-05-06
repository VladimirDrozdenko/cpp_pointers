#pragma once

#include <iostream>

class Base {
public:
    Base() {
        std::cout << "Base created [" << this << "]" << std::endl;
    }

    virtual void speak() {
        std::cout << "-- I'm Base [" << this << "]" << std::endl;
    }

    virtual ~Base() {
        std::cout << "Base destroyed [" << this << "]" << std::endl;
    }

    static void custom_deleter(Base* ptr) {
        std::cout << "Calling custom Base deleter." << std::endl;
        delete ptr;
    } 
};