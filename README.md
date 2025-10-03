# Dungeon Raider

A simple roguelike dungeon crawler built in C using ncurses.  
The project demonstrates struct-based design, dynamic memory allocation, and terminal graphics.

---

## Features

-
-
- ***

## Installation & Build

Clone the repository:

```bash
git clone https://github.com/<your-username>/dungeon-crawler.git
cd dungeon-crawler
```

Compile with:

```bash
make
```

or (manual build):

```bash
gcc -Wall -lncurses main.c -o dungeon
```

Run the game:

```bash
./dungeon
```

---

## Controls

- W – Move Up
- A – Move Left
- S – Move Down
- D – Move Right
- Q – Quit Game

---

## Project Structure

```
dungeon-crawler/
│── src/
│   ├── main.c        # Game entry + loop
│   ├── player.c      # Player logic
│   ├── map.c         # Room/dungeon setup
│   ├── game.c        # Input handling, updates
│── include/
│   ├── dungeon.h     # Structs + function declarations
│── Makefile
│── README.md
```

---

## Roadmap

-
-
- ***

## Demo

(Add screenshots or GIF here)

---

## Contributing

Contributions are welcome.  
Open an issue or submit a pull request with improvements, bug fixes, or new features.

---

## License

MIT License – feel free to use, modify, and share.
