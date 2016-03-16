#include <iostream>
#include <vector> 
#include <fstream> 
using namespace std;

//from file to matrix
vector< vector<int> > read_file (string filename)
{
	char position;
	int value = 0;
	ifstream in(filename);
	vector< vector<int> > matrix; 
	vector<int> row;

	while (in.get(position))
	{
		if (position == '\n') 
		{
			row.push_back(value); 
			matrix.push_back(row); 
			value = 0; 
			row.clear(); 
		}
		else 
		{
			if (position == ' ') 
			{
				row.push_back(value); 
				value = 0; 
			}
			else 
			{
				value = value * 10 + (int(position) - 48); 
			}
		}
	}
	in.close(); 

	if (position != '\n')
	{
		row.push_back(value); 
		matrix.push_back(row);
	}

	return matrix;
}

void print(vector< vector<int> > matrix)
{
	for (int i = 0; i < matrix.size(); i++) 
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}


bool check_square(vector< vector<int> > matrix)
{
	return matrix.size() == matrix[0].size();
}

bool check_magic_square(vector< vector<int> > matrix)
{
	//creating "needed" sum
	int sum = 0; 
	for (int i = 0; i < matrix.size(); i++)
	{
		sum += matrix[0][i];
	}

	//checking
	int up_diag = 0;
	int down_diag = 0;
	for (int i = 0; i < matrix.size(); i++)
	{
		int sum_row = 0;
		int sum_col = 0;
		for (int j = 0; j < matrix.size(); j++)
		{
			sum_row += matrix[i][j];
			sum_col += matrix[j][i];

			if (i == j)
			{
				down_diag += matrix[i][j];
			}

			if (i == matrix.size() - j - 1)
			{
				up_diag += matrix[i][j];
			}
		}

		if (sum_row != sum) return false;
		if (sum_col != sum) return false;
	}

	if (down_diag != sum) return false;
	if (up_diag != sum) return false;

	return true;
}

int main()
{
	vector< vector<int> > matrix = read_file("input.txt");
	print(matrix);

	bool its_square = check_square(matrix);

	if (its_square)
	{
		cout << "Lucky one, it's square" << endl;
		bool its_magic_square = check_magic_square(matrix);

		if (its_magic_square)
		{
			cout << "Congratulations! you have a magic square" << endl;
		}
		else
		{
			cout << "Loooooooser! it's just a square" << endl;
		}
	}
	else
	{
		cout << "it's not a square" << endl;
	}
	return 0;
}

