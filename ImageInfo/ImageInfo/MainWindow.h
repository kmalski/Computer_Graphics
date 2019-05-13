#ifndef __MainWindow__
#define __MainWindow__

#include "Window.h"
#include <array>

class MainWindow : public Window {
public:
	MainWindow(wxWindow* parent = nullptr);
	~MainWindow();
	void refresh(wxClientDC &dc);
	//void drawAnimation();

protected:
	void WindowOnUpdateUI(wxUpdateUIEvent& event);
	void _loadButtonOnButtonClick(wxCommandEvent& event);
	void _cenzuraButtonOnButtonClick(wxCommandEvent& event);
	void _erodeButtonOnButtonClick(wxCommandEvent& event);
	void _checkBoxOnCheckBox(wxCommandEvent& event);

private:
	wxImage *_editImage;
	wxImage *_clearImage;
	//std::array<wxBitmap, 720> _animations;
	//int _tick;
};

#endif 
