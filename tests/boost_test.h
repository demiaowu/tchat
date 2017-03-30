//
// Created by demiaowu on 2017/3/29.
//

#ifndef TCHAT_BOOST_TEST_H
#define TCHAT_BOOST_TEST_H
#include <iostream>

#include <boost/asio.hpp>
#include <boost/circular_buffer.hpp>

#include <gtest/gtest.h>

struct node {
public:
    node(int value = 0) : val_(value) {

    }
    int val_;
};

TEST(cirbuff_test, usage) {
    boost::circular_buffer<node*> cn(3);

    node* n1 = new node(1);
    node* n2 = new node(2);
    node* n3 = new node(3);

    cn.push_back(n1);
    cn.push_back(n2);
    cn.push_back(n3);

    EXPECT_EQ(1, cn[0]->val_);
    EXPECT_EQ(2, cn[1]->val_);
    EXPECT_EQ(3, cn[2]->val_);

    cn.push_back(cn[0]);
    EXPECT_EQ(2, cn[0]->val_);
    EXPECT_EQ(3, cn[1]->val_);
    EXPECT_EQ(1, cn[2]->val_);
    cn.push_back(cn[0]);
    cn.push_back(cn[0]);

    EXPECT_EQ(1, cn[0]->val_);
    EXPECT_EQ(2, cn[1]->val_);
    EXPECT_EQ(3, cn[2]->val_);

    node* n4 = new node(4);

    node* p = cn.front();
    cn.push_back(n4);
    EXPECT_EQ(1, p->val_);
    EXPECT_EQ(2, cn[0]->val_);
    EXPECT_EQ(3, cn[1]->val_);
    EXPECT_EQ(4, cn[2]->val_);
}

#endif //TCHAT_BOOST_TEST_H
