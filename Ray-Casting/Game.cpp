//
//  Game.cpp
//  
//
//
//
#include "Game.hpp"
#include "utility.hpp"
#include "ResourcePath.hpp"

Game::Game()
:
	_rcEngine(),		//le paramètre donne la précision de moteur de ray-casting pas utilisé car les tables ne sont pas utilisée cf voir raycasting::creatTable()
	_player()

	 //float
{
	sf::ContextSettings settings;
	settings.antialiasingLevel =8;
	
	_window.create(sf::VideoMode(800,600), "Ray-Casting",sf::Style::Default,settings);
	
	loadFromFile(_labyrinth);

	
	
	
}




void Game::run(){
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time frameTime = sf::seconds(static_cast<float>(1.0/60));
	
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
				handleKeyboardInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handleKeyboardInput(event.key.code, false);
				break;
			default:
				;
				break;
		}
	}
	
}



void Game::update(const sf::Time &deltaTime){
	
	
	_player.move(deltaTime);
	
	//if(_labyrinth.at(floor(_player.position.y/64)).at(floor(_player.position.y/64)) == 2){
		
	
	

}



void Game::handleKeyboardInput(sf::Keyboard::Key key, bool isPressed){
	
	//###########movement############
	if (key == sf::Keyboard::W) {_player.isMovingUp = isPressed;}
	if (key == sf::Keyboard::S) {_player.isMovingDown = isPressed;}
	if (key == sf::Keyboard::A) {_player.isMovingLeft = isPressed;}
	if (key == sf::Keyboard::D) {_player.isMovingRight = isPressed;}

	//#########angle##############
	if(key == sf::Keyboard::Left){
		_player.angle += 3;
	}
	if(key == sf::Keyboard::Right){
		_player.angle -= 3;
	}
	if(key == sf::Keyboard::Up)		_player.speed++;
	if(key == sf::Keyboard::Down)	_player.speed--;
	
	if(key == sf::Keyboard::L){
		reload();
	}
	

}


void Game::render(){
	_window.clear();
	auto sizeWin = _window.getSize();
	unsigned int barCount{1};
	unsigned int nbRect{400};
	renderSky();
	//renderFloor();
	
	for (float i= _player.angle - 30 ; i < _player.angle + 30; i+= 60.0/nbRect) {
		int blockID;
		float distance = _rcEngine.rayCasting(_player.position, i, _labyrinth, blockID, RayCasting::Algo::LINEAR);
		//distance = distance * cosf(i - _player.angle);
		
		if(distance == 0)
			distance +=1;
		
		
		
		sf::RectangleShape bar{sf::Vector2f( sizeWin.x/nbRect , (64/distance) * _window.getSize().x/(2*tanf(3.1415*30/180)))};	//cstr prends la taille de l'objet comme argument
		
		
		/*
		 
		 le 692 est la distance du joueur jusque au plan de projection definit comme win.x/2*tanj(30)
		 
		 */
		
		bar.setPosition((nbRect-barCount)* sizeWin.x/nbRect, sizeWin.y/2 - bar.getSize().y/2);
		if(blockID ==1){
			bar.setFillColor(sf::Color(floor(1.6*255/(distance/64)),0,0));
		}
		else if (blockID ==2){
			bar.setFillColor(sf::Color(255,255,0));
		}
		
		
		
		
		_window.draw(bar);
		++barCount;
		
		
	}
	_window.display();
	
}





void Game::reload(){
	std::cout <<"reload";
	_labyrinth.clear();
	loadFromFile(_labyrinth);
	
}







void Game::renderSky(){
	/*
	 format du vertex array;
	 
	 1			2
	 
	 
	 0			3
	 
	 */
	
	sf::VertexArray sky{sf::Quads,4};
	sky[0].position = sf::Vector2<float>(0,_window.getSize().y/2);
	sky[0].color = sf::Color(20,20,255);

	sky[1].position = sf::Vector2f(0,0);
	sky[1].color = sf::Color(0,0,255,180);


	sky[2].position = sf::Vector2f(_window.getSize().x,0);
	sky[2].color = sf::Color(0,0,255,180);


	sky[3].position = sf::Vector2f(_window.getSize().x, _window.getSize().y/2);
	sky[3].color = sf::Color(20,20,255);

	
	
	
	_window.draw(sky);
	
}

void Game::renderFloor(){
	/*
	 
	 format est le même que dans void Game::renderSky();
	 
	 
	 */
	
	sf::VertexArray floor{sf::Quads,4};
	
	floor[0].position = sf::Vector2<float>(0,_window.getSize().y);
	floor[0].color = sf::Color::Red;
	
	
	floor[1].position = sf::Vector2f(0,_window.getSize().y/2);
	floor[1].color = sf::Color::Red;

	
	
	floor[2].position = sf::Vector2f(_window.getSize().x,_window.getSize().y/2);
	floor[2].color = sf::Color::Red;

	
	
	floor[3].position = sf::Vector2f(_window.getSize().x, _window.getSize().y);
	floor[3].color = sf::Color::Red;

	
	
	
	_window.draw(floor);
}

