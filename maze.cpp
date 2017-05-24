#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
using namespace std;

void show_maze(vector<vector<int>> vec)
{
	for (int m = 0;m < vec.size();m++)
	{
		for (int n = 0;n < vec[0].size();n++)
			cout << vec[m][n] << " ";
		cout << endl;
	}
}

void show_last_maze(vector<vector<pair<int, int>>> path_group, vector<vector<int>> vec)
{
	if (path_group.size() == 0)
	{
		cout << "no right path!"<<endl;
		return;
	}
	int min_length= path_group[0].size();
	for (int i = 0;i < path_group.size();i++)
		if (path_group[i].size() < min_length)
			min_length = path_group[i].size();

	for (int i = 0;i < path_group.size();i++)
		if (path_group[i].size() == min_length)
		{
			vector<vector<int>> vec1 = vec;
			for (int t = 0;t < min_length;t++)
			{
				int rrow = path_group[i][t].first;
				int ccol = path_group[i][t].second;
				vec1[rrow][ccol] = 2;
			}
			show_maze(vec1);
			cout << endl;
		}
}


void check_way(int row,int col,vector<vector<int>> maze, vector<pair<int, int>> path, vector<vector<pair<int, int>>> &path_group)
{
	if (row < 0 || col < 0 || row >= maze.size() || col >= maze[0].size())
		return;
	if (maze[row][col] == 1 || maze[row][col] == 2)
		return;
	if (maze[row][col] == 6)
	{
		path.push_back(make_pair(row, col));
		path_group.push_back(path);
		return;
	}
	maze[row][col] = 2;
	path.push_back(make_pair(row, col));
	check_way(row - 1, col, maze, path, path_group);
	check_way(row, col + 1, maze, path, path_group);
	check_way(row + 1, col, maze, path, path_group);
	check_way(row, col - 1, maze, path, path_group);

}

void maze(string file)
{
	ifstream in(file);
	stringstream ss;
	string line;
	int row, column;

	vector<pair<int, int>> path;
	vector<vector<pair<int, int>>> path_group;

	getline(in, line);
	ss << line;
	ss >> row >> column;
	vector<vector<int>> maz(row, vector<int>(column));
	for(int m=0;m<row;m++)
	{
		int tmp=0;
		getline(in, line);
		ss.clear();
		ss << line;
		for (int n = 0;n < column;n++)
		{
			ss >> tmp;
			maz[m][n] = tmp;
		}
		ss.clear();
	}
	cout << row << " " << column << endl;
	show_maze(maz);

	maz[row - 1][column - 1] = 6;
	check_way(0, 0, maz, path, path_group);
	cout<<endl;

	show_last_maze(path_group, maz);
}


int main()
{
	maze("mg4.txt");
	system("pause");
	return 0;
}
