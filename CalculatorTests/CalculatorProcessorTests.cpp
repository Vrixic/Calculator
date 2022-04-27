#include "CalculatorProcessorTests.h"

bool CalculatorProcessorTests::AddCommandTest(IBaseCommand* commandToAdd)
{
	calcProcessor->AddCommand(commandToAdd, 0, false);
	return calcProcessor->GetLastCommand()->mOperator == commandToAdd->mOperator;
}

bool CalculatorProcessorTests::ExecuteCommandsTest1()
{
	calcProcessor->AddCommand(new AddCommand(5), 5, false);
	calcProcessor->AddCommand(new SubtractCommand(5), 5, false);
	calcProcessor->AddCommand(new MultiplyCommand(6), 6, true);
	calcProcessor->AddCommand(new DivideCommand(8), 8, true);
	calcProcessor->AddCommand(new ModCommand(4), 4, true);
	calcProcessor->AddCommand(new EqualsCommand(), 3, false);

	return calcProcessor->ExecuteCommands() == 2;
}

bool CalculatorProcessorTests::ExecuteCommandsTest2()
{
	calcProcessor->AddCommand(new ModCommand(50), 50, true);
	calcProcessor->AddCommand(new DivideCommand(4), 4, true);
	calcProcessor->AddCommand(new SubtractCommand(2), 2, false);
	calcProcessor->AddCommand(new MultiplyCommand(1), 1, true);
	calcProcessor->AddCommand(new AddCommand(100), 100, false);
	calcProcessor->AddCommand(new EqualsCommand(), 5, false);

	return calcProcessor->ExecuteCommands() == -94;
}

bool CalculatorProcessorTests::ClearCommandsListTest()
{
	calcProcessor->ClearCommandsList();
	return calcProcessor->GetCommandListSize() == 0;
}

bool CalculatorProcessorTests::BinaryTest21()
{
	std::string binary = calcProcessor->Binary(std::to_string(21));
	return binary == "00000000010101";
}

bool CalculatorProcessorTests::BinaryTest81()
{
	std::string binary = calcProcessor->Binary(std::to_string(81));
	return binary == "00000001010001";
}

bool CalculatorProcessorTests::BinaryTest1214()
{
	std::string binary = calcProcessor->Binary(std::to_string(1214));
	return binary == "00010010111110";
}

bool CalculatorProcessorTests::HexTest21()
{
	std::string hex = calcProcessor->Hex(std::to_string(21));
	return hex == "0x15";
}

bool CalculatorProcessorTests::HexTest81()
{
	std::string hex = calcProcessor->Hex(std::to_string(81));
	return hex == "0x51";
}

bool CalculatorProcessorTests::HexTest1214()
{
	std::string hex = calcProcessor->Hex(std::to_string(1214));
	return hex == "0x4BE";
}
