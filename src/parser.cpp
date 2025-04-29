#include "parser.hpp"
#include <fstream>
#include <sstream>

bool starts_with(const std::string& str, const std::string& prefix) {
    return str.size() >= prefix.size() 
			&& str.compare(0, prefix.size(), prefix) == 0;
}

World parse_world(const std::string& filename) {
	World w;
	std::ifstream file(filename);
	std::string line;

	Room currentRoom;
	int currentRoomId = -1;

	while (std::getline(file, line)) {
		if (line.empty()) continue;

		if (starts_with(line, "ROOM ")) {
			if (currentRoomId != -1) {
				w.rooms[currentRoomId] = currentRoom; // Save previous room
			}
			currentRoom = Room();
			currentRoomId = std::stoi(line.substr(5));
		}
		else if (starts_with(line, "name: ")) {
			currentRoom.name = line.substr(6);
		}
		else if (starts_with(line, "description: ")) {
			currentRoom.description = line.substr(13);
		}
		else if (starts_with(line, "exits: ")) {
			std::string exitsStr = line.substr(7);
			std::istringstream ss(exitsStr);
			int exitId;
			while (ss >> exitId) {
				currentRoom.exits.push_back(exitId);
			}
		}
	}

	// Save last room after EOF
	if (currentRoomId != -1) {
			w.rooms[currentRoomId] = currentRoom;
	}

	return w;
}
