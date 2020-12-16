#include <gtest/gtest.h>

using testing::Eq;
namespace {
    class HashTableTest : public testing::Test {
    };
}

TEST_F (HashTableTest,  test) {


    HashTable list_first;


    Value one {40, 60};
    Value two {52, 49};
    Value three {10, 35};
    Value four {33, 80};


    list_first.insert("1", one);
    list_first.insert("2", two);
    list_first.insert("10", three);

    HashTable list_second(list_first); //вторая таблица - копия первой


    ASSERT_EQ(list_first==list_second, 1);

    ASSERT_EQ(list_first.at("10").weight, 35);
    ASSERT_EQ(list_second.at("10").age, 10);


    ASSERT_EQ(list_first.size(), list_second.size());

    ASSERT_EQ(list_first.contains("1"), 1);

    ASSERT_EQ(list_second.contains("0"), 0);

    ASSERT_EQ(list_first.size(), 3);

    HashTable list_third; // создание третьего пустого листа

    ASSERT_EQ(list_first.empty(), 0);
    ASSERT_EQ(list_third.empty(), 1);


    list_third.insert("5", four); // добавление структуры four в третью таблицу


    ASSERT_EQ(list_first==list_third, 0);


    ASSERT_EQ(list_first!=list_third, 1);
    ASSERT_EQ(list_first!=list_second, 0);


    ASSERT_EQ(list_first.size(), 3);
    ASSERT_EQ(list_third.size(), 1);


    list_first.swap(list_third);



    ASSERT_EQ(list_first.size(), 1);
    ASSERT_EQ(list_third.size(), 3);

/*
    cout<<list_first["Vlad"].age<<endl; //проверка оператора [] (должно вывести "10")

    list_second=list_first;


    cout<<list_second["Vlad"].age<<endl; //проверка оператора = (должно вывести "10")
*/

}
