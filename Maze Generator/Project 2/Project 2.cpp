// Project 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Maze.h"
#include <ctime>

using namespace std;

int main()
{
	srand(time(NULL));
	//build the maze
	//print the maze
	Maze maze1(25,50);
	maze1.displayMaze();
	
	
}

