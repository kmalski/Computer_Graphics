#include "Storage.h"

Storage::Storage(sf::RenderWindow *window) : window(window) {
}

Storage::~Storage() {
	clearStorage();
}

void Storage::clearStorage() {
	for (auto &shape : data)
		delete shape;
	data.clear();
	for (auto &shape : deleted)
		delete shape;
	deleted.clear();
}

void Storage::addOrDelete(sf::Drawable *shape, bool &isReleased, bool &onWorkspace) {
	if (isReleased) {
		data.push_back(shape);
		isReleased = false;
		onWorkspace = false;
	}
	else {
		delete shape;
	}
}

void Storage::drawStorage() {
	for (auto *shape : data) {
		window->draw(*shape);
	}
}

void Storage::saveImage(const std::string filePath) {
	sf::Texture texture;
	texture.create(window->getSize().x, window->getSize().y);
	texture.update(*window);

	sf::Image newWorkingspace;
	newWorkingspace.create(796, 536, sf::Color::Black);
	newWorkingspace.copy(texture.copyToImage(), 0, 0, sf::IntRect(2, 62, 796, 536));
	newWorkingspace.saveToFile(filePath);
}

void Storage::loadImage(const std::string filePath, sf::Texture & texture) {
	sf::Image imageFromFile;
	if (!imageFromFile.loadFromFile(filePath)) 
		return;

	clearStorage();
	texture.loadFromImage(imageFromFile);
	sf::Sprite *newWorkspace = new sf::Sprite(texture);
	newWorkspace->setPosition(sf::Vector2f(2, 62));
	data.push_back(newWorkspace);
}

void Storage::deleteLast() {
	if (!data.empty()) {
		deleted.push_back(data.back());
		data.pop_back();
	}
}

void Storage::returnDeleted() {
	if (!deleted.empty()) {
		data.push_back(deleted.back());
		deleted.pop_back();
	}
}
