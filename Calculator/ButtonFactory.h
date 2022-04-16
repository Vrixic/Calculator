#pragma once

#include "wx/wx.h"

class ButtonFactory
{
public:
	wxFont mFont;
	wxColor mBackgroundColor;
	wxColor mForegroundColor;

public:

	 wxButton* CreateButton(wxWindow* parent, wxWindowID id, const wxString& labelText, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);

	 wxButton* CreateAddButton(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);

	 wxButton* CreateMinusButton(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);

	 wxButton* CreateModButton(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);

	 wxButton* CreateMultiplyButton(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);

	 wxButton* CreateDivideButton(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);


	 wxButton* CreateNegateButton(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);

	 wxButton* CreateDecimalButton(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);

	 wxButton* CreateBinaryButton(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);

	 wxButton* CreateHexButton(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);


	 wxButton* CreateEqualsButton(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);

	 wxButton* CreateClearButton(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);


	wxButton* CreateNumberButton(wxWindow* parent, wxWindowID id, const wxString& labelText, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
};

