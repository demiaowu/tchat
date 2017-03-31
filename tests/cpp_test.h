//
// Created by demiaowu on 2017/3/27.
//

#ifndef TCHAT_CPP_TEST_H
#define TCHAT_CPP_TEST_H
#include <iostream>
#include <set>
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

    std::set<uint64_t> room_ids;

    room_ids.insert(1);
    EXPECT_TRUE(room_ids.end() != room_ids.find(1));
    EXPECT_TRUE(room_ids.end() == room_ids.find(2));

}

#endif //TCHAT_CPP_TEST_H
