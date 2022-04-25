#pragma once

#include "Arithmetic.h"

class IBaseCommand
{
public:
	/*
	* mLeftNumber: the left operand in a equation
	* mRightNumber: the right operand in a equation
	*/
	float mLeftNumber;
	float mRightNumber;

	/*
	* If the commands runs into an error than bError will be flagged
	*/
	bool bError;

	// Current operator for the command
	ArithmeticOperator mOperator;

public:
	// Executes the current command, implemented in child classes
	virtual void Execute() = 0;
};

class AddCommand : public IBaseCommand
{
public:

	AddCommand(float leftNum)
	{
		mLeftNumber = leftNum;
		mRightNumber = 0.f;
		bError = false;

		mOperator = ArithmeticOperator::Add;
	}

	void Execute()
	{
		mLeftNumber += mRightNumber;
	}
};

class SubtractCommand : public IBaseCommand
{
public:

	SubtractCommand(float leftNum)
	{
		mLeftNumber = leftNum;
		mRightNumber = 0.f;
		bError = false;

		mOperator = ArithmeticOperator::Minus;
	}

	void Execute()
	{
		mLeftNumber -= mRightNumber;
	}
};


class MultiplyCommand : public IBaseCommand
{
public:

	MultiplyCommand(float leftNum)
	{
		mLeftNumber = leftNum;
		mRightNumber = 0.f;
		bError = false;

		mOperator = ArithmeticOperator::Multiply;
	}

	void Execute()
	{
		mLeftNumber *= mRightNumber;
	}
};

class DivideCommand : public IBaseCommand
{
public:

	DivideCommand(float leftNum)
	{
		mLeftNumber = leftNum;
		mRightNumber = 0.f;
		bError = false;

		mOperator = ArithmeticOperator::Divide;
	}

	void Execute()
	{
		if (mRightNumber == 0.f)
			bError = true;
		else
			mLeftNumber /= mRightNumber;
	}
};

class ModCommand : public IBaseCommand
{
public:

	ModCommand(float leftNum)
	{
		mLeftNumber = leftNum;
		mRightNumber = 0.f;
		bError = false;

		mOperator = ArithmeticOperator::Mod;
	}

	void Execute()
	{
		mLeftNumber = (int)mLeftNumber % (int)mRightNumber;
	}
};

class EqualsCommand : public IBaseCommand
{
public:

	EqualsCommand()
	{
		mOperator = ArithmeticOperator::Equals;
	}

	void Execute()
	{
	}
};
