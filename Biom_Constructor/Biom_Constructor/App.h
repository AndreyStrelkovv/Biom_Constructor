#pragma once

#include "wx/wx.h"
#include "Menu.h"

class App : public wxApp
{
public:
	App();
	~App();
private:
	Menu* menu = nullptr;
public:
	virtual bool OnInit();
};
