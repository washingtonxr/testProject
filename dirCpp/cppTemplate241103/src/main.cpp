#include "main.h"
using namespace std;

// Function that potentially throws an exception
double divide(double numerator, double denominator) {
    if (denominator == 0) {
        throw runtime_error("Division by zero"); // Throw an exception
    }
    return numerator / denominator;
}

int main() {
    double num = 10.0;
    double denom = 0.0;

    try {
        // Attempt to divide and catch potential exceptions
        double result = divide(num, denom);
        cout << "Result: " << result << std::endl;
    } catch (const std::runtime_error& e) {
        // Catch the exception and handle it
        cerr << "Error: " << e.what() << std::endl;
    }

    cout << "Program continues after exception handling." << std::endl;

    return 0;
}
