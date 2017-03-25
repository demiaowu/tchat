//
// Created by demiaowu on 2017/3/24.
//

#ifndef TCHAT_TEST_UTILS_H
#define TCHAT_TEST_UTILS_H
#include <cstring>


const int TEST_MAX_CUTOFFLINE_LENGTH = 64;

// Print the cut-off line to better visual effect
#define CUT_OFF_LINE(descr)   \
    {   \
        std::cout << std::endl; \
        std::cout << std::endl; \
        int descrLen = strlen(descr);   \
        for (auto i=1; i<=(TEST_MAX_CUTOFFLINE_LENGTH-descrLen)/2; i++) \
            std::cout << "*";    \
        std::cout << descr;     \
        for (auto i=1; i<=(TEST_MAX_CUTOFFLINE_LENGTH-descrLen)/2; i++) \
            std::cout << "*";   \
        std::cout << std::endl;   \
    }


#define LAUNCH_TEST(func_)  \
    CUT_OFF_LINE(#func_##"()")  \
    func_();  \
    CUT_OFF_LINE(#func_##"()")

#endif //TCHAT_TEST_UTILS_H
