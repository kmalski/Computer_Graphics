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
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	_loadButton = new wxButton( this, wxID_ANY, wxT("Wczytaj obrazek"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( _loadButton, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	_cenzuraButton = new wxButton( this, wxID_ANY, wxT("Cenzura"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( _cenzuraButton, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	_erodeButton = new wxButton( this, wxID_ANY, wxT("Erode"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( _erodeButton, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	_checkBox = new wxCheckBox( this, wxID_ANY, wxT("Animacja"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( _checkBox, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	m_gauge1 = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	m_gauge1->SetValue( 0 );
	m_gauge1->Hide();

	bSizer2->Add( m_gauge1, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	_imageInfo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH );
	_imageInfo->SetMinSize( wxSize( 300,-1 ) );
	_imageInfo->SetMaxSize( wxSize( 300,-1 ) );

	bSizer2->Add( _imageInfo, 1, wxALL, 5 );


	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	_panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer3->Add( _panel, 1, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5 );


	bSizer1->Add( bSizer3, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( Window::WindowOnUpdateUI ) );
	_loadButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Window::_loadButtonOnButtonClick ), NULL, this );
	_cenzuraButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Window::_cenzuraButtonOnButtonClick ), NULL, this );
	_erodeButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Window::_erodeButtonOnButtonClick ), NULL, this );
	_checkBox->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Window::_checkBoxOnCheckBox ), NULL, this );
}

Window::~Window()
{
	// Disconnect Events
	this->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( Window::WindowOnUpdateUI ) );
	_loadButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Window::_loadButtonOnButtonClick ), NULL, this );
	_cenzuraButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Window::_cenzuraButtonOnButtonClick ), NULL, this );
	_erodeButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Window::_erodeButtonOnButtonClick ), NULL, this );
	_checkBox->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Window::_checkBoxOnCheckBox ), NULL, this );

}
