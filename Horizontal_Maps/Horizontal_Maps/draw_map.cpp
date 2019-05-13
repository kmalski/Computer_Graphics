#include <wx/wx.h>
#include "GUIMyFrame1.h"

#define SIZE 500

double shepardApproximation(int N, float d[100][3], float x, float y) {
	double numerator = 0;
	double denominator = 0;
	
	for (int i = 0; i < N; ++i) {
		double tmp = 1.0 / fabs((x - d[i][0]) * (x - d[i][0]) + (y - d[i][1]) * (y - d[i][1]));
		numerator += tmp * d[i][2];
		denominator += tmp;
	}

	return numerator / denominator;
}

void GUIMyFrame1::DrawMap(int N, float d[100][3], bool Contour, int MappingType, int NoLevels, bool ShowPoints) {
	wxMemoryDC memDC;
	memDC.SelectObject(MemoryBitmap);
	memDC.SetBackground(*wxWHITE_BRUSH);
	memDC.Clear();

	if (!N) 
		return;

	double shepardData[SIZE][SIZE] = {};
	double dMin = d[0][2];
	double dMax = d[0][2];

	#pragma omp parallel for

	for (int i = 0; i < N; ++i) {
		if (d[i][2] < dMin)
			dMin = d[i][2];
		if (d[i][2] > dMax)
			dMax = d[i][2];
	}

	for (int x = 0; x < SIZE; ++x)
		for (int y = 0; y < SIZE; ++y)
			shepardData[y][x] = shepardApproximation(N, d, y / 100.0 - 2.5, -x / 100.0 + 2.5);

	unsigned char* data = new unsigned char[SIZE * SIZE * 3];
	switch (MappingType) {
	case 1:
		for (int x = 0; x < SIZE; ++x) {
			for (int y = 0; y < SIZE; ++y) {
				const float colorRatio = ((shepardData[x][y] - dMin) / (dMax - dMin) - 0.5) * 2;
				data[y * SIZE * 3 + x * 3 + 0] = 127 - 127 * colorRatio;
				data[y * SIZE * 3 + x * 3 + 1] = 0;
				data[y * SIZE * 3 + x * 3 + 2] = 127 + 127 * colorRatio;
			}
		}
		break;
	case 2:
		for (int x = 0; x < SIZE; ++x) {
			for (int y = 0; y < SIZE; ++y) {
				const float colorRatio = ((shepardData[x][y] - dMin) / (dMax - dMin) - 0.5) * 2;
				data[y * SIZE * 3 + x * 3 + 0] = colorRatio < 0 ? 255 * abs(colorRatio) : 0;
				data[y * SIZE * 3 + x * 3 + 1] = 255 - 255 * abs(colorRatio);
				data[y * SIZE * 3 + x * 3 + 2] = colorRatio > 0 ? 255 * abs(colorRatio) : 0;
			}
		}
		break;
	case 3:
		for (int x = 0; x < SIZE; ++x) {
			for (int y = 0; y < SIZE; ++y) {
				const float colorRatio = ((shepardData[x][y] - dMin) / (dMax - dMin) - 0.5) * 2;
				data[y * SIZE * 3 + x * 3 + 0] = 127 + 127 * colorRatio;
				data[y * SIZE * 3 + x * 3 + 1] = 127 + 127 * colorRatio;
				data[y * SIZE * 3 + x * 3 + 2] = 127 + 127 * colorRatio;
			}
		}
		break;
	default:
		break;
	}
	if (MappingType) {
		memDC.DrawBitmap(wxBitmap(wxImage(SIZE, SIZE, data)), 0, 0);
	}

	if (Contour) {
		memDC.SetPen(*wxBLACK);
		memDC.SetBrush(*wxTRANSPARENT_BRUSH);
		for (int level = 0; level < NoLevels; level++) {
			float thresholdPoint = dMin + (level + 1) * (dMax - dMin) / (NoLevels + 1.0f);
			for (int x = 0; x < SIZE; ++x) {
				for (int y = 0; y < SIZE; ++y) {
					if (shepardData[y][x] > thresholdPoint) {
						for (int i = -1; i <= 1; i++) {
							for (int j = -1; j <= 1; j++) {
								if (i && j && (y + i >= 0) && (y + i < SIZE) && (y + j >= 0) &&
									(x + j < SIZE) && (shepardData[y + i][x + j] < thresholdPoint)) {
									memDC.DrawPoint(y, x);
								}
							}
						}
					}
				}
			}
		}
	}

	if (ShowPoints) {
		memDC.SetPen(*wxBLACK);
		memDC.SetBrush(*wxTRANSPARENT_BRUSH);
		for (int i = 0; i < N; ++i) {
			const int x = (d[i][0] + 2.5) * 100 ;
			const int y = (2.5 - d[i][1]) * 100 ;
			memDC.DrawLine(x, y + 3, x, y - 3);
			memDC.DrawLine(x - 3, y, x + 3, y);
		}
	}
}