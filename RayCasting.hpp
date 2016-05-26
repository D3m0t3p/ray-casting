//
//  RayCasting.h
//  
//
//
//
#pragma once
#include "SFML/Graphics.hpp"
#include "utility.hpp"
class RayCasting {
	
	
	
private:
	std::map<float,float> _cosTable;
	std::map<float,float> _sinTable;
	const double _PI ; //utilisé pour calcule dans creatTable() et passage en radian
	
public:
	enum class Algo{
		LINEAR,
		DDA
	};
	
public:
	RayCasting();
	float rayCasting(const sf::Vector2f& position,float angle, const std::vector<std::vector<int>>& labyrinth,int &blockID, const Algo algo)const;	//retourn la distance jusque au mur rencontré
private:
	sf::Vector2f computeLineCoo(const sf::Vector2f& position,float angle, const std::vector<std::vector<int>>& labyrinth) const;
	
	sf::Vector2f computeColumnCoo(const sf::Vector2f& position,float angle, const std::vector<std::vector<int>>& labyrinth) const;
	
};
