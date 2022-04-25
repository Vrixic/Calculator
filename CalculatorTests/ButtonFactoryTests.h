#pragma once

#include "../Calculator/ButtonFactory.h"
#include "../Calculator/ButtonFactory.cpp"

class ButtonFactoryTests
{
private:
	ButtonFactory mButtonFactory;
public:
	bool AddButtonTest(unsigned int id);

	bool SubtractButtonTest(unsigned int id);

	bool MultiplyButtonTest(unsigned int id);

	bool DivideButtonTest(unsigned int id);

	bool ModButtonTest(unsigned int id);

	bool BinaryButtonTest(unsigned int id);

	bool HexButtonTest(unsigned int id);

	bool NegateButtonTest(unsigned int id);

	bool DecimalButtonTest(unsigned int id);

	bool EqualsButtonTest(unsigned int id);
};

