//
//  RayCasting.h
//  
//
//
//
#pragma once
#include "SFML/Graphics.hpp"
#include "utility.hpp"
#include <array>
class RayCasting {
	
	
	
private:
	std::map<float,float> _cosTable;
	std::map<float,float> _sinTable;
	const double _PI = 3.14159265358979323846; //utilisé pour calcule dans creatTable() et passage en radian
	
private:

public:
	RayCasting();
	float rayCasting(sf::Vector2f& position,float angle, const std::vector<std::vector<int>>& labyrinth,int &blockID)const;	//retourn la distance jusque au mur rencontré
	
};
