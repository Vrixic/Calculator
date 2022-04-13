#pragma once

#include "wx/wx.h"

enum class ArithmeticOperator
{
	None = -1,
	Add,
	Minus,
	Mod,
	Multiply,
	Divide,
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

	const char* btnLabelCodes = "D147~0258BH369%=+-*/";

	bool bStartUpReSize = true;

	wxString mCurrentString;
	
	std::vector<ArithmeticOperator> mOperators; // all user entered operators
	std::vector<double> mNums; // all user entered nums

	bool bFirstClick = true;

private:
	void OnButtonClicked(wxCommandEvent& event);

	//void OnReSize(wxSizeEvent& event);
	
	//void OnKeyDown(wxKeyEvent& event);
	
	//void ProcessOperators(unsigned int id);
	
	//void ProcessOperation();
	
	//void ProcessNumbers(unsigned int id);
	
	//ArithmeticOperator GetOperatorFromChar(char o);

public:
	MainWindow();
	~MainWindow();

	wxDECLARE_EVENT_TABLE();
};

