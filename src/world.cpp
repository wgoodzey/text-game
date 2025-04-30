#include "world.hpp"
#include <iostream>

void listAllRooms(World w) {
	for (auto i : w.rooms) {
		std::cout << i.first << ":" << i.second.name << std::endl;
		for (auto j : i.second.exits) {
			std::cout << "dir:" << static_cast<int>(j.first) << 
				", room_id:" << j.second << 
				", room:" << w.rooms[j.second].name << std::endl;
		}
		std::cout << "\n";
	}
}
