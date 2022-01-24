#include "acutest.hpp"
#include "util.hpp"

void test_add(void){
    TEST_CHECK_(add(2,2)==(2+2), "add(%d,%d)==%d",2,2,(2+2) );
}

void test_type(void){
    TEST_CHECK_(typeid(add(2,2))==typeid(int), "add(%d,%d)==%d",2,2,(2+2) );
}

TEST_LIST = {
    {"int add(int, int);",test_add},
    {"return type is int",test_type},
    {0}
};