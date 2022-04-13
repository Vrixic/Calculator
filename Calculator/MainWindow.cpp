#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Vrij",
	wxPoint(420, 180), wxSize(400, 540))
{
	this->SetTransparent(240);
	int bgc = 255;
	this->SetBackgroundColour(wxColor(bgc, bgc, bgc));
	mMainFont = new wxFont(34, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);

	mLabel = new wxTextCtrl(this, wxID_ANY, "0", wxPoint(0, 450), wxSize(mLabelWidth, mLabelHeight), wxALIGN_RIGHT | wxBORDER_NONE);
	mLabel->SetFont(*mMainFont);
	mLabel->SetForegroundColour(wxColor(10, 10, 10));

	mPrevLabel = new wxStaticText(this, wxID_ANY, "", wxPoint(0, 400), wxSize(mLabelWidth, mLabelHeight), wxALIGN_RIGHT);
	mPrevLabel->SetFont(*mMainFont);
	mPrevLabel->SetForegroundColour(wxColor(bgc, bgc, bgc));

	//std::to_string()

	int bgcs = 255;
	mLabel->SetBackgroundColour(wxColor(bgc, bgc, bgc));
	mPrevLabel->SetBackgroundColour(wxColor(bgc, bgc, bgc));

	mButtons = new wxButton * [M_FIELD_WIDTH * M_FIELD_HEIGHT];

	mMainFont->SetPointSize(24);

	int bnc = 250;

	int buttonIdCount = 0;
	int btnArrNum = 0;

	for (unsigned int x = 0; x < M_FIELD_WIDTH; x++)
	{
		for (unsigned int y = 0; y < M_FIELD_HEIGHT; y++)
		{
			btnArrNum = y * M_FIELD_WIDTH + x;

			mButtons[btnArrNum] = new wxButton(this, buttonIdCount, btnLabelCodes[buttonIdCount], wxPoint(x * mBtnWidth + ((x + 1) * mXOffset), y * mBtnHeight + ((y + 1) * mYOffset)), wxSize(mBtnWidth, mBtnHeight));
			mButtons[btnArrNum]->SetBackgroundColour(wxColor(bnc, bnc, bnc));
			mButtons[btnArrNum]->SetForegroundColour(wxColor(10,10,10));
			mButtons[btnArrNum]->SetFont(*mMainFont);
			mButtons[btnArrNum]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClicked, this);

			buttonIdCount++;
		}
	}

	mClearBtn = new wxButton(this, 20, "Clear", wxPoint(0 + mXOffset, 331 + mYOffset), wxSize(375, 60), wxBORDER_DOUBLE);
	mClearBtn->SetBackgroundColour(wxColor(bnc, bnc, bnc));
	mClearBtn->SetForegroundColour(wxColor(10,10,10));
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

	if (mLabel->GetLabelText() == '0' && id == 0)
		return;

	if (id == 20) // Clear
	{
		mLabel->SetLabelText("0");
		mPrevLabel->SetLabelText("");
		mCurrentString = "";
		bFirstClick = true;
	}
	else if (mLabel->GetLabelText() == "0" && bFirstClick)
	{
		mLabel->SetLabelText(btnLabelCodes[id]);
		ProcessNumbers(id);
		bFirstClick = false;
	}
	else if (id == 0)// decimal
	{
		mLabel->AppendText(".");
		mCurrentString.Append(".");
	}
	else if (id == 4)// Negate
	{
		if (mLabel->GetLabelText()[0] != '-')
		{
			wxString temp = "-";
			temp.Append(mCurrentString);
			mCurrentString = temp;
			mLabel->SetLabelText(mCurrentString);
		}
		else
		{
			mCurrentString = mCurrentString.substr(1, mCurrentString.length());
			mLabel->SetLabelText(mCurrentString);
		}
	}
	else if (id == 9)// Binary
	{

	}
	else if (id == 10)// Hex
	{

	}
	else if (id < 14)
	{
		mLabel->AppendText(btnLabelCodes[id]);
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

	for (unsigned int x = 0; x < M_FIELD_WIDTH; x++)
	{
		for (unsigned int y = 0; y < M_FIELD_HEIGHT; y++)
		{
			btn = mButtons[y * M_FIELD_WIDTH + x];

			btnPos = btn->GetPosition();

			btnPos.x = ((x * (mBtnWidth * widthScaler)) + ((x + 1) * mXOffset));
			btnPos.y = ((y * (mBtnHeight * heightScaler)) + ((y + 1) * mYOffset));

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

	mFontSize *= heightScaler;

	wxPoint labelPos = mLabel->GetPosition();

	labelPos.x *= widthScaler;
	labelPos.y *= heightScaler;

	mLabel->SetPosition(labelPos);
	mLabel->SetSize(wxSize(mLabelWidth, mLabelHeight));

	mMainFont->SetPointSize(mFontSize);

	mLabel->SetFont(*mMainFont);

	event.Skip();
}

void MainWindow::ProcessOperators(unsigned int id)
{

	switch (id)
	{
	case 14: // Mod
		if (mLabel->GetLabelText().Last() != '%')
		{
			mLabel->AppendText("%");
			mCurrentString.Append("%");
		}

		break;
	case 15: // Equals
		if (mLabel->GetLabelText().Last() != '=')
		{
			mLabel->AppendText("=");
			mCurrentString.Append("=");
			//ProcessOperation();
		}
		break;
	case 16: // Add
		if (mLabel->GetLabelText().Last() != '+')
		{
			mLabel->AppendText("+");
			mCurrentString.Append("+");
		}
		break;
	case 17: // Minus
		if (mLabel->GetLabelText().Last() != '-')
		{
			mLabel->AppendText("-");
			mCurrentString.Append("-");
		}
		break;
	case 18: // Multiply
		if (mLabel->GetLabelText().Last() != '*')
		{
			mLabel->AppendText("*");
			mCurrentString.Append("*");
		}
		break;
	case 19: // Divide
		if (mLabel->GetLabelText().Last() != '/')
		{
			mLabel->AppendText("/");
			mCurrentString.Append("/");
		}
		break;
	default:
		break;
	}
}

void MainWindow::ProcessNumbers(unsigned int id)
{
	switch (id)
	{
	case 1:
		mCurrentString.Append('1');
		break;
	case 2:
		mCurrentString.Append('4');
		break;
	case 3:
		mCurrentString.Append('7');
		break;
	case 5:
		mCurrentString.Append('0');
		break;
	case 6:
		mCurrentString.Append('2');
		break;
	case 7:
		mCurrentString.Append('5');
		break;
	case 8:
		mCurrentString.Append('8');
		break;
	case 11:
		mCurrentString.Append('3');
		break;
	case 12:
		mCurrentString.Append('6');
		break;
	case 13:
		mCurrentString.Append('9');
		break;
	default:
		break;
	}
}

void MainWindow::ProcessOperation()
{
	wxString temp(mCurrentString);
	wxString numStr = "";

	mOperators.clear();
	mNums.clear();

	double num = -1;

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
			numStr.ToDouble(&num);

			mNums.push_back(num);

			temp = temp.substr(i + 1, temp.length());

			i = 0;
		}
	}

	num = 0;

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
			if ((int)num % (int)mNums[i] != 0)
				bHasDecimal = true;

			if (mNums[i] != 0)
				num /= mNums[i];
			else
				bNanError = true;
			break;
		default:
			break;
		}
	}


	mPrevLabel->SetLabelText(mCurrentString);
	if (!bNanError)
		if (bHasDecimal)
			mLabel->SetLabelText(std::to_string(num));
		else
			mLabel->SetLabelText(std::to_string((int)num));
	else
		mLabel->SetLabelText("Overflow Error");

	mCurrentString = "" + std::to_string(num);
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
