//
//  utility.h
//  Ray-Casting
//
//

#pragma once
#include <vector>
#include <array>
#include <string>


enum class g_TypeOfBlock;
void fromIntToEnum(std::vector<std::vector<int>> &tabBinary, std::vector<std::vector<g_TypeOfBlock>> &tabEnum);
void loadFromFile(std::vector<std::vector<int>>& labyrinth, std::string labName="labyrinth.txt");
void show(const std::vector<std::vector<int>>& labyrinth);








