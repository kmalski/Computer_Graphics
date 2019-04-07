#ifndef __ChartClass__
#define __ChartClass__

#include <memory>
#include "ConfigClass.h"
class Matrix;

class ChartClass {
public:
	ChartClass(std::shared_ptr<ConfigClass> c);
	void Set_Range();   // ustala wartosci zmiennych x_min,y_min,x_max,y_max
	double Get_Y_min(); // zwraca y_min
	double Get_Y_max(); // zwraca y_max
	void Draw(wxDC *dc, int w, int h);  // rysuje wykres

private:
    std::shared_ptr<ConfigClass> cfg;
    int x_step;         // liczba odcinkow z jakich bedzie sie skladal wykres
    double x_min,x_max; // zakres zmiennej x
    double y_min,y_max; // zakres wartosci przyjmowanych przez funkcje

    double GetFunctionValue(const double x); // zwraca wartosci rysowanej funkcji
	
	/////////////////////////////////////////////////////////////////////////
	Matrix getTranformationMatrix(const int w, const int h);
	void line2d(const double x1, const double y1, const double x2, const double y2, const int w, const int h, const Matrix &t, wxDC *dc);
	void drawAxes(const int w, const int h, const Matrix &t, wxDC *dc);
	void drawText(const double x, const double y, wxString &txt, const int w, const int h, const Matrix &t, wxDC *dc);

};

#endif
