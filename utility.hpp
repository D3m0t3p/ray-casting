//
//  utility.h
//  Ray-Casting
//
//

#pragma once
#include <vector>
#include <array>


enum class g_TypeOfBlock;
void fromIntToEnum(std::vector<std::vector<int>> &tabBinary, std::vector<std::vector<g_TypeOfBlock>> &tabEnum);
void loadFromFile(std::vector<std::vector<int>>& labyrinth);
void show(std::vector<std::vector<int>>& labyrinth);








