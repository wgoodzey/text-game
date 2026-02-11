# Text Adventure Game

This is a C++ project that is designed to load a world from a TXT file, parsing
room data such as title, description, as well as adjacent rooms. The world
files follow the following format:

```txt
ROOM 1
NAME Front Yard
DESC A grassy yard with a sturdy tree in the center. A wooden treehouse peeks out from the branches.
EXIT NORTH 2 UP 4
```

All fields are single lines (**DO NOT USE NEW LINES**). Fields include `ROOM`
number (room id) `NAME`, `DESC`, and `EXIT`. For exits have the direction in
all capital letters followed by the target room ID number. To have multiple
exits for a room, separate with spaces.


## Usage

### Build the project
```bash
make build
```

### Rebuild the project
```bash
make rebuild
```

### Clean artifacts
```bash
make clean
```

## Output Binaries

```bash
build/text-game
```

if you would like to load a specific game file:

```bash
build/text-game ./target-world-file.txt # ex: ./spongebob-world.txt
```

## Requirements

- `gcc`, `g++`
- `make`
- `cmake`
