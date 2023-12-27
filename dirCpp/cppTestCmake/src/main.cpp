#include "main.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    std::cout << "hello world!" << std::endl;

#if 1
    /* Essential operator. */
    essentialCheckVariableLength(false);
    essentialTypeConversion(false);

    essentialTestAllInOne(false);

    AssertFatal(true, "Something went worng. This shouldn't happen\n");

    assert(2 + 2 == 4);
    std::cout << "Checkpoint #1\n";

    assert((void("void helps to avoid 'unused value' warning"), 2 * 2 == 4));
    std::cout << "Checkpoint #2\n";

    assert((2 * 2 == 4) && ("void helps to avoid 'unused value' warning"));
    std::cout << "Checkpoint #2-1\n";

    assert((010 + 010 == 16) && "Yet another way to add an assert message");
    std::cout << "Checkpoint #3\n";

    assertm((2 + 2) % 3 == 1, "Success");
    std::cout << "Checkpoint #4\n";

    assertm(2 + 2 == 5, "Failed");                             // assertion fails
    std::cout << "Execution continues past the last assert\n"; // No output
#else
    /* Algorithm function exmaple. */
    lookUpPrimeNumbers();
    linearSieveMethod();
    multidimensionalArrayVector();

    /* Essential operator. */
    arithemeticOperator();
    relationalOperator();
    logicalOperator();
    bitwiseOperator();
    assigningOperator();
    operatorPrecedenceOperator();
    forOperator();
    whileOperator();
    doWhileOperator();
    nestedLoopOperator();
    breakOperator();
    essentialCheckVariableLength(true);

#if 0
    infiniteLoopOperator();
#endif
    thisIfOperator();
    thisGotoOperator();
    thisDoLoopOperator();
    neatedIfOperator();
    thisIfElseOperator();
    thisIfOperator();
    thisSwitchOperator();
    neatedSwitchOperator();
    passValueFunction();
    passPointerFunction();
    referenceFunction();
    thisNumberial();
    mathematicalOperator();
    randomNumber();
    accessingAnArray();
    multidimensionalArray();
    arrayPointToPointer();
    passAnArrayToFunction();
    functionRetureAnArray();
    thisAboutString();
    stringClass();
    pointerOperator();
    nullPointer();
    pointerArithmetic1();
    pointerArithmetic2();
    pointerArithmetic3();
    pinterArray();
    pointerPointToPointer();
    functionWithPointerParemeter();
    functionReturePointer();
    thisReferenceOperator();
    referenceAsParameter();
    referenceAsReturnValue();
    timeNdate();
    basicIoOperator();
    dataStructureOperator();

    /* About class. */
    testClass();
    testClass2();
    privateClass();
    protectClass();
    publicInheritance();
    protectInheritance();
    privateInheritance();
    constructFunction();
    copyConstructFunction();
    copyConstructFunction2();
    thisInlineFunction();
    thisPointer();
    thisPointer2();
    pointerPointToClass();
    reloadFunction();
    multiStatusFunction();
    tryAndCatch();
    errorAndException();
    dynamicMemory();
    thisNamespace();
    thisAssert();

    /* Logic module test block. */
    slRunCarFactoryModule();
    slRunMealFactoryModule();

    /* Multiple thread block. */
    testMultiThread();
#endif
    return 0;
}

/* End of this file. */
