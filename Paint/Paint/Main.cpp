#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "Storage.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 650), "GFK Lab 01", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;
	sf::Keyboard::Key lastPressedKey = sf::Keyboard::Space;
	sf::Vector2f clickPosition;
	sf::Vector2f movePosition;
	sf::Texture texture;
	Menu menu(&window);
	Storage storage(&window);
	std::string filePath = "test.jpg";
	bool onWorkspace = false;
	bool onColorPick = false;
	bool isReleased = false;
	bool readyForAction = false;

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) 
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				onWorkspace = false;
				onColorPick = false;
				isReleased = false;
				lastPressedKey = event.key.code;
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.key.code == sf::Keyboard::Z) {
					storage.deleteLast();
					readyForAction = menu.setCurrentAction(lastPressedKey);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.key.code == sf::Keyboard::Y) {
					storage.returnDeleted();
					readyForAction = menu.setCurrentAction(lastPressedKey);
				}
				else {
					readyForAction = menu.setCurrentAction(lastPressedKey);
				}
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				clickPosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
				if (menu.isOnWorkspace(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
					onColorPick = false;
				}
				else if (menu.isOnColorChooseBar(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
					onColorPick = true;
				}
			}

			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				isReleased = true;
			}

			if (event.type == sf::Event::MouseMoved)
			{
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
					if (menu.isOnWorkspace(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
						onWorkspace = true;
						movePosition = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
					}
			}
		}

		storage.drawStorage();

		if (readyForAction) {
			if (onWorkspace) {
				switch (lastPressedKey) {
					case sf::Keyboard::R: {
						sf::Drawable *rectangle = menu.drawRectangle(movePosition, clickPosition, true);
						storage.addOrDelete(rectangle, isReleased, onWorkspace);
						break;
					}
					case sf::Keyboard::A: {
						sf::Drawable *rectangle = menu.drawRectangle(movePosition, clickPosition, false);
						storage.addOrDelete(rectangle, isReleased, onWorkspace);
						break;
					}
					case sf::Keyboard::C: {
						sf::Drawable *circle = menu.drawCircle(movePosition, clickPosition);
						storage.addOrDelete(circle, isReleased, onWorkspace);
						break;
					}
					case sf::Keyboard::L: {
						sf::Drawable *line = menu.drawLine(movePosition, clickPosition);
						storage.addOrDelete(line, isReleased, onWorkspace);
						break;
					}
				}
			}
			else if (onColorPick) {
				if (lastPressedKey == sf::Keyboard::F) {
					menu.setBorderColor(menu.pickColor(clickPosition));
					onColorPick = false;
				}
				else if (lastPressedKey == sf::Keyboard::B) {
					menu.setFillColor(menu.pickColor(clickPosition));
					onColorPick = false;
				}
			}
		}

		window.draw(menu);
		window.display();

		if (readyForAction) {
			if (lastPressedKey == sf::Keyboard::Key::W) {
				storage.saveImage(filePath);
				readyForAction = menu.setCurrentAction(sf::Keyboard::Space);
			}
			else if (lastPressedKey == sf::Keyboard::Key::O) {
				storage.loadImage(filePath, texture);
				readyForAction = menu.setCurrentAction(sf::Keyboard::Space);
			}
		}
	}

	return 0;
}