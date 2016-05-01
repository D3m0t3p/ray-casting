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



class Game{

	sf::RenderWindow _window;
	RayCasting _rcEngine;
	Player _player;
	
	std::vector<std::vector<int>> _labyrinth;
	
	
	
private:						//fontion membre
	void processEvent();
	void update(const sf::Time &deltaTime);
	void render();
	void reload();
	void handleKeyboardInput(sf::Keyboard::Key key, bool isPressed);
	void renderSky();
	void renderFloor();
	
	
	
public:
	Game();
	void run();
	
	
	
};
