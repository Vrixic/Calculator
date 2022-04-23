#pragma once

#include "Arithmetic.h"

class IBaseCommand
{
public:
	float mLeftNumber;
	float mRightNumber;

	ArithmeticOperator mOperator;

public:
	virtual void Execute() = 0;
};

class AddCommand : public IBaseCommand
{
public:

	AddCommand(float leftNum)
	{
		mLeftNumber = leftNum;
		mRightNumber = 0.f;

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

		mOperator = ArithmeticOperator::Divide;
	}

	void Execute()
	{
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
