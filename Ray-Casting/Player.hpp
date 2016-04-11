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
	
	void move(float distanceX, float distanceY){		//inline pour de optimiser (peu etre)
		position.x +=  distanceX * cosf(angle*3.14/180);
		position.y +=  distanceY * sinf(angle*3.14/180);
	}
	

};
