///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "Window.h"

///////////////////////////////////////////////////////////////////////////

Window::Window( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 700,500 ), wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	_panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	_panel->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	bSizer2->Add( _panel, 1, wxEXPAND | wxALL, 5 );


	bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	_saveButton = new wxButton( this, wxID_ANY, wxT("Zapis do pliku"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( _saveButton, 0, wxALIGN_CENTER|wxALL, 5 );

	_bananCheck = new wxCheckBox( this, wxID_ANY, wxT("Weź banana!"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( _bananCheck, 0, wxALIGN_CENTER|wxALL, 5 );

	_waggleCheckBox = new wxCheckBox( this, wxID_ANY, wxT("Machaj sam!"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( _waggleCheckBox, 0, wxALIGN_CENTER|wxALL, 5 );

	_angleScroll = new wxScrollBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL );
	_angleScroll->Enable( false );

	bSizer3->Add( _angleScroll, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	_angleGauge = new wxGauge( this, wxID_ANY, 99, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	_angleGauge->SetValue( 0 );
	bSizer3->Add( _angleGauge, 0, wxALIGN_CENTER|wxALL, 5 );

	_startColorButton = new wxButton( this, wxID_ANY, wxT("Kolor Gwiazdki"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( _startColorButton, 0, wxALIGN_CENTER|wxALL, 5 );

	_textCtrl = new wxTextCtrl( this, wxID_ANY, wxT("tekst"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( _textCtrl, 0, wxALIGN_CENTER|wxALL, 5 );

	wxString _itemChoiceChoices[] = { wxT("Gwiazdka"), wxT("Księżyc"), wxT("Słonko") };
	int _itemChoiceNChoices = sizeof( _itemChoiceChoices ) / sizeof( wxString );
	_itemChoice = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, _itemChoiceNChoices, _itemChoiceChoices, 0 );
	_itemChoice->SetSelection( 0 );
	_itemChoice->SetFont( wxFont( 9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer3->Add( _itemChoice, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer1->Add( bSizer3, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	_panel->Connect( wxEVT_PAINT, wxPaintEventHandler( Window::_panelOnPaint ), NULL, this );
	_panel->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( Window::_panelOnUpdateUI ), NULL, this );
	_saveButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Window::_saveButtonOnButtonClick ), NULL, this );
	_bananCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Window::_bananCheckOnCheckBox ), NULL, this );
	_waggleCheckBox->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Window::_waggleCheckBoxOnCheckBox ), NULL, this );
	_angleScroll->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( Window::_angleScrollOnScroll ), NULL, this );
	_angleScroll->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( Window::_angleScrollOnScroll ), NULL, this );
	_angleScroll->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( Window::_angleScrollOnScroll ), NULL, this );
	_angleScroll->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( Window::_angleScrollOnScroll ), NULL, this );
	_angleScroll->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( Window::_angleScrollOnScroll ), NULL, this );
	_angleScroll->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( Window::_angleScrollOnScroll ), NULL, this );
	_angleScroll->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( Window::_angleScrollOnScroll ), NULL, this );
	_angleScroll->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( Window::_angleScrollOnScroll ), NULL, this );
	_angleScroll->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( Window::_angleScrollOnScroll ), NULL, this );
	_startColorButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Window::_startColorButtonOnButtonClick ), NULL, this );
	_textCtrl->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Window::_textCtrlOnText ), NULL, this );
	_itemChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( Window::_itemChoiceOnChoice ), NULL, this );
}

Window::~Window()
{
	// Disconnect Events
	_panel->Disconnect( wxEVT_PAINT, wxPaintEventHandler( Window::_panelOnPaint ), NULL, this );
	_panel->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( Window::_panelOnUpdateUI ), NULL, this );
	_saveButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Window::_saveButtonOnButtonClick ), NULL, this );
	_bananCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Window::_bananCheckOnCheckBox ), NULL, this );
	_waggleCheckBox->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Window::_waggleCheckBoxOnCheckBox ), NULL, this );
	_angleScroll->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( Window::_angleScrollOnScroll ), NULL, this );
	_angleScroll->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( Window::_angleScrollOnScroll ), NULL, this );
	_angleScroll->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( Window::_angleScrollOnScroll ), NULL, this );
	_angleScroll->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( Window::_angleScrollOnScroll ), NULL, this );
	_angleScroll->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( Window::_angleScrollOnScroll ), NULL, this );
	_angleScroll->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( Window::_angleScrollOnScroll ), NULL, this );
	_angleScroll->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( Window::_angleScrollOnScroll ), NULL, this );
	_angleScroll->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( Window::_angleScrollOnScroll ), NULL, this );
	_angleScroll->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( Window::_angleScrollOnScroll ), NULL, this );
	_startColorButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Window::_startColorButtonOnButtonClick ), NULL, this );
	_textCtrl->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Window::_textCtrlOnText ), NULL, this );
	_itemChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( Window::_itemChoiceOnChoice ), NULL, this );

}
