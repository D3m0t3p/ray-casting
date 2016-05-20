//
//  Player.cpp
//  Ray-Casting
//
//

#include "Player.hpp"

Player::Player():
	position(416,416),
	speed(50.0),
	angle(0),
	isMovingUp(false),
	isMovingDown(false),
	isMovingRight(false),
	isMovingLeft(false)

{

}


void Player::move(const sf::Time &deltaTime){
	if(isMovingDown){									//DOWN
		position.y += speed*sinf(angle*3.14/180)*deltaTime.asSeconds();	//met - car sinus
		position.x -= speed*cosf(angle*3.14/180)*deltaTime.asSeconds();
	}
	
	
	
	if(isMovingUp){									//UP
		position.y -= speed*sinf(angle*3.14/180)*deltaTime.asSeconds();	//met + car devrait etre - mais on rajoute un - car c'est un sinus => +
		position.x += speed*cosf(angle*3.14/180)*deltaTime.asSeconds();
	}
	
	if(isMovingRight){
		//UP
		position.y += speed*sinf((angle+90)*3.14/180)*deltaTime.asSeconds();	//met + car devrait etre - mais on rajoute un - car c'est un sinus => +
		position.x -= speed*cosf((angle+90)*3.14/180)*deltaTime.asSeconds();
	}
	if(isMovingLeft){
		//UP
		position.y += speed*sinf((angle-90)*3.14/180)*deltaTime.asSeconds();	//met + car devrait etre - mais on rajoute un - car c'est un sinus => +
		position.x -= speed*cosf((angle-90)*3.14/180)*deltaTime.asSeconds();
	}
}


sf::Vector2f Player::futurMove(const sf::Time &deltaTime){
	float x,y;
	x = position.x;
	y=position.y;
	if(isMovingDown){									//DOWN
		y += speed*sinf(angle*3.14/180)*deltaTime.asSeconds();	//met - car sinus
		x -= speed*cosf(angle*3.14/180)*deltaTime.asSeconds();
	}
	
	
	
	if(isMovingUp){									//UP
		y -= speed*sinf(angle*3.14/180)*deltaTime.asSeconds();	//met + car devrait etre - mais on rajoute un - car c'est un sinus => +
		x += speed*cosf(angle*3.14/180)*deltaTime.asSeconds();
	}
	
	if(isMovingRight){
		//UP
		y += speed*sinf((angle+90)*3.14/180)*deltaTime.asSeconds();	//met + car devrait etre - mais on rajoute un - car c'est un sinus => +
		x -= speed*cosf((angle+90)*3.14/180)*deltaTime.asSeconds();
	}
	if(isMovingLeft){
		//UP
		y += speed*sinf((angle-90)*3.14/180)*deltaTime.asSeconds();	//met + car devrait etre - mais on rajoute un - car c'est un sinus => +
		x -= speed*cosf((angle-90)*3.14/180)*deltaTime.asSeconds();
	}
	return sf::Vector2f(x,y);
}


