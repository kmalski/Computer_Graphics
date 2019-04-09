#ifndef __GUIMyFrame1__
#define __GUIMyFrame1__

#include <wx/filedlg.h>
#include <wx/dcmemory.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/colourdata.h>
#include <wx/colordlg.h>
#include "GUI.h"

class Matrix4;
class Vector4;

class GUIMyFrame1 : public MyFrame1 {
public:
	GUIMyFrame1(wxWindow* parent);
	Matrix4 getScaleMatrix(const double scaleX, const double scaleY, const double scaleZ) const;
	Matrix4 getTranslationMatrix(const double translationX, const double translationY, const double translationZ) const;
	Matrix4 getRotationMatrix(const double rotationX, const double rotationY, const double rotationZ) const;
	void fancyColor();
	void Repaint();

protected:
	void WxPanel_Repaint( wxUpdateUIEvent& event );
	void m_button_load_geometry_click( wxCommandEvent& event );
	void Scrolls_Updated( wxScrollEvent& event );
};

#endif // __GUIMyFrame1__
