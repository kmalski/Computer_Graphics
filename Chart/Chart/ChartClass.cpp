#define _USE_MATH_DEFINES
#include <wx/dc.h>
#include <memory>
#include <cmath>

#include "ChartClass.h"
#include "vecmat.h"

#include <iostream>

ChartClass::ChartClass(std::shared_ptr<ConfigClass> c) {
    cfg= std::move(c);
    x_step=200;
}

void ChartClass::Set_Range() {
	double xmin=9999.9,xmax=-9999.9,ymin=9999.9,ymax=-9999.9;
	double x,y,step;
	int i;

	xmin=cfg->Get_x_start();
	xmax=cfg->Get_x_stop();

	step=(cfg->Get_x_stop()-cfg->Get_x_start())/(double)x_step;
	x=cfg->Get_x_start();

	for (i = 0; i <= x_step; i++) {
		y=GetFunctionValue(x);
		if (y>ymax) ymax=y;
		if (y<ymin) ymin=y;
		x=x+step;
	}

	y_min=ymin;
	y_max=ymax;
	x_min=xmin;
	x_max=xmax;
}


double ChartClass::GetFunctionValue(const double x) {
	if (cfg->Get_F_type()==1) return x*x;
	if (cfg->Get_F_type()==2) return 0.5*exp(4*x-3*x*x);
	return x+sin(x*4.0);
}

double ChartClass::Get_Y_min() {
    Set_Range();
    return y_min;
}

double ChartClass::Get_Y_max() {
    Set_Range();
    return y_max;
}

//////////////////////////////////////////////

Matrix ChartClass::getTranformationMatrix(const int w, const int h) {
	Matrix scale;
	double tmp;
	if (tmp = cfg->Get_x1() - cfg->Get_x0())
		scale.data[0][0] = (w - 20.) / tmp;
	else
		scale.data[0][0] = (w - 20.) / 0.001;
	if (tmp = cfg->Get_y1() - cfg->Get_y0())
		scale.data[1][1] = (h - 20.) / tmp;
	else
		scale.data[1][1] = (h - 20.) / 0.001;
	scale.data[0][2] = 10. - scale.data[0][0] * cfg->Get_x0();
	scale.data[1][2] = 10. - scale.data[1][1] * cfg->Get_y0();

	Matrix translation;
	translation.data[0][0] = translation.data[1][1] = 1;
	translation.data[0][2] = cfg->Get_dX();
	translation.data[1][2] = cfg->Get_dY();

	Matrix rotation;
	const double sin_value = sin(cfg->Get_Alpha() * M_PI / 180.);
	const double cos_value = cos(cfg->Get_Alpha() * M_PI / 180.);
	rotation.data[0][0] = rotation.data[1][1] = cos_value;
	rotation.data[0][1] = -sin_value;
	rotation.data[1][0] = sin_value;

	Matrix move, back;
	move.data[0][0] = move.data[1][1] = back.data[0][0] = back.data[1][1] = 1.;
	if (cfg->RotateScreenCenter()) {
		move.data[0][2] = w / 2.;
		move.data[1][2] = h / 2.;
	}
	else {
		move.data[0][2] = scale.data[0][2];
		move.data[1][2] = scale.data[1][2];
	}
	back.data[0][2] = -move.data[0][2];
	back.data[1][2] = -move.data[1][2];
	rotation = move * rotation * back;
	if(cfg->RotateScreenCenter())
		return rotation * translation * scale;
	return translation * rotation * scale;
}

void ChartClass::Draw(wxDC *dc, int w, int h) {
	Matrix transformation = getTranformationMatrix(w, h);

	dc->SetBackground(wxBrush(RGB(255, 255, 255)));
	dc->Clear();
	dc->SetPen(wxPen(RGB(255, 0, 0)));
	dc->DrawRectangle(10, 10, w - 20, h - 20);
	dc->SetClippingRegion(wxRect(11, 11, w - 21, h - 21));

	dc->SetPen(*wxBLUE_PEN);
	drawAxes(w, h, transformation, dc);

	dc->SetPen(*wxGREEN_PEN);
	const double step = (cfg->Get_x1() - cfg->Get_x0()) / x_step;
	for (double x = cfg->Get_x_start(); x < cfg->Get_x_stop(); x += step)
		line2d(x, GetFunctionValue(x), x + step, GetFunctionValue(x + step), w, h, transformation, dc);
}

void ChartClass::line2d(const double x1, const double y1, const double x2, const double y2, const int w, const int h, const Matrix &t, wxDC *dc) {
	Vector start_Vector, end_Vector;
	start_Vector.Set(x1, y1);
	end_Vector.Set(x2, y2);

	start_Vector = t * start_Vector;
	end_Vector = t * end_Vector;

	dc->DrawLine(start_Vector.GetX(), h - start_Vector.GetY(), end_Vector.GetX(), h - end_Vector.GetY());
}

void ChartClass::drawAxes(const int w, const int h, const Matrix &t, wxDC *dc) {
	line2d(0, Get_Y_min(), 0, Get_Y_max(), w, h, t, dc);
	line2d(cfg->Get_x_start(), 0, cfg->Get_x_stop(), 0, w, h, t, dc);

	const double step_OX = (cfg->Get_x1() - cfg->Get_x0()) / 5.;
	for (double x = 0; x < x_max; x += step_OX) {
		line2d(x, 0.05 , x, -0.05, w, h, t, dc);
		drawText(x - 0.025, -0.05, wxString::Format("%.2g", x), w, h, t, dc);
	}
	for (double x = 0; x >= x_min; x -= step_OX) {
		line2d(x, 0.05, x, -0.05, w, h, t, dc);
		if(x)
			drawText(x - 0.025, -0.05, wxString::Format("%.2g", x), w, h, t, dc);
	}
	line2d(x_max, 0, x_max - 0.08, 0.05, w, h, t, dc);
	line2d(x_max, 0, x_max - 0.08, -0.05, w, h, t, dc);

	const double step_OY = (cfg->Get_y1() - cfg->Get_y0()) / 5.;
	for (double y = 0; y < y_max; y += step_OY) {
		if (y) {
			line2d(0.05, y, -0.05, y, w, h, t, dc);
			drawText(0.06, y, wxString::Format("%.2g", y), w, h, t, dc);
		}
	}
	for (double y = 0; y >= y_min; y -= step_OY) {
		if (y) {
			line2d(0.05, y, -0.05, y, w, h, t, dc);
			drawText(0.06, y, wxString::Format("%.2g", y), w, h, t, dc);
		}
	}
	line2d(0, y_max, -0.05, y_max - 0.08, w, h, t, dc);
	line2d(0, y_max, 0.05, y_max - 0.08, w, h, t, dc);
}

void ChartClass::drawText(const double x, const double y, wxString &txt, const int w, const int h, const Matrix &t, wxDC *dc) {
	Vector vector;
	vector.Set(x, y);
	vector = t * vector;
	dc->DrawRotatedText(txt, vector.GetX(), h - vector.GetY(), cfg->Get_Alpha());
}
