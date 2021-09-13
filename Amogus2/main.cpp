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
	float xPos;
	float yPos;
	int8_t xDir;
	int8_t yDir;
	// RGB? below should be constants, they are properties but shouldn't really change
	uint8_t color[3];
	// 
	float playerSpeed;
	float playerVisibility;
public:
	// Up Down Left Right?
	int8_t setDir(int8_t x, int8_t y) {
		xDir = x;
		yDir = y;
	}
	// delta time needs to be float, also these functions are wrong
	int32_t movePlayer(Time deltaTime) {
		xPos += xDir * playerSpeed * deltaTime.asMilliseconds();
		yPos += yDir * playerSpeed * deltaTime.asMilliseconds();
	}
	
};

int main()
{
	Clock deltaTime;

	const unsigned int playerWidth = 96;
	const unsigned int playerHeight = 118;

	const int spriteNr = 1;
	vector <Player> playerData;

	// Set dynamically, change in settings? - keep scale/res?
	const unsigned int vWidth = 1920;
	const unsigned int vHeight = 1080;
	// Contains sprites
	vector <Sprite> spriteVect;

	RenderWindow window(VideoMode(vWidth, vHeight), "SUS");

	// 
	Texture texture;
	// Create texture to allow for max size pillar
	if (!texture.loadFromFile("sprites/spriteTextures.jpg", IntRect(0, 0, 192, 118))) {
		// Error
	}

	// Create sprites
	for (uint16_t i = 0; i < spriteNr; i++) {}
	Sprite playerS;
	playerS.setTextureRect(IntRect(0, 0, 96, 118));
	playerS.setTexture(texture);
	// Origin set to bottom left, origin should be constant and not re calculated. Maybe just change position of sprite
	// pillar.setOrigin(0, dataSet[i]);
	//pillar.setPosition((i * barWidth) + (i * 5), vHeight);
	// Passes a class of Sprite to vector?
	spriteVect.push_back(playerS);

	Clock clock;
	while (window.isOpen())
	{
		deltaTime.restart();

		// playerData[0].setDir(0,0);

		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				if (event.key.code == sf::Keyboard::D)
				{
					playerData[0].setDir(1, 0);
					spriteVect[0].setTextureRect(IntRect(97, 0, 192, 118));
					spriteVect[0].setTexture(texture);
					cout << "D key pressed \n";
				}
				break;
			default:
				break;
			}
		}

		// Movement 
		playerData[0].movePlayer(deltaTime.getTimeElapsed())
		
		// Draw call 
		window.clear(Color(255, 255, 255, 255));
		for (uint16_t i = 0; i < spriteVect.size(); i++) {
			// Change position of sprite here?
			window.draw(spriteVect[i]);
		}
		window.display();
	}
	return 0;
}