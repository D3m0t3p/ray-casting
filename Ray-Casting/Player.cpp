//
//  Player.cpp
//  Ray-Casting
//
//

#include "Player.hpp"

Player::Player():
	position(384,384),
	speed(50.0),
	angle(270)

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
