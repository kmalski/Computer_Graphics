#include <wx/wx.h>
#include <memory>
#include "MainWindow.h"

class MyApp : public wxApp {

public:

	virtual bool OnInit();
	virtual int OnExit() { return 0; }

};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
	wxFrame *mainFrame = new MainWindow();
	mainFrame->Show(true);
	SetTopWindow(mainFrame);
	return true;
}