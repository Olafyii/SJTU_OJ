#include <iostream>
#include <string>
using namespace std;

int main()
{
	int N;
	string s, stack;
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
	{
		cin >> s;
		stack.append(1, s[0]);
		for (int j = 1; j < s.size(); ++j)
		{
			if (s[j] == ')' && stack.back() == '(')
				stack.pop_back();
			else
				stack.append(1, s[j]);
		}
		if (stack.empty())
			printf("YES\n");
		else
			printf("NO\n");
		stack = "";
	}
}