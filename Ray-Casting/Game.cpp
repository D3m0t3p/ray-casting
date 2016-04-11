//
//  Game.cpp
//  
//
//
//
#include "Game.hpp"
#include "utility.hpp"
#include <iostream>
using std::cout;
using std::endl;

Game::Game()
:_window(sf::VideoMode(800,600), "test"),
	_rcEngine(6),		//le paramètre donne la précision de moteur de ray-casting pas utilisé car les tables ne sont pas utilisée cf voir raycasting::creatTable()
	_player(),

	_isMovingUp(false),
	_isMovingDown(false),
	_isMovingRight(false),
	_isMovingLeft(false),
	_angleOfTeste(90.0) //float
{
		//_window.setVerticalSyncEnabled(true);
	loadFromFile(_labyrinth);
	//fromIntToEnum(_labyrinth, _tabEnum);
	
	
	
	
	
}



void Game::run(){
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time frameTime = sf::seconds((1./60));
	while (_window.isOpen()){
		
		processEvent();
		timeSinceLastUpdate += clock.restart();
		
		while (timeSinceLastUpdate > frameTime){
			timeSinceLastUpdate -= frameTime;
			processEvent();
			update(frameTime);
		}
		render();
		
	}
}
void Game::processEvent(){
	
	sf::Event event{};
	while (_window.pollEvent(event)) {
		
		switch (event.type) {
				
			case sf::Event::Closed:
				_window.close();
				break;
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;
			case sf::Event::MouseMoved:
				handleMouseInput(event);
				break;
			default:
				;
				break;
		}
	}
	
}

//multiplie the time betwen each frame to the speed to give a distance
//the distance (x and y) are passed to the move() member function of the player to set the new position

void Game::update(sf::Time deltaTime){
	
	
	sf::Vector2f movement{0.0f, 0.0f};
	
	if(_isMovingUp){									//UP
		movement.y += _player.speed*sinf(2*3.14 - _player.angle*3.14/180);
		movement.x += _player.speed*cosf(2*3.14 - _player.angle*3.14/180);
	}
	
	
	
	if(_isMovingDown){									//DOWN
		movement.y -= _player.speed*sinf(- _player.angle*3.14/180);
		movement.x -= _player.speed*cosf(- _player.angle*3.14/180);
	}
	
	
	
//	if(_isMovingLeft){									//LEFT
//		movement.x -= _player.speed;
//	}
//	
//	if(_isMovingRight){									//RIGHT
//		movement.x += _player.speed;
//	}
	
	_player.move(movement.x * deltaTime.asSeconds(), movement.y * deltaTime.asSeconds());
	//std::cout << _rcEngine.rayCasting(_player.position, _player.angle, _labyrinth)<<std::endl;
	

}



void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed){
	
	//###########movement############
	if (key == sf::Keyboard::W)
		_isMovingUp = isPressed;
	if (key == sf::Keyboard::S)
		_isMovingDown = isPressed;
	if (key == sf::Keyboard::A)
		_isMovingLeft = isPressed;
	if (key == sf::Keyboard::D)
		_isMovingRight = isPressed;
	
	//#########angle##############
	if(key ==sf::Keyboard::Left)
		_player.angle -= 1;
	if(key ==sf::Keyboard::Right)
		_player.angle += 1;
	
	
	if(key == sf::Keyboard::P){
		std::cout << _player.position.x <<" | "<<_player.position.y<<"\n";
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T))
		test();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
		std::cout <<"\n\n\n\n\n\n\n\n\n";

}
void Game::handleMouseInput(sf::Event& event){
	if (event.type == sf::Event::MouseMoved) {
		
		//cout<<((event.mouseMove.x*100)/_window.getSize().x)-60;
		
	}
}


void Game::render(){
	_window.clear();
	int precision{180};		//60°
	auto sizeWin = _window.getSize();
	int barCount{1};
	
	for (float i= (_player.angle - 30) ; i<precision; ++i) {
		
		float distance = _rcEngine.rayCasting(_player.position, i, _labyrinth);
		
		
		if(distance == 0)
			distance +=1;
		sf::RectangleShape bar{sf::Vector2f( sizeWin.x/precision , (64/distance) * 692 )};	//cstr take size as arg
		
		/*
		 
		 the 692 is the distance from player to projection plane
		 
		 */		
		
		bar.setPosition(barCount* sizeWin.x/60, sizeWin.y/2 - bar.getSize().y/2);
		_window.draw(bar);
		++barCount;
	}
	_window.display();
	
}

void Game::test(){
	
		_rcEngine.rayCasting(_player.position, _player.angle, _labyrinth,true);
	
	
	//cout << _player.position.x/_labyrinth.size()<< " | "<<_player.position.y/_labyrinth.at(1).size()<<endl;;
}
