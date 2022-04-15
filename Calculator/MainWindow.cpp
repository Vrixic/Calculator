#include "MainWindow.h"

#include <sstream>
#include <bitset>

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Vrij",
	wxPoint(420, 180), wxSize(400, 540))
{
	// Colors
	wxColor btnFgColor(200, 200, 200); // button foreground color
	wxColor btnBgColor(10, 10, 10); // button background color
	wxColor winBgColor(0, 0, 0); // window background color

	this->SetTransparent(225);
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

	mButtons = new wxButton * [M_FIELD_WIDTH * M_FIELD_HEIGHT];

	mMainFont->SetPointSize(24);

	int buttonIdCount = 0;
	int btnArrNum = 0;

	for (unsigned int x = 0; x < M_FIELD_WIDTH; x++)
	{
		for (unsigned int y = 0; y < M_FIELD_HEIGHT; y++)
		{
			btnArrNum = y * M_FIELD_WIDTH + x;

			mButtons[btnArrNum] = new wxButton(this, buttonIdCount, mBtnLabelCodes[buttonIdCount], wxPoint(x * mBtnWidth + ((x + 1) * mXOffset), (y * mBtnHeight + ((y + 1) * mYOffset)) + mBtnTopPadding), wxSize(mBtnWidth, mBtnHeight));
			if(y == 0 || x == M_FIELD_WIDTH - 1)
				mButtons[btnArrNum]->SetBackgroundColour(btnBgColor);
			else
				mButtons[btnArrNum]->SetBackgroundColour(wxColor(btnBgColor.GetRed() + 25, btnBgColor.GetGreen() + 25, btnBgColor.GetBlue() + 25));
			mButtons[btnArrNum]->SetForegroundColour(btnFgColor);
			mButtons[btnArrNum]->SetFont(*mMainFont);
			mButtons[btnArrNum]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClicked, this);

			buttonIdCount++;
		}
	}

	mClearBtn = new wxButton(this, 20, "Clear", wxPoint(0 + mXOffset, 435 + mYOffset), wxSize(375, 60), wxBORDER_DOUBLE);
	mClearBtn->SetBackgroundColour(btnBgColor);
	mClearBtn->SetForegroundColour(btnFgColor);
	mClearBtn->SetFont(*mMainFont);
	mClearBtn->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClicked, this);

	this->Bind(wxEVT_SIZE, &MainWindow::OnReSize, this);
	//mLabel->Bind(wxEVT_KEY_DOWN, &MainWindow::OnKeyDown, this);
}

MainWindow::~MainWindow()
{
	delete[] mButtons;
	delete mLabel;
	delete mMainFont;
	delete mClearBtn;
	delete mPrevLabel;
}

void MainWindow::OnButtonClicked(wxCommandEvent& event)
{
	unsigned int id = event.GetId();

	if (mLabel->GetLabelText()[0] == '0' && id == 0)
		return;

	if (id == 20) // Clear
	{		
		mPrevLabel->SetLabelText("");
		SetMainLabelText("0");
		bFirstClick = true;
	}	
	else if (id == 0)// decimal
	{
		AppendToMainLabelText(".");
	}
	else if (id == 4)// Negate
	{
		if (mCurrentString[0] == '0' && mCurrentString.length() == 1)
		{
			SetMainLabelText("-");
		}
		else if (mLabel->GetLabelText()[0] != '-')
		{
			std::string temp("-");
			temp.append(mCurrentString);

			SetMainLabelText(temp);
		}
		else if(mCurrentString.length() > 1)
		{
			mCurrentString = mCurrentString.substr(1, mCurrentString.length());
			mLabel->SetLabelText(mCurrentString);
		}
		else
		{
			SetMainLabelText("0");
		}		
	}
	else if (id == 9)// Binary
	{
		int num = wxAtoi(mCurrentString);

		std::bitset<16> x(num);
		mLabel->SetLabelText(x.to_string());
	}
	else if (id == 10)// Hex
	{
		std::stringstream ss;
		int num = wxAtoi(mCurrentString);

		ss << "0x" << std::hex << num;
		mLabel->SetLabelText(ss.str());
	}
	else if (mLabel->GetLabelText()[0] == '0' && (mCurrentString.length() == 1 || mCurrentString.length() > 1))
	{
		SetMainLabelText(mBtnLabelCodes[id]);
		bFirstClick = false;
	}
	else if (id < 14)
	{
		if (mLabel->GetLabelText()[0] == '0' && mLabel->GetLabelText().length() < 1)
		{
			SetMainLabelText("");
		}
		
		ProcessNumbers(id);
	}
	else if (id > 13) // basic operations on numbers  
	{
		ProcessOperators(id);
	}
	
	event.Skip();
}

void MainWindow::OnReSize(wxSizeEvent& event)
{
	if (bStartUpReSize)
	{
		bStartUpReSize = false;
		return;
	}

	// calculating resize scaler
	int width = event.GetSize().GetWidth();
	int height = event.GetSize().GetHeight();

	float widthScaler = (float)width / mWindowWidth;
	float heightScaler = (float)height / mWindowHeight;

	// updating variables 
	mWindowWidth = width;
	mWindowHeight = height;

	mXOffset *= widthScaler;
	mYOffset *= heightScaler;

	// Resize and reposition buttons
	wxPoint btnPos;
	wxSize btnSize(mBtnWidth * widthScaler, mBtnHeight * heightScaler);
	wxButton* btn;

	mBtnTopPadding *= heightScaler;

	for (unsigned int x = 0; x < M_FIELD_WIDTH; x++)
	{
		for (unsigned int y = 0; y < M_FIELD_HEIGHT; y++)
		{
			btn = mButtons[y * M_FIELD_WIDTH + x];

			btnPos = btn->GetPosition();

			btnPos.x = ((x * (mBtnWidth * widthScaler)) + ((x + 1) * mXOffset));
			btnPos.y = ((y * (mBtnHeight * heightScaler)) + ((y + 1) * mYOffset)) + mBtnTopPadding;

			btn->SetPosition(btnPos);
			btn->SetSize(btnSize);
		}
	}

	btnPos = mClearBtn->GetPosition();
	btnSize = mClearBtn->GetSize();

	btnPos.x *= widthScaler;
	btnPos.y *= heightScaler;

	btnSize.x *= widthScaler;
	btnSize.y *= heightScaler;

	mClearBtn->SetPosition(btnPos);
	mClearBtn->SetSize(btnSize);

	mBtnWidth *= widthScaler;
	mBtnHeight *= heightScaler;

	// reposition and resizing the label
	mLabelWidth *= widthScaler;
	mLabelHeight *= heightScaler;

	mFontSize = mFontSize * heightScaler - mFontSize;

	wxPoint labelPos = mLabel->GetPosition();

	labelPos.x *= widthScaler;
	labelPos.y *= heightScaler;

	mLabel->SetPosition(labelPos);
	mLabel->SetSize(wxSize(mLabelWidth, mLabelHeight));
	mPrevLabel->SetSize(wxSize(mLabelWidth, mLabelHeight));

	mMainFont->SetPointSize(mFontSize);
	mLabel->SetFont(*mMainFont);
	mPrevLabel->SetFont(*mMainFont);

	event.Skip();
}

void MainWindow::ProcessOperators(unsigned int id)
{
	char op = mBtnLabelCodes[id];

	mLabel->AppendText(op);
	mCurrentString.Append(op);

	if (op == '=')
	{
		ProcessOperation();
	}
}

void MainWindow::ProcessNumbers(unsigned int id)
{
	mLabel->AppendText(mBtnLabelCodes[id]);
	mCurrentString.Append(mBtnLabelCodes[id]);
}

void MainWindow::ProcessOperation()
{
	wxString temp(mCurrentString);
	wxString numStr = "";

	mOperators.clear();
	mNums.clear();

	float num = -1;

	if (temp.GetChar(0) != '-')
	{
		mOperators.push_back(ArithmeticOperator::Add);
	}
	else
	{
		mOperators.push_back(ArithmeticOperator::Multiply);
	}

	bool bHasDecimal = false;

	for (int i = 0; i < temp.length(); i++)
	{
		if (temp.GetChar(i) == '.')
			bHasDecimal = true;

		if (temp.GetChar(i) == '+' ||
			temp.GetChar(i) == '-' ||
			temp.GetChar(i) == '/' ||
			temp.GetChar(i) == '*' ||
			temp.GetChar(i) == '%' ||
			temp.GetChar(i) == '=')
		{
			mOperators.push_back(GetOperatorFromChar(temp.GetChar(i)));

			numStr = temp.substr(0, i);
			num = wxAtof(numStr);//.ToDouble(&num);

			mNums.push_back(num);

			temp = temp.substr(i + 1, temp.length());

			i = 0;
		}
	}

	num = 0.f;

	bool bNanError = false;

	for (int i = 0; i < mOperators.size() - 1; i++)
	{
		switch (mOperators[i])
		{
		case ArithmeticOperator::Add:
			num += mNums[i];
			break;
		case ArithmeticOperator::Minus:
			num -= mNums[i];
			break;
		case ArithmeticOperator::Mod:
			num = (int)num % (int)mNums[i];
			break;
		case ArithmeticOperator::Multiply:
			num *= mNums[i];
			break;
		case ArithmeticOperator::Divide:
			if (num != 0 && mNums[i] != 0  && (int)num % (int)mNums[i] != 0)
				bHasDecimal = true;

			if (mNums[i] != 0)
				num /= mNums[i];
			else
				bNanError = true;
			break;
		}
	}


	mPrevLabel->SetLabelText(mCurrentString);
	if (!bNanError)
		if (bHasDecimal)
		{
			mLabel->SetLabelText(std::to_string(num));
			mCurrentString = "" + std::to_string(num);
		}			
		else
		{
			mCurrentString = "" + std::to_string((int)num);
			mLabel->SetLabelText(std::to_string((int)num));
		}
	else
		mLabel->SetLabelText("Overflow Error");	
}

ArithmeticOperator MainWindow::GetOperatorFromChar(char o)
{
	if (o == '+')
		return ArithmeticOperator::Add;
	else if (o == '-')
		return ArithmeticOperator::Minus;
	else if (o == '/')
		return ArithmeticOperator::Divide;
	else if (o == '*')
		return ArithmeticOperator::Multiply;
	else if (o == '%')
		return ArithmeticOperator::Mod;
	else if (o == '=')
		return ArithmeticOperator::Equals;
	else
		return ArithmeticOperator::None;
}

void MainWindow::SetMainLabelText(const std::string& str)
{
	mLabel->SetLabelText(str);
	mCurrentString = str;
}

void MainWindow::SetMainLabelText(const char& c)
{
	mLabel->SetLabelText(c);
	mCurrentString = c;
}

void MainWindow::AppendToMainLabelText(const std::string& str)
{
	mLabel->AppendText(str);
	mCurrentString.Append(str);
}

void MainWindow::AppendToMainLabelText(const char& c)
{
	mLabel->AppendText(c);
	mCurrentString.Append(c);
}
