#ifndef _MODULEPACK_H_
#define _MODULEPACK_H_

#include "common.h"
#include <cstring>

using namespace std;

/* Car's door Objects*/
class classDoor
{
public:
#if 0
    classDoor()
    {}
#endif
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
#if 0
    classEngine()
    {}
#endif
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

//#pragma region classEntree
class classEntree
{
protected:
    char cEntree[16];
public:
    const char *getEntree()
    {
        return cEntree;
    }
};

/* Derived Buger class */
class classBurger : public classEntree
{
public:
    classBurger()
    {
        cout << "\n Grill burger patty, add tomatoes and place them in a bun";
        strcpy(cEntree, "hamburger");
    }
};

/* Derived Hotdog class */
class classHotdog : public classEntree
{
public:
    classHotdog()
    {
        cout << "\n Cook sausage and place it in a bun";
        strcpy(cEntree, "hotdog");
    }
};
//#pragma endregion classEntree

//#pragma region classSide
/*  Base Side class */
class classSide
{
protected:
    char cSide[16];
public:
    char *getSide()
    {
        return cSide;
    }
};

/* Derived Fries class */
class classFries : public classSide
{
public:
    classFries()
    {
        cout << "\n Fry and season potatoes";
        strcpy(cSide, "fries");
    }
};

//Derived Salad class
class classSalad : public classSide
{
public:
    classSalad()
    {
        cout << "\n Toss greens and dressing together";
        strcpy(cSide, "salad");
    }
};
//#pragma endregion classSide

class classDrink
{
protected:
	char cDrink[10];
public:
    classDrink()
    {
        cout << "\n Fill cup with soda" << endl;
        strcpy(cDrink, "soda");
    }
    char *getDrink()
    {
        return cDrink;
    }
};

/* Complex MealCombo object that contains an Entree, a Side and a Drink object. */
class classMealCombo
{
private:
    classEntree *pEntree;
    classSide *pSide;
    classDrink *pDrink;
    char cBag[100];

public:
    classMealCombo(const char *pType)
    {
        sprintf(cBag, "\n %s meal combo:", pType);
    }
    void setEntree(classEntree *e)
    {
        pEntree = e;
    }
    void setSide(classSide *s)
    {
        pSide = s;
    }
    void setDrink(classDrink *d)
    {
        pDrink = d;
    }
    const char *openMealBag()
    {
        sprintf(cBag, "%s %s, %s, %s", cBag, pEntree->getEntree(), pSide->getSide(), pDrink->getDrink());
        return cBag;
    }
};

//#pragma region Builders
// Base Builder
class classMealBuilder
{
protected:
    classMealCombo *pMeal;
public:
    virtual void cookEntree() {};
    virtual void cookSide() {};
    virtual void fillDrink() {};
    classMealCombo* getMeal()
    {
        return pMeal;
    }
};

/* Concrete Builder for a Burger Meal which has a burger, fries and a drink. */
class classBurgerMeal : public classMealBuilder
{
public:
    classBurgerMeal()
    {
        pMeal = new classMealCombo("Burger");
    }
    void cookEntree()
    {
        classBurger *pBurger = new classBurger;
        pMeal->setEntree(pBurger);
    }
    void cookSide()
    {
        classFries *pFries = new classFries;
        pMeal->setSide(pFries);
    }
    void fillDrink()
    {
        classDrink *pDrink = new classDrink;
        pMeal->setDrink(pDrink);
    }
};

/* Concrete Builder for a Hotdog Meal which has a hotdog, salad and a drink. */
class classHotdogMeal : public classMealBuilder
{
public:
	classHotdogMeal()
	{
		pMeal = new classMealCombo("Hotdog");
	}
	void cookEntree()
	{
		classHotdog *pHotdog = new classHotdog;
		pMeal->setEntree(pHotdog);
	}
	void cookSide()
	{
		classSalad *pCaesar = new classSalad;
		pMeal->setSide(pCaesar);
	}
	void fillDrink()
	{
		classDrink *pDrink = new classDrink;
		pMeal->setDrink(pDrink);
	}
};
//#pragma endregion Builders

int slRunMealFactoryModule(void);

#endif
/* End of this file. */