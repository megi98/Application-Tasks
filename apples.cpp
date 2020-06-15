#include <iostream>
#include <istream>
#include <string.h>
#include <sstream>
#include <xstring>
#include <vector>
using namespace std;

struct coordinates
{
	int x;
	int y;
};

const int max_box_rows = 512;
const int max_box_columns = 512;

int main()
{
	string line1, line2;
	int days;
	cout << "Enter the size of the box: ";
	getline(cin, line1);
	cout << "Enter the coordinates of the rotten apples: ";
	getline(cin, line2);
	cout << "After how many days will you come back: ";
	cin >> days;
	const char* boxSize = line1.c_str();
	const char* input = line2.c_str();

	int r = 0;
	string N = "", M = "";

	while (boxSize[r] != 'x')
	{
		N.push_back(boxSize[r]);
		r++;
	}
	r++;
	while (boxSize[r])
	{
		M.push_back(boxSize[r]);
		r++;
	}

	const char* column = N.c_str();
	const char* row = M.c_str();

	const int boxColumns = atoi(column);                      // запазваме размерите на касетката 
	const int boxRows = atoi(row);

	if (boxRows <= 0 || boxColumns <= 0)
		cout << "Incorrect input";

	vector<coordinates> coord;                               // запазваме координатите на изгнилите ябълки във вектор coord    
	coordinates point;
	int l = strlen(input);
	string a = "", b = "";

	for (int i = 0; i < l; i++)
	{
		if (input[i] == '(')
		{
			i++;
			while (input[i] != ',')
			{
				a.push_back(input[i]);
				i++;
			}
			i++;
			while (input[i] != ')')
			{
				b.push_back(input[i]);
				i++;
			}

			point.x = stoi(a);
			point.y = stoi(b);
			coord.push_back(point);
		}

		a = "";
		b = "";
	}

	char box[max_box_columns][max_box_rows];

	for (int i = 0; i < boxRows; i++)
		for (int j = 0; j < boxColumns; j++)
			box[i][j] = 'O';

	int div = days / 3;

	for (vector<coordinates>::iterator it = coord.begin(); it != coord.end(); it++)
	{
		int X = it->x - 1;
		int Y = it->y - 1;
		box[Y][X] = 'X';

		if (div >= 1)
		{
			for (int p = Y - div; p <= Y + div; p++)
				for (int k = X - div; k <= X + div; k++)
				{
					if(box[p][k] && box[p][k] == 'O')
					box[p][k] = 'X';
				}
		}
			
	}


	for (int i = 0; i < boxRows; i++)
	{
		for (int j = 0; j < boxColumns; j++)
			cout << box[i][j];
		cout << endl;
	}

	return 0;
}