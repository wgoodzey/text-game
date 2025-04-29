#include "world.hpp"
#include "parser.hpp"
#include <iostream>

int main (int argc, char *argv[]) {
	World w;
	w = parse_world("./world-load.txt");

	for (auto i : w.rooms) {
		std::cout << i.first << ":" << i.second.name << std::endl;
	}

	return 0;
}
