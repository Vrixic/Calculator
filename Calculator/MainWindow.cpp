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

	//this->Bind(wxEVT_SIZE, &MainWindow::OnReSize, this);
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

	

	event.Skip();
}

