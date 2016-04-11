//
//  utility.cpp
//  
//
//
//

#include "utility.hpp"
#include <fstream>
#include <iostream>

//#############			the labs		#############

const int g_preMakeLabSize{11};

int sizeOfBlock{64};
int xMax = g_preMakeLabSize * sizeOfBlock;
int yMax = g_preMakeLabSize * sizeOfBlock;

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




enum class g_TypeOfBlock{
	WALL,
	AIR
	
};

void loadFromFile(std::vector<std::vector<int>>& labyrinth){
		std::ifstream labFile{};
		labFile.open("labyrinth.txt");
		std::string line{};
		int count{0};
		if(labFile.is_open()){
			
			while (std::getline(labFile,line)) {
				labyrinth.push_back(std::vector<int>());	//nouvelle ligne 2d
				
				for (int i{0}; i<line.size(); i+=2) {	//saute le caractère ',' et va au prochain nombre
					
					if(line.at(i)== '1')					//utilise  '1' car .at() retourn un char et ne peux pas etre comparé avec int
					{
						labyrinth.at(count).push_back(1);						//collonne
					}
					else if(line.at(i) == '0'){
						labyrinth.at(count).push_back(0);
					}
					else{}
					
				}
				++count;
			}
			
		}
	
	
	show(labyrinth);
	
	labFile.close();
	
}
void show(std::vector<std::vector<int>>& labyrinth){
	
	for(auto& i:labyrinth){
		for(auto&j :i){
			std::cout <<j<<" ";
		}
		std::cout<<std::endl;
	}
}

void fromIntToEnum(std::vector<std::vector<int>> &tabBinary, std::vector<std::vector<g_TypeOfBlock>> &tabEnum){
	std::cout <<tabBinary.size()<<std::endl<<"\n\n";
	for(int i{0};i<tabBinary.size();++i){								//i = std::vector<int>
		
		
		tabEnum.push_back( std::vector<g_TypeOfBlock>() );	//new line
		
		for(int j{0}; j< tabBinary.at(i).size(); ++j){
			if(j == 1){
				tabEnum.at(i).push_back(g_TypeOfBlock::WALL);
				
			}
			
			else if (j == 0){
				tabEnum.at(i).push_back(g_TypeOfBlock::AIR);
				if(tabEnum.at(i).at(j) == g_TypeOfBlock::AIR)
					std::cout <<j;

			}
			else std::cout <<"  ";
		}
		std::cout <<std::endl;
	}
	
}

//IMPLEMENT LE LOAD FROM FILE AVEC LE GETLINE






































