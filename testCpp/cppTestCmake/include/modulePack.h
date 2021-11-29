#ifndef _MODULEPACK_H_
#define _MODULEPACK_H_

#include "common.h"
#include <cstring>

using namespace std;

/* Car's door Objects*/
class classDoor
{
public:
    classDoor()
    {}
    virtual void openDoor() = 0;
};

class classGasolineCarDoor : public classDoor
{
public:
    classGasolineCarDoor()
    {
        cout << "Making a door for a gasoline car." << endl;
    }
    void openDoor()
    {
        cout << "Click click." << endl;
    }
};

class classElectronicCarDoor : public classDoor
{
public:
    classElectronicCarDoor()
    {
        cout << "Making a door for a electronic car." << endl;
    }
    void openDoor()
    {
        cout << "Thrmm." << endl;
    }
};

/* Car's engine Objects*/
class classEngine
{
protected:
    char cSound[15];
public:
    virtual void runEngine() = 0;
};

class classGasolineCarEngine : public classEngine
{
public:
    classGasolineCarEngine()
    {
        strcpy(cSound, "Vroom");
        cout << "Creating a gasoline engine." << endl;
    }
    void runEngine()
    {
        cout << "Engine runing with " << cSound << endl;
    }
};

class classElectronicCarEngine : public classEngine
{
public:
    classElectronicCarEngine()
    {
        strcpy(cSound, "Shhhh");
        cout << "Creating a electronic engine." << endl;
    }
    void runEngine()
    {
        cout << "Engine runing with " << cSound << endl;
    }
};

/* Cars plant */
class classCarFactory
{
public:
    virtual classDoor *createCarDoor() = 0;
    virtual classEngine *createCarEngine() = 0;
};

class classGasolineCarFactroy : public classCarFactory
{
public:
    classDoor *createCarDoor()
    {
        return new classGasolineCarDoor();
    }

    classEngine *createCarEngine()
    {
        return new classGasolineCarEngine();
    }
};

class classElectronicCarFactroy : public classCarFactory
{
public:
    classDoor *createCarDoor()
    {
        return new classElectronicCarDoor();
    }

    classEngine *createCarEngine()
    {
        return new classElectronicCarEngine();
    }
};

int slRunCarFactoryModule(void);

#endif
/* End of this file. */