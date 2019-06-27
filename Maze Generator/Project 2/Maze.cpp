#include "Maze.h"
#include <iostream>
#include <list>


#define CELLWALLS 15

using namespace std;


Maze::Maze(int rows, int cols)
	: rowSize(rows) , colSize(cols)
{
	mazeArray = new char*[rows];
	for (int i = 0; i < rows; i++)
	{
		mazeArray[i] = new char[cols];
	}
	fillArray(CELLWALLS);
	generateMaze();
}

Maze::~Maze()
{
}

//displays 2d maze array
void Maze::display()
{
	for (int r = 0; r < rowSize; r++)
	{
		for (int c = 0; c < colSize; c++)
		{
			printf("%2d " ,(int)(mazeArray[r][c]) );
		}
		cout << endl;
	}
}

//Actual visual represntation of the maze based on the numbers in the maze array
void Maze::displayMaze()
{
	for (int i = 0; i < rowSize; i++)
	{
		//display top row of maze
		for (int j = 0; j < colSize; j++)
		{
			if (mazeArray[i][j] & 1)//check if north wall has been turned off
			{
				printf("+---");
			}
			else
			{
				printf("+   ");
			}
		}
		printf("+\n");

		//display vertical walls of maze
		for (int j = 0; j < colSize; j++)
		{
			if (mazeArray[i][j] & 8)//check if west wall has been turned off
			{
				printf("|   ");
			}
			else
			{
				printf("    ");
			}
		}
		if (mazeArray[i][colSize - 1] & 2)
			printf("|");
		cout << endl;
	}

	//display very last row of maze
	for (int j = 0; j < colSize; j++)
	{
		if (mazeArray[rowSize-1][j] & 4)//check if north wall has been turned off
		{
			printf("+---");
		}
		else
		{
			printf("+   ");
		}
	}
	printf("+\n");
}


//private function that fills 2D array with specified parameter
void Maze::fillArray(int num)
{
	for (int r = 0; r < rowSize; r++)
	{
		for (int c = 0; c < colSize; c++)
		{
			mazeArray[r][c] = num;
		}
	}
}

//private function to generate Maze
void Maze::generateMaze()
{
	list<Coord> pathList;
	Coord currCoord = { 0 , 0 };
	int directions[4];
	int validDir;
	int pathCount = 0;
	do
	{
		validDir = findLegalDirections(currCoord, directions);
		if (pathCount >= 8)
			validDir = 0;
		if (validDir > 0)
		{
			if (validDir > 1)
				pathList.push_back(currCoord);
			int index = (rand() % validDir);
			int dir = directions[index];
			breakWall(currCoord, dir);
			currCoord = findNextCoordinate(currCoord, dir);
			pathCount++;
			
		}
		else
		{
			if (pathList.empty())
				break;
			currCoord = pathList.front();
			pathList.pop_front();
			validDir = 1;
			pathCount = 0;
			continue;
		}
		//displayMaze();
		//display();
		//cout << endl;
	}
	while (validDir > 0);

}

//private function that finds which directions are valid in the maze for the path finder to go
	//directions will be as follows: 0 - North; 1 - East; 2 - South; 3 - West
int Maze::findLegalDirections(Coord c1, int arr[])
{
	int numDirs = 0;
	for (int i = 0; i <= 3; i++)
	{
		if (isDirectionValid(c1, i))
		{
			arr[numDirs++] = i;
		}
	}
	return numDirs;
}

//private function that returns whether the next coordinate (based on direction given) is valid to move to in the maze array
bool Maze::isDirectionValid(Coord c1, int dir)
{
	Coord newCoord = findNextCoordinate(c1, dir); //find next coordinate
	if (dir % 2 == 0) //check north and south validity
	{ 
		if ( (newCoord.row >= 0) && (newCoord.row < rowSize) && (mazeArray[newCoord.row][newCoord.col] == CELLWALLS) )
			return true;
		else
			return false;
	}
	else // check east and west validity
	{
		if ((newCoord.col >= 0) && (newCoord.col < colSize) && (mazeArray[newCoord.row][newCoord.col] == CELLWALLS) )
			return true;
		else
			return false;
	}

}

//private function that finds the next coordinate based on current coordinate and a direction
Coord Maze::findNextCoordinate(Coord c1, int dir)
{
	Coord newCoord;
	if (dir % 2 == 0) //find coord based on north or south
	{
		newCoord = { (c1.row + (dir - 1)) , c1.col }; //find next coordinate
		return newCoord;
	}
	else // find coord based on east or west
	{
		newCoord = { c1.row , (c1.col + (2 - dir)) }; //find next coordinate
		return newCoord;
	}
}

//breaks wall between two cells based on current cell and direction given
void Maze::breakWall(Coord currCoord, int dir)
{
	Coord newCoord = findNextCoordinate(currCoord, dir);
	removeWall(currCoord, dir);
	removeWall(newCoord, ((dir + 2) % 4));
}

//removes the wall of current cell based on direction of next cell
void Maze::removeWall(Coord currCoord, int dir)
{
	char wallMask = 1 << dir;
	char cellVal = mazeArray[currCoord.row][currCoord.col];
	cellVal &= ~wallMask;
	mazeArray[currCoord.row][currCoord.col] = cellVal;
}