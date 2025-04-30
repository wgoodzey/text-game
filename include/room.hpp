#pragma once

#include <string>
#include <stdexcept>
#include <unordered_map>

enum class Direction {
	NORTH,
	SOUTH,
	EAST,
	WEST,
	UP,
	DOWN,
};

static const std::unordered_map<std::string, Direction> mapping = {
	{ "NORTH", Direction::NORTH },
	{ "SOUTH", Direction::SOUTH },
	{ "EAST",  Direction::EAST  },
	{ "WEST",  Direction::WEST  },
	{ "UP",    Direction::UP    },
	{ "DOWN",  Direction::DOWN  },
};

inline Direction stringToDirection(const std::string &str) {
	auto it = mapping.find(str);
	if (it != mapping.end()) {
		return it->second;
	} else {
		throw std::invalid_argument("Invalid direction: " + str);
	}
}

typedef struct room {
	int room_id;
	std::string name;
	std::string description;
	std::unordered_map<Direction, int> exits;
} Room;
