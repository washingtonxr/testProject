#include "modulePack.h"

int slRunCarFactoryModule(void)
{
    classCarFactory *carFactory = NULL;
    unsigned char ucYourChoice = 0xFF;

    cout << "Please select a car type:" << endl;
    cout << "1, Gasoline car. " << endl;
    cout << "2, Electronic car. " << endl;
    cin >> ucYourChoice;
    switch (ucYourChoice)
    {
    case '1':
        cout << "You chose gasoline car. " << endl;
        carFactory = new classGasolineCarFactroy;
        break;
    case '2':
        cout << "You chose electronic car. " << endl;
        carFactory = new classElectronicCarFactroy;
        break;
    default:
        cout << "Invalid choice!!!" << endl;
        break;
    }

    if (NULL != carFactory) {
        classDoor *carDoor = carFactory->createCarDoor();
        classEngine *carEngine = carFactory->createCarEngine();

        carDoor->openDoor();
        carEngine->runEngine();
    }

    return 0;
}

/* End of this file. */