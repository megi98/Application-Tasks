#include <iostream>
#include <string.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <list>
using namespace std;

struct sensor
{
	int X;
	int Y;
	int value;
};

double distance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

int main()
{
	string file;
	int maxDist, maxError;

	cout << "Filename:";
	getline(cin, file);
	cout << "Neighbours distance:";
	cin >> maxDist;
	cout << "Max error:";
	cin >> maxError;

	sensor point;
	list<sensor> Sensors;						
	string x = "", y = "", v = "";
	char lines[32];
	
	ifstream myFile(file, ios::in);
	while (myFile.getline(lines, 32))
	{
		int i = 0;
		while (lines[i] != ',')
		{
			x.push_back(lines[i]);
			i++;
		}
		i++;
		while (lines[i] != ',')
		{
			y.push_back(lines[i]);
			i++;
		}
		i++;
		while (lines[i])
		{
			v.push_back(lines[i]);
			i++;
		}

		const char* p = x.c_str();
		const char* q = y.c_str();
		const char* w = v.c_str();

		point.X = atoi(p);
		point.Y = atoi(q);
		point.value = atoi(w);

		Sensors.push_back(point);

		x = "";
		y = "";
		v = "";
	}

	list<sensor> currentL, resultList;
	int count = 0;

	for (list<sensor>::iterator it = Sensors.begin(); it != Sensors.end(); it++)
	{
		currentL.push_back(*it);
		for (list<sensor>::iterator current = Sensors.begin(); current != Sensors.end(); current++)
		{
			if (it != current && distance(it->X, it->Y, current->X, current->Y) <= maxDist)
				currentL.push_back(*current);
		}
		
		if (currentL.size() == 2 && abs(currentL.front().value - currentL.back().value) > maxError)
				resultList.push_back(currentL.front());

		if (currentL.size() > 2)
		{
			list<sensor>::iterator it1 = currentL.begin();
			it1++;
			for (list<sensor>::iterator it2 = it1; it2 != currentL.end(); it2++)
			{
				if (abs(currentL.front().value - it2->value) > maxError)
					count++;
			}
		}
		if (count > 1)
			resultList.push_back(currentL.front());

		count = 0;
		currentL.clear();
	}

	if (!resultList.empty())
	{
		cout << "Please check sensors at: ";
		for (list<sensor>::iterator it = resultList.begin(); it != resultList.end(); it++)
		{
			if (it->X == resultList.back().X && it->Y == resultList.back().Y && it->value == resultList.back().value)
				cout << "(" << it->X << "," << it->Y << ")";
			else
				cout << "(" << it->X << "," << it->Y << "), ";
		}
	}

	else
		cout << "All sensors are OK." << endl;

	return 0;

}
