#include "CImg.h"
#include "MainWindow.h"

#include <FreeImage.h>
#include <wx/dcbuffer.h>
#include <wx/window.h>
#include <wx/filedlg.h>
#include <string>

MainWindow::MainWindow(wxWindow* parent) : Window(parent) {
	_editImage = new wxImage();
	_clearImage = new wxImage();
	wxInitAllImageHandlers();
}

MainWindow::~MainWindow() {
	delete _editImage;
	delete _clearImage; 
}

void MainWindow::refresh(wxClientDC &dc) {
	wxBufferedDC buff(&dc);
	if (_editImage->Ok()) {
		_editImage->Rescale(dc.GetSize().x, dc.GetSize().y);
		wxBitmap bitmap(*_editImage);
		buff.DrawBitmap(bitmap, 0, 0);
	}
}

void MainWindow::WindowOnUpdateUI(wxUpdateUIEvent& event) {
	wxClientDC dc(_panel);
	refresh(dc);
}

void MainWindow::_loadButtonOnButtonClick(wxCommandEvent& event) {
	wxClientDC dc(_panel);
	wxFileDialog * dialog = new wxFileDialog(this, "Load file", "", "", wxT("to jpg (*.jpg)|*.jpg"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	dialog->ShowModal();
	std::string info("Rozmiar obrazka: ");
	_clearImage->LoadFile(dialog->GetPath(), wxBITMAP_TYPE_JPEG);
	*_editImage = _clearImage->Copy();

	FIBITMAP *dib = FreeImage_Load(FIF_JPEG, dialog->GetPath(), JPEG_DEFAULT);
	FITAG *tagMake = NULL;

	info +=  std::to_string(FreeImage_GetWidth(dib)) + "*" + std::to_string(FreeImage_GetHeight(dib)) + "\n EXIF Info:\n";
	FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "Artist", &tagMake);
	info += std::string("Artist: ") + std::string((FreeImage_TagToString(FIMD_EXIF_MAIN, tagMake))) + std::string("\n");
	FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "Copyright", &tagMake);
	info += std::string("Copyright: ") + FreeImage_TagToString(FIMD_EXIF_MAIN, tagMake) + std::string("\n");
	FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "ResolutionUnit", &tagMake);
	info +=  std::string("Resolution Unit: ") + FreeImage_TagToString(FIMD_EXIF_MAIN, tagMake) + std::string("\n");
	FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "XResolution", &tagMake);
	info += std::string("XResolution: ") + FreeImage_TagToString(FIMD_EXIF_MAIN, tagMake) + std::string("\n");
	FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "YCbCrPositioning", &tagMake);
	info += std::string("YCbCrPositioning: ") + FreeImage_TagToString(FIMD_EXIF_MAIN, tagMake) + std::string("\n");
	FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "YResolution", &tagMake);
	info += std::string("YResolution: ") + FreeImage_TagToString(FIMD_EXIF_MAIN, tagMake);
	FreeImage_Unload(dib);

	info += "\n";
	_imageInfo->AppendText(info);
	refresh(dc);
}

void MainWindow::_cenzuraButtonOnButtonClick(wxCommandEvent& event) {
	*_editImage = _clearImage->Copy();
	wxClientDC dc(_panel);

	if (_editImage->Ok()) {
		const int height = 0.1 * _editImage->GetHeight();
		const int width = 0.2 * _editImage->GetWidth();
		const int x = 0.55 * _editImage->GetWidth();
		const int y = 0.05 * _editImage->GetHeight();

		cimg_library::CImg<unsigned char> cImage(width, height, 1, 3);

		for (int i = 0; i < width; ++i) {
			for (int j = 0; j < height; ++j) {
				cImage(i, j, 0) = _editImage->GetRed(x + i, y + j);
				cImage(i, j, 1) = _editImage->GetGreen(x + i, y + j);
				cImage(i, j, 2) = _editImage->GetBlue(x + i, y + j);
			}
		}

		cImage.blur(2.5);

		for (int i = 0; i < width; ++i)
			for (int j = 0; j < height; ++j)
				_editImage->SetRGB(x + i, y + j, cImage(i, j, 0), cImage(i, j, 1), cImage(i, j, 2));

		refresh(dc);
	}
}

void MainWindow::_erodeButtonOnButtonClick(wxCommandEvent& event) {
	*_editImage = _clearImage->Copy();
	wxClientDC dc(_panel);

	if (_editImage->Ok()) {
		const int height = _editImage->GetHeight();
		const int width = _editImage->GetWidth();
		cimg_library::CImg<unsigned char> cImage(width, height, 1, 3);

		for (int i = 0; i < width; ++i) {
			for (int j = 0; j < height; ++j) {
				cImage(i, j, 0) = _editImage->GetRed(i, j);
				cImage(i, j, 1) = _editImage->GetGreen(i, j);
				cImage(i, j, 2) = _editImage->GetBlue(i, j);
			}
		}

		cImage.erode(5, 5);

		for (int i = 0; i < width; ++i)
			for (int j = 0; j < height; ++j)
				_editImage->SetRGB(i, j, cImage(i, j, 0), cImage(i, j, 1), cImage(i, j, 2));

		refresh(dc);
	}
}

void MainWindow::_checkBoxOnCheckBox(wxCommandEvent& event) {

}