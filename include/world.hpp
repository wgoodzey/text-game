#pragma once

#include "room.hpp"
#include <unordered_map>

typedef struct world {
	int current_room;
	std::unordered_map<int, Room> rooms;
} World;

void listAllRooms(World w);
