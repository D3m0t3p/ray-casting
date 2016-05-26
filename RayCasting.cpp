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



RayCasting::RayCasting():
	_PI(3.14159265358979323846)
{

}
sf::Vector2f RayCasting::computeLineCoo(const sf::Vector2f &position, float angle, const std::vector<std::vector<int> > &labyrinth) const{
	
	angle = angle * _PI / 180;
	float x = position.x;
	float y = position.y;
	sf::Vector2f A;
	
	if(static_cast<int>(floor(angle))%360 <180){  //[0; π]
		
		A.y = floor( (x/sizeOfBlock) * 64 -1);
		A.x = x + ((y-A.y) / tanf(angle));
		while (true) {
			if(labyrinth.at(floor(A.x/sizeOfBlock)).at(floor(A.y/sizeOfBlock)) != 0){
				return sf::Vector2f(A.x, A.y);
				
			}
			
			A.x += sizeOfBlock/tan(angle);
			A.y -= 64;
		}
	}
	else{	// ]π; 2π[
		A.y = floor(x/64)*64+64;
		A.x = x + ((y-A.y)/tan(angle));
		
		while (true) {
			if(labyrinth.at(A.x/sizeOfBlock).at(A.y/sizeOfBlock) != 0){
				return sf::Vector2f(A.x, A.y);
				
			}
			
			A.x += sizeOfBlock/tan(angle);
			A.y += 64;
		}
	}
}

sf::Vector2f RayCasting::computeColumnCoo(const sf::Vector2f &position, float angle, const std::vector<std::vector<int> > &labyrinth) const {
	
	angle = angle * _PI / 180;
	float x = position.x;
	float y = position.y;
	sf::Vector2f A;
	
	if(static_cast<int>(floor(angle))%360 >270 && static_cast<int>(floor(angle)) % 360 <90){	//angle [270;0] U ]0;90]
		A.x = floor(x/sizeOfBlock)*sizeOfBlock+sizeOfBlock;
		A.y = y - tan(angle) *(A.x - x);
		
		while (true) {
//			if(labyrinth.at(floor(A.y/sizeOfBlock)).at(floor(A.x/sizeOfBlock)) != 0){
//				return sf::Vector2f(A.x, A.y);
//			}
			
			A.x += 64;
			A.y += tan(angle) * 64;
		}
	}
	else{	//angle 90 < angle <270
		A.x = floor(x/64) * 64 - 1;
		A.y = y - tan(angle) * (A.x - x);
		while (true) {
			if(labyrinth.at(floor(A.y/sizeOfBlock)).at(floor(A.x/sizeOfBlock)) != 0){
				return sf::Vector2f(A.x, A.y);
			}
			
			A.x -= 64;
			A.y += tan(angle) * 64;
		}
	}
}

//calcule la distance depius un certaine position avec un cerain angle jusque au mur le plus proche
//retourn la distance jusque au mur

float RayCasting::rayCasting(const sf::Vector2f& playerPosition,float angle,const std::vector<std::vector<int>> &labyrinth,int &blockID, const Algo algo) const{
	
	float x = playerPosition.x;
	float y = playerPosition.y;

	if (algo == Algo::LINEAR) {
		
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
	else{		//DDA algo
		auto line = computeLineCoo(playerPosition, angle, labyrinth);
		auto column = computeColumnCoo(playerPosition, angle, labyrinth);
		
		//float distanceLine = sqrtf( powf(line.x - x, 2) + pow(line.y - y,2));
		float distanceColumn = sqrtf( powf(line.x - x, 2) + pow(line.y - y,2));
//		float dist;
//		
//		if(distanceColumn < distanceLine){
//			dist = distanceColumn;
//			
//			if(labyrinth.at(floor(column.y/sizeOfBlock)).at(floor(column.x/sizeOfBlock)) ==1)
//				blockID = 1;
//			else
//				blockID = 2;
//		}
//		else{
//			dist = distanceLine;
//			if(labyrinth.at(floor(column.y/sizeOfBlock)).at(floor(column.x/sizeOfBlock)) ==1)
//				blockID = 1;
//			else
//				blockID = 2;
//		}
//		return dist;
	}
	
	
	return 0;	//ne devrait jamais arriver ici car la map est entourée de mur
}




