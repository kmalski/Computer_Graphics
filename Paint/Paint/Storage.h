#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

class Storage {
public:
	Storage(sf::RenderWindow *window);
	~Storage();
	void clearStorage();
	void addOrDelete(sf::Drawable *shape, bool &isReleased, bool &onWorkspace);
	void drawStorage();
	void saveImage(const std::string filePath);
	void loadImage(const std::string filePath, sf::Texture & texture);
	void deleteLast();
	void returnDeleted();

private:
	std::vector<sf::Drawable *> data;
	std::vector<sf::Drawable *> deleted;
	sf::RenderWindow *window;
};
