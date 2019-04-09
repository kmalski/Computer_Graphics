#define _USE_MATH_DEFINES

#include "GUIMyFrame1.h"
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>
#include "vecmat.h"

struct Point {
 float x, y, z;
 Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Color {
 int R, G, B;
 Color(int _R, int _G, int _B) : R(_R), G(_G), B(_B) {}
};

struct Segment {
 Point begin, end;
 Color color;
 Segment(Point _begin, Point _end, Color _color) : begin(_begin), end(_end), color(_color) {}
};

bool cmp(Segment &seg1, Segment &seg2) {
	return seg1.end.y > seg2.end.y;
}

std::vector<Segment> data;

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_button_load_geometry->SetLabel(_("Wczytaj Geometri\u0119"));
 m_staticText25->SetLabel(_("Obr\u00F3t X:"));
 m_staticText27->SetLabel(_("Obr\u00F3t Y:"));
 m_staticText29->SetLabel(_("Obr\u00F3t Z:"));

 WxSB_TranslationX->SetRange(0, 200); WxSB_TranslationX->SetValue(100);
 WxSB_TranslationY->SetRange(0, 200); WxSB_TranslationY->SetValue(100);
 WxSB_TranslationZ->SetRange(0, 200); WxSB_TranslationZ->SetValue(100);

 WxSB_RotateX->SetRange(0, 360); WxSB_RotateX->SetValue(0);
 WxSB_RotateY->SetRange(0, 360); WxSB_RotateY->SetValue(0);
 WxSB_RotateZ->SetRange(0, 360); WxSB_RotateZ->SetValue(0);

 WxSB_ScaleX->SetRange(1, 200); WxSB_ScaleX->SetValue(100);
 WxSB_ScaleY->SetRange(1, 200); WxSB_ScaleY->SetValue(100);
 WxSB_ScaleZ->SetRange(1, 200); WxSB_ScaleZ->SetValue(100);
}

void GUIMyFrame1::WxPanel_Repaint( wxUpdateUIEvent& event )
{
 Repaint();
}

void GUIMyFrame1::m_button_load_geometry_click( wxCommandEvent& event )
{
 wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

 if (WxOpenFileDialog.ShowModal() == wxID_OK)
 {
  double x1, y1, z1, x2, y2, z2;
  int r, g, b;

  std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
  if (in.is_open())
  {
   data.clear();
   while (!in.eof())
   {
    in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
    data.push_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2), Color(r, g, b)));
   }
   in.close();
  }
 }
 fancyColor();
}

void GUIMyFrame1::Scrolls_Updated( wxScrollEvent& event )
{
WxST_TranslationX->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationX->GetValue() - 100) / 50.0));
WxST_TranslationY->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationY->GetValue() - 100) / 50.0));
WxST_TranslationZ->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationZ->GetValue() - 100) / 50.0));

WxST_RotateX->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateX->GetValue()));
WxST_RotateY->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateY->GetValue()));
WxST_RotateZ->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateZ->GetValue()));

WxST_ScaleX->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleX->GetValue() / 100.0));
WxST_ScaleY->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleY->GetValue() / 100.0));
WxST_ScaleZ->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleZ->GetValue() / 100.0));


Repaint();
}

Matrix4 GUIMyFrame1::getScaleMatrix(const double scaleX, const double scaleY, const double scaleZ) const {
	Matrix4 scale;

	scale.data[0][0] = scaleX;
	scale.data[1][1] = -scaleY;
	scale.data[2][2] = scaleZ;

	return scale;
}

Matrix4 GUIMyFrame1::getTranslationMatrix(const double translationX, const double translationY, const double translationZ) const {
	Matrix4 translation;

	translation.data[0][0] = translation.data[1][1] = translation.data[2][2] = 1.;
	translation.data[0][3] = translationX;
	translation.data[1][3] = -translationY;
	translation.data[2][3] = translationZ;

	return translation;
}

Matrix4 GUIMyFrame1::getRotationMatrix(const double rotationX, const double rotationY, const double rotationZ) const {
	const double angleX = rotationX * M_PI / 180.;
	const double angleY = rotationY * M_PI / 180.;
	const double angleZ = rotationZ * M_PI / 180.;

	Matrix4 rotateX, rotateY, rotateZ;

	rotateX.data[0][0] = 1.;
	rotateX.data[1][1] = rotateX.data[2][2] = cos(angleX);
	rotateX.data[2][1] = sin(angleX);
	rotateX.data[1][2] = -sin(angleX);

	rotateY.data[1][1] = 1.;
	rotateY.data[0][0] = rotateY.data[2][2] = cos(angleY);
	rotateY.data[2][0] = -sin(angleY);
	rotateY.data[0][2] = sin(angleY);

	rotateZ.data[2][2] = 1.;
	rotateZ.data[0][0] = rotateZ.data[1][1] = cos(angleZ);
	rotateZ.data[1][0] = sin(angleZ);
	rotateZ.data[0][1] = -sin(angleZ);

	Matrix4 rotation = rotateX * rotateY * rotateZ;
	return rotation;
}

void GUIMyFrame1::fancyColor() {
	double step = 255. / data.size();
	double red = 255.;
	double blue = 0.;

	sort(data.begin(), data.end(), cmp);

	for (auto & segment : data) {
		segment.color.R = red;
		segment.color.B = blue;
		red -= step;
		blue += step;
	}
}

void GUIMyFrame1::Repaint() {
	wxClientDC dc(WxPanel);
	wxBufferedDC dcBuff(&dc);
	int width, height;
	WxPanel->GetSize(&width, &height);
	dc.SetClippingRegion(wxRect(0, 0, width, height));
	dcBuff.SetBackground(wxBrush(RGB(255, 255, 255)));
	dcBuff.Clear();

	Matrix4 scale = getScaleMatrix(WxSB_ScaleX->GetValue() / 100.0, WxSB_ScaleY->GetValue() / 100.0,	WxSB_ScaleZ->GetValue() / 100.0);
	Matrix4 translation = getTranslationMatrix((WxSB_TranslationX->GetValue() - 100.0) / 50.0, (WxSB_TranslationY->GetValue() - 100.0) / 50.0, (WxSB_TranslationZ->GetValue() - 100.0) / 50.0 + 2);
	Matrix4 rotation = getRotationMatrix(WxSB_RotateX->GetValue(), WxSB_RotateY->GetValue(), WxSB_RotateZ->GetValue());
	const Matrix4 transformation = translation * rotation * scale;

	Matrix4 center;
	center.data[0][0] = center.data[2][2] = center.data[1][1] = 1;
	center.data[0][3] = center.data[1][3] = 0.5;

	for (const auto & segment : data) {
		Vector4 start, end;

		start.Set(segment.begin.x, segment.begin.y, segment.begin.z);
		start = transformation * start;

		end.Set(segment.end.x, segment.end.y, segment.end.z);
		end = transformation * end;

		if (end.GetZ() < 0 && start.GetZ() > 0)
			end.data[2] = 0.001;

		if (start.GetZ() < 0 && end.GetZ() > 0)
			start.data[2] = 0.001;

		if (start.GetZ() > 0 && end.GetZ() > 0) {
			start.Set(start.GetX() / start.GetZ(), start.GetY() / start.GetZ(), start.GetZ());
			start = center * start;

			end.Set(end.GetX() / end.GetZ(), end.GetY() / end.GetZ(), end.GetZ());
			end = center * end;

			dcBuff.SetPen(wxPen(RGB(segment.color.R, segment.color.G, segment.color.B)));
			dcBuff.DrawLine(start.GetX() * width, start.GetY() * height, end.GetX() * width, end.GetY() * height);
		}
	}
}

