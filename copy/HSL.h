#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <SFML/Graphics.hpp>
#include "ColorRepresentation.h"

class HSL final : public ColorRepresentation {
public:
	HSL(unsigned int radius, unsigned int x, unsigned int y);
	virtual void outtextxy(sf::RenderTarget &target, float x, float y) const;
	virtual sf::Color convert(const double angle, const double r);
};

HSL::HSL(unsigned int radius, unsigned int x, unsigned int y) : ColorRepresentation(radius, x, y) {
	createTexture();
	_sprite->setTexture(*_texture);
}

void HSL::outtextxy(sf::RenderTarget &target, float x, float y) const {
	_text->setPosition(x + 50, y + 10 + 2 * _radius);
	_text->setString("HSL  L = " + std::to_string(_scale));
	target.draw(*_text);
}

sf::Color HSL::convert(const double angle, const double r) {
	double h = angle;
	double s = r / _radius;
	double c = (1 - fabs(2 * _scale - 1)) * s ;

	double x = c * (1 - fabs(fmod(h * 3 / M_PI, 2) - 1)) ;
	double m = _scale - c / 2 ;

	double red, g, b;
	if (h <= M_PI / 3) {
		red = c;
		g = x;
		b = 0;
	}
	else if (h <= 2 * M_PI / 3) {
		red = x;
		g = c;
		b = 0;
	}
	else if (h <= M_PI) {
		red = 0;
		g = c;
		b = x;
	}
	else if (h <= 4 * M_PI / 3) {
		red = 0;
		g = x;
		b = c;
	}
	else if (h <= 5 * M_PI / 3) {
		red = x;
		g = 0;
		b = c;
	}
	else if (h <= 2 * M_PI) {
		red = c;
		g = 0;
		b = x;
	}
	else red = g = b = -255;

	return sf::Color(static_cast<sf::Uint8>((red + m) * 255), static_cast<sf::Uint8>((g + m) * 255), static_cast<sf::Uint8>((b + m) * 255));
}
