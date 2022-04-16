#pragma once

#include "ButtonFactory.h"
#include <list>

enum class ButtonID
{
	None = -1,
	Zero,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	
	Add,
	Minus,
	Multiply,
	Divide,
	Mod,
	Equals,

	Negate,
	Decimal,
	Binary,
	Hex,

	Clear
};

enum class ArithmeticOperator
{
	None = -1,
	Add = 10,
	Minus,
	Multiply,
	Divide,
	Mod,		
	Equals
};

class MainWindow : public wxFrame
{

private:
	const unsigned int M_FIELD_WIDTH = 4;
	const unsigned int M_FIELD_HEIGHT = 5;

	unsigned int mWindowWidth = 400;
	unsigned int mWindowHeight = 540;

	float mXOffset = 5.0f;
	float mYOffset = 1.0f;

	float mBtnTopPadding = 100.f;

	float mBtnWidth = 90;
	float mBtnHeight = 65;

	float mLabelWidth = 385;
	float mLabelHeight = 50;

	float mFontSize = 68.0f;

	wxFont* mMainFont;

	wxButton** mButtons = nullptr;

	wxStaticText* mPrevLabel = nullptr;
	wxTextCtrl* mLabel = nullptr;

	wxButton* mClearBtn = nullptr;

	//const char* mBtnLabelCodes = "D147~0258BH369%=+-*/";
	const char* mBtnLabelCodes = "0123456789+-*/%=~.BH";

	bool bStartUpReSize = true;

	wxString mLabelString = "0"; // string visble to user
	wxString mNumberString = "";

	//std::vector<ArithmeticOperator> mOperators; // all user entered operators
	std::vector<float> mNums; // all user entered nums

	std::list<float> mNumbers; // list of floats 
	std::list<ArithmeticOperator> mOperators;

	unsigned int mLastOperatorIndex = 0;

	// all buttons
	ButtonFactory mButtonFactory;
	wxButton* mAddButton;
	wxButton* mMinusButton;
	wxButton* mModButton;
	wxButton* mMultiplyButton;
	wxButton* mDivideButton;
	wxButton* mNegateButton;
	wxButton* mDecimalButton;
	wxButton* mBinaryButton;
	wxButton* mHexButton;
	wxButton* mEqualsButton;
	wxButton* mClearButton;
	wxButton** mNumberButtons;

private:
	void OnButtonClicked(wxCommandEvent& event);

	void OnReSize(wxSizeEvent& event);

	//void OnKeyDown(wxKeyEvent& event);

	void ProcessOperation();

	void ProcessNumbers(unsigned int id);

public:
	MainWindow();
	~MainWindow();

	wxDECLARE_EVENT_TABLE();
};

