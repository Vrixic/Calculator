#include "ButtonFactoryTests.h"

bool ButtonFactoryTests::AddButtonTest(unsigned int id)
{
    wxButton* btn = mButtonFactory.CreateAddButton(nullptr, id);
    unsigned int btnId = btn->GetId();
    delete btn;
    return btnId == id;
}

bool ButtonFactoryTests::SubtractButtonTest(unsigned int id)
{
    wxButton* btn = mButtonFactory.CreateMinusButton(nullptr, id);
    unsigned int btnId = btn->GetId();
    delete btn;
    return btnId == id;
}

bool ButtonFactoryTests::MultiplyButtonTest(unsigned int id)
{
    wxButton* btn = mButtonFactory.CreateMultiplyButton(nullptr, id);
    unsigned int btnId = btn->GetId();
    delete btn;
    return btnId == id;
}

bool ButtonFactoryTests::DivideButtonTest(unsigned int id)
{
    wxButton* btn = mButtonFactory.CreateDivideButton(nullptr, id);
    unsigned int btnId = btn->GetId();
    delete btn;
    return btnId == id;
}

bool ButtonFactoryTests::ModButtonTest(unsigned int id)
{
    wxButton* btn = mButtonFactory.CreateModButton(nullptr, id);
    unsigned int btnId = btn->GetId();
    delete btn;
    return btnId == id;
}

bool ButtonFactoryTests::BinaryButtonTest(unsigned int id)
{
    wxButton* btn = mButtonFactory.CreateBinaryButton(nullptr, id);
    unsigned int btnId = btn->GetId();
    delete btn;
    return btnId == id;
}

bool ButtonFactoryTests::HexButtonTest(unsigned int id)
{
    wxButton* btn = mButtonFactory.CreateHexButton(nullptr, id);
    unsigned int btnId = btn->GetId();
    delete btn;
    return btnId == id;
}

bool ButtonFactoryTests::NegateButtonTest(unsigned int id)
{
    wxButton* btn = mButtonFactory.CreateNegateButton(nullptr, id);
    unsigned int btnId = btn->GetId();
    delete btn;
    return btnId == id;
}

bool ButtonFactoryTests::DecimalButtonTest(unsigned int id)
{
    wxButton* btn = mButtonFactory.CreateDecimalButton(nullptr, id);
    unsigned int btnId = btn->GetId();
    delete btn;
    return btnId == id;
}

bool ButtonFactoryTests::EqualsButtonTest(unsigned int id)
{
    wxButton* btn = mButtonFactory.CreateEqualsButton(nullptr, id);
    unsigned int btnId = btn->GetId();
    delete btn;
    return btnId == id;
}
