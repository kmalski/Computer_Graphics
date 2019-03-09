#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <codecvt>

class Menu : public sf::Drawable {
public:
	Menu(sf::RenderWindow *parent);
	~Menu();
	void outtextxy(sf::RenderTarget& target, float x, float y, const wchar_t *str) const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool isOnWorkspace(const sf::Vector2f &mousePosition);
	bool isOnColorChooseBar(const sf::Vector2f &mousePosition);
	sf::Color pickColor(const sf::Vector2f &position);
	const sf::Color & getBorderColor() const;
	const sf::Color & getFillColor() const;
	void setBorderColor(const sf::Color &color);
	void setFillColor(const sf::Color &color);
	void stringToWstring(const std::string &str, std::wstring &wstr);
	void setCurrentAction(sf::Keyboard::Key key);
	sf::Drawable * drawRectangle(const sf::Vector2f &movePosition, const sf::Vector2f &clickPosition, const bool &isTransparent);
	sf::Drawable * drawCircle(const sf::Vector2f &movePosition, const sf::Vector2f &clickPosition);
	sf::Drawable * drawLine(const sf::Vector2f &movePosition, const sf::Vector2f &clickPosition);

private:
	sf::Font font;
	sf::Text *text;
	sf::RectangleShape *rectangle;

	sf::Texture *colors_texture;
	sf::Sprite *colors_sprite;
	sf::Uint8 *colors_pixels;
	const unsigned int colors_size_x = 765;
	const unsigned int colors_size_y = 60;

	sf::Color borderColor; //kolor ramki
	sf::Color fillColor; //kolor wypelnienia
	sf::RectangleShape *fillColorRec; //prostokat koloru wypelnienia
	sf::RectangleShape *borderColorRec;	//prostokat koloru ramki
	std::wstring currentAction;
	sf::RenderWindow *parent;

	inline void draw_to_color_pixels(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b) {
		colors_pixels[4 * (y * colors_size_x + x) + 0] = r;
		colors_pixels[4 * (y * colors_size_x + x) + 1] = g;
		colors_pixels[4 * (y * colors_size_x + x) + 2] = b;
		colors_pixels[4 * (y * colors_size_x + x) + 3] = 255;
	}
};