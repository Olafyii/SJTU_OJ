#include <iostream>
#include <vector>

using namespace std;

int get_string_length(char *s)
{
    int len = 0;
    while (s[len] != '\0')
        ++len;
    return len;
}

int main()
{
    char s[101];
    while(cin.getline(s, 101))
    {
        int len = get_string_length(s);
        vector< pair<int, int> > line;

        line.push_back(pair<char, int>(s[0], 0));
        for (int i = 1; i < len; ++i)
        {
            if (s[i] != '(' && s[i] != ')')
                continue;
            if (s[i] == ')' && line.back().first == '(')
                line.pop_back();
            else
                line.push_back(pair<char, int>(s[i], i));
        }

        cout << s << endl;
        int current = 0, tmp;
        for (int i = 0; i < line.size(); ++i)
        {
            tmp = line[i].second - current;
            current = line[i].second + 1;
            for (int j = 0; j < tmp; ++j)
                cout << ' ';
            if (line[i].first == '(')
                cout << '$';
            if (line[i].first == ')')
                cout << '?';
        }
    }
}
