#include <gtest/gtest.h>
//#include "CircularBuffer.h"
#include "CircularBuffer.cpp"

using testing::Eq;
namespace {
    class CircularBufferTest : public testing::Test {
    };
}

using namespace std;

TEST_F (CircularBufferTest,  test) {


    CircularBuffer list_first(10);


    ASSERT_EQ(list_first.empty(), 1);


    list_first.push_back(1);
    list_first.push_back(2);
    list_first.push_back(3);


    ASSERT_EQ(list_first.front(), 1);
    ASSERT_EQ(list_first.size(), 3);
    ASSERT_EQ(list_first.reserve(), 7);
    ASSERT_EQ(list_first.full(), 0);
    ASSERT_EQ(list_first.capacity(), 10);

    for (char i=4; i<15; i++){
        list_first.push_back(i);
    }

    ASSERT_EQ(list_first.full(), 1);
    ASSERT_EQ(list_first.size(), 10);

    ASSERT_EQ(list_first.front(), 5);
    ASSERT_EQ(list_first.back(), 14);

    list_first.pop_front();
    list_first.pop_back();

    ASSERT_EQ(list_first.front(), 6);
    ASSERT_EQ(list_first.back(), 13);
    ASSERT_EQ(list_first.front(), list_first[0]);
    ASSERT_EQ(list_first.reserve(), 2);

    list_first.linearize();
    ASSERT_EQ(list_first.is_linearized(), 1);

    list_first.pop_front();
    ASSERT_EQ(list_first.front(), 7);
    ASSERT_EQ(list_first.is_linearized(), 0);

    ASSERT_EQ(list_first.at(5), 12);
    ASSERT_EQ(list_first.at(0), 7);


    CircularBuffer list_second(5, 1);

    ASSERT_EQ(list_second.reserve(), 0);

    list_second.erase(2,3);
    ASSERT_EQ(list_second.reserve(), 2);


    ASSERT_EQ(list_second.at(0), 1);
    ASSERT_EQ(list_second.at(1), 1);
    ASSERT_EQ(list_second.at(4), 1);

    list_second.push_front(8);
    ASSERT_EQ(list_second.at(0), 8);
    ASSERT_EQ(list_second.front(), 8);

    ASSERT_EQ(list_second!=list_first, 1);


    ASSERT_EQ(list_second.size(), 3);
    list_second.set_capacity(10);
    ASSERT_EQ(list_second.reserve()+list_second.size(), 10);
    ASSERT_EQ(list_second.size(), 3);

    list_second.resize(15, 2);
    ASSERT_EQ(list_second.size(), 8);



    list_first=list_second;
    ASSERT_EQ(list_first.size(), 8);
    ASSERT_EQ(list_first.at(0), 2);


    for(int i=0; i<15; i++){
        list_second.push_back(i);
    }

    ASSERT_EQ(list_second.at(0), 5);


    list_second.rotate(5);
    ASSERT_EQ(list_second.at(0), 10);




    list_first.swap(list_second);
    ASSERT_EQ(list_first.at(0), 10);
    ASSERT_EQ(list_second.at(0), 2);


    ASSERT_EQ(list_first.size(), 10);
    ASSERT_EQ(list_second.size(), 8);


    list_second.clear();
    ASSERT_EQ(list_second.size(), 0);
}
