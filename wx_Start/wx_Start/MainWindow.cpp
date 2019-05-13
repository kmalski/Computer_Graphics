#include "MainWindow.h"
#include <wx/colordlg.h>
#include <wx/dcclient.h>
#include <wx/dcmemory.h>
#include <wx/image.h>
#include <wx/dcbuffer.h>
#include <iostream>

MainWindow::MainWindow() :
	Window(NULL),
	_isBanana(false),
	_starColor(wxColor(*wxBLACK)),
	_text("tekst"),
	_bananaPos(0),
	_chosenItem(0),
	_saveDialog(new wxFileDialog(this, _("Choose a file"), _(""), _("image"), _("PNG files (*.png)|*.png"), wxFD_SAVE)),
	_extensionPNGHandler(new wxPNGHandler()),
	_waggleTimer(new wxTimer()),
	_move(5)
{
	_waggleTimer->SetOwner(this);
	Bind(wxEVT_TIMER, &MainWindow::_waggleHand, this);

	_angleScroll->SetScrollbar(0, 1, 100, 1);
	wxImage::AddHandler(_extensionPNGHandler);
	wxImage bananaImg = wxImage(wxSize(50, 38));
	bananaImg.LoadFile("banan.png", wxBITMAP_TYPE_PNG);
	_bananaBitmap = new wxBitmap(bananaImg);
	//SetBackgroundStyle(wxBG_STYLE_PAINT);
}

MainWindow::~MainWindow() {
	delete _saveDialog;
	delete _bananaBitmap;
	wxImage::CleanUpHandlers();
}

void MainWindow::_panelOnPaint(wxPaintEvent &event) {
	wxClientDC dcClient(_panel);
	_panel->Refresh();
	_panel->Update();
	draw(dcClient);
}

void MainWindow::_panelOnUpdateUI(wxUpdateUIEvent &event) {
	wxClientDC dcClient(_panel);
	draw(dcClient);
}

void MainWindow::_saveButtonOnButtonClick(wxCommandEvent &event) {
	wxClientDC dcClient(_panel);
	wxBufferedDC dcBuffer(&dcClient);
	PrepareDC(dcBuffer);

	if (_saveDialog->ShowModal() == wxID_OK) {
		Refresh();
		wxString fileName = _saveDialog->GetPath();
		wxSize panelSize = _panel->GetVirtualSize();
		wxBitmap saveBitmap = wxBitmap(panelSize);
		wxMemoryDC memory;

		memory.SelectObject(saveBitmap);
		memory.Blit(0, 0, panelSize.GetX(), panelSize.GetY(), &dcBuffer, 0, 0, wxCOPY, true);
		saveBitmap.ConvertToImage().SaveFile(fileName, wxBITMAP_TYPE_PNG);
	}
}

void MainWindow::_bananCheckOnCheckBox(wxCommandEvent &event) {
	_isBanana = event.IsChecked();
	_angleScroll->Enable(_isBanana);
	Refresh();
}

void MainWindow::_angleScrollOnScroll(wxScrollEvent &event) {
	_bananaPos = event.GetPosition();
	_angleGauge->SetValue(_bananaPos);
	Refresh();
}

void MainWindow::_startColorButtonOnButtonClick(wxCommandEvent &event) {
	wxColourDialog colorDialog(this);
	if (colorDialog.ShowModal() == wxID_OK)
		_starColor = colorDialog.GetColourData().GetColour();
	Refresh();
}

void MainWindow::_textCtrlOnText(wxCommandEvent &event) {
	_text = event.GetString();
	wxClientDC dcClient(_panel);
	draw(dcClient);
	Refresh();
}

void MainWindow::_itemChoiceOnChoice(wxCommandEvent &event) {
	_chosenItem = event.GetSelection();
	Refresh();
}

void MainWindow::_waggleCheckBoxOnCheckBox(wxCommandEvent &event) {
	_angleScroll->Enable(event.IsChecked());
	if (event.IsChecked()) {
		_waggleTimer->Start(1);
	}
	else {
		if (_waggleTimer->IsRunning()) {
			_waggleTimer->Stop();
		}
	}
	Refresh();
}

void MainWindow::_waggleHand(wxTimerEvent &event) {
	_bananaPos = _angleScroll->GetThumbPosition();
	if (_bananaPos >= 96)
		_move = -5;
	if (_bananaPos <= 4)
		_move = 5;
	_angleScroll->SetThumbPosition(_bananaPos + _move);
	_angleGauge->SetValue(_bananaPos + _move);

	Refresh();
}

void MainWindow::draw(wxClientDC &dcClient) {
	wxBufferedDC dcBuffer(&dcClient);
	PrepareDC(dcBuffer);
	dcBuffer.Clear();

	dcBuffer.SetDeviceOrigin(0, 0);
	wxSize panelSize = _panel->GetVirtualSize();
	unsigned int x = panelSize.GetWidth() / 2;
	unsigned int y = panelSize.GetHeight() / 2;
	unsigned int radius = 40;

	dcBuffer.SetPen(wxPen(wxColor(0, 0, 0), 2));
	dcBuffer.DrawLine(x, y, x, y + 100); //body
	dcBuffer.DrawLine(x, y, x + 70, y + 45); //right hand
	dcBuffer.DrawLine(x, y + 100, x + 50, y + 160); //right leg
	dcBuffer.DrawLine(x, y + 100, x - 50, y + 160); //left leg
	dcBuffer.DrawCircle(x, y - radius, radius); //head
	dcBuffer.DrawCircle(x - 17, y - 13 - radius, radius / 4); //left eye
	dcBuffer.DrawCircle(x + 17, y - 13 - radius, radius / 4); //right eye

	if (_isBanana) {
		dcBuffer.DrawBitmap(*_bananaBitmap, x - 100, y + 35 - _bananaPos / 2); //draw banana
		dcBuffer.DrawEllipticArc(x - 20, y - 35, 40, 15, 0, -180); //happy smile
		dcBuffer.DrawLine(x, y, x - 70, y + 45 - _bananaPos / 2); //left hand
	}
	else {
		dcBuffer.DrawLine(x, y, x - 70, y + 45 - _bananaPos / 2); //left hand
		dcBuffer.DrawEllipticArc(x - 17, y - 20, 35, 15, 0, 180); //sad smile
	}

	switch (_chosenItem) {
		case 0: //gwiazdka
			dcBuffer.SetPen(wxPen(_starColor));
			dcBuffer.SetBrush(wxBrush(_starColor));
			placeStar(x, y);
			dcBuffer.DrawPolygon(5, _starPos, -30, 50);
			break;
		case 1: //ksiezyc
			dcBuffer.SetPen(wxPen(*wxGREY_PEN));
			dcBuffer.SetBrush(wxBrush(*wxGREY_BRUSH));
			dcBuffer.DrawCircle(wxPoint(x - 100, y - 150 + radius), radius);
			dcBuffer.SetPen(wxPen(*wxWHITE_PEN));
			dcBuffer.SetBrush(wxBrush(*wxWHITE_BRUSH));
			dcBuffer.DrawCircle(wxPoint(x - 100 - 15, y - 150 - 15 + radius), radius - 10);
			dcBuffer.SetPen(wxPen(*wxBLACK_PEN));
			dcBuffer.SetBrush(wxBrush(*wxBLACK_BRUSH));
			dcBuffer.DrawLine(x - 98, y - 100, x - 90, y - 95);
			dcBuffer.DrawCircle(x - 80, y - 120, 5);
			break;
		case 2: //slonce
			dcBuffer.SetPen(wxPen(*wxYELLOW_PEN));
			dcBuffer.SetBrush(wxBrush(*wxYELLOW_BRUSH));
			dcBuffer.DrawCircle(wxPoint(x - 100, y - 150 + radius), radius);
			break;
	}

	dcBuffer.DrawText(_text, x - 100, y + 150);
	dcBuffer.SetFont(wxFont(wxFontInfo(30).FaceName("Brush Script MT").Italic()));
	dcBuffer.DrawRotatedText(_text, x + 70, y + 160, 90);
}

void MainWindow::placeStar(const int x, const int y) {
	_starPos[0] = wxPoint(x - 100, y - 150);
	_starPos[1] = wxPoint(x - 100 + 20, y - 150 + 55);
	_starPos[2] = wxPoint(x - 100 - 35, y - 150 + 25);
	_starPos[3] = wxPoint(x - 100 + 35, y - 150 + 25);
	_starPos[4] = wxPoint(x - 100 - 20, y - 150 + 55);
}
