#include "ButtonFactory.h"

wxButton* ButtonFactory::CreateButton(wxWindow* parent, wxWindowID id, const wxString& labelText, const wxPoint& pos, const wxSize& size)
{
    wxButton* btn = new wxButton(parent, id, labelText, pos, size);
    btn->SetFont(mFont);
    btn->SetBackgroundColour(mBackgroundColor);
    btn->SetForegroundColour(mForegroundColor);
    return btn;
}

wxButton* ButtonFactory::CreateAddButton(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
{
    return CreateButton(parent, id, "+", pos, size);
}

wxButton* ButtonFactory::CreateMinusButton(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
{
    return CreateButton(parent, id, "-", pos, size);
}

wxButton* ButtonFactory::CreateModButton(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
{
    return CreateButton(parent, id, "%", pos, size);
}

wxButton* ButtonFactory::CreateMultiplyButton(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
{
    return CreateButton(parent, id, "*", pos, size);
}

wxButton* ButtonFactory::CreateDivideButton(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
{
    return CreateButton(parent, id, "/", pos, size);
}

wxButton* ButtonFactory::CreateNegateButton(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
{
    return CreateButton(parent, id, "~", pos, size);
}

wxButton* ButtonFactory::CreateDecimalButton(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
{
    return CreateButton(parent, id, ".", pos, size);
}

wxButton* ButtonFactory::CreateBinaryButton(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
{
    return CreateButton(parent, id, "B", pos, size);
}

wxButton* ButtonFactory::CreateHexButton(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
{
    return CreateButton(parent, id, "H", pos, size);
}

wxButton* ButtonFactory::CreateEqualsButton(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
{
    return CreateButton(parent, id, "=", pos, size);
}

wxButton* ButtonFactory::CreateClearButton(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
{
    return CreateButton(parent, id, "Clear", pos, size);
}

wxButton* ButtonFactory::CreateNumberButton(wxWindow* parent, wxWindowID id, const wxString& labelText = "", const wxPoint& pos, const wxSize& size)
{
    return CreateButton(parent, id, labelText, pos, size);
}
