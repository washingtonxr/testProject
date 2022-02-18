//
//  main.h
//  test1
//
//  Created by WASHINGTON RUAN on 11/21/21.
//

#ifndef main_h
#define main_h

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <typeinfo>
#include <cstdint>

#define MAX_VALUE   100
#if 0
#define DEBUG_EN    1
#endif
#define MAX_ARRAY_DEPTH 10
using namespace std;

enum enum_cow_purpose
{
    DAIRY,
    MEAT,
    HIDE,
    PET
};

typedef struct cow_T{
    string name;
    uint8_t age;
    enum_cow_purpose purpose;
}cow_t;

class thisCow{
public:
    int editThisCow(string name_i, uint8_t age_i, enum_cow_purpose purpose_i) {
        cowInfo.name = name_i;
        cowInfo.age = age_i;
        cowInfo.purpose = purpose_i;
        return 0;
    }
    string get_name(){
        cout << "cow's name is " << cowInfo.name << endl;
        return cowInfo.name;
    }
    int get_age(){
        cout << "cow's age is " << cowInfo.age << endl;
        return cowInfo.age;
    }
    enum_cow_purpose get_purpose(){
        cout << "cow's purpose is " << cowInfo.purpose << endl;
        return cowInfo.purpose;
    }
private:
    cow_t cowInfo;
};

#endif /* main_h */
