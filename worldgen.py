#!/usr/bin/env python3
"""
 Chatgpt generated script to generate really large world files

 an N x N grid world for a text adventure loader.

Format per room (all single-line fields):
ROOM <id>
NAME <single-line name>
DESC <single-line description>
EXIT <DIR1> <TARGET1> <DIR2> <TARGET2> ...

Exits include grid neighbors (NORTH/SOUTH/EAST/WEST).
Optionally, you can add periodic vertical links (UP/DOWN) to increase branching.
"""

import argparse
import random
from pathlib import Path

def room_id(x: int, y: int, W: int) -> int:
    # x in [0, W-1], y in [0, H-1]; return 1-based ID
    return y * W + x + 1

def generate_world(n: int,
                   out_path: Path,
                   seed: int = 42,
                   vertical_every: int | None = None,
                   vertical_distance: int = 0,
                   name_prefix: str = "Room",
                   desc_phrase: str = "A procedurally generated chamber") -> None:
    """
    Write an n x n world to `out_path`.

    vertical_every: if set to k>0, every k-th room (by 1-based ID) gets an UP to +vertical_distance (if in range).
                    The target room later gets a DOWN back automatically.
    vertical_distance: the offset used for UP/DOWN links; 0 disables vertical links even if vertical_every is set.
    """
    W = H = n
    total = W * H
    rng = random.Random(seed)

    with out_path.open("w", encoding="utf-8") as f:
        for y in range(H):
            for x in range(W):
                rid = room_id(x, y, W)

                # ROOM header
                f.write(f"ROOM {rid}\n")

                # NAME (single-line)
                f.write(f"NAME {name_prefix} R{y+1}C{x+1}\n")

                # DESC (single-line; keep compact and deterministic)
                # You can sprinkle a tiny bit of variety without newlines:
                flavor = rng.choice(["humming", "buzzing", "quiet", "echoing", "sterile"])
                f.write(f"DESC {desc_phrase} at row {y+1}, column {x+1}, {flavor} with test energy.\n")

                # Build exits
                exits: list[str] = []

                # Cardinal neighbors
                if y > 0:            # north neighbor
                    exits += ["NORTH", str(room_id(x, y-1, W))]
                if y < H - 1:        # south neighbor
                    exits += ["SOUTH", str(room_id(x, y+1, W))]
                if x > 0:            # west neighbor
                    exits += ["WEST",  str(room_id(x-1, y, W))]
                if x < W - 1:        # east neighbor
                    exits += ["EAST",  str(room_id(x+1, y, W))]

                # Optional vertical links
                if vertical_every and vertical_every > 0 and vertical_distance > 0:
                    # Add UP link from every k-th room to rid + vertical_distance (if within bounds)
                    if rid % vertical_every == 0 and rid + vertical_distance <= total:
                        exits += ["UP", str(rid + vertical_distance)]
                    # Add DOWN link back when we reach the target room
                    if rid - vertical_distance >= 1 and (rid - vertical_distance) % vertical_every == 0:
                        exits += ["DOWN", str(rid - vertical_distance)]

                if exits:
                    f.write("EXIT " + " ".join(exits) + "\n")
                else:
                    f.write("EXIT\n")

                f.write("\n")  # blank line between rooms

def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description="Generate an N x N world file.")
    p.add_argument("n", type=int, help="Grid size N (creates N x N rooms).")
    p.add_argument("-o", "--outfile", type=Path,
                   help="Output path (default: world-NxN.txt in current dir).")
    p.add_argument("--seed", type=int, default=42, help="PRNG seed for minor flavor variety.")
    p.add_argument("--vertical-every", type=int, default=0,
                   help="Every k-th room gets an UP link (0 disables).")
    p.add_argument("--vertical-distance", type=int, default=0,
                   help="Room ID offset for UP/DOWN links (0 disables).")
    p.add_argument("--name-prefix", type=str, default="Room", help="Prefix used for NAME fields.")
    p.add_argument("--desc-phrase", type=str, default="A procedurally generated chamber",
                   help="Base description text (single line).")
    return p.parse_args()

def main():
    args = parse_args()
    if args.n <= 0:
        raise SystemExit("N must be a positive integer.")
    if args.vertical_every < 0 or args.vertical_distance < 0:
        raise SystemExit("--vertical-every and --vertical-distance must be >= 0")

    outfile = args.outfile or Path(f"world-{args.n}x{args.n}.txt")
    generate_world(
        n=args.n,
        out_path=outfile,
        seed=args.seed,
        vertical_every=(args.vertical_every or None),
        vertical_distance=args.vertical_distance,
        name_prefix=args.name_prefix,
        desc_phrase=args.desc_phrase,
    )
    print(f"Wrote {args.n}x{args.n} world to {outfile}")

if __name__ == "__main__":
    main()

