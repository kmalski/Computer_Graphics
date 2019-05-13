#define _USE_MATH_DEFINES

#include "GUIMyFrame1.h"
#include <cmath>

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_staticText1->SetLabel(_(L"Jasno\u015B\u0107"));
 m_b_threshold->SetLabel(_(L"Pr\u00F3g 128"));
 this->SetBackgroundColour(wxColor(192, 192, 192));
 m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
 m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));
}

void GUIMyFrame1::m_scrolledWindow_update( wxUpdateUIEvent& event ) {
	Repaint();
}

void GUIMyFrame1::m_b_grayscale_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Copy().ConvertToGreyscale();
}

void GUIMyFrame1::m_b_blur_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Copy().Blur(5);
}

void GUIMyFrame1::m_b_mirror_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Copy().Mirror();
}

void GUIMyFrame1::m_b_replace_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.Replace(254, 0, 0, 0, 0, 255);
}

void GUIMyFrame1::m_b_rescale_click( wxCommandEvent& event ) {
	m_scrolledWindow->ClearBackground();
	Img_Cpy = Img_Org.Copy().Rescale(320, 240);
}

void GUIMyFrame1::m_b_rotate_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Copy().Rotate(30 * M_PI / 180., wxPoint(Img_Org.GetWidth() / 2, Img_Org.GetHeight() / 2));
}

void GUIMyFrame1::m_b_rotate_hue_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.RotateHue(0.5);
}

void GUIMyFrame1::m_b_mask_click( wxCommandEvent& event ) {
	m_scrolledWindow->ClearBackground();
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.SetMaskFromImage(Img_Mask, 0, 0, 0);
}

void GUIMyFrame1::m_s_brightness_scroll( wxScrollEvent& event ) {
	Brightness(m_s_brightness->GetValue() - 100);
	Repaint();
}

void GUIMyFrame1::m_s_contrast_scroll( wxScrollEvent& event ) {
	Contrast(m_s_contrast->GetValue() - 100);
	Repaint();
}

void GUIMyFrame1::m_b_prewitt_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Copy();
	unsigned char *pixels = Img_Cpy.GetData();
	unsigned char *original = Img_Org.GetData();

	#pragma omp parallel for
	for (int i = 1; i < Img_Cpy.GetHeight() - 1; i++) {
		for (int j = 1; j < Img_Cpy.GetWidth() - 1; j++) {
			for (int c = 0; c < 3; c++) {
				int value = 0;
				value +=  original[c + i       * Img_Cpy.GetWidth() * 3 + (j + 1) * 3];
				value += -original[c + i       * Img_Cpy.GetWidth() * 3 + (j - 1) * 3];
				value +=  original[c + (i + 1) * Img_Cpy.GetWidth() * 3 + (j + 1) * 3];
				value += -original[c + (i + 1) * Img_Cpy.GetWidth() * 3 + (j - 1) * 3];
				value +=  original[c + (i - 1) * Img_Cpy.GetWidth() * 3 + (j + 1) * 3];
				value += -original[c + (i - 1) * Img_Cpy.GetWidth() * 3 + (j - 1) * 3];
				pixels[c + i * Img_Cpy.GetWidth() * 3 + j * 3] = fabs(value) / 3.0;
			}
		}
	}
}

void GUIMyFrame1::m_b_threshold_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Copy();
	unsigned char *pixels = Img_Cpy.GetData();

	#pragma omp parallel for
	for (int i = 0; i < Img_Cpy.GetWidth() * Img_Cpy.GetHeight() * 3; i++)
		pixels[i] = pixels[i] < 128 ? 0 : 255;
}


void GUIMyFrame1::Contrast(double value) {
	Img_Cpy = Img_Org.Copy();
	unsigned char *pixels = Img_Cpy.GetData();
	const double alpha = (value + 100) / (101 - value);

	#pragma omp parallel for
	for (int i = 0; i < Img_Cpy.GetWidth() * Img_Cpy.GetHeight() * 3; i++) {
		int tmp_value = alpha * (pixels[i] - 128.) + 128.;
		if (tmp_value > 255)
			tmp_value = 255;
		else if (tmp_value < 0)
			tmp_value = 0;
		pixels[i] = tmp_value;
	}
}

void GUIMyFrame1::Repaint() {
	wxBitmap bitmap(Img_Cpy);          
	wxClientDC dc(m_scrolledWindow);   
	m_scrolledWindow->DoPrepareDC(dc); 
	dc.DrawBitmap(bitmap, 0, 0, true); 
}

void GUIMyFrame1::Brightness(int value) {
	Img_Cpy = Img_Org.Copy();
	unsigned char * pixels = Img_Cpy.GetData();

	#pragma omp parallel for
	for (int i = 0; i < Img_Cpy.GetWidth() * Img_Cpy.GetHeight() * 3; i++) {
		int tmp_value = pixels[i] + value;
		if (tmp_value > 255)
			tmp_value = 255;
		else if (tmp_value < 0)
			tmp_value = 0;
		pixels[i] = tmp_value;
	}
}