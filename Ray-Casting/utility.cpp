//
//  utility.cpp
//  
//
//
//

#include "utility.hpp"
#include "ResourcePath.hpp"
#include <fstream>
#include <iostream>

//#############			the labs		#############


int sizeOfBlock{64};
//std::array< std::array<int, g_preMakeLabSize>, g_preMakeLabSize> preMakeLab {
//	
//	{
//		{1,1,1,1,1,1,1,1,1,1},
//		{1,0,0,0,0,0,0,0,0,1},
//		{1,0,0,0,0,0,0,0,0,1},
//		{1,0,0,0,0,0,0,0,0,1},
//		{1,0,0,0,1,0,0,0,0,1},
//		{1,0,0,0,0,1,0,0,0,1},
//		{1,0,0,0,0,0,0,0,0,1},
//		{1,0,0,0,0,0,0,0,0,1},
//		{1,0,0,0,0,0,0,0,0,1},
//		{1,1,1,1,1,1,1,1,1,1}
//	}
//};






bool loadFromFile(std::vector<std::vector<int>>& labyrinth,const unsigned int labNum){
	
	/*
	 
	 format :
	 
	 1,1,1,1,1,1,1,1
	 1,0,0,0,0,0,0,1
	 1,0,0,0,0,0,0,1
	 1,0,0,0,0,0,0,1
	 1,0,0,0,0,0,0,1
	 1,0,0,0,0,0,0,1
	 1,1,1,1,1,1,1,1
	 
	 1 = wall
	 
	 */
	std::string extension{".txt"};
	std::ifstream labFile{};
	
	labFile.open(resourcePath() + "lab" + std::to_string(labNum) + extension);
		std::string line{};
		size_t count{0};
	
	
		if(labFile.is_open()){
			
			while (std::getline(labFile,line)) {
				labyrinth.push_back(std::vector<int>());	//nouvelle ligne 2d
				
				for (size_t i{0}; i<line.size(); i+=2) {	//saute le caractère ',' et va au prochain nombre
					
					if(line.at(i)== '1')					//utilise  '1' car .at() retourn un char et ne peux pas etre comparé avec int
					{
						labyrinth.at(count).push_back(1);						//collonne
					}
					else if(line.at(i) == '0'){
						labyrinth.at(count).push_back(0);
					}
					else if(line.at(i) == '2'){
						labyrinth.at(count).push_back(2);
					}
					
				}
				++count;
			}
			return true;
		}
	
		else{
			return false;
		}
	
	
	
	
}


void show(const std::vector<std::vector<int>>& labyrinth){
	
	for(auto& i:labyrinth){
		for(auto&j :i){
			std::cout <<j<<" ";
		}
		std::cout<<std::endl;
	}
}


