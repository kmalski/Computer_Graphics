#define _USE_MATH_DEFINES
#include <cmath>
#include "Menu.h"
#include "font.h"

Menu::Menu(sf::RenderWindow *parent) : parent(parent) {
	font.loadFromMemory(font_data, font_data_size);
	text = new sf::Text;
	text->setFont(font);
	text->setCharacterSize(12);
	text->setFillColor(sf::Color::White);

	rectangle = new sf::RectangleShape(sf::Vector2f(796, 536));
	rectangle->setFillColor(sf::Color::Transparent);
	rectangle->setOutlineColor(sf::Color::White);
	rectangle->setOutlineThickness(1.0f);
	rectangle->setPosition(2, 62);

	unsigned int x, y;
	colors_pixels = new sf::Uint8[colors_size_x * colors_size_y * 4];
	for (x = 0; x < 255; x++)
		for (y = 0; y < 30; y++) {
			draw_to_color_pixels(x, y, x, 255, 0);
			draw_to_color_pixels(x + 255, y, 255, 255 - x, 0);
			draw_to_color_pixels(x + 510, y, 255, 0, x);
			draw_to_color_pixels(254 - x, y + 30, 0, 255, 255 - x);
			draw_to_color_pixels(509 - x, y + 30, 0, x, 255);
			draw_to_color_pixels(764 - x, y + 30, 255 - x, 0, 255);
		}

	colors_texture = new sf::Texture();
	colors_texture->create(colors_size_x, colors_size_y);
	colors_texture->update(colors_pixels);

	colors_sprite = new sf::Sprite();
	colors_sprite->setTexture(*colors_texture);
	colors_sprite->setPosition(1, 1);

	//ustalanie pozycji prostakatkow reprezentujacych aktualne kolory
	auto size_x = parent->getSize().x - colors_size_x;
	auto size_y = colors_size_y / 2;

	//tworzenie obiektu reprezentujacego aktualny kolor rysowania
	borderColor = sf::Color::Black;
	borderColorRec = new sf::RectangleShape(sf::Vector2f(size_x - 2, size_y - 2));
	borderColorRec->setPosition(sf::Vector2f(colors_size_x + 2, 2));
	borderColorRec->setFillColor(borderColor);

	//towrzenie obiektu reprezentujacego aktualny kolor wypelnienia
	fillColor = sf::Color::Black;
	fillColorRec = new sf::RectangleShape(sf::Vector2f(size_x - 2, size_y - 2));
	fillColorRec->setPosition(sf::Vector2f(colors_size_x + 2, size_y + 2));
	fillColorRec->setFillColor(fillColor);

	//ustawianie aktualnej akcji
	currentAction = L"";
}

Menu::~Menu() {
	delete text;
	delete rectangle;
	delete fillColorRec;
	delete borderColorRec;
	delete colors_pixels;
	delete colors_sprite;
	delete colors_texture;
}

void Menu::outtextxy(sf::RenderTarget& target, float x, float y, const wchar_t *str) const {
	text->setPosition(x, y);
	text->setString(str);
	target.draw(*text);
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	outtextxy(target, 5, 600, L"f - wybór koloru rysowania");
	outtextxy(target, 5, 615, L"b - wybór koloru wype³niania");
	outtextxy(target, 5, 630, L"l - rysowanie linii");

	outtextxy(target, 200, 600, L"r - rysowanie prostok¹ta");
	outtextxy(target, 200, 615, L"a - rysowanie wype³nionego prostok¹ta");
	outtextxy(target, 200, 630, L"c - rysowanie okrêgu");

	outtextxy(target, 470, 600, L"w - zapis do pliku");
	outtextxy(target, 470, 615, L"o - odczyt z pliku");
	outtextxy(target, 470, 630, L"esc - wyjœcie");

	outtextxy(target, 650, 615, L"Aktualne:");
	//wypisywanie aktualnej akcji
	outtextxy(target, 710, 615, currentAction.c_str());

	//rysowanie aktualnie wybranych kolorow
	fillColorRec->setFillColor(fillColor);
	borderColorRec->setFillColor(borderColor);
	target.draw(*borderColorRec);
	target.draw(*fillColorRec);

	target.draw(*rectangle);
	target.draw(*colors_sprite);
}

bool Menu::isOnWorkspace(const sf::Vector2f &mousePosition) {
	if (mousePosition.x < 2 || mousePosition.x > 798)
		return false;
	if (mousePosition.y < 62 || mousePosition.y > 598)
		return false;
	return true;
}

bool Menu::isOnColorChooseBar(const sf::Vector2f &mousePosition) {
	if (mousePosition.x > 765)
		return false;
	if (mousePosition.y > 60)
		return false;
	return true;
}

sf::Color Menu::pickColor(const sf::Vector2f &position) {
	int x = static_cast<int>(position.x);
	int y = static_cast<int>(position.y);
	return sf::Color(colors_pixels[4 * (y * colors_size_x + x) + 0],
		colors_pixels[4 * (y * colors_size_x + x) + 1],
		colors_pixels[4 * (y * colors_size_x + x) + 2]);
}

const sf::Color & Menu::getBorderColor() const {
	return borderColor;
}

const sf::Color & Menu::getFillColor() const {
	return fillColor;
}

void Menu::setBorderColor(const sf::Color &color) {
	borderColor = color;
}

void Menu::setFillColor(const sf::Color &color) {
	fillColor = color;
}

bool Menu::setCurrentAction(sf::Keyboard::Key key) {
	switch (key) {
	case sf::Keyboard::F: {
		currentAction = L"f";
		return true;
	}
	case sf::Keyboard::B: {
		currentAction = L"b";
		return true;
	}
	case sf::Keyboard::L: {
		currentAction = L"l";
		return true;
	}
	case sf::Keyboard::R: {
		currentAction = L"r";
		return true;
	}
	case sf::Keyboard::A: {
		currentAction = L"a";
		return true;
	}
	case sf::Keyboard::C: {
		currentAction = L"c";
		return true;
	}
	case sf::Keyboard::W: {
		currentAction = L"w";
		return true;
	}
	case sf::Keyboard::O: {
		currentAction = L"o";
		return true;
	}
	default:
		currentAction = L"";
		return false;
	}
}

sf::Drawable * Menu::drawRectangle(const sf::Vector2f &movePosition, const sf::Vector2f &clickPosition, const bool &isTransparent) {
	sf::RectangleShape *rectangle = new sf::RectangleShape(movePosition - clickPosition);
	rectangle->setPosition(clickPosition);
	rectangle->setOutlineColor(borderColor);
	rectangle->setOutlineThickness(1);
	if (isTransparent)
		rectangle->setFillColor(sf::Color::Transparent);
	else
		rectangle->setFillColor(fillColor);
	parent->draw(*rectangle);
	return rectangle;
}

sf::Drawable * Menu::drawCircle(const sf::Vector2f &movePosition, const sf::Vector2f &clickPosition) {
	sf::CircleShape *circle = new sf::CircleShape();
	double radius = sqrt(pow(clickPosition.x - movePosition.x, 2) + pow(clickPosition.y - movePosition.y, 2)) / 2;
	double rotatingAngle = atan2(movePosition.y - clickPosition.y, movePosition.x - clickPosition.x) * (180 / M_PI) - 45;
	circle->setRadius(radius);
	circle->setPosition(clickPosition);
	circle->rotate(rotatingAngle);
	circle->move(sf::Vector2f((radius - radius * sqrt(2)) * cos((rotatingAngle + 45) * M_PI / 180),
		(radius - radius * sqrt(2)) * sin((rotatingAngle + 45) * M_PI / 180)));
	circle->setOutlineColor(borderColor);
	circle->setOutlineThickness(1);
	circle->setFillColor(sf::Color::Transparent);
	parent->draw(*circle);
	return circle;
}

sf::Drawable * Menu::drawLine(const sf::Vector2f &movePosition, const sf::Vector2f &clickPosition) {
	sf::VertexArray *line = new sf::VertexArray(sf::LinesStrip, 2);
	(*line)[0].position = clickPosition;
	(*line)[0].color = borderColor;
	(*line)[1].position = movePosition;
	(*line)[1].color = fillColor;
	parent->draw(*line);
	return line;
}

