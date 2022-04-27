#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
wxEND_EVENT_TABLE()

#define DEBUG_ALLOC_NUMBER -1

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Vrij",
	wxPoint(420, 180), wxSize(400, 540), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX)
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(DEBUG_ALLOC_NUMBER);

	// Colors
	wxColor btnFgColor(200, 200, 200); // button foreground color
	wxColor btnBgColor(10, 10, 10); // button background color
	wxColor btnBgColorL(25, 25, 25); // lighter
	wxColor winBgColor(0, 0, 0); // window background color

	this->SetTransparent(235);
	this->SetBackgroundColour(winBgColor);
	mMainFont = new wxFont(34, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);

	mLabel = new wxTextCtrl(this, wxID_ANY, "0", wxPoint(0, 50), wxSize(mLabelWidth, mLabelHeight), wxALIGN_RIGHT | wxBORDER_NONE);
	mLabel->SetFont(*mMainFont);
	mLabel->SetForegroundColour(btnFgColor);

	mPrevLabel = new wxStaticText(this, wxID_ANY, "", wxPoint(0, 0), wxSize(mLabelWidth, mLabelHeight), wxALIGN_RIGHT | wxBORDER_NONE);
	mPrevLabel->SetFont(*mMainFont);
	mPrevLabel->SetForegroundColour(btnFgColor);

	mLabel->SetBackgroundColour(winBgColor);
	mPrevLabel->SetBackgroundColour(winBgColor);

	mNumberButtons = new wxButton * [10];

	mMainFont->SetPointSize(24);

	mButtonFactory.mFont = *mMainFont;
	mButtonFactory.mBackgroundColor = btnBgColor;
	mButtonFactory.mForegroundColor = btnFgColor;

	int btnXOffsetCount = 0;
	int btnYOffsetCount = 0;

	for (int i = 0; i < 10; i++)
	{
		if (i == 0) btnXOffsetCount = 1;

		mNumberButtons[i] = mButtonFactory.CreateNumberButton(this, i, mBtnLabelCodes[i], wxPoint((btnXOffsetCount++ * mBtnWidth) + (mXOffset * (btnXOffsetCount + 1)), (btnYOffsetCount * mBtnHeight) + (mYOffset * (btnYOffsetCount + 1)) + mBtnTopPadding), wxSize(mBtnWidth, mBtnHeight));
		mNumberButtons[i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClicked, this);

		if (i == 0 || i % 3 == 0)
		{
			btnXOffsetCount = 0;
			btnYOffsetCount++;
		}
	}

	mNumberButtons[0]->SetBackgroundColour(btnBgColorL);

	mHexButton = mButtonFactory.CreateHexButton(this, (int)ButtonID::Hex, wxPoint((2 * mBtnWidth) + (mXOffset * 3), mBtnTopPadding + mYOffset), wxSize(mBtnWidth, mBtnHeight));
	mHexButton->SetBackgroundColour(btnBgColorL);
	mHexButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClicked, this);

	mBinaryButton = mButtonFactory.CreateBinaryButton(this, (int)ButtonID::Binary, wxPoint(mXOffset * 1, mBtnTopPadding + mYOffset), wxSize(mBtnWidth, mBtnHeight));
	mBinaryButton->SetBackgroundColour(btnBgColorL);
	mBinaryButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClicked, this);

	mEqualsButton = mButtonFactory.CreateEqualsButton(this, (int)ButtonID::Equals, wxPoint((3 * mBtnWidth) + (mXOffset * 4), mBtnTopPadding + mYOffset), wxSize(mBtnWidth, mBtnHeight));
	mEqualsButton->SetBackgroundColour(btnBgColorL);
	mEqualsButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClicked, this);

	mAddButton = mButtonFactory.CreateAddButton(this, (int)ButtonID::Add, wxPoint((3 * mBtnWidth) + (mXOffset * 4), (1 * mBtnHeight) + mBtnTopPadding + (mYOffset * 2)), wxSize(mBtnWidth, mBtnHeight));
	mAddButton->SetBackgroundColour(btnBgColorL);
	mAddButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClicked, this);

	mMinusButton = mButtonFactory.CreateMinusButton(this, (int)ButtonID::Minus, wxPoint((3 * mBtnWidth) + (mXOffset * 4), (2 * mBtnHeight) + mBtnTopPadding + (mYOffset * 3)), wxSize(mBtnWidth, mBtnHeight));
	mMinusButton->SetBackgroundColour(btnBgColorL);
	mMinusButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClicked, this);

	mMultiplyButton = mButtonFactory.CreateMultiplyButton(this, (int)ButtonID::Multiply, wxPoint((3 * mBtnWidth) + (mXOffset * 4), (3 * mBtnHeight) + mBtnTopPadding + (mYOffset * 4)), wxSize(mBtnWidth, mBtnHeight));
	mMultiplyButton->SetBackgroundColour(btnBgColorL);
	mMultiplyButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClicked, this);

	mDivideButton = mButtonFactory.CreateDivideButton(this, (int)ButtonID::Divide, wxPoint((3 * mBtnWidth) + (mXOffset * 4), (4 * mBtnHeight) + mBtnTopPadding + (mYOffset * 5)), wxSize(mBtnWidth, mBtnHeight));
	mDivideButton->SetBackgroundColour(btnBgColorL);
	mDivideButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClicked, this);

	mNegateButton = mButtonFactory.CreateNegateButton(this, (int)ButtonID::Negate, wxPoint(mXOffset, (4 * mBtnHeight) + mBtnTopPadding + (mYOffset * 5)), wxSize(mBtnWidth, mBtnHeight));
	mNegateButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClicked, this);

	mDecimalButton = mButtonFactory.CreateDecimalButton(this, (int)ButtonID::Decimal, wxPoint((1 * mBtnWidth) + (mXOffset * 2), (4 * mBtnHeight) + mBtnTopPadding + (mYOffset * 5)), wxSize(mBtnWidth, mBtnHeight));
	mDecimalButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClicked, this);

	mModButton = mButtonFactory.CreateModButton(this, (int)ButtonID::Mod, wxPoint((2 * mBtnWidth) + (mXOffset * 3), (4 * mBtnHeight) + mBtnTopPadding + (mYOffset * 5)), wxSize(mBtnWidth, mBtnHeight));
	mModButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClicked, this);

	mClearBtn = mButtonFactory.CreateClearButton(this, (int)ButtonID::Clear, wxPoint(0 + mXOffset, 435 + mYOffset), wxSize(375, 60));
	mClearBtn->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClicked, this);

	//mLabel->Bind(wxEVT_KEY_DOWN, &MainWindow::OnKeyDown, this);
}

MainWindow::~MainWindow()
{
	delete mAddButton;
	delete mMinusButton;
	delete mModButton;
	delete mMultiplyButton;
	delete mDivideButton;
	delete mNegateButton;
	delete mDecimalButton;
	delete mBinaryButton;
	delete mHexButton;
	delete mEqualsButton;
	delete mClearBtn;

	delete mLabel;
	delete mMainFont;
	delete mPrevLabel;

	delete[] mNumberButtons;
}

void MainWindow::OnButtonClicked(wxCommandEvent& event)
{
	int id = event.GetId();

	if (id < 10) // its a number
	{
		ProcessNumbers(id);
	}
	else if (id < 16) // an arithemetic operator
	{
		ProcessArithmeticOperators(id);
	}
	else if (id == 16) // negate operator
	{
		if (mNumberString.length() < 1)
			return;

		if (mNumberString[0] == '-') // has already been negated
		{
			wxString str = mNumberString(1, mNumberString.length());
			mNumberString = str;

			str = mLabelString.substr(0, mLabelString.length() - mNumberString.length() - 1) + mLabelString.substr(mLabelString.length() - mNumberString.length(), mLabelString.length());

			mLabelString = str;
		}
		else
		{
			wxString str("~");
			str.Append(mNumberString);

			mNumberString = str;

			str = mLabelString.substr(0, mLabelString.length() - (mNumberString.length() - 1));
			str.Append(mNumberString);

			mLabelString = str;
			mNumberString[0] = '-';
		}
	}
	else if (id == 17) // decimal operator
	{
		mLabelString.Append(".");
		mNumberString.Append(".");
	}
	else if (id == 20) // clear
	{
		mLabelString = "0";
		mNumberString = "";
		mPrevLabel->SetLabelText("");
		calcProcessor->ClearCommandsList();
	}

	if (id == 18) // binary
	{
		wxString str = calcProcessor->Binary(mNumberString.ToStdString());
		SetFontSize(GetFontSizeCalc(str));
		mLabel->SetLabelText(str);
	}
	else if (id == 19) // hex
	{
		wxString str = calcProcessor->Hex(mNumberString.ToStdString());
		SetFontSize(GetFontSizeCalc(str));
		mLabel->SetLabelText(str);
	}
	else
	{
		mLabel->SetLabelText(mLabelString);
		SetFontSize(GetFontSizeCalc(mLabelString));
	}
	event.Skip();
}

void MainWindow::ProcessArithmeticOperators(unsigned int id)
{
	float num = wxAtof(mNumberString);

	switch ((ArithmeticOperator)id)
	{
	case ArithmeticOperator::Add:
		calcProcessor->AddCommand(new AddCommand(num), num, false);
		break;
	case ArithmeticOperator::Minus:
		calcProcessor->AddCommand(new SubtractCommand(num), num, false);
		break;
	case ArithmeticOperator::Multiply:
		calcProcessor->AddCommand(new MultiplyCommand(num), num, true);
		break;
	case ArithmeticOperator::Divide:
		calcProcessor->AddCommand(new DivideCommand(num), num, true);
		break;
	case ArithmeticOperator::Mod:
		calcProcessor->AddCommand(new ModCommand(num), num, true);
		break;
	case ArithmeticOperator::Equals:
		calcProcessor->AddCommand(new EqualsCommand(), num, false);
		break;
	}
	mNumberString.Clear();

	mLabelString.Append(mBtnLabelCodes[id]);

	if (id == 15) // equals
	{
		float number = calcProcessor->ExecuteCommands();

		// ran into an error
		if (calcProcessor->GetCommandError())
		{
			mLabelString = "error";
			mNumberString = "";
			calcProcessor->ResetCommandError();
		}
		else
		{
			mPrevLabel->SetLabelText(mLabelString);
			if ((int)num == num)
			{
				mLabelString = std::to_string((int)number);
				mNumberString = mLabelString;
			}
			else
			{
				mLabelString = std::to_string(number);
				mNumberString = mLabelString;
			}
		}
	}
}

void MainWindow::ProcessNumbers(unsigned int id)
{
	if (mLabelString != "" && mLabelString.length() == 1 && mLabelString[0] == '0')
	{
		mLabelString = mBtnLabelCodes[id];
		mNumberString = mBtnLabelCodes[id];
	}
	else if (mNumberString.length() == 1 && mNumberString[0] == '0')
	{

		wxString str(mLabelString.substr(0, mLabelString.length() - 1));

		str.Append(mBtnLabelCodes[id]);
		mNumberString = mBtnLabelCodes[id];

		mLabelString = str;
	}
	else
	{
		mLabelString.Append(mBtnLabelCodes[id]);
		mNumberString.Append(mBtnLabelCodes[id]);
	}
}

void MainWindow::SetFontSize(float size)
{
	mMainFont->SetPointSize(size);
	mLabel->SetFont(*mMainFont);
}

float MainWindow::GetFontSizeCalc(wxString& str)
{
	float fSize = mWindowWidth / str.length() + 3;
	return fSize > 34 ? 34 : fSize;
}