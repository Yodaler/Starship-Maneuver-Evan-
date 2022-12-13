#include <SFML/Graphics.hpp>
#include <iostream>
#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text text(MAX_NUMBER_OF_ITEMS);

};

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("fonts/Star_Shield.ttf"))
	{
		//handle error
	}

	menu[0].setFont(font);
	menu[0].setColor(sf::Color::White);
	menu[0].setString("Play");
	menu[0].setPosition(Vector2f(width / 2, height / 1));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("Controls");
	menu[1].setPosition(Vector2f(width / 2, height / 1));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(Vector2f(width / 2, height / 1));
	

	selectedItemIndex = 0;

}

Menu::~Menu()
{

}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Title Screen");

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();

				break;
			}
		}

		window.clear();
		window.display();
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex-- ;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}