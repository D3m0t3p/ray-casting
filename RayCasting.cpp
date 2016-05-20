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



RayCasting::RayCasting()
{

}



//calcule la distance depius un certaine position avec un cerain angle jusque au mur le plus proche
//retourn la distance jusque au mur

float RayCasting::rayCasting(sf::Vector2f& playerPosition,float angle,const std::vector<std::vector<int>> &labyrinth,int &blockID, const Algo algo) const{
	
	

	if (algo == Algo::LINEAR) {
		float x = playerPosition.x;
		float y = playerPosition.y;
		float d{0.0f};
		angle = angle*_PI/180;
		float cosAngle = cosf(angle);
		float sinAngle = -sinf(angle);
		while (true) {
			try {
				if(labyrinth.at(floor(y/sizeOfBlock)).at(floor(x/sizeOfBlock)) == 1){
					blockID = 1;
					return d;	//return distance au mur
				}
				else if (labyrinth.at(floor(y/sizeOfBlock)).at(floor(x/sizeOfBlock)) ==2){
					blockID = 2;
					return d;
				}
				
				x += 2*cosAngle;
				y += 2*sinAngle;
				d += 2;		//simplification de l'equation de pythagor
				
				
			} catch (std::out_of_range& ec) {
				
				return EXIT_FAILURE;
			}
			
		}
	
	
	}
	else{

		float d{0};
		float incrementY;
		
		if((static_cast<int>(angle)%360) <180)
			incrementY=64;
		else
			incrementY = -64;
		angle = angle *_PI/180;
		float cosAngle = cosf(angle);
		float sinAngle = -sinf(angle);
		 //= static_cast<int>(floor(angle))%360 <= 90 ? 64 : static_cast<int>(floor(angle))%360 > 270 ? 64 : (-64); //si regarde a droit , ajoute 64 sinon diminue de 64
		

		float incrementX = (64 - playerPosition.y)/tanf(angle)+playerPosition.x;
		
		float x = playerPosition.x;
		float y = playerPosition.y;
		while(true){
			
			if(labyrinth.at(floor(y/sizeOfBlock)).at(floor(x/sizeOfBlock)) == 1){
				blockID = 1;
				return d;
			}
			else if (labyrinth.at(floor(y/sizeOfBlock)).at(floor(x/sizeOfBlock))==1){
				blockID = 2;
				return d;
			}
			
			x += incrementX * cosAngle;
			y += incrementY * sinAngle;
			d += sqrtf((powf(x, 2)+powf(y, 2)));
			//std::cout<<x<<" "<<y<<"   dist: "<<d<<std::endl;
		
			std::cout<<incrementY<<'\n';
		}
		
	}
	
	
	return 0;	//ne devrait jamais arriver ici car la map est entourée de mur
}


