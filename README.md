# oop_assign7
=======

## Description

In this stealth-based grid game, your objective is to reach the blue goal area located at the top of the map without being detected by any enemies.

Enemies actively patrol the area and can spot you within their line of sight. To make the challenge even greater, they periodically fire recon projectiles—scanning bursts that temporarily reveal hidden zones. If you're caught in an enemy’s vision or scanned by a recon, the game ends.

Stay out of sight, time your movements carefully, and make strategic use of the terrain to reach the target zone undetected.

Objective: Reach the blue area at the top of the screen.
Challenge: Avoid enemy detection and recon scans.
Victory Condition: Enter the blue zone without being spotted.
Failure Condition: Being seen by any enemy or caught in a recon scan.

### Controls

Use the W, A, S, and D keys to move your character:

W – Move up

A – Move left

S – Move down

D – Move right

Plan your moves carefully—every step could bring you closer to safety… or right into danger.

## Compile and Run
Before compiling the program, in **Project Folder**:
```console
mkdir build
```
```console
cd build
```

Then in `build/`:
```console
cmake ..
```

To compile the program, in `build/`:
```console
make
```

To run the program, in `build/`:
```console
./exec
```

## UML Class Diagram
![UML Diagram](docs/diagram.png)
