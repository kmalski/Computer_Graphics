#pragma once

#include <SFML/Graphics.hpp>

#define HEIGHT 400
#define WIDTH 50

class Slider : public sf::Drawable, public sf::Transformable {
public:
	Slider(unsigned int x, unsigned int y);
	~Slider();
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void update(const sf::Vector2f &position);
	void update(double offset);
	void initTexture();
	void initBorder(const sf::Color color);
	double getScale() const;

private:
	sf::Sprite *_sprite;
	sf::Texture *_texture;
	sf::Uint8 *_colors;
	sf::VertexArray _line;

	unsigned int _x;
	unsigned int _y;
	double _scale;
};