#pragma once

#include <vector>

struct History {
	std::vector<std::vector<int>> maze;
	std::pair<int, int> heroPos;
	int level;
	int heroLife;
	std::vector<std::pair<int, int>> monsterPos;
	int monsterSpeed;
	std::vector<std::pair<int, int>> dragonPos;
	int dragonSpeed;
	std::vector<std::pair<int, int>> collectionPos;
	std::vector<std::pair<int, int>> potionPos;
	std::vector<std::pair<int, int>> superPotionPos;
	std::vector<std::pair<int, int>> trapPos;
};