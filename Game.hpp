//
//  Game.h
//  
//
//
//
#pragma once
#include <vector>
#include "RayCasting.hpp"
#include "Player.hpp"


const unsigned int size{100};
const unsigned int prorata{30};

class Game{

	sf::RenderWindow _window;
	RayCasting _rcEngine;
	Player _player;
	
	bool _isMovingUp;
	bool _isMovingDown;
	bool _isMovingRight;
	bool _isMovingLeft;
	float _angleOfTeste;
	
	std::vector<std::vector<g_TypeOfBlock>> _tabEnum;
	std::vector<std::vector<int>> _labyrinth;
	
	
	
private:						//fontion membre
	void processEvent();
	void update(sf::Time deltaTime);
	void render();
	void reload();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void handleMouseInput(sf::Event& event);
	void clearConsole();
	void renderSky();
	void renderFloor();
	
	
	
public:
	Game();
	void run();
	
	
	
};
