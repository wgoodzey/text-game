#include "world.hpp"
#include <iostream>

void listAllRooms(World w) {
	for (auto i : w.rooms) {
		std::cout << i.first << ":" << i.second.name << std::endl;
		for (auto j : i.second.exits) {
			std::cout << static_cast<int>(j.first) << ":" << j.second << std::endl;
		}
	}
}
