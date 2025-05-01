#include "world.hpp"
#include "parser.hpp"
#include <iostream>
#include <algorithm>
#include <cctype>

std::string toUpper(const std::string &str) {
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(),
			[](unsigned char c) { return std::toupper(c); });
	return result;
}

int main(int argc, char *argv[]) {
	World w;
	Direction dir;
	w = parseWorld("./world-load.txt");

	std::string input;
	Room* room = &w.rooms[1];
	w.current_room = 1;

	while (true) {
		std::cout << "\nYou are in " << room->name << "\n";
		std::cout << room->description << "\n";
		std::cout << "Exits: ";
		for (const auto& [dir, id] : room->exits) {
			for (const auto& [str, enum_dir] : mapping) {
				if (enum_dir == dir) {
					std::cout << str << " ";
					break;
				}
			}
		}
		std::cout << "\n> ";
		std::getline(std::cin, input);
		input = toUpper(input);

		try {
			dir = stringToDirection(input);
			if (room->exits.find(dir) != room->exits.end()) {
				w.current_room = room->exits[dir];
				room = &w.rooms[w.current_room];
			} else {
				std::cout << "You can't go that way.\n";
			}
		} catch (const std::exception &e) {
			std::cout << e.what() << "\n";
		}
	}

	return 0;
}
