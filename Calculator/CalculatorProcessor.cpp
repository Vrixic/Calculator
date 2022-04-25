#include "CalculatorProcessor.h"

#include <sstream>
#include <bitset>

CalculatorProcessor::~CalculatorProcessor()
{
	delete mLastCommand;
	mCommandsList.clear();
}

/*
* @Param: command - command that is being added to the list of commands
* @Param: rightNum - if mLastCommand isn't null, then rightNum is the 
		right number of the last command that was added to the list of commands
*/
void CalculatorProcessor::AddCommand(IBaseCommand* command, float rightNum)
{
	if (mLastCommand != nullptr)
		mLastCommand->mRightNumber = rightNum;

	mCommandsList.push_back(command);
	mLastCommand = command;
}

/*
* Executes all the commands in order in the list of commands 
*/

float CalculatorProcessor::ExecuteCommands()
{
	float num = 0; // Temporary number used to keep in track of the final output number

	for (std::list<IBaseCommand*>::iterator it = mCommandsList.begin(); it != mCommandsList.end();)
	{
		(*it)->Execute(); // executes the current command
		if ((*it)->bError)
		{
			bCommandError = true;
			break;
		}


		num = (*it)->mLeftNumber; // sets the tempNum to the left number
		it++; // goes to the next command

		if ((*it)->mOperator == ArithmeticOperator::Equals) // Checks if the current commands operator is the Equals operator
		{
			break; // hit the end of the commands
		}

		/*if (it != mCommandsList.end())*/
		(*it)->mLeftNumber = num; // sets the current commands left number to the last commands executed number
	}

	ClearCommandsList();// Clears the list of commands
	return num;// returns the final number
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
