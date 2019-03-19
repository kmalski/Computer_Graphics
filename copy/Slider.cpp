#include "Slider.h"

Slider::Slider(unsigned int x, unsigned int y) : 
	_x(x), _y(y), 
	_texture(new sf::Texture), 
	_sprite(new sf::Sprite),
	_line(sf::Lines, 2),
	_scale(0.5)
{
	this->setPosition(static_cast<float>(_x), static_cast<float>(_y));

	_colors = new sf::Uint8[4 * HEIGHT * WIDTH];

	_texture->create(WIDTH, HEIGHT);
	initTexture();
	initBorder(sf::Color::Black);
	_texture->update(_colors);

	_sprite->setTexture(*_texture);

	_line[0] = sf::Vertex(sf::Vector2f(-10, HEIGHT / 2), sf::Color::Black);
	_line[1] = sf::Vertex(sf::Vector2f(10 + WIDTH, HEIGHT / 2), sf::Color::Black);
}

Slider::~Slider() {
	delete _texture;
	delete _sprite;
	delete[] _colors;
}

void Slider::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(*_sprite, states);
	target.draw(_line, states);
}

void Slider::update(const sf::Vector2f & position) {
	if (position.x >= _x && position.x <= _x + WIDTH && position.y <= _y + HEIGHT && position.y >= _y) {
		_line[0].position.y = _line[1].position.y = position.y - _y;
		_scale = (position.y - _y) / static_cast<double>(HEIGHT);
	}
}

void Slider::update(double offset) {
	unsigned int position = _line[0].position.y;
	_line[0].position.y = _line[1].position.y = position + offset * 400;
	_scale += offset;
}

void Slider::initTexture() {
	for (int x = 0; x < WIDTH; ++x) {
		for (int y = 0; y < HEIGHT; ++y) {
			_colors[4 * (y * WIDTH + x) + 0] = y * 255 / HEIGHT;
			_colors[4 * (y * WIDTH + x) + 1] = y * 255 / HEIGHT;
			_colors[4 * (y * WIDTH + x) + 2] = y * 255 / HEIGHT;
			_colors[4 * (y * WIDTH + x) + 3] = 220;
		}
	}
}

void Slider::initBorder(const sf::Color color) {
	for (int x = 0; x < WIDTH; x++) {
		_colors[4 * x + 0] = color.r;
		_colors[4 * x + 1] = color.g;
		_colors[4 * x + 2] = color.b;
		_colors[4 * x + 3] = color.a;
		_colors[4 * ((HEIGHT - 1) * WIDTH + x) + 0] = color.r;
		_colors[4 * ((HEIGHT - 1) * WIDTH + x) + 1] = color.g;
		_colors[4 * ((HEIGHT - 1) * WIDTH + x) + 2] = color.g;
		_colors[4 * ((HEIGHT - 1) * WIDTH + x) + 3] = color.a;
	}
	for (int y = 0; y < HEIGHT; y++) {
		_colors[4 * (y * WIDTH) + 0] = color.r;
		_colors[4 * (y * WIDTH) + 1] = color.g;
		_colors[4 * (y * WIDTH) + 2] = color.b;
		_colors[4 * (y * WIDTH) + 3] = color.a;
		_colors[4 * (y * WIDTH + WIDTH - 1) + 0] = color.r;
		_colors[4 * (y * WIDTH + WIDTH - 1) + 1] = color.g;
		_colors[4 * (y * WIDTH + WIDTH - 1) + 2] = color.b;
		_colors[4 * (y * WIDTH + WIDTH - 1) + 3] = color.a;
	}
}

double Slider::getScale() const {
	return _scale;
}
