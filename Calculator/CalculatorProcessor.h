#pragma once

#include <string>
#include "IBaseCommand.h"
#include <list>

class CalculatorProcessor
{
private:
	std::list<IBaseCommand*> mCommandsList;
	IBaseCommand* mLastCommand = nullptr;

	bool bCommandError = false;
private:
	CalculatorProcessor() { }

	~CalculatorProcessor();

public:		
	static CalculatorProcessor& getInstance()
	{
		static CalculatorProcessor calcProc;
		return calcProc;
	}

public:
	void AddCommand(IBaseCommand* command, float rightNum);

	float ExecuteCommands();

	void ClearCommandsList();

public:
	float Add(float num1, float num2);

	float Subtract(float num1, float num2);

	float Multiply(float num1, float num2);

	float Divide(float num1, float num2);

	unsigned int Mod(unsigned int num1, unsigned int num2);

	std::string Binary(const std::string& numStr);

	std::string Hex(const std::string& numStr);

	inline void ResetCommandError() { bCommandError = false; }

	inline bool GetCommandError() { return bCommandError; }


	/* Made for testing purposes... */
	inline IBaseCommand* GetLastCommand()
	{
		return *mCommandsList.end();
	}

	inline int GetCommandListSize()
	{
		return mCommandsList.size();
	}

};

