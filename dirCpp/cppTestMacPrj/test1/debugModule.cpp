//
//  debugModule.cpp
//  test1
//
//  Created by WASHINGTON RUAN on 11/21/21.
//
#include <iostream>
#include "debugModule.hpp"

int writeFile(float a, float b)
{
    std::string str;
    std::ofstream outFile;

    //float a = 3.14159f;
    //float b = 1.2f;

    outFile.open(DEBUG_FILE);
    if (outFile.fail()){
        std::cout << "Open file failed." << std::endl;
    }else{
        std::cout << "Open file successfully." << std::endl;
        outFile << "a = " << a << std::endl;
        outFile << "a + b = " << a + b << std::endl;
        outFile << "a * b = " << a * b << std::endl;
        outFile << "a / b = " << a / b << std::endl;
        outFile.close();
        std::cout << "Write file successfully." << std::endl;
    }
    outFile.p
    return 0;
}

int readFile(void)
{
    std::string str;
    std::ifstream inFile;
    inFile.open(DEBUG_FILE);
    if (inFile.fail()){
        std::cout << "Open file failed." << std::endl;
    }else{
        std::cout << "Open file successfully." << std::endl;
        while (!inFile.eof()){
            getline(inFile, str);
            std::cout << str << std::endl;
        }
        inFile.close();
    }
    return 0;
}

/* End of this file. */
