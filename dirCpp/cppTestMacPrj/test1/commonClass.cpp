//
//  commonClass.cpp
//  test1
//
//  Created by WASHINGTON RUAN on 11/21/21.
//

#include "commonClass.hpp"

int thisCar::editThisCar(std::string band_i, uint8_t age_i, enum_car_purpose purpose_i) {
    carInfo.band = band_i;
    carInfo.age = age_i;
    carInfo.purpose = purpose_i;
    std::cout << carInfo.band << "Edit done." << std::endl;
    return 0;
}

std::string thisCar::get_band(void){
    std::cout << "car's band is " << carInfo.band << std::endl;
    return carInfo.band;
}

int thisCar::get_age(void) {
    std::cout << "car's age is " << carInfo.age << std::endl;
    return carInfo.age;
}

enum_car_purpose thisCar::get_purpose(void) {
    std::cout << "car's purpose is " << carInfo.purpose << std::endl;
    return carInfo.purpose;
}



/* End of this file. */
