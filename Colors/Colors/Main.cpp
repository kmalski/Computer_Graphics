#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "RGB.h"
#include "CMY.h"
#include "HSV.h"
#include "HSL.h"
#include "Slider.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 650), "GFK Lab 02", sf::Style::Titlebar | sf::Style::Close);
	sf::Clock clock;
	sf::Time time = sf::Time::Zero;

	double parameter;
	unsigned int FPS = 0, frame_counter = 0;

	RGB rgb = RGB(100, 50, 50);
	CMY cmy = CMY(100, 350, 50);
	HSV hsv = HSV(100, 50, 350);
	HSL hsl = HSL(100, 350, 350);

	sf::Text fpsCounter;
	sf::Font font = sf::Font(rgb.getFont());
	fpsCounter.setFont(font);
	fpsCounter.setFillColor(sf::Color::Black);
	fpsCounter.setCharacterSize(16);
	fpsCounter.setPosition(685, 500);

	Slider slider = Slider(675, 50);

	clock.restart().asMilliseconds();
	while (window.isOpen())
	{
		sf::Event event;
		window.clear(sf::Color::White);

		while (window.pollEvent(event))
		{
			switch (event.type) {
				case sf::Event::Closed: {
					window.close();
					break;
				}
				case sf::Event::MouseButtonPressed: {
					if (event.mouseButton.button == sf::Mouse::Left)
						slider.update(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
					break;
				}
				case sf::Event::MouseMoved: {
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						slider.update(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
					break;
				}
			}
		}

		parameter = slider.getScale();
		rgb.update(parameter);
		cmy.update(parameter);
		hsv.update(parameter);
		hsl.update(parameter);
		window.draw(slider);
		window.draw(hsl);
		window.draw(hsv);
		window.draw(cmy);
		window.draw(rgb);

		fpsCounter.setString(std::to_string(FPS));
		window.draw(fpsCounter);

		if (clock.getElapsedTime().asSeconds() >= 1.0f)
		{
			FPS = static_cast<unsigned int>(static_cast<float>(frame_counter) / clock.getElapsedTime().asSeconds());
			clock.restart();
			frame_counter = 0;
		}
		frame_counter++;

		window.display();
	}
}