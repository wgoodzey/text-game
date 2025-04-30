#include "world.hpp"
#include "parser.hpp"
#include <iostream>

int main (int argc, char *argv[]) {
	World w;
	w = parseWorld("./world-load.txt");

	listAllRooms(w);

	return 0;
}
