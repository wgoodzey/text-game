#include <string>
#include <vector>
typedef struct room {
	int room_id;
	std::string name;
	std::string description;
	std::vector<std::string> exits;
} Room;
