#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class ColorRepresentation : public sf::Drawable, public sf::Transformable {
public:
	ColorRepresentation(unsigned int radius, unsigned int x, unsigned int y);
	virtual ~ColorRepresentation();
	virtual sf::Color convert(const double angle, const double r) = 0;
	virtual void outtextxy(sf::RenderTarget &target, float x, float y) const = 0;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual void createTexture();
	void update(double scale);
	sf::Font & getFont();

protected:
	unsigned int _x;
	unsigned int _y;

	sf::Font _font;
	sf::Text *_text;
	sf::Sprite *_sprite;
	sf::Texture *_texture;
	sf::Uint8 *_colors;

	const unsigned _radius;
	double _scale;
};
