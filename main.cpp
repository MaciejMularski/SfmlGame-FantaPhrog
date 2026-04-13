#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <optional>

int main() {

	//font for exp popup
	sf::Font font;
	if (!font.openFromFile("C:/Users/noupi/Downloads/C++Project/C++Project/FantaPhrog/x64/Debug/arial.ttf"))
	{
		std::cout << "Error loading font\n";
	}

	sf::Text expText(font);
	expText.setString("+10 EXP");
	expText.setCharacterSize(16);
	expText.setFillColor(sf::Color::White);
	
	
	
	
	//creating a window for the game
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "FantaPhrog");

	//setting framerate limit to 60 
	window.setFramerateLimit(100);

	sf::RectangleShape player({ 50.f, 50.f });
	player.setPosition({ 400.f, 300.f });
	player.setFillColor(sf::Color::Green);

	//creating a random seed for the exp item to spawn in different locations each time the game is run
	srand(time(0));

	//Player movement speed
	float speed = 1.f;
	
	//creating an exp item for the player to pick up
	sf::CircleShape expItem(10.f);
	expItem.setFillColor(sf::Color::Yellow);

	//setting random location for the exp item 
	float randomX = static_cast<float>(rand() % 780);
	float randomY = static_cast<float>(rand() % 580);
	expItem.setPosition({ randomX, randomY });


	bool showExpPopup = false;
	float expPopupTimer = 0.f;
	sf::Vector2f expPopupPosition;
	


	/////////////////////////////////////////////
	//creating enemey and making it red color
	sf::CircleShape enemy(20.f);
	enemy.setFillColor(sf::Color::Red);
	
	//creating if statement to make sure the enemy doesn's spawn on player or exp item
	bool validPosition = false;

	while (!validPosition)
	{
		 float EnemyRandomX = static_cast<float>(rand() % 760);
		float EnemyRandomY = static_cast<float>(rand() % 560);
	
		enemy.setPosition({ EnemyRandomX, EnemyRandomY });

		if (!enemy.getGlobalBounds().findIntersection(player.getGlobalBounds()) &&
			!enemy.getGlobalBounds().findIntersection(expItem.getGlobalBounds()))
		{
			validPosition = true;
		}
	}


	//regular player stats when game starts
	const int mainPlayerNumber = 0;
	double playerHealth = 100.0;
	double playerStamina = 100.0;
	int playerLevel = 1;
	double playerDamage = 1.00;
	double playerExp = 0;


	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		//player movement

		//movement controls for the player using WASD keys
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			player.move({ -speed, 0.f });
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			player.move({ 0.f, -speed });

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			player.move({ 0.f, speed });
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			player.move({ speed, 0.f });

		//creating boundaries for the player to prevent them from moving outside the window
		if (player.getPosition().x < 0.f)
			player.setPosition({ 0.f, player.getPosition().y });
		
		if (player.getPosition().x > 749.f)
			player.setPosition({ 749.f, player.getPosition().y });

		if (player.getPosition().y < 0.f)
			player.setPosition({ player.getPosition().x, 0.f });

		if (player.getPosition().y > 550.f)
			player.setPosition({ player.getPosition().x, 550.f });

		
		
		
		//creating pickup mechanics for the exp item
		if (player.getGlobalBounds().findIntersection(expItem.getGlobalBounds()))
		{
			playerExp += 10;
			std::cout << "Player picked up an experience item! EXP: " << playerExp << std::endl;

			// start popup
			showExpPopup = true;
			expPopupTimer = 30.f; // exp text popup
			expPopupPosition = { player.getPosition().x, player.getPosition().y - 25.f };

			expText.setPosition(expPopupPosition);

			// respawn exp item in a new random location
			randomX = static_cast<float>(rand() % 780);
			randomY = static_cast<float>(rand() % 580);
			expItem.setPosition({ randomX, randomY });
		}

		
		
		//exp popup mechanics 
		if (showExpPopup)
		{
			expPopupTimer -= 0.3f;
			expPopupPosition.y -= 0.2f; // float upward
			expText.setPosition(expPopupPosition);

			if (expPopupTimer <= 0.f)
			{
				showExpPopup = false;
			}
		}
		
		
		
		
		
		//reset game window and redraw player
		window.clear();

		if (showExpPopup)
		{
			window.draw(expText);
		}

		window.draw(player);
		window.draw(expItem);
		window.draw(enemy);
		window.display();
	}







	
}