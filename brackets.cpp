#include <iostream>
#include <stack>
#include <string>
#include <stdio.h>
using namespace std;

bool correctBrackets(string& input)
{
	stack<char> st;
	int n = input.length();

	for (int i = 0; i < n; i++)
	{
		if (input[i] == '(')
			st.push(input[i]);

		if (input[i] == ')' && !st.empty())
			st.pop();
		else if (input[i] == ')' && st.empty())
			return false;
	}

	if (st.empty())
		return true;
}

int main()
{ 

	return 0;
}
