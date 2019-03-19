#define _USE_MATH_DEFINES

#include <math.h>
#include "ColorRepresentation.h"
#include "font.h"

ColorRepresentation::ColorRepresentation(unsigned int radius, unsigned int x, unsigned int y) : 
	_radius(radius),
	_x(x), _y(y), 
	_text(new sf::Text),
	_texture(new sf::Texture),
	_sprite(new sf::Sprite)
{
	this->setPosition(static_cast<float>(_x), static_cast<float>(_y));
	_font.loadFromMemory(font_data, font_data_size);
	_text->setFont(_font);
	_text->setCharacterSize(16);
	_text->setFillColor(sf::Color::Black);
	_scale = 0.5;

	_colors = new sf::Uint8[16 * _radius * _radius];
	_texture->create(2 * _radius, 2 * _radius);

	_sprite->setTexture(*_texture);
}

ColorRepresentation::~ColorRepresentation() {
	delete _text;
	delete _sprite;
	delete _texture;
	delete[] _colors;
}

void ColorRepresentation::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(*_sprite, states);
	outtextxy(target, static_cast<float>(_x), static_cast<float>(_y));
}

void ColorRepresentation::createTexture() {
	sf::Color color;

	for (int x = 0; x < static_cast<int>(2 * _radius); x++) {
		for (int y = 0; y < static_cast<int>(2 * _radius); y++) {

			double x_r = x - static_cast<int>(_radius);
			double y_r = static_cast<int>(_radius) - y;
			double angle = atan2(y_r, x_r);

			if (angle < 0)
				angle += 2 * M_PI;

			double r = sqrt(x_r * x_r + y_r * y_r);

			if (r  < _radius) {
				color = convert(angle, r);
				_colors[4 * (y * 2 * _radius + x) + 0] = color.r;
				_colors[4 * (y * 2 * _radius + x) + 1] = color.g;
				_colors[4 * (y * 2 * _radius + x) + 2] = color.b;
				_colors[4 * (y * 2 * _radius + x) + 3] = 255;
			}
			else {
				for (int i = 0; i < 4; ++i)
					_colors[4 * (y * 2 * _radius + x) + i] = 0;
			}
		}
	}
	_texture->update(_colors);
}

void ColorRepresentation::update(double scale) {
	if (fabs(_scale - scale) > 0.01) {
		_scale = scale;
		createTexture();
		_texture->update(_colors);
	}
}

sf::Font & ColorRepresentation::getFont() {
	return _font;
}
