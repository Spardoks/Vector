#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "vector.hpp"

TEST_CASE("Vector init, int")
{
    Vector<int> v1;
    REQUIRE(v1.size() == 0);
    REQUIRE(v1.capacity() == 0);
    REQUIRE(v1.empty() == true);
}



TEST_CASE("Vector init, float")
{
    Vector<float> v1;
    REQUIRE(v1.size() == 0);
    REQUIRE(v1.capacity() == 0);
    REQUIRE(v1.empty() == true);
}



TEST_CASE("Vector push_back, int")
{
    Vector<int> v1;
    v1.push_back(888);
    REQUIRE(v1.size() == 1);
    REQUIRE(v1.capacity() >= 1);
    REQUIRE(v1.empty() == false);

    v1.push_back(999);
    REQUIRE(v1.size() == 2);
    REQUIRE(v1.capacity() >= 2);
    REQUIRE(v1.empty() == false);

    v1.push_back(3);
    REQUIRE(v1.size() == 3);
    REQUIRE(v1.capacity() >= 3);
    REQUIRE(v1.empty() == false);
}



TEST_CASE("Vector push_back, float")
{
    Vector<float> v1;
    v1.push_back(888.8);
    REQUIRE(v1.size() == 1);
    REQUIRE(v1.capacity() >= 1);
    REQUIRE(v1.empty() == false);

    v1.push_back(999.9);
    REQUIRE(v1.size() == 2);
    REQUIRE(v1.capacity() >= 2);
    REQUIRE(v1.empty() == false);

    v1.push_back(3.3);
    REQUIRE(v1.size() == 3);
    REQUIRE(v1.capacity() >= 4);
    REQUIRE(v1.empty() == false);
}



TEST_CASE("Vector pop_back, int")
{
    Vector<int> v1;
    v1.push_back(888);
    REQUIRE(v1.size() == 1);
    v1.pop_back();
    REQUIRE(v1.size() == 0);
    REQUIRE(v1.empty() == true);

    v1.push_back(2000);
    v1.push_back(2001);
    REQUIRE(v1.size() == 2);
    REQUIRE(v1.capacity() >= 2);
    REQUIRE(v1.empty() == false);

    v1.pop_back();
    REQUIRE(v1.size() == 1);
    REQUIRE(v1.capacity() >= 1);
    REQUIRE(v1.empty() == false);
}



TEST_CASE("Vector clear, int")
{
    Vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.clear();
    REQUIRE(v1.capacity() >= 0);
    REQUIRE(v1.size() == 0);

    v1.push_back(2);
    v1.push_back(1);
    REQUIRE(v1.capacity() >= 2);
    REQUIRE(v1.size() == 2);

    v1.push_back(3);
    REQUIRE(v1.capacity() >= 3);
    REQUIRE(v1.size() == 3);

    v1.clear();
    REQUIRE(v1.capacity() >= 0);
    REQUIRE(v1.size() == 0);
}



TEST_CASE("Vector at, back, front, operator[], int")
{
    Vector<int> v1;
    v1.push_back(888);
    v1.push_back(999);
    int tmp = v1.at(0);
    REQUIRE(tmp == 888);
    REQUIRE(tmp == v1.front());

    tmp = v1.at(1);
    REQUIRE(tmp == 999);
    REQUIRE(tmp == v1.back());

    REQUIRE(v1[0] == 888);
    REQUIRE(v1[1] == 999);
}



TEST_CASE("Vector assign, int")
{
    Vector<int> v1;
    v1.assign(3, 5);
    REQUIRE(v1.size() == 3);
    REQUIRE(v1.capacity() >= 3);
    REQUIRE(v1[0] == 5);
    REQUIRE(v1[1] == 5);
    REQUIRE(v1[2] == 5);

    v1.push_back(1);
    REQUIRE(v1.size() == 4);
    REQUIRE(v1.capacity() >= 4);
    REQUIRE(v1[3] == 1);

    v1.assign(17, 0);
    REQUIRE(v1.size() == 17);
    REQUIRE(v1.capacity() >= 17);
    REQUIRE(v1.at(0) == 0);
    REQUIRE(v1.at(8) == 0);
    REQUIRE(v1.at(16) == 0);
}



TEST_CASE("Vector copy constructor, int")
{
    Vector<int> v2;
    v2.push_back(888);
    v2.push_back(999);
    Vector<int> v1(v2);
    int tmp = v1.at(0);
    REQUIRE(tmp == 888);
    REQUIRE(tmp == v1.front());

    tmp = v1.at(1);
    REQUIRE(tmp == 999);
    REQUIRE(tmp == v1.back());
    REQUIRE(v1[0] == 888);
    REQUIRE(v1[1] == 999);

    v2.pop_back();
    tmp = v1.at(0);
    REQUIRE(tmp == 888);
    REQUIRE(tmp == v1.front());

    tmp = v1.at(1);
    REQUIRE(tmp == 999);
    REQUIRE(tmp == v1.back());
    REQUIRE(v1[0] == 888);
    REQUIRE(v1[1] == 999);
}



TEST_CASE("Vector copy operator=, int")
{
    Vector<int> v1;
    v1.push_back(888);
    v1.push_back(999);

    Vector<int> v3;
    v3 = v1;
    int tmp = v3.at(0);
    REQUIRE(tmp == 888);
    REQUIRE(tmp == v3.front());

    tmp = v3.at(1);
    REQUIRE(tmp == 999);
    REQUIRE(tmp == v3.back());
    REQUIRE(v3[0] == 888);
    REQUIRE(v3[1] == 999);

    v1.pop_back();
    tmp = v3.at(0);
    REQUIRE(tmp == 888);
    REQUIRE(tmp == v3.front());

    tmp = v3.at(1);
    REQUIRE(tmp == 999);
    REQUIRE(tmp == v3.back());

    REQUIRE(v3[0] == 888);
    REQUIRE(v3[1] == 999);

    v3.pop_back();
    v3.pop_back();
    tmp = v1.at(0);
    REQUIRE(tmp == 888);
    REQUIRE(tmp == v1.front());

    REQUIRE(v1[0] == 888);
}



TEST_CASE("Vector reserve, int")
{
    Vector<int> v1;
    v1.reserve(4);
    REQUIRE(v1.size() == 0);
    REQUIRE(v1.capacity() >= 4);

    v1.push_back(1);
    v1.push_back(1);
    v1.push_back(1);
    v1.push_back(1);
    REQUIRE(v1.size() == 4);
    REQUIRE(v1.capacity() >= 4);

    v1.push_back(1);
    REQUIRE(v1.size() == 5);
    REQUIRE(v1.capacity() >= 5);

    v1.reserve(3);
    REQUIRE(v1.size() == 5);
    REQUIRE(v1.capacity() >= 5);
}



TEST_CASE("Vector resize, int")
{
    Vector<int> v1;
    v1.resize(9);
    REQUIRE(v1.size() == 9);
    REQUIRE(v1.capacity() >= 9);
    for (size_t i = 0; i < 9; ++i) {
        REQUIRE(v1[i] == 0);
    }

    v1.assign(15, 1);
    REQUIRE(v1.size() == 15);
    REQUIRE(v1.capacity() >= 15);
    REQUIRE(v1[6] == 1);

    v1.resize(9);
    REQUIRE(v1.size() == 9);
    REQUIRE(v1.capacity() >= 9);
    REQUIRE(v1[6] == 1);

    v1.resize(5);
    REQUIRE(v1.size() == 5);
    REQUIRE(v1.capacity() >= 5);
    REQUIRE(v1[4] == 1);
}



TEST_CASE("Vector shrink_to_fit, int")
{
    Vector<int> v1;
    v1.resize(16);
    REQUIRE(v1.size() == 16);
    REQUIRE(v1.capacity() >= 16);

    v1.shrink_to_fit();
    REQUIRE(v1.size() == 16);
    REQUIRE(v1.capacity() == 16);

    v1.assign(10, 8);
    REQUIRE(v1.size() == 16);
    REQUIRE(v1.capacity() >= 16);

    for (std::size_t i = 0; i < 12; ++i) {
        v1.pop_back();
    }
    v1.shrink_to_fit();
    REQUIRE(v1.size() == 4);
    REQUIRE(v1.capacity() == 4);
}
