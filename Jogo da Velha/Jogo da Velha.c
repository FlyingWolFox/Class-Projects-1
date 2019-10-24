#include <stdio.h>
#include <stdlib.h>

int winVerifyer(int grid[3][3])
{
	if (grid[0][0] == 1)
	{
		if (grid[0][1] == 1 && grid[0][2] == 1)
			return 1;
		if (grid[1][0] == 1 && grid[2][0] == 1)
			return 1;
		if (grid[1][1] == 1 && grid[2][2] == 1)
			return 1;
	}
	if (grid[0][1] == 1)
	{
		if (grid[1][1] == 1 && grid[2][1] == 1)
			return 1;
	}
	if (grid[0][2] == 1)
	{
		if (grid[1][2] == 1 && grid[2][2] == 1)
			return 1;
		if (grid[1][1] == 1 && grid[2][0] == 1)
			return 1;
	}
	if (grid[1][0] == 1 && grid[1][1] == 1 && grid[1][2] == 1)
		return 1;
	if (grid[2][0] == 1 && grid[2][1] == 1 && grid[2][2] == 1)
		return 1;
}

void gridPrinter(int grid[3][3])
{

}

int main(int argc, char* argv[])
{
	int grid[3][3];
	int play;
	int player;


}