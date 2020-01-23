# Milestone-2
Advanced Programming 1, Computer Science Major at Bar-Ilan University

[Link to project's github repository](https://github.com/niliya96/MIlestone-2)

This project provides a structure for solving problems and managing their solutions with a LRU cache manager. Particularly, the following problem sovlers were implemented:
1. StringReverser - Reverse any string
2. Searchers - graph searching algorithms (Best First Search, A*, BFS, DFS)

## Key Features

* Server-client connection
* Multi-Threading (and Mutex)
* Usage of C++ STL, I/O
* Usage of OOP Design Patterns: Bridge, Object Adapter...

### Prerequisites

What things you need to install the software and how to install them

```
Flightgear - Download it from Ubuntu Software application. 
```
Make sure to copy generic_small.xml to protocol folder, under the installation folder.
 
## Running the tests

###Finding a path in KxN Graphs:
```
//This is a 3x4 graph
1,6,2,3
7,-1,1,6
3,7,8,1
2,6,7,5
0,0
3,3
end
```
This means the program will find a path from (0,0) to (3,3) vertices in this spesific graph.
``` -1 ``` means that this vertix isn't connected to any other vertix.

The default searching algorithm (and our favorite) is Best First Search which returns the shortest path between two vertices. That said, switching to another searching algorithm can be easily changed in ```Server.h```

###Reverse a string
First you need to switch the alternative code which is in ```Server.h```, then run the program, connect to localhost server, and type any string you'd like to reverse. The program can get multiple strings till the user hits ```end```.


## Built With

* [Clion](https://www.jetbrains.com/clion/) - Our favorite IDE

## Authors

* **Nili Alfia* - [niliya96](https://github.com/niliya96)

* **Idan Yarchi* - [idany95](https://github.com/Idany95)

## Acknowledgments

* We'd like to thank our families and friends again(*) for supporting us during the making of this project.
*(we already thanked them once after Milestone 1)
