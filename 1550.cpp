#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    int x, tmp, data[1000], highest = 0, sum = 0, l, r;
    scanf("%d\n", &x);
    scanf("[%d,", &tmp);
    data[0] = tmp;
    highest = tmp;
    for (int i = 1; i < x - 1; ++i)
    {
        scanf("%d,", &tmp);
        data[i] = tmp;
        if (tmp > highest)
            highest = tmp;
    }
    scanf("%d]", &tmp);
    data[x - 1] = tmp;
    if (tmp > highest)
        highest = tmp;


    for (int i = 1; i <= highest; ++i)
    {
        l = 0;
        r = x - 1;
        while (data[l] < i)
            l++;
        while (data[r] < i)
            r--;
        sum += (r - l + 1);
    }
    for (int i = 0; i < x; ++i)
        sum -= data[i];
    cout << sum;
}
