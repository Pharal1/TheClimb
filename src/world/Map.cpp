// Map.cpp

#include "Map.h"

Map::Map(MapData mapData) : mapData_(mapData) {
	const auto& map = mapData.map_;
	int maxXN;
	maxY_ = map.size();

	for (int i = 0; i < maxY_; i++) {
		map_.push_back(std::vector<TileType>{});
	}

	for (int y = 0; y < map.size(); y++) {
		maxXN = 0;
		for (int x = 0; x < map[y].size(); x++) {
			maxXN += 1;
			switch (map[y][x]) {
			case '0':
				map_[y].push_back(TileType::eFloor);
				break;
			case '1':
			case '2':
				map_[y].push_back(TileType::eWall);
				break;
			}
		}
		if (maxXN > maxX_) maxX_ = maxXN;
	}
}

void Map::Render() {
	const int tileSize = mapData_.cellSize_;
	const auto& map = mapData_.map_;
	const Color linesColor = WHITE;
	Color color = WHITE;
	
	//render tiles
	
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			color = tileSet[map[y][x]].color;

			DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, color);
		}
	}

	//render lines

	for (int x = 0; x < maxX_; x++) {
		DrawLine(x * tileSize, 0, x * tileSize, maxY_ * tileSize, linesColor);
	}
	for (int y = 0; y < maxY_; y++) {
		DrawLine(0, y * tileSize, maxX_ * tileSize, y * tileSize, linesColor);
	}
}

bool Map::isFree(int x, int y) {
	if (x >= maxX_ || x < 0 || y >= maxY_ || y < 0) {
		std::cout << "Map::isFree() out of range" << std::endl;
		return false;
	}
	if (isCellFree(map_[y][x])) return true;
	return false;
}

bool isCellFree(TileType tileType) {
	if (tileType == TileType::eFloor) return true;
	return false;
}

MapData::MapData(std::vector<std::string> map, int cellSize) : map_(map), cellSize_(cellSize) {}