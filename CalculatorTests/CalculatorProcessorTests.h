#pragma once

#include "../Calculator/CalculatorProcessor.h"
#include "../Calculator/CalculatorProcessor.cpp"

class CalculatorProcessorTests
{
private:
	CalculatorProcessor* calcProcessor = &CalculatorProcessor::getInstance();

public:
	bool AddCommandTest(IBaseCommand* commandToAdd);

	/*
	* Add -> Subtract -> Multiply - > Divide -> Mod
	* 5 + 5 - 6 * 8 / 4 % 3 = 2
	*/
	bool ExecuteCommandsTest1();

	/*
	* Mod -> Divide -> Subtract -> Multiply -> Add
	* 50 % 4 / 2 - 1 * 100 + 5 = 5
	*/
	bool ExecuteCommandsTest2();

	bool ClearCommandsListTest();

	bool BinaryTest21();

	bool BinaryTest81();

	bool BinaryTest1214();

	bool HexTest21();

	bool HexTest81();

	bool HexTest1214();
};

