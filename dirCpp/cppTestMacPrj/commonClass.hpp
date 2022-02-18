//
//  commonClass.hpp
//  test1
//
//  Created by WASHINGTON RUAN on 11/21/21.
//

#ifndef commonClass_hpp
#define commonClass_hpp
#include <iostream>
#include <stdio.h>
enum enum_car_purpose
{
    HOME,
    OFFICE,
    LUXAY,
    COLLECTED,
    OTHER
};

typedef struct car_T{
    std::string band;
    std::uint8_t age;
    enum_car_purpose purpose;
}car_t;

class thisCar{
public:
    int editThisCar(std::string band_i, uint8_t age_i, enum_car_purpose purpose_i);
    std::string get_band();
    int get_age();
    enum_car_purpose get_purpose();
private:
    car_t carInfo;
};




#endif /* commonClass_hpp */
