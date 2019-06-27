#pragma once

struct Coord
{
	int row;
	int col;
};
class Maze
{
public:
	Maze(int rows = 5, int cols = 5);
	~Maze();
	void display();
	void displayMaze();
private:
	int rowSize;
	int colSize;
	char** mazeArray;
	void fillArray(int num);
	void generateMaze();
	int findLegalDirections(Coord c1, int arr[]);
	bool isDirectionValid(Coord c1 , int dir);
	Coord findNextCoordinate(Coord c1, int dir);
	void breakWall(Coord c1, int dir);
	void removeWall(Coord currCoord, int dir);
};


