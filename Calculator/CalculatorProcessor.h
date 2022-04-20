#pragma once

#include <string>

class CalculatorProcessor
{
private:
	CalculatorProcessor() { }

public:		
	static CalculatorProcessor& getInstance()
	{
		static CalculatorProcessor calcProc;
		return calcProc;
	}

public:
	float Add(float num1, float num2);

	float Subtract(float num1, float num2);

	float Multiply(float num1, float num2);

	float Divide(float num1, float num2);

	unsigned int Mod(unsigned int num1, unsigned int num2);

	std::string Binary(const std::string& numStr);

	std::string Hex(const std::string& numStr);

};

