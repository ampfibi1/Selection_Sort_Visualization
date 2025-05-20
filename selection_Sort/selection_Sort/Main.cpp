#include<SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
const int width = 1000;
const int height = 800; 
const int barWidth = 3; 

void fillBars(std::vector<sf::RectangleShape> &bars) {
	int xOffset = 0; 
	while (xOffset <= width) {
		float barHeight = rand() % (height - 50) + 5; 
		sf::RectangleShape bar(sf::Vector2f(barWidth,barHeight));
		bar.setFillColor(sf::Color::Blue);
		bar.setPosition(sf::Vector2f(xOffset,height-barHeight));

		bars.push_back(bar);

		xOffset += barWidth + 3; 
	}
}

int main() {
	sf::RenderWindow windows(sf::VideoMode(width,height),"Selection Sort");
	sf::Event event; 

	std::vector<sf::RectangleShape> bars; 
	srand(time(NULL));
	bool isSort = false;
	sf::Clock clock; 
	int i = 0;
	int min = i, j = i + 1;

	fillBars(bars);

	while (windows.isOpen()){
		while (windows.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				windows.close();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			std::cout << "Sorting Start\n";
			isSort = true; 
		}

		if (isSort && clock.getElapsedTime().asMilliseconds() >= 1.f) {
			if (i < bars.size()) {
				if (j < bars.size()) {
					if (bars[min].getSize().y > bars[j].getSize().y) {
						min = j; 
					}
					j++;
				}
				else {
					if (min != i) {
						float tempX = bars[i].getPosition().x;
						bars[i].setPosition(sf::Vector2f(bars[min].getPosition().x, bars[i].getPosition().y));
						bars[min].setPosition(sf::Vector2f(tempX, bars[min].getPosition().y));

						std::swap(bars[i], bars[min]);
					}
					i++;
					j = i;
					min = i;
				}
				
			}
			else {
				isSort = false; 
				std::cout << "Sorted\n"; 
			}
			clock.restart();
		}

		windows.clear(sf::Color::White);
		for (auto& x : bars) windows.draw(x);
		windows.display();
	}
}