#pragma once

#include "ButtonFactory.h"
#include "CalculatorProcessor.h"
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
	wxStaticText* mPrevLabel = nullptr;
	wxTextCtrl* mLabel = nullptr;	

	const char* mBtnLabelCodes = "0123456789+-*/%=~.BH";

	bool bStartUpReSize = true;

	wxString mLabelString = "0"; // string visble to user
	wxString mNumberString = "";

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
	wxButton* mClearBtn = nullptr;
	wxButton** mNumberButtons;

	// Processor
	CalculatorProcessor* calcProcessor = &CalculatorProcessor::getInstance();

private:
	void OnButtonClicked(wxCommandEvent& event);

	void ProcessArithmeticOperators(unsigned int id);

	//void OnKeyDown(wxKeyEvent& event);

	void ProcessNumbers(unsigned int id);

	void SetFontSize(float size);

	float GetFontSizeCalc(wxString& str);

public:
	MainWindow();
	~MainWindow();

	wxDECLARE_EVENT_TABLE();
};

