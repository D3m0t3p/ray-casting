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
	
	
	
public:	//function
	Player();
	Player(const sf::Vector2i& startPosition);
	Player(const int x, const int y);
	
	void move(float distanceX, float distanceY){		
		position.x +=  distanceX;
		position.y +=  distanceY; // on met le '-' car les axes sont inversé ( en bas = y augmente)
	}
	

};
