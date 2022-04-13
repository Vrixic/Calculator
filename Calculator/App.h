#pragma once

#include "wx/wx.h"
#include "MainWindow.h"

class App : public wxApp
{
private:
	MainWindow* mMainWindowPtr = nullptr;

public:
	App();
	~App();

	virtual bool OnInit();
};
