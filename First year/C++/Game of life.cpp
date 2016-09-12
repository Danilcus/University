#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <stdlib.h>
#include <math.h>

using namespace std;
const short rows = 20;
const short cols = 40;
vector<short> graph;
const short max_generation = 500;

//формирование первой генерации
void FirstGeneration(short Arr[rows][cols])
{
	srand(time(NULL));
	for (short i = 0; i < rows; i++)
		for (short j = 0; j < cols; j++)
			Arr[i][j] = rand() % 2;
}

void print(short Arr[rows][cols])
{
	system("cls");
	for (short i = 0; i < rows; i++)
	{
		for (short j = 0; j < cols; j++)
		{
			if (Arr[i][j] == 1)
				cout << "*";
			else
				cout << " ";
		}
		cout << endl;
	}
}

short value(short row, short col, short arr[rows][cols])
{
	if (row < 0) row += rows;
	if (row == rows) row -= rows;
	if (col < 0) col += cols;
	if (col == cols) col -= cols;

	short result = arr[row][col];
	return result;
}

void nextGeneration(short Arr[rows][cols], short newArr[rows][cols])
{
	for (short i = 0; i < rows; i++)
	{
		for (short j = 0; j < cols; j++)
		{
			short sum = value(i - 1, j - 1, Arr) + value(i - 1, j, Arr) + value(i - 1, j + 1, Arr) +
				value(i, j - 1, Arr) + value(i, j + 1, Arr) +
				value(i + 1, j - 1, Arr) + value(i + 1, j, Arr) + value(i + 1, j + 1, Arr);

			if ((Arr[i][j] == 1 && (sum == 2 || sum == 3)) || (Arr[i][j] == 0 && sum == 3))  // условия нового поколения
				newArr[i][j] = 1;
			else newArr[i][j] = 0;
		}
	}
}

bool itIsUnstable(short current[rows][cols], short old[rows][cols], short tooOld[rows][cols])
{
	short count_old = 0;
	short count_too_old = 0;
	short sum = 0;

	for (short i = 0; i < rows; i++)
	{
		for (short j = 0; j < cols; j++)
		{
			if (current[i][j] == old[i][j]) count_old++;
			if (current[i][j] == tooOld[i][j]) count_too_old++;
			sum += current[i][j];
		}
	}
	cout << "curent population is " << sum << endl;
	//this_thread::sleep_for(chrono::nanoseconds(15000000));
	graph.push_back(sum);

	if (count_old == rows * cols || count_too_old == rows * cols)
	{
		cout << "Your field is stable" << endl;
		return false;
	}

	if (graph.size() > max_generation)
	{
		cout << "It's living for so long" << endl;
		return false;
	}

	return true;
}

void copy(short Arr[rows][cols], short newArr[rows][cols])
{
	for (short i = 0; i < rows; i++)
	{
		for (short j = 0; j < cols; j++)
			newArr[i][j] = Arr[i][j];
	}
}

void print_graph()
{
	system("cls");
	HDC hDC = GetDC(GetConsoleWindow());
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255)); //создал ручку
	SelectObject(hDC, Pen);
	int max_value = *max_element(begin(graph), end(graph));
	MoveToEx(hDC, 10, max_value / 2 - (graph[0] / 2), NULL); //поставил в стартовую позицию
	
	for (short i = 1; i < graph.size(); i++)
	{
		LineTo(hDC, i+10, max_value / 2 - (graph[i]/2)); //повёл из точки в точку
	}
}

short main()
{
	short field[rows][cols];
	short newField[rows][cols];
	short oldField[rows][cols];
	short veryOldField[rows][cols];

	FirstGeneration(field);
	print(field);

	while (itIsUnstable(field, oldField, veryOldField))
	{
		copy(oldField, veryOldField);
		copy(field, oldField);
		nextGeneration(field, newField);
		copy(newField, field);
		print(field);
	}
	cout << endl << "Amount of generations is " << graph.size() << endl << endl;
	cout << endl << "Would you like to see the changing of population?" << endl
		<< "Click 'y' or 'n' " << endl;

	char answer;
	cin >> answer;
	switch (answer)
	{
	case 'y':
	
		print_graph();
		break;
	default:
		break;
	}
	system("pause");
	return 0;
}