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

void printHelp() {
	std::cout << "Available commands:\n"
		<< "- move with -> north, south, east, or west\n"
		<< "- help       : Show this help message\n"
		<< "- quit       : Exit the game\n";
}

int main(int argc, char *argv[]) {
	std::string worldFile = "world-load.txt"; // Default file

	if (argc > 1) {
			worldFile = argv[1]; // Use argument if provided
	}
	World w;
	Direction dir;
	w = parseWorld(worldFile);

	std::string input;
	Room* room = &w.rooms[1];
	w.current_room = 1;

	std::cout << "Welcome to your text adventure!\n" << 
		"Press ENTER to continue" << std::endl;

	std::getline(std::cin, input);

	printHelp();

	while (true) {
		std::cout << "\nYou are in " << room->name << "\n";
		std::cout << room->description << "\n";
		std::cout << "Exits:\n";
		for (const auto& [dir, id] : room->exits) {
			for (const auto& [str, enum_dir] : mapping) {
				if (enum_dir == dir) {
					std::cout << str << "\t(" << w.rooms.at(id).name << ")\n";
					break;
				}
			}
		}
		std::cout << "\n> ";
		std::getline(std::cin, input);
		input = toUpper(input);

		if (input == "QUIT" || input == "EXIT") {
			break;
		}

		if (input == "HELP") {
			printHelp();
			continue;
		}

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
