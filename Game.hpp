//
//  Game.h
//  
//
//
//
#pragma once
#include <vector>
#include "SFML/Audio.hpp"
#include "RayCasting.hpp"
#include "Player.hpp"



class Game{

	sf::RenderWindow _window;
	sf::Music _music;
	RayCasting _rcEngine;
	Player _player;
	unsigned int _levelID;
	std::vector<std::vector<int>> _labyrinth;
	void (Game:: *statPlayed)(sf::Clock &clock, sf::Time& timeSinceLastUpdate);
	RayCasting::Algo _algo;
	
	
	
	
private:						//fontion membre
	void processPlayEvent();
	void update(const sf::Time &deltaTime);
	void render();
	void loadLevel(const unsigned int levelID);
	void handleKeyboardInput(sf::Keyboard::Key key, bool isPressed);
	void renderSky();
	void renderFloor();
	void play(sf::Clock &clock,sf::Time& timeSinceLastUpdate );
	
	
	void pause(sf::Clock &clock,sf::Time& timeSinceLastUpdate);
	void handlePauseEvent();
	void renderPause();

	sf::Time _deadLine;
	
public:
	Game();
	void run();
	
	
};
