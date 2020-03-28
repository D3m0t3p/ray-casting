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
	_rcEngine(),
	_player(),
	_levelID(1),
	_music(),
	_algo(RayCasting::Algo::LINEAR),
	_deadLine()

{
	sf::ContextSettings settings;
	settings.antialiasingLevel =8;
	
	_window.create(sf::VideoMode(1200,900), "Ray-Casting",sf::Style::Default,settings);
	
	load_from_file(_labyrinth,1);
	 statPlayed = &Game::pause;
	
	
	
}



void Game::play(sf::Clock &clock, sf::Time& timeSinceLastUpdate){

	
	const sf::Time frameTime = sf::seconds(static_cast<float>(1.0/60.0));
	
	processPlayEvent();
	timeSinceLastUpdate += clock.restart();
	
	while (timeSinceLastUpdate > frameTime){
		timeSinceLastUpdate -= frameTime;
		processPlayEvent();
		update(frameTime);
	}
	render();
	
	_deadLine -= sf::seconds(1.0/60);
	
}



void Game::pause(sf::Clock &clock, sf::Time& timeSinceLastUpdate){
	handlePauseEvent();
	
	_window.clear(sf::Color::Black);
	renderPause();
	_window.display();
}

void Game::renderPause(){
	_window.clear();
	sf::Font font;
	if(!font.loadFromFile(resourcePath()+"arial.ttf"))
		return;
	sf::Text txt;
	txt.setFont(font);
	txt.setCharacterSize(50);
	txt.setPosition(_window.getSize().x/2 -txt.getGlobalBounds().width/2, _window.getSize().y/2 -txt.getGlobalBounds().height/2);
	txt.setString("Pause");
	
	_window.draw(txt);
	_window.display();
	
}
void Game::handlePauseEvent(){
	
	sf::Event event;
	
	while (_window.pollEvent(event)) {
		switch(event.type){
				
			case sf::Event::EventType::KeyPressed :
				
				if(event.key.code == sf::Keyboard::Key::Escape){
					statPlayed = &Game::play;
				}
				break;
			case sf::Event::EventType::KeyReleased:
				handleKeyboardInput(event.key.code, false);
			default:
				
				;
				break;
		}
	}
}

void Game::run(){
	
	_deadLine = sf::seconds(60);
	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	while (_window.isOpen()){
		
			(this->*statPlayed)(clock, timeSinceLastUpdate);

	}
	
		
	
}
void Game::processPlayEvent(){
	
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
			case sf::Event::Resized:
				//std::cout<< event.size.width<<" "<<event.size.height<<'\n';
				break;
			default:
				;
				break;
		}
	}
	
}



void Game::update(const sf::Time &deltaTime){
	
	
	
	 if (_labyrinth.at(floor(_player.position.y/64)).at(floor(_player.position.x/64)) ==2){
		 if(_levelID != 4){
			 loadLevel(_levelID++);
			 _player.position = sf::Vector2f(100,100);
			 _player.angle = 360;
			 
		 }
		
	 }
	auto posi = _player.futurMove(deltaTime);
	if(_labyrinth.at(floor(posi.y/64)).at(floor(posi.x/64)) != 1){
		_player.move(deltaTime);
	}
	
	
	
	

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
	
	//########	speed	#######
	if(key == sf::Keyboard::Up)		_player.speed+=3;
	if(key == sf::Keyboard::Down)	_player.speed-=3;
	
	
	
	if(key == sf::Keyboard::N and !isPressed){
		
		if(_levelID != 4)
			loadLevel(++_levelID);
		
	}
	
	if(key == sf::Keyboard::Key::L and !isPressed){
		
		loadLevel(_levelID);
	}
	
	if (key == sf::Keyboard::P and !isPressed) {
		if(_levelID != 1)
			loadLevel(--_levelID);

	}
	if(key == sf::Keyboard::Escape && isPressed){
		statPlayed = &Game::pause;
	}
	/*if(key == sf::Keyboard::Space && isPressed){
		_algo = (_algo == RayCasting::Algo::LINEAR) ? RayCasting::Algo::DDA : RayCasting::Algo::LINEAR;
		std::cout <<"changes algo\n";
		
	}*/
	
	if(key == sf::Keyboard::Key::T){
		_deadLine.asSeconds() < 0 ? _deadLine = sf::seconds(10) : _deadLine += sf::seconds(10);
	}
	if(key == sf::Keyboard::Key::G)
		_deadLine -= sf::seconds(10);
		
	if(key == sf::Keyboard::H)
		std::cout<< _player.position.x<<" "<<_player.position.y<<"\t|\t"<< _player.angle<<'\n';
	
	
		
	

}


void Game::render(){
	sf::Font font;
	if(!font.loadFromFile(resourcePath()+"arial.ttf"))
		return;
	sf::Text time,level;
	time.setFont(font);
	level.setFont(font);
	time.setCharacterSize(25);
	level.setCharacterSize(25);
	level.setString(std::string("level: ")+std::to_string(_levelID));
	level.setPosition(_window.getSize().x- level.getGlobalBounds().width*1.2,time.getPosition().y);
	_deadLine.asSeconds() <= 0 ? time.setString("Time's up !") : time.setString (std::to_string(static_cast<int>(_deadLine.asSeconds()))) ;
	
	_window.clear();
	auto sizeWin = _window.getSize();
	unsigned int barCount{1};
	unsigned int nbRect{400};
	renderSky();
	//renderFloor();
	
	for (float i= _player.angle - 30 ; i < _player.angle + 30; i+= 60.0/nbRect) {
		int blockID;
		sf::Vector2f hitPosition;
		float distance = _rcEngine.rayCasting(_player.position, i, _labyrinth, blockID, hitPosition, _algo);
		
		if(distance < .5){
			distance +=1.1f;
		}
		distance *= cosf((i- _player.angle) * 3.141592/180);	//correct fish-eyes
		
		sf::RectangleShape bar{sf::Vector2f( sizeWin.x/nbRect , (64/distance) */*692*/ _window.getSize().x/(2*tanf(30*3.1415/180)))};	//cstr prends la taille de l'objet comme argument
		
		
		/*
		 
		 le 692 est la distance du joueur jusque au plan de projection definit comme win.x/2*tanj(30)
		 
		 */
		
		bar.setPosition((nbRect-barCount)* sizeWin.x/nbRect, sizeWin.y/2 - bar.getSize().y/2);
		if(blockID ==1){
			bar.setFillColor(sf::Color(
									   static_cast<sf::Uint8>(floor(((1.6*255.0)/distance)*64)) < 0 || static_cast<sf::Uint8>(floor(((1.6*255.0)/distance)*64)) > 255 ? 250:static_cast<sf::Uint8>(floor(((1.6*255.0)/distance)*64)),
									   0,
									   0));
			
			
		}
		else if (blockID ==2){
			bar.setFillColor(sf::Color(204,127,49));
			
		}
		
		
		
		_window.draw(bar);
		_window.draw(time);
		_window.draw(level);
		++barCount;
		
		
	}
	_window.display();
	
}





void Game::loadLevel(const unsigned int levelID){
	
	if(_levelID == 5 or levelID == 0 or levelID == 5 or _levelID == 0){
		return;
	
		
	}
	
	_labyrinth.clear();
	load_from_file(_labyrinth,levelID);
	std::cout << "\n\n" << levelID << '\n';
	show(_labyrinth);
	
	_deadLine = sf::seconds(60);
	
}







void Game::renderSky(){
	/*
	 format du vertex array;
	 
	 1			2
	 
	 
	 0			3
	 
	 */
	
	sf::VertexArray sky{sf::Quads,4};
	sky[0].position = sf::Vector2<float>(0, _window.getSize().y/2);
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
	floor[0].color = sf::Color::Green;
	
	
	floor[1].position = sf::Vector2f(0,_window.getSize().y/2);
	floor[1].color = sf::Color::Green;

	
	
	floor[2].position = sf::Vector2f(_window.getSize().x,_window.getSize().y/2);
	floor[2].color = sf::Color::Green;

	
	
	floor[3].position = sf::Vector2f(_window.getSize().x, _window.getSize().y);
	floor[3].color = sf::Color::Green;

	
	
	
	_window.draw(floor);
}

