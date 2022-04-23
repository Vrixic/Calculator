#include "CalculatorProcessor.h"

#include <sstream>
#include <bitset>

CalculatorProcessor::~CalculatorProcessor()
{
	delete mLastCommand;
	mCommandsList.clear();
}

void CalculatorProcessor::AddCommand(IBaseCommand* command, float rightNum)
{
	if (mLastCommand != nullptr)
		mLastCommand->mRightNumber = rightNum;

	mCommandsList.push_back(command);
	mLastCommand = command;
}

float CalculatorProcessor::ExecuteCommands()
{
	float num = 0;

	for (std::list<IBaseCommand*>::iterator it = mCommandsList.begin(); it != mCommandsList.end();)
	{
		(*it)->Execute();
		num = (*it)->mLeftNumber;
		it++;

		if ((*it)->mOperator == ArithmeticOperator::Equals)
		{
			ClearCommandsList();
			return num;
		}

		/*if (it != mCommandsList.end())*/
		(*it)->mLeftNumber = num;
	}

	ClearCommandsList();

	return num;
}

void CalculatorProcessor::ClearCommandsList()
{
	mCommandsList.clear();
	mLastCommand = nullptr;
}

float CalculatorProcessor::Add(float num1, float num2)
{
	return num1 + num2;
}

float CalculatorProcessor::Subtract(float num1, float num2)
{
	return num1 - num2;
}

float CalculatorProcessor::Multiply(float num1, float num2)
{
	return num1 * num2;
}

float CalculatorProcessor::Divide(float num1, float num2)
{
	return num1 / num2;
}

unsigned int CalculatorProcessor::Mod(unsigned int num1, unsigned int num2)
{
	return num1 % num2;
}

std::string CalculatorProcessor::Binary(const std::string& numStr)
{
	int num = std::stoi(numStr);
	std::bitset<14> x(num);

	return x.to_string();
}

std::string CalculatorProcessor::Hex(const std::string& numStr)
{
	std::stringstream ss;
	int num = std::stoi(numStr);
	ss << "0x" << std::hex << num;

	return ss.str();
}
