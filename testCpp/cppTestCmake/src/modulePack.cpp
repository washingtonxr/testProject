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

int slRunMealFactoryModule(void)
{
    classMealBuilder *pCook = new classMealBuilder;
    classMealCombo *pMeal;
    int choice;

    // Prompt user for their meal choice
    cout << "Select a meal: " << endl;
    cout << "1: Hamburger Meal" << endl;
    cout << "2: Hotdog Meal" << endl;
    cout << "Selection: ";
    cin >> choice;
    cout << endl;

    // Instantiate the appropriate builder based on user input
    switch (choice)
    {
    case 1:
        cout << "You chose Hamburger Meal. " << endl;
        pCook = new classBurgerMeal;
        break;
    case 2:
        cout << "You chose Hotdog Meal. " << endl;
        pCook = new classHotdogMeal;
        break;
    default:
        cout << "Invalid Selection" << endl;
        pCook = NULL;
        break;
    }

    cout << "Making selected meal" << endl;

    // Build the complex object
    pCook->cookEntree();
    pCook->cookSide();
    pCook->fillDrink();
    pMeal = pCook->getMeal();
    cout << pMeal->openMealBag() << endl;

    return 0;
}
/* End of this file. */