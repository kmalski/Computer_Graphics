#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <SFML/Graphics.hpp>
#include "ColorRepresentation.h"

class RGB final : public ColorRepresentation {
public:
	RGB(unsigned int radius, unsigned int x, unsigned int y);
	virtual void outtextxy(sf::RenderTarget &target, float x, float y) const;
	virtual sf::Color convert(const double angle, const double r);
};

RGB::RGB(unsigned int radius, unsigned int x, unsigned int y) : ColorRepresentation(radius, x, y) {
	createTexture();
	_sprite->setTexture(*_texture);
}

void RGB::outtextxy(sf::RenderTarget &target, float x, float y) const {
	_text->setPosition(x + 50, y + 10 + 2 * _radius);
	_text->setString("RGB  B = " + std::to_string(static_cast<short>(_scale * 255)));
	target.draw(*_text);
}

sf::Color RGB::convert(const double angle, const double r) {
	return sf::Color(static_cast<sf::Uint8>(255.0 * r / _radius), static_cast<sf::Uint8>((angle / (2 * M_PI)) * 255), static_cast<sf::Uint8>(_scale * 255));
}
