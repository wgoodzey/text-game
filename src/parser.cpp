#include "parser.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

bool startsWith(const std::string& str, const std::string& prefix) {
    return str.size() >= prefix.size() 
			&& str.compare(0, prefix.size(), prefix) == 0;
}

World parseWorld(const std::string& filename) {
	World w;
	std::ifstream file(filename);
	std::string line;

	Room currentRoom;
	int currentRoomId = -1;

	while (std::getline(file, line)) {
		if (line.empty()) continue;

		if (startsWith(line, "ROOM ")) {
			if (currentRoomId != -1) {
				w.rooms[currentRoomId] = currentRoom; // Save previous room
			}
			currentRoom = Room();
			currentRoomId = std::stoi(line.substr(5));
		}
		else if (startsWith(line, "name: ")) {
			currentRoom.name = line.substr(6);
		}
		else if (startsWith(line, "description: ")) {
			currentRoom.description = line.substr(13);
		}
		
		else if (startsWith(line, "exits: ")) {
			std::string exitsStr = line.substr(7);
			std::istringstream ss(exitsStr);
			std::string dirStr;
			int exitId;

			while (ss >> dirStr >> exitId) {
				try {
					Direction dir = stringToDirection(dirStr);
					currentRoom.exits.insert({dir, exitId});
				} catch (const std::invalid_argument& e) {
					std::cerr << "Error: " << e.what() << std::endl;
				}
			}
		}

	}

	// Save last room after EOF
	if (currentRoomId != -1) {
			w.rooms[currentRoomId] = currentRoom;
	}

	return w;
}
