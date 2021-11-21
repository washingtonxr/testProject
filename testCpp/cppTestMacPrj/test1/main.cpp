//
//  main.cpp
//  test1
//
//  Created by WASHINGTON RUAN on 8/22/21.
//
#include <vector>
#include "main.h"
#include "commonClass.hpp"
#include "debugModule.hpp"

auto a = 8;
auto b = 12345678;
auto c = 3.14f;
auto d = 3.14;
auto e = true;
auto f = 'x';
auto g = "hello world.";

#if 1
static void swapTest(int& x, int& y)
{
    int temp = x;
    x = y;
    y = temp;
    return;
}
#else
static void swapTest(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
    return;
}
#endif

static int checkVector(void)
{
    vector<int> primes;
    vector<int> numbers = {11,22,33,44,55,66};

    primes.push_back(2);
    primes.push_back(3);
    cout << "The vector has " << primes.size() << " elements." << endl;
    
    cout << "The vector " << primes[1] << " elements." << endl;
    cout << *(int *)(primes.end()-1).base() << endl;
    cout << *(int *)(prev(primes.end()-1)).base() << endl;
    cout << *(int *)primes.begin().base() << endl;

    vector<int>::iterator ptr = numbers.begin();

    while (ptr != numbers.end())
    {
        cout << *ptr << endl;
        ptr = next(ptr, 1);
    }

    int i =0;
    do{
        cout << numbers[i++] << endl;
    }while(i < numbers.size());

    for (auto x:numbers){
        cout << x << endl;
    }
    return 0;
}

static int checkCalss2(void)
{
    thisCar *pMycar = NULL;
    pMycar = (thisCar *)malloc(sizeof(thisCar));
    if (NULL == pMycar) {
        cout << "Memory alloc failed." << endl;
    }
    memset(pMycar, 0, sizeof(thisCar));

    pMycar->editThisCar("Chevrolet", 2, HOME);
    pMycar->get_band();
    pMycar->get_age();
    pMycar->get_purpose();

    free(pMycar);
    return 0;
}

static int checkClass(void)
{
    thisCow *pMycow = NULL;
    pMycow = (thisCow *)malloc(sizeof(thisCow));
    if (NULL == pMycow) {
        cout << "Memory alloc failed." << endl;
    }
    memset(pMycow, 0, sizeof(cow_t));
    
    pMycow->editThisCow("Lulu", 2, PET);

    pMycow->get_name();
    pMycow->get_age();
    pMycow->get_purpose();

    free(pMycow);
    return 0;
}

static int checkStructure(void)
{
    cow_t *pMycow = NULL;
    pMycow = (cow_t *)malloc(sizeof(cow_t));
    if (NULL == pMycow) {
        cout << "Memory alloc failed." << endl;
    }
    memset(pMycow, 0, sizeof(cow_t));

    pMycow->name = "Tom";
    pMycow->age = 12;
    pMycow->purpose = DAIRY;

    cout << "COW name: " << pMycow->name << endl;
    cout << "COW age: " << (uint8_t)pMycow->age << endl;
    cout << "COW purpose: " << pMycow->purpose << endl;

    free(pMycow);
    return 0;
}

static int checkArray(void)
{
    int age[MAX_ARRAY_DEPTH] = {0};
    float temperature[] = {11.3, 42.2, 67.7, 100.0, 3.2};
    unsigned int xDepth = 0;

    int i = 0;
    for (i = 0; i < MAX_ARRAY_DEPTH; i++) {
        age[i] = i + MAX_VALUE;
    }
    xDepth = sizeof(age);
    cout << "size of age: " << (uint32_t)xDepth << endl;
    for (i = 0; i < xDepth; i++) {
        cout << "Value of age " << i << ": " << age[i] << endl;
    }
    xDepth = sizeof(temperature);
    cout << "size of temperature: " << (uint32_t)xDepth << endl;
    for (i = 0; i < xDepth; i++) {
        cout << "Temperature " << i << ": " << temperature[i] << endl;
    }
    return 0;
}

static int checkMaxValue(void)
{
    cout << MAX_VALUE << endl;
    return 0;
}

static int checkType(void) {
    cout << typeid(a).name() << endl;
    cout << typeid(b).name() << endl;
    cout << typeid(c).name() << endl;
    cout << typeid(d).name() << endl;
    cout << typeid(e).name() << endl;
    cout << typeid(f).name() << endl;
    cout << typeid(g).name() << endl;
    return 0;
}

int main(int argc, const char * argv[]) {
    int i = 0;
    // insert code here...
    //std::cout << "Hello, World!\n";
    //std::cout << "Hello, World----1!\n";
#if 0
    for(i = 0; i < 10000;i++)
    {
        printf("hello world.\n");
    }
#else
    int ia[] = {1,2,3,4,5};
    for (auto i : ia)
    {
        printf("hello world %d\n", i);
    }
#endif
    printf("i=%d\n", i);

    checkType();
    checkMaxValue();
    checkArray();
    checkStructure();
    checkClass();
    checkCalss2();
#if 0
    while(1){
        printf("xxx");
    }
#endif

    checkVector();
    int a = 0;
    int b = 10;

    cout << "a:" << a << endl;
    cout << "b:" << b << endl;
    swapTest(a, b);
    cout << "a:" << a << endl;
    cout << "b:" << b << endl;

    writeFile(3.14f, 1.2222);
    readFile();
    return 0;
}


/* End of file. */
