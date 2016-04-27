//
//  RayCasting.cpp
//  
//
//
//

#include "RayCasting.hpp"
#include <cmath>
#include <iostream>
															//definit dans utility.cpp
extern int sizeOfBlock;														//pareil
extern const int g_preMakeLabSize{10};										//pareil
extern std::array< std::array<int, g_preMakeLabSize>, g_preMakeLabSize> preMakeLab; //pareil



RayCasting::RayCasting(int precisionOfTables)
{
	creatTable(precisionOfTables);
}



//calcule la distance depius un certaine position avec un cerain angle jusque au mur le plus proche
//retourn la distance jusque au mur

float RayCasting::rayCasting(sf::Vector2f& playerPosition,float angle,const std::vector<std::vector<int>> &labyrinth) const{
	float x = playerPosition.x;
	float y = playerPosition.y;
	float d{0.0f};
	angle = angle*_PI/180;
	float cosAngle = cosf(angle);
	float sinAngle = -sinf(angle);
	

	
	while (true) {
		try {
			if(labyrinth.at(floor(y/sizeOfBlock)).at(floor(x/sizeOfBlock)) == 1){
				return d;	//return distance au mur
			}
			
			x += 2*cosAngle;
			y += 2*sinAngle;
			d += 2;		//simplification de l'equation de pythagor
			
			
		} catch (std::out_of_range& ec) {

			return EXIT_FAILURE;
		}
		
	}
	
	return 0;	//ne devrait jamais arriver ici car la map est entourée de mur
}


//crée les sin cos et tang table pour les angles
//sinf fonction retourn float
//si  veut int comme retour: sin(angle)
//il faut completer  if/  else if

void RayCasting::creatTable(int precision){
	int angleTab{0};
	for (int i{0}; i< 360*precision; ++i) {
		
		angleTab = i/precision;
		_sinTable[i] = sinf((angleTab*_PI)/180);		//_PI est définit dans raycasting.hpp
		_cosTable[i] = cosf((angleTab*_PI)/180);
		
		
		if(angleTab == 90){
			//a complete
		}
		else if(angleTab ==180){
			//a complete
		}
		else if (angleTab == 270){
			//a complete
		}
		else if (angleTab == 360 || angleTab == 0){
			//a complete
		}
		else{
			
		}
		
	}
}























