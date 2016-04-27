//
//  Player.cpp
//  Ray-Casting
//
//

#include "Player.hpp"

Player::Player():
	position(416,416),
	speed(50.0),
	angle(180)

{}


Player::Player(const int x, const int y):
	position(x,y),
	speed(25.0f),
	angle(90)
{}



Player::Player(const sf::Vector2i& position):
	position(position),
	speed(25.0f),
	angle(90)
{}

//move function is inlined
