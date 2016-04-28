//
//  Player.hpp
//  Ray-Casting
//
//

#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <cmath>


class Player {
public:	//var
	sf::Vector2f position;
	float angle;
	float speed; //30 pixeel/s

	
	bool isMovingUp;
	bool isMovingDown;
	bool isMovingRight;
	bool isMovingLeft;
	
	
	
	
public:	//function
	Player();
	void move(const sf::Time &deltaTime);

};
