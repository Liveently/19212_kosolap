#include <iostream>
#include <gtest/gtest.h>
#include "test.cpp"

using namespace std;


int main() {

    testing::InitGoogleTest();
    RUN_ALL_TESTS();


    cout<<"end";
    return 0;
}

