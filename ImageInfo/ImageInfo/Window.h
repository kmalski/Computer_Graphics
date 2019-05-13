///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/button.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/checkbox.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class Window
///////////////////////////////////////////////////////////////////////////////
class Window : public wxFrame
{
	private:

	protected:
		wxButton* _loadButton;
		wxButton* _cenzuraButton;
		wxButton* _erodeButton;
		wxCheckBox* _checkBox;
		wxGauge* m_gauge1;
		wxTextCtrl* _imageInfo;
		wxPanel* _panel;

		// Virtual event handlers, overide them in your derived class
		virtual void WindowOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void _loadButtonOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void _cenzuraButtonOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void _erodeButtonOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void _checkBoxOnCheckBox( wxCommandEvent& event ) { event.Skip(); }


	public:

		Window( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1000,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~Window();

};

