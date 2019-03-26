#pragma once

#include "Window.h"
#include <wx/filedlg.h>
#include <wx/timer.h>


class MainWindow : public Window {
public:
	MainWindow();
	virtual ~MainWindow();
	void _panelOnPaint(wxPaintEvent &event);
	void _panelOnUpdateUI(wxUpdateUIEvent &event);
	void _saveButtonOnButtonClick(wxCommandEvent &event);
	void _bananCheckOnCheckBox(wxCommandEvent &event);
	void _angleScrollOnScroll(wxScrollEvent &event);
	void _startColorButtonOnButtonClick(wxCommandEvent &event);
	void _textCtrlOnText(wxCommandEvent &event);
	void _itemChoiceOnChoice(wxCommandEvent &event);
	void _waggleCheckBoxOnCheckBox(wxCommandEvent &event);
	void _waggleHand(wxTimerEvent &event);

private:
	void draw(wxClientDC &dcClient);
	void placeStar(const int x, const int y);

	wxTimer *_waggleTimer;
	wxImageHandler *_extensionPNGHandler;
	wxBitmap *_bananaBitmap;
	wxFileDialog *_saveDialog;
	wxString _text;
	wxPoint _starPos[5];
	wxColor _starColor;
	int _move;
	bool _isBanana;
	int _chosenItem;
	int _bananaPos;
};