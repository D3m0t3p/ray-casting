//
//  RayCasting.cpp
//  
//
//
//

#include "RayCasting.hpp"
#include <cmath>
#include <iostream>
extern int xMax;															//definit dans utility.cpp
extern int yMax;															//pareil
extern int sizeOfBlock;														//pareil
extern const int g_preMakeLabSize{10};										//pareil
extern std::array< std::array<int, g_preMakeLabSize>, g_preMakeLabSize> preMakeLab; //pareil



RayCasting::RayCasting(int precisionOfTables)
{
	creatTable(precisionOfTables);
}



//calcule la distance depius un certaine position avec un cerain angle jusque au mur le plus proche
//retourn la distance jusque au mur

float RayCasting::rayCasting(sf::Vector2f& playerPosition,float angle,const std::vector<std::vector<int>> &labyrinth,bool  wantPlaceInLab) const{
	float x = playerPosition.x;
	float y = playerPosition.y;
	float d{0.0f};
	//angle = 360 - angle;
	angle = angle*_PI/180; 
	float cosAngle = cosf(angle);
	float sinAngle = -sinf(angle);
	

	
	while (true) {
		try {
			if(labyrinth.at(floor(y/sizeOfBlock)).at(floor(x/sizeOfBlock)) == 1){
				if(wantPlaceInLab)
					std::cout <<  floor(y/sizeOfBlock) <<"  "<< floor(x/sizeOfBlock)<<"\n";
				return d;	//return distance to the wall
			}
			
			x += 2*cosAngle;
			y += 2*sinAngle;
			d += 2;		//simplification de l'equation de pythagor
			
			
		} catch (std::out_of_range& ec) {
			std::cout << "error Raycasting::raycasting at line "
			<< __LINE__<<"\nerror type: "<<ec.what()<<"(out of range)\n\n";
			playerPosition.x = 100.0;
			playerPosition.y = 100.0;
			return EXIT_FAILURE;
		}
		
	}
	
	return 0;	//should not be here
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
			//complete
		}
		else if(angleTab ==180){
			//complete
		}
		else if (angleTab == 270){
			//complete
		}
		else if (angleTab == 360 || angleTab == 0){
			//complete
		}
		else{
			
		}
		
	}
}























