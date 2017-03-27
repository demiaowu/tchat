//
// Created by demiaowu on 2017/3/27.
//

#ifndef TCHAT_CPP_TEST_H
#define TCHAT_CPP_TEST_H
#include <iostream>
#include <gtest/gtest.h>

using namespace std;

class Base {
public:
    virtual void test() = 0;
};

class Derived : public Base {
public:
    void test() override {
        std::cout<< "Derived.test()" << std::endl;
    }
};

TEST(cppderived, usage) {
    Derived derived;
    derived.test();
}

#endif //TCHAT_CPP_TEST_H
