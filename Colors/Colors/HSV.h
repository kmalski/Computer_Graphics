#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <SFML/Graphics.hpp>
#include "ColorRepresentation.h"

class HSV final : public ColorRepresentation {
public:
	HSV(unsigned int radius, unsigned int x, unsigned int y);
	virtual void outtextxy(sf::RenderTarget &target, float x, float y) const;
	virtual sf::Color convert(const double angle, const double r);
};

HSV::HSV(unsigned int radius, unsigned int x, unsigned int y) : ColorRepresentation(radius, x, y) {
	createTexture();
	_sprite->setTexture(*_texture);
}

void HSV::outtextxy(sf::RenderTarget & target, float x, float y) const {
	_text->setPosition(x + 50, y + 10 + 2 * _radius);
	_text->setString("HSV  V = " + std::to_string(_scale));
	target.draw(*_text);
}

sf::Color HSV::convert(const double angle, const double r) {
	double s = r / _radius;
	double c = _scale * s;
	double x = c * (1 - fabs(fmod(angle * 3 / M_PI, 2) - 1));
	double m = _scale - c;

	double red, green, blue;
	if (angle <= M_PI / 3) {
		red = c;
		green = x;
		blue = 0;
	}
	else if (angle <= 2 * M_PI / 3) {
		red = x;
		green = c;
		blue = 0;
	}
	else if (angle <= M_PI) {
		red = 0;
		green = c;
		blue = x;
	}
	else if (angle <= 4 * M_PI / 3) {
		red = 0;
		green = x;
		blue = c;
	}
	else if (angle <= 5 * M_PI / 3) {
		red = x;
		green = 0;
		blue = c;
	}
	else if (angle <= 2 * M_PI) {
		red = c;
		green = 0;
		blue = x;
	}

	return sf::Color(static_cast<sf::Uint8>((red + m) * 255), static_cast<sf::Uint8>((green + m) * 255), static_cast<sf::Uint8>((blue + m) * 255));
}
