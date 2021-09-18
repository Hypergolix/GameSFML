#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

// Uh deltatime pls
// Time since last frame, * float to move faster or slower depending on fps

/* idk how classes work:
	  player
	 /		\
  crew		 impostor

*/

class Player {
	float xPos = 0.0f;
	float yPos = 0.0f;
	float xDir = 1.0f;
	float yDir = 0.0f;
	// RGB? below should be constants, they are properties but shouldn't really change
	uint8_t color[3] = { 127, 127, 127 };
	// These might be the same across all players - apart from enemies
	float playerSpeed = 300.0f;
	float playerVisibility = 1.f;
	// Should each player have it's graphics be part of the player class?
public:
	// Up Down Left Right?
	void setDir(float x, float y) {
		xDir += x;
		yDir += y;
	}
	// Returns Vector2f with x and y position of player
	Vector2f getXY() {
		return Vector2f(xPos, yPos);
	}
	float getDir(){
		return xDir, yDir;
	}
	// delta time needs to be float, also these functions are wrong
	void movePlayer(float x, float y, float deltaTime) {
		xPos += x * playerSpeed * deltaTime;
		yPos += y * playerSpeed * deltaTime;
		// Think this way we can save direction but only move when the move/keypress happens
		setDir(x, y);
	}
};

int main()
{
	cout << fixed;

	const unsigned int playerWidth = 196;
	const unsigned int playerHeight = 253;

	const int spriteNr = 1;
	vector <Player> playerData;
	Player player1;
	playerData.push_back(player1);

	// Set dynamically, change in settings? - keep scale/res?
	const unsigned int vWidth = 1920;
	const unsigned int vHeight = 1080;
	// Contains sprites
	vector <Sprite> spriteVect;

	RenderWindow window(VideoMode(vWidth, vHeight), "SUS");
	window.setFramerateLimit(144);
	// 
	Texture texture;
	// Create texture to allow for max size pillar
	if (!texture.loadFromFile("sprites/spriteTextures2Debug.png", IntRect(0, 0, 1024, 1024))) {
		// Error
	}

	// Create sprites
	for (uint16_t i = 0; i < spriteNr; i++) {
		Sprite playerS;
		playerS.setTextureRect(IntRect(0, 0, playerWidth, playerHeight));
		playerS.setTexture(texture);
		// pillar.setOrigin();
		// pillar.setPosition();
		spriteVect.push_back(playerS);
	}
	Clock clock;

	while (window.isOpen())
	{
		// Save time since last restart, and restart the clock
		float deltaTime = clock.restart().asSeconds();

		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				break;
			default:
				break;
			}
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			playerData[0].movePlayer(0.f, -1.f, deltaTime);
			spriteVect[0].setTextureRect(IntRect(196, 0, playerWidth - 1, playerHeight));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			playerData[0].movePlayer(-1.f, 0.f, deltaTime);
			spriteVect[0].setTextureRect(IntRect(196, 0, playerWidth - 1, playerHeight));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			playerData[0].movePlayer(0.f, 1.f, deltaTime);
			spriteVect[0].setTextureRect(IntRect(196, 0, playerWidth - 1, playerHeight));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			playerData[0].movePlayer(1.f, 0.f, deltaTime);
			spriteVect[0].setTextureRect(IntRect(196, 0, playerWidth - 1, playerHeight));
		}

		// Tries to move every frame, maybe check if position has been changed?
		//playerData[0].movePlayer(deltaTime);
		// Graphics - use .move() ?
		spriteVect[0].setPosition(playerData[0].getXY());

		// Draw call 
		window.clear(Color(255, 255, 255, 255));
		for (uint16_t i = 0; i < spriteVect.size(); i++) {
			// Change position of sprite here?
			window.draw(spriteVect[i]);
		}
		window.display();

		//cout << "deltaTime: " << deltaTime << "\n";
		//cout << "xPos: " << playerData[0].getX() << "\n";
		//cout << "yPos: " << playerData[0].getY() << "\n";

	}
	return 0;
}